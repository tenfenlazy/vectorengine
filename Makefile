ifeq ($(shell uname),Linux)

# Linux makefile
include Makefile.linux

else

ifeq ($(shell uname),Darwin)

# macOS makefile
include Makefile.macos

else

include Makefile.unix

endif

endif
