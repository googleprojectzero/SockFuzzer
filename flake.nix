{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system: let
    ccWrapper = (self: super: {
      cc-wrapper = 
        import (builtins.fetchTarball {
          url = "https://github.com/NixOS/nixpkgs/archive/879d59508d54c7fde5c61ab41eefaf5f4b18472d.tar.gz";
          sha256 = "RTcsZoO5C7V42Rp2ZXNGQhjt8CS4OSB3JOlBfVb4PWE=";
        }) {
          inherit (super) stdenv gccUnwrapped clangUnwrapped;
          lib = super.lib;
        };
    });
    pkgs = import nixpkgs {
      inherit system;
      overlays = [ ccWrapper ];
    };
  in {
    devShells.default = pkgs.mkShellNoCC {
      name = "rules_nixpkgs_shell";
      packages = with pkgs; [
        bazel
        cacert
        nix
        git
        nodejs
        kubectl
        go
        llvmPackages_18.libstdcxxClang
        stdenv.cc.cc.lib
        coreutils
        gdb
        rr
      ];
      shellHook = ''
        # Enable history substring search
        bind '"\e[A": history-search-backward'
        bind '"\e[B": history-search-forward'
        bind '"\eOA": history-search-backward'
        bind '"\eOB": history-search-forward'

        alias reset='tput reset'
        # TODO(nedwill): is there a better way to do this?
        export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [
          pkgs.stdenv.cc.cc
        ]}
        export ASAN_SYMBOLIZER_PATH=${pkgs.llvmPackages_18.libllvm}/bin/llvm-symbolizer
      '';
    };
  });
}