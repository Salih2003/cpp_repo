#ifndef KAYIT_SECIM_HPP
#define KAYIT_SECIM_HPP

#include "alan_basliklar.hpp"

class KAYIT_SECIM
{
    public:
    void tanimlamalar(SDL_Renderer* isleyici)
    {
        this->isleyici = isleyici;
        kayit_kareleri[0] = {640/4,480/6 - 25,300,100};
        kayit_kareleri[1] = {kayit_kareleri[0].x,kayit_kareleri[0].y + 110,300,100};
        kayit_kareleri[2] = {kayit_kareleri[0].x,kayit_kareleri[1].y + 110,300,100};

        fontt[0] = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",50);
        fontt[1] = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",20);

        yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
    }
    void ciz(void)
    {
        if(sira == 1)
        {
            SDL_SetRenderDrawColor(isleyici,0x00,0xFF,0xFF,0xFF);
        }
        else
        {
            SDL_SetRenderDrawColor(isleyici,0xFF,0xFF,0xFF,0xFF);
        }
        SDL_RenderDrawRect(isleyici,&kayit_kareleri[0]);
        ///
        if(sira == 2)
        {
            SDL_SetRenderDrawColor(isleyici,0x00,0xFF,0xFF,0xFF);
        }
        else
        {
            SDL_SetRenderDrawColor(isleyici,0xFF,0xFF,0xFF,0xFF);
        }
        SDL_RenderDrawRect(isleyici,&kayit_kareleri[1]);
        ///
        if(sira == 3)
        {
            SDL_SetRenderDrawColor(isleyici,0x00,0xFF,0xFF,0xFF);
        }
        else
        {
            SDL_SetRenderDrawColor(isleyici,0xFF,0xFF,0xFF,0xFF);
        }
        SDL_RenderDrawRect(isleyici,&kayit_kareleri[2]);

        yazilar[KAYIT_1_SURE].ciz(isleyici,kayit_kareleri[0].x + 5, kayit_kareleri[0].y + 5);
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

    TTF_Font *fontt[2];
    SDL_Color ak = {0xFF,0xFF,0xFF,0xFF};
    SDL_Color turkuvaz = {0x00,0xFF,0xFF,0xFF};
    SDL_Color renk = ak;

    SDL_Renderer* isleyici = nullptr;

    Yazi *yazilar = new Yazi[20];

    int8_t sira = 1;
    bool gecilmeDurumu = true;

    private:
    void kapat(void)
    {
        delete[] yazilar;
        yazilar = nullptr;
        SDL_DestroyRenderer(isleyici);
        isleyici = nullptr;
    }

    enum yazi_bolumler
    {
        KAYIT_1_SURE = 0,
        KAYIT_1_ODA_ADI,
        KAYIT_1_SIL,
        KAYIT_1_YENI,
        KAYIT_1_DEVAM,

        KAYIT_2_SURE,
        KAYIT_2_ODA_ADI,
        KAYIT_2_SIL,
        KAYIT_2_YENI,
        KAYIT_2_DEVAM,

        KAYIT_3_SURE,
        KAYIT_3_ODA_ADI,
        KAYIT_3_SIL,
        KAYIT_3_YENI,
        KAYIT_3_DEVAM,

        GERI
    };
};

#endif // KAYIT_SECIM_HPP
