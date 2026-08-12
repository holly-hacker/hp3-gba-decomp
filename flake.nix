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

        pythonEnv = pkgs.python3.withPackages (ps: [ ps.capstone ]);

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
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = [
            pkgs.gcc-arm-embedded
            pythonEnv
            pkgs.just
            pkgs.mgba
            gbadisasm
          ];
        };
      });
}
