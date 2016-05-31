## Iotlab Continuous Integration System Firmwares

This repository contains the instructions and firmware source codes to be used
with the continuous integration system of Iotlab.

The firmwares are based on [RIOT](https://github.com/RIOT-OS/RIOT) operating
system. Iotlab CI uses 2 different firmwares:
* **idle** does basically nothing and is only used to verify that the board can
  be flashed by the iotlab management tools;

* **autotest** verify basic functionalities provided by the boards:
  * **echo**: replies the exact serial input
  * **get_time**: replies the current time provided by the internal board
    timer. The format is `ACK get_time <time> ticks_32khz`. <time> is computed
    by the firmware.
  * **leds_on**: turn on on-board LEDs using input flag (e.g 7 <=> 111 in binary,
    will turn on all 3 LEDs, etc)
  * **leds_off**: turn off on-board LEDs using input flag (e.g 7 <=> 111 in
    binary, will turn off all 3 LEDs, etc)

To be continued...


### Usage

1. Build the firmwares
<pre>
$ cd ci-firmwares
$ for firmware in idle autotest
do
cd firmwares/$firmware
for board in iotlab-m3 samr21-xpro arduino-mega2560 fox
do
make BOARD=$board
done
cd ../..
done
</pre>
2. Copy the firmware in the **iotlab-gateway** repositoty. The built firmwares are
   located in **firmwares/autotest/bin/samr21-xpro/autotest.elf** for example.
   The destination folder is **iotlab-gateway/gateway-code/static**.



