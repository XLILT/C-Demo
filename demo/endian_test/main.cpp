#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

void hex_dump(FILE *f, uint8_t *data, uint32_t len)
{
    for(int i = 0; i < len; i++)
    {        
        if(0 == i % 16)
        {
            fprintf(f, "\n%04x ", i);
        }

        fprintf(f, "%02x ", *(data + i));
    }

    printf("\n");
}

int main()
{
    int x = 0xF;
    hex_dump(stdout, (uint8_t *)&x, sizeof(x));
    return 0;
}
