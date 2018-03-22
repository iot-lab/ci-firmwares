# Prerequisite
all: init_submodules

.PHONY: init_submodules
init_submodules:
	git submodule update --init --recursive

install-arduino-ide:
	if [ ! -f arduino-1.8.5-linux64.tar.xz ]; then\
		wget http://downloads.arduino.cc/arduino-1.8.5-linux64.tar.xz;\
		fi; \
	if [ ! -d arduino-1.8.5 ]; then tar xf arduino-1.8.5-linux64.tar.xz; fi;

# Meta targets
all: build

build: build_zigduino_autotest build_zigduino_idle

clean: clean_zigduino_autotest clean_zigduino_idle
	rm -f *_autotest.elf
	rm -f *_idle.elf

# Build Zigduino
build_zigduino_autotest:
	make -C firmwares/zigduino_autotest
	cp firmwares/zigduino_autotest/build-zigduino_r2/zigduino_autotest.elf .

build_zigduino_idle:
	make -C firmwares/zigduino_idle
	cp firmwares/zigduino_idle/build-zigduino_r2/zigduino_idle.elf .

# Clean Zigduino
clean_zigduino_autotest:
	make -C firmwares/zigduino_autotest clean

clean_zigduino_idle:
	make -C firmwares/zigduino_idle clean
