// resizes a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (n > 100 || n < 1)
    {
        fprintf(stderr, "Enter value between 1 and 100\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //declare new outfile variables
    int outfile_biWidth = bi.biWidth *= n;
    int outfile_biHeight = bi.biHeight *= n;

    //define padding
    int infile_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outfile_padding = (4 - (outfile_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int outfile_biSizeImage = ((sizeof(RGBTRIPLE) * outfile_biWidth) + outfile_padding) * abs(outfile_biHeight);
    int outfile_bfSize = outfile_biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    bf.bfSize = outfile_bfSize;
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    bi.biWidth = outfile_biWidth;
    bi.biHeight = outfile_biHeight;
    bi.biSizeImage = outfile_biSizeImage;
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        RGBTRIPLE line[bi.biWidth];

        int pixpos = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int p = 0; p < n; p++)
            {
                line[pixpos] = triple;
                pixpos++;
            }
        }
        // skip over padding, if any
        fseek(inptr, infile_padding, SEEK_CUR);

        for (int m = 0; m < n; m++)
        {
            // write RGB triple to outfile
            fwrite(&line, sizeof(line), 1, outptr);

            // then add it back (to demonstrate how)
            for (int k = 0; k < outfile_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        //old position of infile padding


        //old position of outfile padding
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
