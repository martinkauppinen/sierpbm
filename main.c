#include <stdio.h>
#include <stdlib.h>

/* simple power function for image size */
unsigned int ipow(unsigned int base, unsigned int exp)
{
    unsigned int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Incorrect number of arguments.\n");
        printf("Provide one (1) argument (the number of iterations).\n");
        exit(0);
    }

    const unsigned int iterations = atoi(argv[1]);
    const unsigned int width = ipow(2, iterations);
    const unsigned int height = width;
    unsigned int i, j;
    FILE *f = fopen("test.pbm", "wb");
    (void) fprintf(f, "P4\n%d %d\n", width, height);
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            static unsigned char pixels;
            if (i % 8 == 0) // start of new byte
                pixels = 0x00;
            pixels |= (i & j) ? 0 : (0x01 << (7 - (i & 7)));
            if (i % 8 == 7) // end of byte, write it to file
                (void) fwrite(&pixels, 1, 1, f);
        }
    }
    (void) fclose(f);
    return 0;
}
