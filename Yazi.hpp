#ifndef YAZI_HPP
#define YAZI_HPP

#include "basliklar.hpp"

class Yazi
{
    public:
        bool yaziOlustur(SDL_Renderer* isleyici,TTF_Font* font,const char* yazi,SDL_Color renk);
        ~Yazi();
        void ciz(SDL_Renderer* isleyici,int x, int y);
        void renkMod(Uint8 r, Uint8 g, Uint8 b);
        void kapat(void);
    protected:

    private:
        SDL_Texture* doku;
        int x,y,w,h;
        bool basarili = true;
};

#endif // YAZI_HPP
