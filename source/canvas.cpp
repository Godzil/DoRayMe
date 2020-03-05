/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Canvas implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <canvas.h>
#include <lodepng.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* NanoJPEG is a bit interesting to include as a header */
extern "C" {
#define _NJ_INCLUDE_HEADER_ONLY
#include <nanojpeg.c>
#undef _NJ_INCLUDE_HEADER_ONLY
}

#define BPP (24)
#define BytePP (BPP / 8)

#define MIN(_a, _b) ((_a)<(_b)?(_a):(_b))
#define MAX(_a, _b) ((_a)>(_b)?(_a):(_b))

Canvas::Canvas(uint32_t width, uint32_t height) : width(width), height(height)
{
    this->bitmap = (uint8_t *)calloc(4, width * height);
    this->stride = BytePP * width;
}

Canvas::Canvas(const Canvas &b)
{
    this->width = b.width;
    this->height = b.height;
    this->stride = b.stride;
    this->bitmap = (uint8_t *)calloc(4, b.width * b.height);
    memcpy(this->bitmap, b.bitmap, 4 * b.width * b.height);
}

Canvas::Canvas(const Canvas *b)
{
    this->width = b->width;
    this->height = b->height;
    this->stride = b->stride;
    this->bitmap = (uint8_t *)calloc(4, b->width * b->height);
    memcpy(this->bitmap, b->bitmap, 4 * b->width * b->height);
}

Canvas::Canvas(const char *imgfile)
{
    /* Try to determine the file type in a really lazy way */
    const char *fileExt = strrchr(imgfile, '.');

    this->bitmap = NULL;

    if (fileExt == NULL)
    {
        printf("ERROR: Invalid file name '%s' - Can't determine the file format\n", imgfile);
    }
    else if (strncasecmp(fileExt, ".png", sizeof(fileExt)) == 0)
    {
        uint32_t ret = lodepng_decode24_file(&this->bitmap, &this->width, &this->height, imgfile);
        if (ret)
        {
            printf("ERROR: %s\n", lodepng_error_text(ret));
        }
    }
    else if ( (strncasecmp(fileExt, ".jpg", sizeof(fileExt)) == 0) || (strncasecmp(fileExt, ".jpeg", sizeof(fileExt)) == 0) )
    {
        FILE *fp;
        char *fileBuff;
        size_t fileSize;

        fp = fopen(imgfile, "rb");

        if (fp)
        {

            fseek(fp, 0, SEEK_END);
            fileSize = ftell(fp);
            fileBuff = (char *)calloc(fileSize, 1);
            fseek(fp, 0, SEEK_SET);
            fileSize = fread(fileBuff, 1, fileSize, fp);
            fclose(fp);

            njInit();
            if (!njDecode(fileBuff, fileSize))
            {
                this->width = njGetWidth();
                this->height = njGetHeight();
                /* Need to do a local copy */

                this->bitmap = (uint8_t *)calloc(1, njGetImageSize());
                memcpy(this->bitmap, njGetImage(), njGetImageSize());
            }
            else
            {
                printf("ERROR: Error while decoding the file '%s'\n", imgfile);
            }
            free(fileBuff);

            njDone();
        }
        else
        {
            printf("ERROR: Can't opening the file '%s'.\n", imgfile);
        }
    }
    else
    {
        printf("ERROR: File extention '%s' is not a recognized one.\n", fileExt);
    }

    if (this->bitmap == NULL)
    {
        printf("ABORT: Opening image file '%s' failed\n", imgfile);
        exit(-1);
    }

    this->stride = BytePP * width;
}

Canvas::~Canvas()
{
    if (this->bitmap != nullptr)
    {
        free(this->bitmap);
    }
}

void Canvas::putPixel(uint32_t x, uint32_t y, Tuple colour)
{
    uint32_t offset = y * this->stride + x * BytePP;
    this->bitmap[offset + 0] = MAX(MIN(colour.x * 255, 255), 0);
    this->bitmap[offset + 1] = MAX(MIN(colour.y * 255, 255), 0);
    this->bitmap[offset + 2] = MAX(MIN(colour.z * 255, 255), 0);
}

Colour Canvas::getPixel(uint32_t x, uint32_t y)
{
    uint32_t offset = y * this->stride + x * BytePP;
    return Colour(this->bitmap[offset + 0] / 255.0, this->bitmap[offset + 1] / 255.0, this->bitmap[offset + 2] / 255.0);
}

bool Canvas::SaveAsPNG(const char *filename)
{
    uint32_t ret = lodepng_encode24_file(filename, this->bitmap, this->width, this->height);

    return ret == 0;
}