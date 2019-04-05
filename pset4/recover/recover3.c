//recovers a jpeg file

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //declare array for filenames
    char filename[8];
    //int to keep track of file number
    int filecounter = 0;

    //ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Please insert .raw File\n");
        return 1;
    }

    //open .raw file
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    //declare buffer array
    typedef uint8_t BYTE;
    BYTE buffer[512];

    FILE *jpeg = NULL;

    while ((fread(buffer, sizeof(buffer), 1, raw_file)) == 1)   //iterate over raw_file until end of file
    {

        //check beginning of a JPEG File
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            sprintf(filename, "%03d.jpeg", filecounter);

            jpeg = fopen(filename, "w");
            filecounter++;
        }

        if (jpeg != NULL)
        {
            fwrite(buffer, 512, 1, jpeg);
        }
    }

    fclose(raw_file);
    fclose(jpeg);
    return 0;
}