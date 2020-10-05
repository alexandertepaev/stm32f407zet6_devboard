# STM32F407ZET6 development board

This repository is used for documenting my first experience with the STM32 MPU family. I use [this](https://www.aliexpress.com/item/32901691948.html) STM32f406zet6 development board which I bought on AliExpress for around 18$.
Main features:
 - ARM Cortex M4
 - 1.8V - 3.6V operating voltage
 - 512kB Flash
 - 128kB SRAM + 68 kB CCM (core coupled memory) SRAM
 - Up to 168 MHz frequency
 - 8MHz system crystal
 - 32.768KHz RTC crystal
 - JTAG/SWD interface
 - 3x ADC (12-bit / 16-channel), 2x DAC (12-bit)
 -  3x SPI, 3x USART, 2x UART, 2x I2S, 3x I2C
 - 1x FSMC, 1x SDIO, 2x CAN
 - Micro SD slot
 - Reset button, Wakeup button, 2x user buttons
 - 2x user LEDs
 - ... and many more

## Installing the toolchain for Linux
### Compiler, Linker, etc. 

Download and unpack GNU Arm Embedded Toolchain from the ARM Developer [page](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). After unpacking it, modify your $PATH variable by appending the following line to your *~/.bashrc* file. GNU_ARM_EMBEDDED_ROOT is the directory into which you extracted the downloaded archive.

```
export PATH=$PATH:[GNU_ARM_EMBEDDED_ROOT]/bin
```
### DFU flasher

Binary files can be flashed onto the STM32F407ZET6 using the [USB DFU interface](https://www.st.com/resource/en/application_note/cd00264379-usb-dfu-protocol-used-in-the-stm32-bootloader-stmicroelectronics.pdf) and the *dfu-util* command-line tool, which can be installed by executing the following command.

```
sudo apt-get install dfu-util
```


### ST-Link/V2 flasher 

STM32F407ZET6 has a Serial Wire Debugging (SWD) interface, which can also be used to program the MPU using ST-LINK/V2 or a clone (approx. 2-4$ on Aliexpress). ST-Link/V2 is a in-circuit debugger and programmer (more information can be found [here](https://www.st.com/en/development-tools/st-link-v2.html) and [here](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf)) and can be used for symbolic debugging and [semihosting](https://www.keil.com/support/man/docs/armcc/armcc_pge1358787046598.htm). 
In order to use it, we have to install the ST-Link utilities by [stlink-org](https://github.com/stlink-org). 

Get the source code and build it by running: 
```
git clone https://github.com/stlink-org/stlink.git 
cd stlink
cmake .
make
```
Now, the binaries into the */usr/local/bin*
```
cd bin
sudo cp st-* /usr/local/bin
```
Finally, copy the udev rules and restart the udev service
```
sudo cp stlink/config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
sudo /etc/init.d/udev restart
```

Connect the ST-Link/V2 to the USB Port of your PC and run in order to ensure that it is working
```
st-info --probe
```

## Flashing .bin files

Minimal template with Makefile can be found in the */minimal_template* directory of this repo. Run 'make' in order to generate .bin file.

### Flashing via DFU
In order to flash the board using *dfu-utils*, we have to put it into the DFU mode. Disconnect your board from USB and connect PB11 to GND using the provided jumper or a wire. Reconnect your board via Mini USB and execute 
```
dfu-util -a 0 -s 0x08000000 -D main.elf
```
Now, disconnect the board, connect PB12 to 3.3V and reconnect the board back. LED0 and LED1 should blink.



### Flashing via ST-Link/V2
Connect your ST-Link/V2 debugger to your board as shown in the table below.

| Board I/O pins | ST-Link v2 |
| --- | --- |
| PA13 | SWDIO |
| PA14 | SWCLK |
| GND | GND |
| 3.3V | 3.3V |

Connect your board to the USB Port of your PC and execute

```
st-flash write main.elf 0x08000000
```

LED0 and LED1 should blink.
