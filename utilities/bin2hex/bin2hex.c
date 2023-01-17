#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

size_t strlen_s(const char *s, size_t n) {
    size_t i;

    for (i = 0; i < n && s[i] != '\0'; i++) {
      continue;
    }

    return i;
}

void print_help() {
    printf("hex2bin <hex>\n");
    return;
}

bool check_string(char *str) {
    // Maximum size is 32 bytes.
    size_t length = strlen_s(str, 32);

    if(length == 0 || length > 32) {
      printf("Length was invalid!\n");
      return false;
    }

    for(int i = 0; i < length; i++) {
      if(str[i] != '0' && str[i] != '1') {
        printf("Invalid character: %c\n", str[i]);
        return false;
      }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if(argc <= 2) {
      print_help();
      return 0;
    }

    char *binary_input = argv[1];
    char *end = NULL;
    int base = 2;

    if(!check_string(binary_input)) {
        printf("Error: Input string must be only 0s or 1s\n");
        return 0;
    }

    int result = strtol(binary_input, &end, base);

    printf("Binary to Decimal: %d\n", result);
    printf("Binary to Hex:     0x%X\n", result);
    return 0;
}
