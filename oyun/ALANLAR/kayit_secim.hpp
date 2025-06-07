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
        fontt[2] = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",33);

        ayarDos.open("DOSYALAR/ayarlar.json");
        if(!ayarDos.is_open())
        {
            std::cerr << "Dosya açılamadı:(" << std::endl;
        }
        else
        {
            ayarDos >> ayarJSON;
            dilDos[0].open("DOSYALAR/turkce.json");
            dilDos[1].open("DOSYALAR/english.json");
            dilDos[2].open("DOSYALAR/custom.json");
            for(int i = 0;i<3;i += 1)
            {
                if(!dilDos[i].is_open())
                {
                    std::cerr << "Dosya açılamadı:(" << std::endl;
                }
                else
                {
                    dilDos[i] >> dilJSON[i];
                }
            }
            dil = ayarJSON["dil"];
        }
        if(dil == "Türkçe")
        {
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[0]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[0]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[0]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[0]["GERİ"],ak);
        }
        else if(dil == "English")
        {
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[1]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[1]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[1]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[1]["GERİ"],ak);
        }
        else
        {
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[2]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[2]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[2]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[2]["GERİ"],ak);
        }

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
        ///
        if(sira == 4)
        {
            yazilar[GERI].renkMod(0x00,0xFF,0xFF);
        }
        else
        {
            yazilar[GERI].renkMod(0xFF,0xFF,0xFF);
        }

        yazilar[KAYIT_1_SURE].ciz(isleyici,kayit_kareleri[0].x + 5, kayit_kareleri[0].y + 5);
        yazilar[KAYIT_1_ODA_ADI].ciz(isleyici,kayit_kareleri[0].x + 20, kayit_kareleri[0].y + 20);
        yazilar[KAYIT_1_DEVAM].ciz(isleyici,kayit_kareleri[0].x + kayit_kareleri[0].w - 55, kayit_kareleri[0].y + 80);
        yazilar[KAYIT_1_SIL].ciz(isleyici,kayit_kareleri[0].x + kayit_kareleri[0].w  / 2 - 10, kayit_kareleri[0].y + 80);
        yazilar[KAYIT_1_YENI].ciz(isleyici, kayit_kareleri[0].x + 10, kayit_kareleri[0].y + 80);

        yazilar[KAYIT_2_SURE].ciz(isleyici,kayit_kareleri[0].x + 5, kayit_kareleri[1].y + 5);
        yazilar[KAYIT_2_ODA_ADI].ciz(isleyici,kayit_kareleri[0].x + 20, kayit_kareleri[1].y + 20);
        yazilar[KAYIT_2_DEVAM].ciz(isleyici,kayit_kareleri[0].x + kayit_kareleri[0].w - 55, kayit_kareleri[1].y + 80);
        yazilar[KAYIT_2_SIL].ciz(isleyici,kayit_kareleri[0].x + kayit_kareleri[0].w  / 2 - 10, kayit_kareleri[1].y + 80);
        yazilar[KAYIT_2_YENI].ciz(isleyici, kayit_kareleri[1].x + 10, kayit_kareleri[1].y + 80);

        yazilar[KAYIT_3_SURE].ciz(isleyici,kayit_kareleri[0].x + 5, kayit_kareleri[2].y + 5);
        yazilar[KAYIT_3_ODA_ADI].ciz(isleyici,kayit_kareleri[0].x + 20, kayit_kareleri[2].y + 20);
        yazilar[KAYIT_3_DEVAM].ciz(isleyici,kayit_kareleri[0].x + kayit_kareleri[0].w - 55, kayit_kareleri[2].y + 80);
        yazilar[KAYIT_3_SIL].ciz(isleyici,kayit_kareleri[0].x + kayit_kareleri[0].w  / 2 - 10, kayit_kareleri[2].y + 80);
        yazilar[KAYIT_3_YENI].ciz(isleyici, kayit_kareleri[0].x + 10, kayit_kareleri[2].y + 80);

        yazilar[GERI].ciz(isleyici,640/2 - 30,480 - 50);
    }

    void gecilmeDurumuAyarla(bool durum)
    {
        if(!durum)
        {
            dilDeğişim();
            std::cout << "dilDeğişimi\n";
        }
        gecilmeDurumu = durum;
        return;
    }
    bool gecilmeDurumuVer(void)
    {
        return gecilmeDurumu;
    }

    uint8_t olaylar(SDL_Event* olay)
    {
        //const Uint8* tuslar = SDL_GetKeyboardState(NULL);

        if(!tusaBasildimi)
        {
            if(olay->type == SDL_KEYDOWN)
            {
                ///
                if(olay->key.keysym.sym == SDLK_UP)
                {
                    tusaBasildimi = true;
                    if(sira > 1 || sira == 2)
                        --sira;
                }
                ///
                if(olay->key.keysym.sym == SDLK_DOWN)
                {
                    tusaBasildimi = true;
                    if(sira < 4 || sira == 2)
                        ++sira;
                }
                ///
            }
                if(olay->key.keysym.scancode == SDL_SCANCODE_Z)
                {
                    if(sira == 4)
                    {
                        gecilmeDurumuAyarla(true);
                        return 2;
                    }
                }
        }
        if(olay->type == SDL_KEYUP)
        {
            tusaBasildimi = false;
        }
        return 1;
    }

    void kapat(void)
    {
        //delete[] yazilar;
        //yazilar = nullptr;
        SDL_DestroyRenderer(isleyici);
        isleyici = nullptr;
    }

    void siraSifirla(void){sira = 1;}
    protected:

    private:
    SDL_Rect kayit_kareleri[3];

    TTF_Font *fontt[3];
    SDL_Color ak = {0xFF,0xFF,0xFF,0xFF};
    SDL_Color turkuvaz = {0x00,0xFF,0xFF,0xFF};
    SDL_Color renk = ak;

    SDL_Renderer* isleyici = nullptr;

//    Yazi yazilar[YAZILAR];

    int8_t sira = 1;
    bool gecilmeDurumu = true;
    std::string dil;

    std::ifstream ayarDos, dilDos[3];
    json ayarJSON, dilJSON[3];

    private:

    enum yazi_bolumler
    {
        KAYIT_1_SURE = 0,
        KAYIT_1_ODA_ADI = 1,
        KAYIT_1_SIL = 2,
        KAYIT_1_YENI = 3,
        KAYIT_1_DEVAM = 4,

        KAYIT_2_SURE = 5,
        KAYIT_2_ODA_ADI = 6,
        KAYIT_2_SIL = 7,
        KAYIT_2_YENI = 8,
        KAYIT_2_DEVAM = 9,

        KAYIT_3_SURE = 10,
        KAYIT_3_ODA_ADI = 11,
        KAYIT_3_SIL = 12,
        KAYIT_3_YENI = 13,
        KAYIT_3_DEVAM = 14,

        GERI = 15,

        YAZILAR = 16
    };
    Yazi yazilar[YAZILAR];
    bool tusaBasildimi = false;

    void dilDeğişim(void)
    {
        ayarJSON.clear();
        ayarDos.seekg(0,std::ios::beg);
        ayarDos >> ayarJSON;
        dil = ayarJSON["dil"];
        if(dil == "Türkçe")
        {
            yazilar[KAYIT_1_SURE].kapat();
            yazilar[KAYIT_1_ODA_ADI].kapat();
            yazilar[KAYIT_1_DEVAM].kapat();
            yazilar[KAYIT_1_SIL].kapat();
            yazilar[KAYIT_1_YENI].kapat();
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[0]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[KAYIT_2_SURE].kapat();
            yazilar[KAYIT_2_ODA_ADI].kapat();
            yazilar[KAYIT_2_DEVAM].kapat();
            yazilar[KAYIT_2_SIL].kapat();
            yazilar[KAYIT_2_YENI].kapat();
            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[0]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[KAYIT_3_SURE].kapat();
            yazilar[KAYIT_3_ODA_ADI].kapat();
            yazilar[KAYIT_3_DEVAM].kapat();
            yazilar[KAYIT_3_SIL].kapat();
            yazilar[KAYIT_3_YENI].kapat();
            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[0]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[GERI].kapat();
            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[0]["GERİ"],ak);
        }
        else if(dil == "English")
        {
            yazilar[KAYIT_1_SURE].kapat();
            yazilar[KAYIT_1_ODA_ADI].kapat();
            yazilar[KAYIT_1_DEVAM].kapat();
            yazilar[KAYIT_1_SIL].kapat();
            yazilar[KAYIT_1_YENI].kapat();
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[1]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[KAYIT_2_SURE].kapat();
            yazilar[KAYIT_2_ODA_ADI].kapat();
            yazilar[KAYIT_2_DEVAM].kapat();
            yazilar[KAYIT_2_SIL].kapat();
            yazilar[KAYIT_2_YENI].kapat();
            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[1]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[KAYIT_3_SURE].kapat();
            yazilar[KAYIT_3_ODA_ADI].kapat();
            yazilar[KAYIT_3_DEVAM].kapat();
            yazilar[KAYIT_3_SIL].kapat();
            yazilar[KAYIT_3_YENI].kapat();
            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[1]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[GERI].kapat();
            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[1]["GERİ"],ak);
        }
        else
        {
            yazilar[KAYIT_1_SURE].kapat();
            yazilar[KAYIT_1_ODA_ADI].kapat();
            yazilar[KAYIT_1_DEVAM].kapat();
            yazilar[KAYIT_1_SIL].kapat();
            yazilar[KAYIT_1_YENI].kapat();
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[2]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[KAYIT_2_SURE].kapat();
            yazilar[KAYIT_2_ODA_ADI].kapat();
            yazilar[KAYIT_2_DEVAM].kapat();
            yazilar[KAYIT_2_SIL].kapat();
            yazilar[KAYIT_2_YENI].kapat();
            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[2]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[KAYIT_3_SURE].kapat();
            yazilar[KAYIT_3_ODA_ADI].kapat();
            yazilar[KAYIT_3_DEVAM].kapat();
            yazilar[KAYIT_3_SIL].kapat();
            yazilar[KAYIT_3_YENI].kapat();
            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],"Süre",ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],dilJSON[2]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[GERI].kapat();
            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[2]["GERİ"],ak);
        }
    }
};

#endif // KAYIT_SECIM_HPP
