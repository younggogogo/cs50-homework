#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == 0)
    {
        printf("FLIE OPEN ERROR");
        return 2;
    }

    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    if (buffer == 0)
    {
        printf("LACK OF MEMORY");
        return 3;
    }

    int num = 0;
    char filename[8];
    FILE *output = NULL;
    BYTE bytesize = 1;
    while (fread(buffer, bytesize, 512, input) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 &&
            buffer[3] <= 0xef)
        {
            sprintf(filename, "%03d.jpg", num);
            num++;
            if (output != NULL)
            {
                if (fclose(output) != 0)
                {
                    return 6;
                }
            }
            output = fopen(filename, "w");
            if (output == 0)
            {
                return 5;
            }
        }
        if (output != NULL)
        {
            fwrite(buffer, bytesize, 512, output);
        }
    }

    if (fclose(input) != 0)
    {
        return 4;
    }
    if (output != NULL)
    {
        if (fclose(output) != 0)
        {
            return 5;
        }
    }
    free(buffer);
}
