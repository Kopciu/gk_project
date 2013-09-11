#ifndef __HEIGHTMAP_HPP__
#define __HEIGHTMAP_HPP__

#include <SDL.h>

class HeightMap
{
    private:
        size_t size;
        char** hm;

    public:
        HeightMap();
        HeightMap(const char* filename);
        ~HeightMap();

        bool load(const char* filename);
        void unload();
        char** getHeightMap();
        size_t getSize();
};

#endif
