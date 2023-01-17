#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define EEPROM_SIZE (1024 * 256)  // EEPROM is 256kb, 1kb = 1024 bytes
#define DEFAULT_NOP_SIZE 128

int main(int argc, char *argv[]) {
    int instruction_count = DEFAULT_NOP_SIZE;

    if(argc <= 1) {
        printf("Warning: Defaulting to 128 NOP instructions.\n");
        printf("Use './nop [n]' to specify NOP instructions\n");
    } else {
        int count = atoi(argv[1]);

        if(count <= 0 || count > EEPROM_SIZE) {
            printf("Warning: Count for instructions is invalid. Defaulting to %d\n",
                    DEFAULT_NOP_SIZE);
        } else {
            instruction_count = count;
        }
    }

    printf("Generating binary with %d NOP instructions\n", instruction_count);
    
    FILE* outfile = fopen("./nop.bin", "wb");
    uint8_t nop_instruction = 0x4E71;


}
