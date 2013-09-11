#include "HeightMap.h"
#include <conio.h>
#include <exception>
#include <iostream>
using namespace std;

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch (bpp)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
    } // switch
}

HeightMap::HeightMap()
{
    hm=NULL;
    size=0;
}

HeightMap::HeightMap(const char* filename)
{
    hm=NULL;
    size=0;

    load(filename);
}

HeightMap::~HeightMap()
{
    unload();
}

bool HeightMap::load(const char* filename)
{
    SDL_Surface *s=NULL;

    if(hm!=NULL)
        unload();

    s=SDL_LoadBMP(filename);
    if(s==NULL)
        return false;

    size=s->w;

    hm=new char*[size];
    for(size_t i=0;i<size;i++)
    {
        hm[i]=new char[size];
        if(hm[i] == NULL)
            cout << "BOOM ! ALLOCATION FAILS !" << endl;

    }
    //getch();
    for(size_t i=0;i<size;i++)
    {
        for(size_t j=0;j<size;j++)
        {
            Uint32 buffer = getpixel(s,i,j);
            SDL_PixelFormat *fmt = s->format;
            buffer = buffer & fmt->Rmask;
            buffer = buffer >> fmt->Rshift;
            buffer = buffer << fmt->Rloss;
            cout << i << ":" << j << endl;
            hm[i][j]=(char)(buffer );
        }
    }
    SDL_FreeSurface(s);
    return true;
}

void HeightMap::unload()
{
    for(size_t i=0;i<size;i++)
        delete [] hm[i];
    delete [] hm;

    hm=NULL;
    size=0;
}

char** HeightMap::getHeightMap()
{
    return hm;
}

size_t HeightMap::getSize()
{
    return size;
}
