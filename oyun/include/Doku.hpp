#ifndef DOKU_HPP
#define DOKU_HPP

#include "basliklar.hpp"

class Doku
{
    public:
        //Doku();
        ~Doku();
        void dokuYukle(SDL_Renderer* isleyici,const char* dosyaAdi);
        void ciz(SDL_Renderer* isleyici,int x, int y);
        void ciz(SDL_Renderer* isleyici,int x, int y, int w, int h);
        void konumAl(int x, int y);
        void boyutAl(int w, int h);
        void renkAyarla(Uint8 r, Uint8 g, Uint8 b);
    protected:

    private:
        SDL_Texture* doku = nullptr;
        int x, y, w, h;
};

#endif // DOKU_HPP
