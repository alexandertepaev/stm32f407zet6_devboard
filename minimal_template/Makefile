SRC    = main
TARGET = $(SRC)

#################################

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CP = arm-none-eabi-objcopy

#################################

CC_FLAGS  = -c -fno-common -O0 -g -mcpu=cortex-m4 # -fno-common - place uninit global variables in the BSS section 
						  # -O0 - no optimizations
						  # -g - default debug information
LD_SCRIPT = linker_script.ld
LD_FLAGS  = -T$(LD_SCRIPT)
CP_FLAGS  = -O binary # create .bin file

#################################

PROG_MEM_START 	= 0x08000000 			# Start of program memory
DFU_FLAGS 	= -a 0 -s $(PROG_MEM_START) -D  # altsetting 0 - copy into RAM, -s - dfuse-address-start, -D write file
 
					
all: $(TARGET).elf $(TARGET).bin
 
%.o: %.c
	arm-none-eabi-gcc $(CC_FLAGS) -o $@ $<

%.elf: %.o
	arm-none-eabi-ld $(LD_FLAGS) -o $@ $<

%.bin: %.elf
	arm-none-eabi-objcopy $(CP_FLAGS) -S $< $@

clean:
	rm -rf *.o *.elf *.bin

flash_dfu: $(TARGET).bin
	dfu-util $(DFU_FLAGS) $<

flash_stlink: $(TARGET).bin
	st-flash write $< $(PROG_MEM_START)

	