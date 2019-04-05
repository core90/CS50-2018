# Questions

## What's `stdint.h`?

The `stdint.h` header declares integer types having specified widths.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These integers have an exact width of bits. The "u" stands for unsigned.

For example: `uint8_t` is an unsigned integer with a width of 8 bits.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

* `BYTE`    1 byte
* `DWORD`   4 bytes
* `LONG`    4 bytes
* `WORD`    2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes in ASCII are "B" and "M".

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the file size in bytes of the full Bitmap.
`biSize` is the file size in bytes of the header part of a Bitmap.

## What does it mean if `biHeight` is negative?

`biHeight`specifies the height of a bitmap in pixels. If the `biHeight`is negative, the bitmap is a top-down DIB (Device Indepent Bitmap)
with the origin in the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount` specifies the number of bits per pixel. It determines the number of bits that define each pixel and the maximum number of colors of the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file does not exist.

## Why is the third argument to `fread` always `1` in our code?

The third argument to `fread`is always `1`, because we are specifying the number of elements to read.
For example, we can iterate over every pixel.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

If `bi.biWidth` is `3`, the value assigned to `padding` will be `3`.
This line of code ensures, that every scanline is a multiple of 4.

## What does `fseek` do?

With `feek` we can change the offset of a pointer.

## What is `SEEK_CUR`?

The current position of the file pointer.
