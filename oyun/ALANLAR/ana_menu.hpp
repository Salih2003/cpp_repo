#ifndef ANA_MENU_HPP
#define ANA_MENU_HPP

#include "alan_basliklar.hpp"

class ANA_MENU
{
    public:
        void tanimlamalar(SDL_Renderer* isle)
        {
            zaman.Reset();
            buyukYazi = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",150);
            ortaYazi = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",110);
            kucukYazi = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",50);
            if(buyukYazi == NULL)
                std::cerr << "hata " << TTF_GetError() << std::endl;

            belirtmeKare = {EKRAN_GENISLIK1/4 - 5,EKRAN_YUKSEKLIK1/3+60,110,30};

            ayarDos.open("DOSYALAR/ayarlar.json",std::ios::binary);
            if(!ayarDos.is_open())
                std::cerr << "DOSYA AÇILAMADI" << std::endl;
            else
            {
                ayarDos.seekg(0,std::ios::end);
                if(ayarDos.tellg() == 0)
                {
                    std::cout << "Dosya boş" << std::endl;
                    ayarJSON["dil"] = "Türkçe";
                    dil = ayarJSON["dil"];
                    ayarDos.seekg(0,std::ios::beg);
                }
                else
                {
                    ayarDos.seekg(0,std::ios::beg);
                    ayarDos >> ayarJSON;

                    dil = ayarJSON["dil"];

                    dilDosyasi[0].open("DOSYALAR/turkce.json");
                    dilDosyasi[0] >> dilJSON[0];
                    dilDosyasi[1].open("DOSYALAR/english.json");
                    dilDosyasi[1] >> dilJSON[1];
                    dilDosyasi[2].open("DOSYALAR/custom.json");
                    dilDosyasi[2] >> dilJSON[2];

                    if(dil == "Türkçe")
                    {
                        yazilar[0].yaziOlustur(isle,buyukYazi,dilJSON[0]["başlık"],ak);
                        yazilar[1].yaziOlustur(isle,kucukYazi,dilJSON[0]["başla"],ak);
                        yazilar[2].yaziOlustur(isle,kucukYazi,"Ayarlar",ak);
                        yazilar[3].yaziOlustur(isle,kucukYazi,"Çık",ak);
                    }
                    else if(dil == "English")
                    {
                        yazilar[0].yaziOlustur(isle,buyukYazi,dilJSON[1]["başlık"],ak);
                        yazilar[1].yaziOlustur(isle,kucukYazi,dilJSON[1]["başla"],ak);
                        yazilar[2].yaziOlustur(isle,kucukYazi,dilJSON[1]["ayarlar"],ak);
                        yazilar[3].yaziOlustur(isle,kucukYazi,dilJSON[1]["çık"],ak);
                    }
                    else
                    {
                        yazilar[0].yaziOlustur(isle,buyukYazi,dilJSON[2]["başlık"],ak);
                        yazilar[1].yaziOlustur(isle,kucukYazi,dilJSON[2]["başla"],ak);
                        yazilar[2].yaziOlustur(isle,kucukYazi,dilJSON[2]["ayarlar"],ak);
                        yazilar[3].yaziOlustur(isle,kucukYazi,dilJSON[2]["çık"],ak);
                    }
                }
            }

        }
        void kapat()
        {
            TTF_CloseFont(buyukYazi);
            buyukYazi = nullptr;
            TTF_CloseFont(ortaYazi);
            ortaYazi = nullptr;
            TTF_CloseFont(kucukYazi);
            kucukYazi = nullptr;zaman.Reset();
        }
        bool gecilmeDurumunuVer()
        {
            return gecilmeDurumu;
        }
        void gecilmeDurumunuAyarla(bool aktif)
        {
            gecilmeDurumu = aktif;
            return;
        }
        void ciz(SDL_Renderer* isle)
        {
            SDL_SetRenderDrawColor(isle,ak.r,ak.g,ak.b,ak.a);
            SDL_RenderDrawRect(isle,&belirtmeKare);
            yazilar[0].ciz(isle,EKRAN_GENISLIK1 /4,EKRAN_YUKSEKLIK1 /6);
            yazilar[1].ciz(isle,EKRAN_GENISLIK1/4,EKRAN_YUKSEKLIK1/3+50);
            yazilar[2].ciz(isle,EKRAN_GENISLIK1/4,EKRAN_YUKSEKLIK1/3+90);
            yazilar[3].ciz(isle,EKRAN_GENISLIK1/4,EKRAN_YUKSEKLIK1/3+130);

        }

        int olayYonetimi()
        {
            //std::cout << (int)zaman.GetMilliseconds() << " " << sayac << std::endl;
            const Uint8* klavyeDurum = SDL_GetKeyboardState(NULL);
            if(klavyeDurum[SDL_SCANCODE_UP])
            {
                if(sayac > 0 && sayac <= 2)
                {
                    if(dur == false)
                    {
                        belirtmeKare.y = belirtmeKare.y - 40;
                        dur = true;
                        sayac--;
                    }
                }
            }
            if(zaman.GetMilliseconds() > 350.00F)
            {
                zaman.Reset();
                dur = false;
            }
            if(klavyeDurum[SDL_SCANCODE_DOWN])
            {
                if(sayac >= 0 && sayac < 2)
                {
                    if(dur == false)
                    {
                        belirtmeKare.y = belirtmeKare.y + 40;
                        dur = true;
                        sayac++;
                    }
                }
            }
            //secim oldumu baslangic
            if(klavyeDurum[SDL_SCANCODE_Z])
            {
                if(sayac == 0)
                {
                    gecilmeDurumu = true;
                    return 0;
                }
                if(sayac == 1)
                {
                    gecilmeDurumu = true;
                    return 1;
                }
                if(sayac == 2)
                {
                    gecilmeDurumu = true;
                    kapat();
                    return 2;
                }
            }
            //secim oldumu son
            //sayaca gore secim karesinin pozisyonu belirleme
            if(sayac == 1)
            {
                belirtmeKare.w = 160;
            }
            else if(sayac == 2)
            {
                belirtmeKare.w = 70;
            }
            else
            {
                belirtmeKare.w = 110;
            }
            return -1;
        }

    protected:

    private:
        Yazi yazilar[5];
        SDL_Rect belirtmeKare;//basla cık tan hangisi old. kullanıcıya gosterir.
        const int EKRAN_GENISLIK1 = 640;
        const int EKRAN_YUKSEKLIK1 = 480;

        int8_t sayac = 0;//ana menu secenklerden hangisinde oldugunu gosterir.

        TTF_Font* buyukYazi;
        TTF_Font* ortaYazi;
        TTF_Font* kucukYazi;

        SDL_Color kara = {0x00,0x00,0x00,0xFF};
        SDL_Color ak = {0xFF,0xFF,0xFF,0xFF};

        b2Timer zaman;//secenekler arası gecis suresi icin.

        bool dur = false;
        bool gecilmeDurumu = false;
        std::ifstream dilDosyasi[3];
        std::ifstream ayarDos;

        std::string dil;

        json ayarJSON;
        json dilJSON[3];

        void dilGecisi(void)
        {
            return;
        }
};

#endif // ANA_MENU_HPP
