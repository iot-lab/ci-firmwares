# name of your application
APPLICATION = autotest

# If no BOARD is found in the environment, use this default:
BOARD ?= samr21-xpro

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../riot-upstream

FEATURES_REQUIRED += periph_uart
FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_cpuid
USEMODULE += shell xtimer

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP
CFLAGS += -DSHELL_NO_PROMPT -DSHELL_NO_ECHO

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
