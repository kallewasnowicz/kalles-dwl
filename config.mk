_VERSION = 0.5
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
CFLAGS = -march=native -Ofast -pipe -flto -fpass-plugin=LLVMPolly.so -fplugin-arg-polly-polly -fplugin-arg-polly-polly-vectorizer=stripmine
