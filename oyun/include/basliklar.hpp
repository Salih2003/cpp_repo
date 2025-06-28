#ifndef BASLIKLAR_HPP
#define BASLIKLAR_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <box2d/box2d.h>

#include <iostream>

struct pencereBilgi
{
    int temelPencereYükseklik;
    int temelPencereGenişlik;
    int ekranYüksekliği;
    int ekranGenişliği;
    double pencereEkranYükseklikOranı;
    double pencereEkranGenişlikOranı;
    Uint32 ekranBayrağı;
};

#endif // BASLIKLAR_HPP

