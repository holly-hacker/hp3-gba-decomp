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
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = [
            pkgs.gcc-arm-embedded
            pkgs.python3
            pkgs.python3Packages.pip
            pkgs.just
            pkgs.mgba
          ];
        };
      });
}
