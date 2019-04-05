// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    //for example 1/4
    int x = fraction[0] - '0';  // x==1
    int y = fraction[2] - '0';   // y==4

    return ((8 / y) * x);

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO

    float f;
    float n; // number of semitones the note is away from A4
    int fullnote = strlen(note);
    int LetterNote = note[0];
    int octave = note[fullnote - 1] - '0';

    switch (LetterNote) // check how far the letter is away from A
    {
        case 'A':
            n = 0.0;
            break;

        case 'B':
            n = 2.0;
            break;

        case 'C':
            n = -9.0;
            break;

        case 'D':
            n = -7.0;
            break;

        case 'E':
            n = -5.0;
            break;

        case 'F':
            n = -4.0;
            break;

        case 'G':
            n = -2.0;
            break;

        default:
            return 0;
    }

    //look if note have an accidental and move one semitone up or down
    if (fullnote == 3)

        if (note[1] == '#')
        {
            n = n + 1.0;
        }
        if (note[1] == 'b')
        {
            n = n - 1.0;
        }

    //calculate ovtave
    if (octave < 8 && octave > 0)
    {
        n = n + ((octave -4.0) * 12.0); // if octave is 4, n remains unchanged, if 5 n would be 12 more (one whole octave up)
    }
    if (octave > 8 && octave < 0)
    {
        return 0;
    }

    f = round(pow(2.0, (n / 12.0)) * 440.00); //calculate frequency, n=number of semitones, then round it
    return f;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO

    if (s[0] == '\0')
    {
        return true;
    }

    else
    {
        return false;
    }
}
