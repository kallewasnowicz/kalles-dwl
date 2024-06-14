# DWL

## Patches

### Commands
git merge guidocella/alwayscenter
git merge sevz/autostart
git merge wochap/v0.5/centeredmaster
git merge wochap/v0.5/cursortheme
git merge notchoc/ipc
git merge palanix/monfig
git merge wochap/v0.5/movecenter
git merge wochap/v0.5/pertag
git merge wochap/v0.5/regexrules
git merge guidocella/unclutter
git merge korei999/xwayland-handle-minimize


### Alwayscenter
Automatically center floating windows.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/alwayscenter

https://codeberg.org/guidocella/dwl/src/branch/alwayscenter


### Autostart
Allow dwl to execute commands from autostart array in your config.h file. And when you exit dwl all processes from autostart array will be killed.

Note: Commands from array are executed using execvp(). So if you need to execute shell command you need to prefix it with "sh", "-c" (change sh to any shell you like).

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/autostart

https://codeberg.org/sevz/dwl/src/branch/autostart


### Centered Master
This is a port of centeredmaster patch for dwm: https://dwm.suckless.org/patches/centeredmaster

centeredmaster centers the nmaster area on screen, using mfact * monitor width & height, with the stacked windows distributed to the left and right. It can be selected with Alt+c.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/centeredmaster

https://codeberg.org/wochap/dwl/src/branch/v0.5/centeredmaster


### Cursortheme
Adds ability to change cursor's theme and size.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/cursortheme

https://codeberg.org/wochap/dwl/src/branch/v0.5/cursortheme


### IPC
Largely based on raphi's somebar, this patch provides an ipc for wayland clients to get and set dwl state. The ipc is intended for status bars, but can also be scripted with tools like dwlmsg.

Status information to stdout is currently disabled as dwl tends to freeze. For now, dwlmsg -w should act as a drop-in replacement.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/ipc

https://codeberg.org/notchoc/dwl/src/branch/ipc


### Monfig
Allows more monitor configuration in config.h

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/monfig

https://codeberg.org/Palanix/dwl/src/branch/monfig


### Movecenter
This patch provides a keybinding to center the focused floating window.

Press MODKEY + x to center the focused floating window.

It does NOT center windows that are not floating.

The variable center_relative_to_monitor allows the user to choose whether to center relative to the monitor or relative to the window area.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/movecenter

https://codeberg.org/wochap/dwl/src/branch/v0.5/movecenter


### Perinputconfig
Replace the singular keyboard and pointer input configuration with an array allowing to set different variables matching by name.

Tip to find the names: Grep for device_name and add a line after it to print to stdout. Then run EX: dwl > /tmp/print_device_names.log, exit dwl, and should see the names.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/perinputconfig

https://codeberg.org/nullsystem/dwl/src/branch/main_perinputconfig


### Pertag
Makes layout, mwfact and nmaster individual for every tag.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/pertag

https://codeberg.org/wochap/dwl/src/branch/v0.5/pertag


### Regexrules
Allows the use of regular expressions for window rules "app_id" and "title"

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/regexrules

https://codeberg.org/wochap/dwl/src/branch/v0.5/regexrules


### Unclutter
Hide the mouse cursor if it isn't being used for a certain period of time.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/unclutter

https://codeberg.org/guidocella/dwl/src/branch/unclutter


### Xwayland-Handle-Minimize
Some windows (wine) games go black screen after losing focus and never recover https://github.com/swaywm/sway/issues/4324. This patch fixes this by handling minimize requests that some xwayland clients do.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/xwayland-handle-minimize

https://codeberg.org/korei999/dwl/src/branch/xwayland-handle-minimize


### Zoomswap
This patch swaps the current window (C) with the previous master (P) when zooming.

https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/zoomswap

https://codeberg.org/Palanix/dwl/src/branch/zoomswap