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

ARCHIS += samr21-xpro
PREFIX_samr21-xpro = samr21

ARCHIS += samr30-xpro
PREFIX_samr30-xpro = samr30

ARCHIS += samr34-xpro
PREFIX_samr34-xpro = samr34

ARCHIS += arduino-mega2560
PREFIX_arduino-mega2560 = mega

ARCHIS += arduino-zero
PREFIX_arduino-zero = arduino-zero

ARCHIS += b-l072z-lrwan1
PREFIX_b-l072z-lrwan1 = st-lrwan1

ARCHIS += microbit
PREFIX_microbit = microbit

ARCHIS += microbit-v2
PREFIX_microbit-v2 = microbit2

ARCHIS += b-l475e-iot01a
PREFIX_b-l475e-iot01a = st-iotnode

ARCHIS += nrf51dk
PREFIX_nrf51dk = nrf51dk

ARCHIS += nrf52dk
PREFIX_nrf52dk = nrf52dk

ARCHIS += nrf52840dk
PREFIX_nrf52840dk = nrf52840dk

ARCHIS += nrf52840-mdk
PREFIX_nrf52840-mdk = nrf52840mdk

ARCHIS += nrf52832-mdk
PREFIX_nrf52832-mdk = nrf52832mdk

ARCHIS += frdm-kw41z
PREFIX_frdm-kw41z = frdm-kw41z

ARCHIS += pba-d-01-kw2x
PREFIX_pba-d-01-kw2x = phynode

ARCHIS += firefly
PREFIX_firefly = firefly

ARCHIS += samd21-xpro
PREFIX_samd21-xpro = samd21

ARCHIS += nucleo-f070rb
PREFIX_nucleo-f070rb = nucleo-f070rb

ARCHIS += dwm1001
PREFIX_dwm1001 = dwm1001

ARCHIS += p-nucleo-wb55
PREFIX_p-nucleo-wb55 = nucleo-wb55

ARCHIS += nucleo-wl55jc
PREFIX_nucleo-wl55jc = nucleo-wl55jc

include Makefile.in
