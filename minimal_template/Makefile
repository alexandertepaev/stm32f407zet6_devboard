LINKER_SCRIPT = linker_script.ld
C_FLAGS  = -c -O0 -mcpu=cortex-m4
 
all: main.bin
 
%.o: %.c
	arm-none-eabi-gcc $(C_FLAGS) -o $@ $<

%.elf: %.o
	arm-none-eabi-ld -T$(LINKER_SCRIPT) -o $@ $<

%.hex: %.elf
	arm-none-eabi-objcopy -O ihex $< $@

%.bin: %.elf
	arm-none-eabi-objcopy -O binary -S $< $@

clean:
	rm -rf *.o *.elf *.hex *.bin

flash_dfu: main.bin
	dfu-util -a 0 -s 0x08000000 -D $<

flash_stlink: main.bin
	st-flash write main.bin 0x08000000

	