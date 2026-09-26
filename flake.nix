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
        # numpy: renders collision maps in tools/collision/dump_collision.py.
        # toml: decomp-permuter's settings/weights files below.
        pythonEnv = pkgs.python3.withPackages (ps: [ ps.capstone ps.numpy ps.pillow ps.toml ]);

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
        # pythonEnv on PATH.
        decompPermuter = pkgs.stdenv.mkDerivation {
          pname = "decomp-permuter";
          version = "unstable-2024-01-01";
          src = pkgs.fetchFromGitHub {
            owner = "simonlindholm";
            repo = "decomp-permuter";
            rev = "fb516c435c6f362fbced66e171545324306b607b";
            hash = "sha256-xD7/9vizoALBpQR0l8ZVq8pVOOja1tq1+F1LhQgL45k=";
          };
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

        # The compiler the ROM was built with (docs/compiler.md). agbcc_arm
        # isn't built -- it doesn't configure on a modern host.
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
            make -C libgcc -j$NIX_BUILD_CORES
            make -C libc -j$NIX_BUILD_CORES
            runHook postBuild
          '';
          # Layout follows agbcc's install.sh.
          installPhase = ''
            runHook preInstall
            mkdir -p $out/bin $out/lib
            cp agbcc old_agbcc $out/bin/
            cp libgcc/libgcc.a libc/libc.a $out/lib/
            cp -R libc/include $out/include
            cp ginclude/* $out/include/
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
            decompPermuter
          ];
        };
      });
}
