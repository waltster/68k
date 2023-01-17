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
    printf("dec2hex <dec>\n");
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
      if(str[i] < '0' || str[i] > '9') {
        printf("Invalid character: %c\n", str[i]);
        return false;
      }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if(argc <= 1) {
      print_help();
      return 0;
    }

    char *decimal_input = argv[1];
    char *end = NULL;
    int base = 2;

    if(!check_string(decimal_input)) {
        printf("Error: Input string must be only numerals\n");
        return 0;
    }

    int result = strtol(decimal_input, &end, 10);

    printf("Decimal to Hex:     0x%X\n", result);
    return 0;
}
