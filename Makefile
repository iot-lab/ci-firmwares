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

ARCHIS += samr30-xpro
PREFIX_samr30-xpro = samr30

ARCHIS += arduino-mega2560
PREFIX_arduino-mega2560 = mega

ARCHIS += arduino-zero
PREFIX_arduino-zero = arduino-zero

ARCHIS += b-l072z-lrwan1
PREFIX_b-l072z-lrwan1 = st-lrwan1

ARCHIS += microbit
PREFIX_microbit = microbit

ARCHIS += b-l475e-iot01a
PREFIX_b-l475e-iot01a = st-iotnode

ARCHIS += nrf52dk
PREFIX_nrf52dk = nrf52dk

ARCHIS += nrf52840dk
PREFIX_nrf52840dk = nrf52840dk

include Makefile.in
