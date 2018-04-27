
Debian
====================
This directory contains files used to package keycod/keyco-qt
for Debian-based Linux systems. If you compile keycod/keyco-qt yourself, there are some useful files here.

## keyco: URI support ##


keyco-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install keyco-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your keycoqt binary to `/usr/bin`
and the `../../share/pixmaps/keyco128.png` to `/usr/share/pixmaps`

keyco-qt.protocol (KDE)

