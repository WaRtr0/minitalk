#include "minitalk.h"

int main()
{

    unsigned char *test = dec_to_binary(77, 8);
    int i = 0;
    while (i < 8)
    {
        printf("%d", test[i]);
        i++;
    }
    printf("\n M == %c \n",binary_to_dec(test, 8));
    return (0);
}
