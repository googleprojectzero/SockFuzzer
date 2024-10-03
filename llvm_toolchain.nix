with import <nixpkgs> {
  config = {};
  overlays = [];
}; let
  pkgs = import <nixpkgs> {};
  llvm = pkgs.llvmPackages_18;
  lld = pkgs.lld;
  mold = pkgs.mold;
  libcxx = llvm.libcxx;
  compiler-rt = llvm.compiler-rt;
  stdenv = llvm.stdenv;

  clang = llvm.libstdcxxClang;
in
  pkgs.buildEnv {
    name = "llvm-cc-wrapper";
    paths = [
      clang
      lld
      mold
    ];
    pathsToLink = ["/bin"]; # Consider reviewing this
    passthru = {
      isClang = true;
      inherit (stdenv.cc) targetPrefix;
      # Review and remove potentially unnecessary attributes
      inherit (clang) libc nativePlugins nativeLibc nativeTools;
      inherit (clang) gcc lib version;
    };
  }
