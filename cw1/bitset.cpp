#include <stdio.h>
#include <limits.h>

void print_bits(unsigned short value) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

int main() {
    unsigned short short1 = 4;
    printf("bitset1: ");
    print_bits(short1);

    unsigned short short2 = short1 << 1;
    printf("bitset2: ");
    print_bits(short2);

    unsigned short short3 = short1 << 2;
    printf("bitset3: ");
    print_bits(short3);

    return 0;
}