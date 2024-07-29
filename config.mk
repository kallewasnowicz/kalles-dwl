_VERSION = 0.8-dev
VERSION  = `git describe --tags --dirty 2>/dev/null || echo $(_VERSION)`

PKG_CONFIG = pkg-config

# paths
PREFIX = ~/.local
MANDIR = $(PREFIX)/share/man
DATADIR = $(PREFIX)/share

XWAYLAND =
XLIBS =
# Uncomment to build XWayland support
XWAYLAND = -DXWAYLAND
XLIBS = xcb xcb-icccm

# Custom Flags
CFLAGS = -march=native -O2 -pipe -flto -fpass-plugin=LLVMPolly.so -fplugin-arg-polly-polly -fplugin-arg-polly-polly-vectorizer=stripmine
LDFLAGS = -Wl,-O1 -Wl,--as-needed -Wl,-z,pack-relative-relocs -Wl,--as-needed -fuse-ld=mold -march=native -O2 -pipe -flto -fpass-plugin=LLVMPolly.so -fplugin-arg-polly-polly -fplugin-arg-polly-polly-vectorizer=stripmine
CC=/usr/lib/llvm/18/bin/clang
