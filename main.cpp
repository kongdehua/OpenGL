#include <GL/gl.h>
#include <FreeImage.h>
#include <stdio.h>

int main()
{
    char filename[40] = "./NeHe.bmp";
    //
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

    // pointer to the image, once loaded.
    FIBITMAP *dib = NULL;

    // pointer to the image date
    BYTE* bits = NULL;

    // image width and height;
    unsigned int width = 0, height = 0;

    // OpenGL's image ID to map to
    GLuint gl_texID;

    // check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    // if still unknown, try to guess the file format form the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    // if still unknown, return failure
    if (fif == FIF_UNKNOWN)
    {
        return -1;
    }

    // check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
    // if the image failed to load, return failure
    if (!dib)
        return -1;

    bits   = FreeImage_GetBits(dib);
    width  = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE,
                 dib);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Free FreeImage's copy of the data
    FreeImage_Unload(dib);


    return 0;
};

