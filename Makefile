# Define all target architectures
#
# For each target define:
#
#  * PREFIX_$(target) variable with the firmware name prefix
#


ARCHIS += iotlab-m3
PREFIX_iotlab-m3 = m3

ARCHIS += iotlab-a8-m3
PREFIX_iotlab-a8-m3 = a8

ARCHIS += fox
PREFIX_fox = fox

ARCHIS += samr21-xpro
PREFIX_samr21-xpro = samr21

ARCHIS += arduino-mega2560
PREFIX_arduino-mega2560 = mega


include Makefile.in
