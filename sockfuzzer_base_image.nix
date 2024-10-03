with import <nixpkgs> {};

let
    basePackages = [
        glibc
        stdenv.cc.cc.lib
        libunwind
        xz.out
        elfutils.out
        openssl.out
        # llvm-symbolizer
        clang_18
        llvmPackages_18.stdenv
        lld_18
        # For computing pod index
        gawk
        python3
    ];
    # TODO(nedwill): consider disabling these for production images
    debugPackages = [
        coreutils
        bashInteractive
        binutils
        gnugrep
        # lddtree
        pax-utils
        gdb
    ];
    dockerImage = dockerTools.buildLayeredImage {
    name = "fuzzer-base-image";
    created = "now";
    contents = basePackages ++ debugPackages;
    };
in runCommand "sockfuzzer-base-image" { } ''
  mkdir -p $out/bin
  gzip -dc ${dockerImage} > $out/image.tar
''
