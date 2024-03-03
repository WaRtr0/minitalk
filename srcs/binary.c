# include "minitalk.h"

unsigned char *dec_to_binary(unsigned int dec, unsigned char bits)
{
    unsigned char *binary = malloc(sizeof(unsigned char) * bits);
    if (!binary)
        return ((void *)0);
    int index;

    index = 0;
    while (index < bits)
    { 
        if (dec & 1 << ((bits - 1) - index))
            binary[index] = 1;
        else
            binary[index] = 0;
        ++index;
    }
    return (binary);
}

unsigned int    binary_to_dec(unsigned char *binary, unsigned char bits)
{
    unsigned int res;
    int index;

    res = 0;
    index = 0;
    while (index < bits)
    {
        res |= binary[index] << ((bits - 1) - index);
        ++index;
    }
    return (res);
}