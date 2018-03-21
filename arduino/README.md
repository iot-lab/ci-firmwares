## Arduino IoT-LAB Continuous Integration System Firmwares

The firmwares are based on [Arduino](https://www.arduino.cc) operating
system. IoT-LAB CI uses 2 different firmwares:
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

```
$ make all
git submodule update --init --recursive
make -C firmwares/zigduino_autotest
...

$ ls *.elf
zigduino_autotest.elf  zigduino_idle.elf
```

2. Copy the firmware in the **iotlab-gateway** repositoty.
   The destination folder is **iotlab-gateway/gateway-code/static**.



