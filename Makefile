
SRC+=$(wildcard ./src/*.c)
SRC+=$(wildcard ./src/*.cpp)

OBJ+=$(patsubst %,%.o,$(SRC))

ELF_TERGET+=$(patsubst %,%.elf,$(wildcard ./dev/*.c))
ELF_TERGET+=$(patsubst %,%.elf,$(wildcard ./dev/*.cpp))

HEX_TERGET+=$(patsubst %.elf,%.hex,$(ELF_TERGET))

# -L/mnt/c/SysGCC/msp430/msp430-elf/lib/
FLAGS+= -mmcu=msp430f5529 -Os -I./src -fpermissive

test:$(HEX_TERGET) $(OBJ)

%.hex: %.elf
	msp430-objcopy -O ihex $< $@

%.elf:%.o $(OBJ)
	msp430-gcc $(FLAGS) $^ -lm -o $@ 

%.c.o:%.c
	msp430-gcc $(FLAGS) -o $@ -c $<

%.cpp.o:%.cpp
	msp430-g++ $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(ELF_TERGET) $(HEX_TERGET) $(OBJ)
