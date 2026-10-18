{
  description = "Harry Potter and the Prisoner of Azkaban (GBA) decompilation";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };

        # pillow: writes the extracted PNGs in tools/items/extract_item_icons.py.
        # numpy: collision maps (tools/collision) and GammaLz match search (tools/graphics).
        # pyyaml: the graphics group descriptions under graphics/ (tools/graphics).
        # toml: decomp-permuter's settings/weights files below.
        pythonEnv = pkgs.python3.withPackages (ps: [ ps.capstone ps.numpy ps.pillow ps.pyyaml ps.toml ]);

        # pret's matching GBA disassembler. Pinned to the last upstream
        # commit (inactive since 2020-01). Two heap bugs in disasm.c crash
        # it on real ROMs under modern glibc; patched here.
        gbadisasm = pkgs.stdenv.mkDerivation {
          pname = "gbadisasm";
          version = "unstable-2020-01-07";
          src = pkgs.fetchFromGitHub {
            owner = "camthesaxman";
            repo = "gbadisasm";
            rev = "e35982bd105fd8b9bb497d955900f8375cdc9e60";
            hash = "sha256-XcYvUqDyytySjav2fSMV4t3GU1pjDBlYQzhEPlvsjJc=";
          };
          nativeBuildInputs = [ pkgs.gnutar ];
          patches = [
            ./patches/gbadisasm/0001-fix-double-free-thumb-fallback.patch
            ./patches/gbadisasm/0002-fix-realloc-stale-pointer.patch
            ./patches/gbadisasm/0003-fix-tail-truncation.patch
          ];
          installPhase = ''
            mkdir -p $out/bin
            cp gbadisasm $out/bin/
          '';
        };

        # Krawall module/sample/instrument data extraction/export tool.
        # Used only for casual `.xm` listening exports
        # (`just extract-music-xm`) and manual one-off `-m`/`-x` runs --
        # not for discovery (see tools/krawall/extract_krawall.py). A
        # heap-corrupting out-of-bounds write in its XM writer is patched
        # here -- see patches/unkrawerter/README.md.
        unkrawerter = pkgs.stdenv.mkDerivation {
          pname = "unkrawerter";
          version = "4.0";
          src = pkgs.fetchFromGitHub {
            owner = "MCJack123";
            repo = "UnkrawerterGBA";
            rev = "999e310fcc62a0d21e783549051a06a2a3fbd848";
            hash = "sha256-1ohPQZ0FHxfVCKA/D6tFwbjPlzS64tJ8btulWvLNfG4=";
          };
          patches = [
            ./patches/unkrawerter/0001-fix-oob-channel-memory-heap-corruption.patch
          ];
          buildPhase = ''
            g++ -std=c++11 -O2 -o unkrawerter unkrawerter.cpp
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp unkrawerter $out/bin/
          '';
        };

        # Randomized/exhaustive AST-level rewriter that scores candidate C
        # against a target .o via objdump diffing -- used to close small
        # (few-instruction) gaps in an otherwise-matching function that
        # resist hand fishing. Pure Python (pycparser is vendored in-repo
        # as perm_pycparser), so this just wraps permuter.py/import.py with
        # pythonEnv on PATH. Patched to accept ARM-mode objects' R_ARM_V4BX.
        decompPermuter = pkgs.stdenv.mkDerivation {
          pname = "decomp-permuter";
          version = "unstable-2024-01-01";
          src = pkgs.fetchFromGitHub {
            owner = "simonlindholm";
            repo = "decomp-permuter";
            rev = "fb516c435c6f362fbced66e171545324306b607b";
            hash = "sha256-xD7/9vizoALBpQR0l8ZVq8pVOOja1tq1+F1LhQgL45k=";
          };
          patches = [
            ./patches/decomp-permuter/0001-ignore-arm-v4bx-relocations.patch
          ];
          nativeBuildInputs = [ pkgs.makeWrapper ];
          dontBuild = true;
          installPhase = ''
            mkdir -p $out/share/decomp-permuter $out/bin
            cp -r . $out/share/decomp-permuter
            makeWrapper ${pythonEnv}/bin/python3 $out/bin/permuter.py \
              --add-flags $out/share/decomp-permuter/permuter.py
            makeWrapper ${pythonEnv}/bin/python3 $out/bin/import.py \
              --add-flags $out/share/decomp-permuter/import.py
          '';
        };

        # The compiler the ROM was built with (docs/compiler.md), plus
        # agbcc_arm for ARM-mode C.
        agbcc = pkgs.stdenv.mkDerivation {
          pname = "agbcc";
          version = "unstable-2026-01-20";
          src = pkgs.fetchFromGitHub {
            owner = "pret";
            repo = "agbcc";
            rev = "da598c1d918402c42c0c0d7128ba14567f3175e9";
            hash = "sha256-/7SM2bRuz44WQiomMYqkf4pXge0ypSNViVu26FnEi2Q=";
          };
          nativeBuildInputs = [ pkgs.gcc-arm-embedded ];
          # gcc/Makefile races on its generated headers, hence -j1.
          buildPhase = ''
            runHook preBuild
            make -C gcc old -j1
            mv gcc/old_agbcc .
            make -C gcc clean
            make -C gcc -j1
            mv gcc/agbcc .
            (cd gcc_arm && ./configure --target=arm-elf --host=i386-linux-gnu && make cc1)
            mv gcc_arm/cc1 agbcc_arm
            make -C libgcc -j$NIX_BUILD_CORES
            make -C libc -j$NIX_BUILD_CORES
            runHook postBuild
          '';
          # Layout follows agbcc's install.sh.
          installPhase = ''
            runHook preInstall
            mkdir -p $out/bin $out/lib
            cp agbcc old_agbcc agbcc_arm $out/bin/
            cp libgcc/libgcc.a libc/libc.a $out/lib/
            cp -R libc/include $out/include
            cp ginclude/* $out/include/
            runHook postInstall
          '';
        };

        # The compiler Krawall was built with (docs/compiler.md). Only cc1
        # is built, for a 32-bit host, the only kind GCC 3.0 supports.
        gccKrawall = pkgs.pkgsi686Linux.stdenv.mkDerivation {
          pname = "gcc-arm-elf-cc1";
          version = "3.0.2";
          src = pkgs.fetchurl {
            url = "mirror://gnu/gcc/gcc-3.0.2/gcc-core-3.0.2.tar.gz";
            hash = "sha256-xe0UqSf0iaY/W/aL5EVAMr9kkTNFXIKcWzRmTZhqnkU=";
          };
          patches = [
            ./patches/gcc-3.0.2/0001-obstack-no-cast-lvalue.patch
            ./patches/gcc-3.0.2/0002-arm-set-decl-rtl.patch
          ];
          hardeningDisable = [ "all" ];
          env.NIX_CFLAGS_COMPILE = "-std=gnu89 -fcommon -fpermissive -w";
          configurePlatforms = [ ];
          dontDisableStatic = true;
          configureFlags = [
            "--build=i686-pc-linux-gnu"
            "--host=i686-pc-linux-gnu"
            "--target=arm-elf"
            "--enable-languages=c"
            "--disable-nls"
            "--without-headers"
          ];
          # GCC must be configured from a separate build directory.
          preConfigure = ''
            mkdir build && cd build
            configureScript=../configure
          '';
          buildPhase = ''
            runHook preBuild
            make -j$NIX_BUILD_CORES all-libiberty
            make -C gcc -j$NIX_BUILD_CORES cc1
            runHook postBuild
          '';
          installPhase = ''
            runHook preInstall
            install -Dm755 gcc/cc1 $out/bin/arm-elf-cc1-3.0.2
            runHook postInstall
          '';
        };
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = [
            pkgs.gcc-arm-embedded
            pythonEnv
            pkgs.just
            pkgs.mgba
            gbadisasm
            unkrawerter
            agbcc
            gccKrawall
            decompPermuter
          ];
        };
      });
}
