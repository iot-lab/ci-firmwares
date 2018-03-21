# This has to be the absolute path to the Arduino base directory:
ARDUINOBASE = $(CURDIR)/../../../arduino

ARDUINO_DIR = $(ARDUINOBASE)/arduino-1.8.5
BOARDS_TXT = $(ARDUINOBASE)/arduino-zigduino-package/src/zigduino-avr_1.0.0/boards.txt
ARDUINO_VAR_PATH = $(ARDUINOBASE)/arduino-zigduino-package/src/zigduino-avr_1.0.0/variants
ARDUINO_CORE_PATH = $(ARDUINOBASE)/arduino-zigduino-package/src/zigduino-avr_1.0.0/cores/zigduino
BOARD_TAG = zigduino_r2

CPPFLAGS += -$(MCU_FLAG_NAME)=$(MCU) -DF_CPU=$(F_CPU) -DARDUINO=$(ARDUINO_VERSION) $(ARDUINO_ARCH_FLAG) \
        -I$(ARDUINO_CORE_PATH) -I$(ARDUINO_VAR_PATH)/$(VARIANT) \
        $(SYS_INCLUDES) $(PLATFORM_INCLUDES) $(USER_INCLUDES) -w -ffunction-sections \
        -fdata-sections

include ../../Arduino-Makefile/Arduino.mk
