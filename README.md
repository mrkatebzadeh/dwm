# Raha - minimalist window manager fork of dwm, dmenu, and dwmblocks
Raha is a fork of dwm, which is an extremely fast, small, and dynamic window manager for X.


## Requirements
In order to build Raha you need the Xlib header files.


## Installation
Edit `config.mk` to match your local setup (dwm is installed into the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if necessary as root):

```sh
    make clean install
```

## Running Raha
-----------
Add the following line to your .xinitrc to start dwm using startx:

```sh
    exec dwm
```

In order to connect dwm to a specific display, make sure that the DISPLAY environment variable is set correctly, e.g.:

```sh
    DISPLAY=foo.bar:1 exec dwm
```
