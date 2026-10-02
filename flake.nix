{
  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs =
    inputs:
    inputs.flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = (import (inputs.nixpkgs) { inherit system; });
        nativeBuildInputs = [
          pkgs.cmake
          pkgs.clang-tools
          pkgs.pkg-config
        ];

        buildInputs = [
          pkgs.raylib
        ];
      in
      {
        devShell = pkgs.mkShell { inherit nativeBuildInputs buildInputs; };
      }
    );
}
