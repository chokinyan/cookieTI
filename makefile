# ----------------------------
# Makefile Options
# ----------------------------

NAME = COOKIETI
ICON ?= cookie.png
DESCRIPTION = "Cookie Clicker Clone"
COMPRESSED = YES
COMPRESSED_MODE = zx0
HAS_PRINTF = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)