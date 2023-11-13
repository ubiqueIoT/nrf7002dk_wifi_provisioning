#include "utils.h"

void byte_to_hex(char *ptr, uint8_t byte, char base)
{
    int i, val;

    for (i = 0, val = (byte & 0xf0) >> 4; i < 2; i++, val = byte & 0x0f)
    {
        if (val < 10)
        {
            *ptr++ = (char)(val + '0');
        }
        else
        {
            *ptr++ = (char)(val - 10 + base);
        }
    }
}
