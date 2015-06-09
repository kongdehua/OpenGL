#include <stdio.h>

#include "functions.h"

void printVersion()
{
    const char *byteVersion = (const char *)glGetString(GL_VERSION);
    printf("version is %s.\n", byteVersion);
    byteVersion = (const char *)glGetString(GL_VENDOR);
    printf("vendor is %s.\n", byteVersion);

    /*
     *     byteVersion = (const char *)glGetString(GL_EXTENSIONS);
     *     printf("Extensions is %s.\n", byteVersion);
     *     */
}

bool loadTexture(GLuint *pnTexture, const char *filename)
{
    //
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    // check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    // if still unknown, try to guess the file format form the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    // if still unknown, return failure
    if (fif == FIF_UNKNOWN)
    {
        return false;
    }

    // pointer to the image, once loaded.
    FIBITMAP *dib = NULL;

    // check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
    // if the image failed to load, return failure
    if (!dib)
        return false;

    // pointer to the image date
    BYTE* bits = NULL;

    // image width and height;
    unsigned int width = 0, height = 0;

    bits   = FreeImage_GetBits(dib);
    width  = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);


    printf("width is %d, height is %d\n", width, height);
    glGenTextures(1, pnTexture);
    printf("pnTexture is %d\n", *pnTexture);
    glBindTexture(GL_TEXTURE_2D, *pnTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE,
                 bits);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Free FreeImage's copy of the data
    FreeImage_Unload(dib);
    return true;
}
