# Scenario Skeleton - make file using gnu make 3.8 under Cygwin

# NB: pc.exe is in the win32 path so no need to define full path to it

# Variables
# You need to define the path to the ISCC compiler, adjust this if you
# have not done a default install or are using a version other than v5
CC="C:/Program Files/Inno Setup 5/ISCC.exe"

# Assumes you are running the make file from a command line in the Installer
# directory.
BUILDDIR=.

.PHONY : all single

# master "build it all" target
all: single

# Executes compiler in verbose mode.
single:
	$(CC) "$(BUILDDIR)/epic_install_maker_complete.iss"

noart:
	$(CC) "$(BUILDDIR)/epic_install_maker_no_art.iss"