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

        # unicorn: CPU emulator, used by tools/decode_type6.py to run the
        # game's own ARM-mode decompressor against real ROM bytes instead of
        # a hand-reimplementation -- see docs/formats/graphics.md.
        pythonEnv = pkgs.python3.withPackages (ps: [ ps.capstone ps.unicorn ]);

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

        # Krawall module/sample/instrument data extraction/export tool. No
        # longer used for discovery by tools/extract_krawall.py (see its
        # docstring), only for casual `.xm` listening exports
        # (`just extract-music-xm`) and manual one-off `-m`/`-x` runs. A
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
          ];
        };
      });
}
