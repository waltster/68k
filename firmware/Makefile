# Toolchain related stuff
PATH_PREFIX=~/opt/cross/bin/
TOOL_PREFIX=$(PATH_PREFIX)m68k-elf-
CC=$(TOOL_PREFIX)gcc
AS=$(TOOL_PREFIX)as
LD=$(TOOL_PREFIX)ld
OBJCOPY=$(TOOL_PREFIX)objcopy
OBJDUMP=$(TOOL_PREFIX)objdump
C_FLAGS=-mcpu=68000 -Isrc -Isrc/include -Wall -O0 -c -lgcc -fno-builtin -nostdlib
AS_FLAGS=-mcpu=68000 -Isrc -Isrc/include
LD_FLAGS=-T link.ld

# Sources/targets
OBJECTS=src/vectors.o src/startup.o #src/post.o src/a.o src/vectors.o
OUTFILE=firmware
ELF_FILE=$(OUTFILE).elf
BIN_FILE=$(OUTFILE).bin

all: rom 

rom: even.rom odd.rom

$(BIN_FILE): $(ELF_FILE)
	$(OBJCOPY) -O binary $< $@

$(ELF_FILE): $(OBJECTS)
	$(LD) -nostdlib -nostartfiles $(LD_FLAGS) -o $@ $(OBJECTS) -Map linker.map

even.rom: $(BIN_FILE)
	echo TODO

odd.rom: $(BIN_FILE)
	echo TODO

disassemble: $(ELF_FILE)
	$(OBJDUMP) -d $<

%.o: %.s
	$(AS) -o $@ $< $(AS_FLAGS)

%.o: %.c
	$(CC) $(C_FLAGS) $< -o $@

clean:
	rm -r even.rom odd.rom $(OBJECTS) $(ELF_FILE) $(BIN_FILE) linker.map
