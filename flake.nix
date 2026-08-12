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

        luvdis = pkgs.python3Packages.buildPythonApplication rec {
          pname = "Luvdis";
          version = "0.8.0";
          format = "pyproject";
          src = pkgs.python3Packages.fetchPypi {
            inherit pname version;
            sha256 = "5df5e7754d4231ce2daf3d2462a1bf8cdc9159537b428abfc524dcc86e0d743d";
          };
          # Luvdis 0.8.0 uses pkg_resources.resource_stream/resource_string to
          # load its bundled data files, but pkg_resources was removed from
          # recent setuptools. Patch both usages to importlib.resources.
          postPatch = ''
            substituteInPlace luvdis/rom.py \
              --replace-fail "import pkg_resources" "import importlib.resources" \
              --replace-fail "DB_F = pkg_resources.resource_stream('luvdis', 'gba-db.pickle')" \
                              "DB_F = importlib.resources.files('luvdis').joinpath('gba-db.pickle').open('rb')"
            substituteInPlace luvdis/analyze.py \
              --replace-fail "import pkg_resources" "import importlib.resources" \
              --replace-fail "MACROS = pkg_resources.resource_string('luvdis', 'functions.inc').decode('utf-8')" \
                              "MACROS = importlib.resources.files('luvdis').joinpath('functions.inc').read_text()"
          '';
          nativeBuildInputs = [ pkgs.python3Packages.setuptools ];
          propagatedBuildInputs = with pkgs.python3Packages; [
            click
            click-default-group
            tqdm
          ];
          doCheck = false;
        };

        pythonEnv = pkgs.python3.withPackages (ps: [ ps.capstone ]);
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = [
            pkgs.gcc-arm-embedded
            pythonEnv
            pkgs.just
            pkgs.mgba
            luvdis
          ];
        };
      });
}
