#ifndef KAYIT_SECIM_HPP
#define KAYIT_SECIM_HPP

#include "alan_basliklar.hpp"

class KAYIT_SECIM
{
    public:
    void tanimlamalar(SDL_Renderer* isle)
    {
        isleyici = isle;
        kayit_kareleri[0] = {640/4,480/6,300,100};
    }
    void ciz(void)
    {
        if(sira == 1)
        {
            SDL_SetRenderDrawColor(isleyici,0x00,0xFF,0xFF,0xFF);
        }
        SDL_RenderDrawRect(isleyici,&kayit_kareleri[0]);
    }

    void gecilmeDurumuAyarla(bool durum)
    {
        gecilmeDurumu = durum;
        return;
    }
    bool gecilmeDurumuVer(void)
    {
        return gecilmeDurumu;
    }
    protected:

    private:
    SDL_Rect kayit_kareleri[3];

    SDL_Renderer* isleyici = nullptr;

    Yazi yazilar[15];

    int8_t sira = 1;
    bool gecilmeDurumu = true;
};

#endif // KAYIT_SECIM_HPP
