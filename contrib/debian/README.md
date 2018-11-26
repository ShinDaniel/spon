
Debian
====================
This directory contains files used to package spond/spon-qt
for Debian-based Linux systems. If you compile spond/spon-qt yourself, there are some useful files here.

## spon: URI support ##


spon-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install spon-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your sponqt binary to `/usr/bin`
and the `../../share/pixmaps/spon128.png` to `/usr/share/pixmaps`

spon-qt.protocol (KDE)

