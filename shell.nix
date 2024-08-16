{ pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
  packages = with pkgs; [
    gnumake
    pkg-config
    wayland
    xwayland
    xorg.libxcb
    xorg.xcbutilwm
    wayland-protocols
    wayland-scanner
    libinput
    wlroots_0_16
    libxkbcommon
    pixman
  ];
}