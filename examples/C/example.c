#include <stdio.h>

typedef const char * string;

string fizzbuzz(int n)
    switch !!(n % 3) | !!(n % 5) << 1
        case 0:
            return "FIZZBUZZ";
        case 1:
            return "FIZZ";
        case 2:
            return "BUZZ";
        default:
            static char buffer[3] = {0};
            snprintf(buffer, sizeof(buffer), "%i", n);
            return buffer;


int main()
    for int i = 0; i < 20; ++i
        printf("[%d] %s\n", i, fizzbuzz(i));
