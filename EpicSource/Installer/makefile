# Scenario Skeleton - make file using gnu make 3.8 under Cygwin

# NB: pc.exe is in the win32 path so no need to define full path to it

# Variables
CC=c:/program/files/istool/istool.exe

# EOCDIR=c:\iwar2
BUILDDIR=.\EpicSource\Installer

.PHONY : all single parts

# master "build it all" target
all: parts single

single:
	$(CC) -compile $(BUILDDIR)\epic_install_maker.iss

parts:
	$(CC) -compile $(BUILDDIR)\epic_install_maker_core.iss
	$(CC) -compile $(BUILDDIR)\epic_install_maker_music.iss
	$(CC) -compile $(BUILDDIR)\epic_install_maker_nebula.iss
	$(CC) -compile $(BUILDDIR)\epic_install_maker_planets.iss
