
Debian
====================
This directory contains files used to package sktd/skt-qt
for Debian-based Linux systems. If you compile sktd/skt-qt yourself, there are some useful files here.

## skt: URI support ##


skt-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install skt-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your skt-qt binary to `/usr/bin`
and the `../../share/pixmaps/skt128.png` to `/usr/share/pixmaps`

skt-qt.protocol (KDE)

