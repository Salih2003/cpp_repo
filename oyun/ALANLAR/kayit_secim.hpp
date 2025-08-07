#ifndef KAYIT_SECIM_HPP
#define KAYIT_SECIM_HPP

#include "alan_basliklar.hpp"

class KAYIT_SECIM
{
    public:
    void tanimlamalar(SDL_Renderer* isleyici,const pencereBilgi *pencereBilgisi)
    {
        this->isleyici = isleyici;//std::cout << mod->w << " " << mod->h << std::endl;
        //kullanılanEkranModu = mod;
        PencereninBilgisi = pencereBilgisi;
        fontt[0] = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",50);
        fontt[1] = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",20);
        fontt[2] = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",33);

        kayit_kareleri[0] = { PencereninBilgisi->temelPencereGenişlik / 6, PencereninBilgisi->temelPencereYükseklik / 5 - 15, 4*PencereninBilgisi->temelPencereGenişlik/6, 100 };
        kayit_kareleri[1] = { kayit_kareleri[0].x, kayit_kareleri[0].y + 110, kayit_kareleri[0].w, kayit_kareleri[0].h };
        kayit_kareleri[2] = { kayit_kareleri[0].x, kayit_kareleri[1].y + 110, kayit_kareleri[0].w, kayit_kareleri[0].h };

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
        kilitle k("DOSYALAR/VERI/açacaklar.key");
//ef437a9a5a47099ada42932f8f2d0a7bfdbc722926cb69d4264af4411e0b7b45
//        k.EncryptFile("DOSYALAR/VERI/ilkKayit.txt","DOSYALAR/VERI/ilkKayit.dat");
//        k.EncryptFile("DOSYALAR/VERI/ikinciKayit.txt","DOSYALAR/VERI/ikinciKayit.dat");
//        k.EncryptFile("DOSYALAR/VERI/ucuncuKayit.txt","DOSYALAR/VERI/ucuncuKayit.dat");

        if(k.DecryptFileToData("DOSYALAR/VERI/ilkKayit.dat",kayitString[0]))
        {
           if(k.DecryptFileToData("DOSYALAR/VERI/ikinciKayit.dat",kayitString[1]))
           {
                if(k.DecryptFileToData("DOSYALAR/VERI/ucuncuKayit.dat",kayitString[2]))
                {
                  std::cout << "başarılı \n";
                }
           }
        }
        else
        {
            std::cerr << "başarısız....\n";
            return;
        }
        kayitJSONlari[0] = nlohmann::json::parse(kayitString[0]);
        kayitJSONlari[1] = nlohmann::json::parse(kayitString[1]);
        kayitJSONlari[2] = nlohmann::json::parse(kayitString[2]);
        for(int i = 0; i < 3; i++)
        {
            std::cout << "json " << i << "içindeki veriler: " << kayitJSONlari[i].dump(4) << std:: endl;
        }

        if(dil == "Türkçe")
        {
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[0]["geçen_süre"],ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[0]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[1]["geçen_süre"],ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[1]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[2]["geçen_süre"],ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[2]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[0]["GERİ"],ak);
        }
        else if(dil == "English")
        {
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[0]["geçen_süre"],ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[0]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[1]["geçen_süre"],ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[1]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[2]["geçen_süre"],ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[2]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[1]["GERİ"],ak);
        }
        else
        {
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[0]["geçen_süre"],ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[0]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[1]["geçen_süre"],ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[1]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[2]["geçen_süre"],ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[2]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[2]["GERİ"],ak);
        }
        yanSıra[0] = 1;
        yanSıra[1] = 1;
        yanSıra[2] = 1;

    }
    void ciz(void)
    {
        if(sira == 1)
        {
            SDL_SetRenderDrawColor(isleyici,0x00,0xFF,0xFF,0xFF);
            switch(yanSıra[0])
            {
                case 1:
                    yazilar[KAYIT_1_DEVAM].renkMod(255,255,255);
                    yazilar[KAYIT_1_SIL].renkMod(255,255,255);
                    yazilar[KAYIT_1_YENI].renkMod(0,255,0xFF);
                    break;
                case 2:
                    yazilar[KAYIT_1_DEVAM].renkMod(255,255,255);
                    yazilar[KAYIT_1_SIL].renkMod(0,255,255);
                    yazilar[KAYIT_1_YENI].renkMod(255,255,0xFF);
                    break;
                case 3:
                    yazilar[KAYIT_1_DEVAM].renkMod(0,255,255);
                    yazilar[KAYIT_1_SIL].renkMod(255,255,255);
                    yazilar[KAYIT_1_YENI].renkMod(255,255,0xFF);
                    break;
                default:
                    std::cout << "Hatalı işlem \n";
            };
        }
        else
        {
            yazilar[KAYIT_1_DEVAM].renkMod(255,255,255);
            yazilar[KAYIT_1_SIL].renkMod(255,255,255);
            yazilar[KAYIT_1_YENI].renkMod(255,255,0xFF);
            SDL_SetRenderDrawColor(isleyici,0xFF,0xFF,0xFF,0xFF);
        }
        SDL_RenderDrawRect(isleyici,&kayit_kareleri[0]);
        ///
        if(sira == 2)
        {
            SDL_SetRenderDrawColor(isleyici,0x00,0xFF,0xFF,0xFF);
            switch(yanSıra[1])
            {
                case 1:
                    yazilar[KAYIT_2_DEVAM].renkMod(255,255,255);
                    yazilar[KAYIT_2_SIL].renkMod(255,255,255);
                    yazilar[KAYIT_2_YENI].renkMod(0,255,0xFF);
                    break;
                case 2:
                    yazilar[KAYIT_2_DEVAM].renkMod(255,255,255);
                    yazilar[KAYIT_2_SIL].renkMod(0,255,255);
                    yazilar[KAYIT_2_YENI].renkMod(255,255,0xFF);
                    break;
                case 3:
                    yazilar[KAYIT_2_DEVAM].renkMod(0,255,255);
                    yazilar[KAYIT_2_SIL].renkMod(255,255,255);
                    yazilar[KAYIT_2_YENI].renkMod(255,255,0xFF);
                    break;
                default:
                    std::cout << "Hatalı işlem \n";
            };
        }
        else
        {
            yazilar[KAYIT_2_DEVAM].renkMod(255,255,255);
            yazilar[KAYIT_2_SIL].renkMod(255,255,255);
            yazilar[KAYIT_2_YENI].renkMod(255,255,0xFF);
            SDL_SetRenderDrawColor(isleyici,0xFF,0xFF,0xFF,0xFF);
        }
        SDL_RenderDrawRect(isleyici,&kayit_kareleri[1]);
        ///
        if(sira == 3)
        {
            SDL_SetRenderDrawColor(isleyici,0x00,0xFF,0xFF,0xFF);
            switch(yanSıra[2])
            {
                case 1:
                    yazilar[KAYIT_3_DEVAM].renkMod(255,255,255);
                    yazilar[KAYIT_3_SIL].renkMod(255,255,255);
                    yazilar[KAYIT_3_YENI].renkMod(0,255,0xFF);
                    break;
                case 2:
                    yazilar[KAYIT_3_DEVAM].renkMod(255,255,255);
                    yazilar[KAYIT_3_SIL].renkMod(0,255,255);
                    yazilar[KAYIT_3_YENI].renkMod(255,255,0xFF);
                    break;
                case 3:
                    yazilar[KAYIT_3_DEVAM].renkMod(0,255,255);
                    yazilar[KAYIT_3_SIL].renkMod(255,255,255);
                    yazilar[KAYIT_3_YENI].renkMod(255,255,0xFF);
                    break;
                default:
                    std::cout << "Hatalı işlem \n";
            };
        }
        else
        {
            yazilar[KAYIT_3_DEVAM].renkMod(255,255,255);
            yazilar[KAYIT_3_SIL].renkMod(255,255,255);
            yazilar[KAYIT_3_YENI].renkMod(255,255,0xFF);
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

            yazilar[GERI].ciz(isleyici,(640/2 - 30),480 - 50);
    }

    void gecilmeDurumuAyarla(bool durum)
    {
        if(!durum)
            dilDeğişim();
        gecilmeDurumu = durum;
        return;
    }
    bool gecilmeDurumuVer(void)
    {
        return gecilmeDurumu;
    }

    uint8_t olaylar(SDL_Event* olay)
    {
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
                if(olay->key.keysym.sym == SDLK_RIGHT)
                {
                    tusaBasildimi = true;
                    if(sira == 1)
                    {
                        if(yanSıra[0] < 3 || yanSıra[0] == 2)
                            ++yanSıra[0];
                    }

                    if(sira == 2)
                    {
                        if(yanSıra[1] < 3 || yanSıra[1] == 2)
                            ++yanSıra[1];
                    }

                    if(sira == 3)
                    {
                        if(yanSıra[2] < 3 || yanSıra[2] == 2)
                            ++yanSıra[2];
                    }
                }
                ///
                if(olay->key.keysym.sym == SDLK_LEFT)
                {
                    tusaBasildimi = true;
                    if(sira == 1)
                    {
                        if(yanSıra[0] > 1 || yanSıra[0] == 2)
                            --yanSıra[0];
                    }
                    if(sira == 2)
                    {
                        if(yanSıra[1] > 1 || yanSıra[1] == 2)
                            --yanSıra[1];
                    }
                    if(sira == 3)
                    {
                        if(yanSıra[2] > 1 || yanSıra[2] == 2)
                            --yanSıra[2];
                    }
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
    SDL_DisplayMode* kullanılanEkranModu;

//    Yazi yazilar[YAZILAR];

    int8_t sira = 1;
    uint8_t yanSıra[3];
    bool gecilmeDurumu = true;
    std::string dil, kayitString[3];

    std::ifstream ayarDos, dilDos[3], kayitDosyalari[3];
    json ayarJSON, dilJSON[3], kayitJSONlari[3];

    const pencereBilgi *PencereninBilgisi;

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
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[0]["geçen_süre"],ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[0]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[KAYIT_2_SURE].kapat();
            yazilar[KAYIT_2_ODA_ADI].kapat();
            yazilar[KAYIT_2_DEVAM].kapat();
            yazilar[KAYIT_2_SIL].kapat();
            yazilar[KAYIT_2_YENI].kapat();
            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[1]["geçen_süre"],ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[1]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[0]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[0]["yeni"],ak);

            yazilar[KAYIT_3_SURE].kapat();
            yazilar[KAYIT_3_ODA_ADI].kapat();
            yazilar[KAYIT_3_DEVAM].kapat();
            yazilar[KAYIT_3_SIL].kapat();
            yazilar[KAYIT_3_YENI].kapat();
            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[2]["geçen_süre"],ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[2]["oda_adı"],ak);
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
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[0]["geçen_süre"],ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[0]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[KAYIT_2_SURE].kapat();
            yazilar[KAYIT_2_ODA_ADI].kapat();
            yazilar[KAYIT_2_DEVAM].kapat();
            yazilar[KAYIT_2_SIL].kapat();
            yazilar[KAYIT_2_YENI].kapat();
            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[1]["geçen_süre"],ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[1]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[1]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[1]["yeni"],ak);

            yazilar[KAYIT_3_SURE].kapat();
            yazilar[KAYIT_3_ODA_ADI].kapat();
            yazilar[KAYIT_3_DEVAM].kapat();
            yazilar[KAYIT_3_SIL].kapat();
            yazilar[KAYIT_3_YENI].kapat();
            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[2]["geçen_süre"],ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[2]["oda_adı"],ak);
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
            yazilar[KAYIT_1_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[0]["geçen_süre"],ak);
            yazilar[KAYIT_1_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[0]["oda_adı"],ak);
            yazilar[KAYIT_1_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_1_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_1_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[KAYIT_2_SURE].kapat();
            yazilar[KAYIT_2_ODA_ADI].kapat();
            yazilar[KAYIT_2_DEVAM].kapat();
            yazilar[KAYIT_2_SIL].kapat();
            yazilar[KAYIT_2_YENI].kapat();
            yazilar[KAYIT_2_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[1]["geçen_süre"],ak);
            yazilar[KAYIT_2_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[1]["oda_adı"],ak);
            yazilar[KAYIT_2_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_2_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_2_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[KAYIT_3_SURE].kapat();
            yazilar[KAYIT_3_ODA_ADI].kapat();
            yazilar[KAYIT_3_DEVAM].kapat();
            yazilar[KAYIT_3_SIL].kapat();
            yazilar[KAYIT_3_YENI].kapat();
            yazilar[KAYIT_3_SURE].yaziOlustur(this->isleyici,fontt[1],kayitJSONlari[2]["geçen_süre"],ak);
            yazilar[KAYIT_3_ODA_ADI].yaziOlustur(this->isleyici,fontt[0],kayitJSONlari[2]["oda_adı"],ak);
            yazilar[KAYIT_3_DEVAM].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["devam"],ak);
            yazilar[KAYIT_3_SIL].yaziOlustur(this->isleyici,fontt[1],dilJSON[2]["sil"],ak);
            yazilar[KAYIT_3_YENI].yaziOlustur(this->isleyici, fontt[1], dilJSON[2]["yeni"],ak);

            yazilar[GERI].kapat();
            yazilar[GERI].yaziOlustur(this->isleyici,fontt[2],dilJSON[2]["GERİ"],ak);
        }
    }
};

#endif // KAYIT_SECIM_HPP
