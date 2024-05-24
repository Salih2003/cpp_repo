#ifndef SECENEKLER_MENU_HPP
#define SECENEKLER_MENU_HPP
// 71 30
#include "alan_basliklar.hpp"

class SECENEKLER_MENU
{
    public:
        ///
        ///
        ///
        void tanimlamalar(SDL_Renderer* isleyici)
        {
            buyukYazi = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",150);
            ortaYazi = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",70);
            kucukYazi = TTF_OpenFont("VARLIKLAR/TTF/Instructions.ttf",50);

            imlecDoku.dokuYukle(isleyici,"VARLIKLAR/PNG/imleç.png");
            imlecDoku.konumAl(&imlecX,&imlecY);
            imlecX = 40;
            imlecY = 100;
            yazilar[0].yaziOlustur(isleyici,ortaYazi,"seçenekler",ak);
            yazilar[1].yaziOlustur(isleyici,kucukYazi,"Ana Ses",ak);
            yazilar[2].yaziOlustur(isleyici,kucukYazi,"Ses Efekt",ak);
            yazilar[3].yaziOlustur(isleyici,kucukYazi,"Dil =",ak);
            yazilar[4].yaziOlustur(isleyici,kucukYazi,dilSecenegi.c_str(),ak);
            yazilar[5].yaziOlustur(isleyici,ortaYazi,"Sıfırla",kizil);
            yazilar[6].yaziOlustur(isleyici,kucukYazi,"Geri",ak);
            ///ses seviye karelerinin boyutlandırılması ve konumlandirilmasi baslangici
            int ww = 9, ww2 = 9;
            int hh = -10, hh2 = -10;
            int xx = 230, yy = 123;
            int xx2 = 265, yy2 = 165;
            for(int i=0; i<=7; i++)
            {
                if(i <= 3)
                {
                    sesSeviyesi[i].x = xx;
                    sesSeviyesi[i].y = yy;
                    sesSeviyesi[i].w = ww;
                    sesSeviyesi[i].h = hh;
                    hh -= 5;
                    xx += 11;
                }
                else
                {
                    sesSeviyesi[i].x = xx2;
                    sesSeviyesi[i].y = yy2;
                    sesSeviyesi[i].w = ww2;
                    sesSeviyesi[i].h = hh2;
                    hh2 -= 5;
                    xx2 += 11;
                }
            }
            ///ses seviye karelerinin boyutlandırılması ve konumlandirilmasi sonu
        }
        ///
        ///
        ///
        void ciz(SDL_Renderer* isleyici)
        {
            SDL_SetRenderDrawColor(isleyici,ak.r,ak.g,ak.b,ak.a);
            //koşullar boyutu başlangıç o_O
            switch(sesDuzeyiSirasi[0])
            {
                case 0:

                    break;
                case 1:
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[0]);
                    break;
                case 2:
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[0]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[1]);
                    break;
                case 3:
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[0]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[1]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[2]);
                    break;
                case 4:
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[0]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[1]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[2]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[3]);
                    break;

            }

            switch(sesDuzeyiSirasi[1])
            {
                case 0:

                    break;
                case 1:
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[4]);
                    break;
                case 2:
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[4]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[5]);
                    break;
                case 3:
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[4]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[5]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[6]);
                    break;
                case 4:
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[4]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[5]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[6]);
                    SDL_RenderFillRect(isleyici,&sesSeviyesi[7]);
                    break;

            }
            //koşullar boyutu sonu \(0o0)/

            for(int i = 0;i <= 7;i++)
            {
//                SDL_SetRenderDrawColor(isleyici,ak.r,ak.g,ak.b,ak.a);
//                SDL_RenderFillRect(isleyici,&sesSeviyesi[i]);
                SDL_RenderDrawRect(isleyici,&sesSeviyesi[i]);
            }
            yazilar[0].ciz(isleyici,30,20);
            yazilar[1].ciz(isleyici,90,90);
            yazilar[2].ciz(isleyici,90,132);
            yazilar[3].ciz(isleyici,90,174);
            yazilar[4].ciz(isleyici,200,174);
            yazilar[5].ciz(isleyici,90,210);
            yazilar[6].ciz(isleyici,284,430);
            imlecDoku.ciz(isleyici,imlecX,imlecY,35,35);

            for(int i = 0;i <= 7; i++)
                SDL_RenderDrawRect(isleyici,&sesSeviyesi[i]);
        }
        ///
        ///
        ///
        void kapat()
        {
            TTF_CloseFont(buyukYazi);
            buyukYazi = nullptr;
            TTF_CloseFont(ortaYazi);
            ortaYazi = nullptr;
            TTF_CloseFont(kucukYazi);
            kucukYazi = nullptr;
        }
        ///
        ///
        ///
        bool gecilmeDurumunuVer()
        {
            return gecilmeDurumu;
        }
        void gecilmeDurumunuAyarla(bool aktif)
        {
            gecilmeDurumu = aktif;
            return;
        }
        ///
        ///
        ///
        uint8_t olayIsleyici(SDL_Event* olay)
        {
            if(olay->type == SDL_KEYDOWN)
            {
                if(olay->key.keysym.sym == SDLK_UP)
                {
                    if(tusBirakilmaDurumu == true)
                    {
                        tusBirakilmaDurumu = false;
                        if(imlecSirasi > 1 && imlecSirasi <= 5)
                            imlecSirasi--;
                    }
                }
                else if(olay->key.keysym.sym == SDLK_DOWN)
                {
                    if(tusBirakilmaDurumu == true)
                    {
                        tusBirakilmaDurumu = false;
                        if(imlecSirasi >= 1 && imlecSirasi < 5)
                            imlecSirasi++;
                    }
                }
                if(olay->key.keysym.sym == SDLK_RIGHT)
                {
                    if(imlecSirasi == 1)
                    {
                        if(tusBirakilmaDurumu)
                        {
                            tusBirakilmaDurumu = false;
                            if(sesDuzeyiSirasi[0] < 5)
                            {
                                if(sesDuzeyiSirasi[0] == 4)
                                {
                                    sesDuzeyiSirasi[0] = 4;
                                }
                                else
                                {
                                    sesDuzeyiSirasi[0]++;
                                }
                            }
                        }
                    }

                    if(imlecSirasi == 2)
                    {
                        if(tusBirakilmaDurumu)
                        {
                            tusBirakilmaDurumu = false;
                            if(sesDuzeyiSirasi[1] < 5)
                            {
                                if(sesDuzeyiSirasi[1] == 4)
                                {
                                    sesDuzeyiSirasi[1] = 4;
                                }
                                else
                                {
                                    sesDuzeyiSirasi[1]++;
                                }
                            }
                        }
                    }
                }
                if(olay->key.keysym.sym == SDLK_LEFT)
                {
                    if(imlecSirasi == 1)
                    {
                        if(tusBirakilmaDurumu)
                        {
                            tusBirakilmaDurumu = false;
                            if(sesDuzeyiSirasi[0] > -1)
                            {
                                if(sesDuzeyiSirasi[0] == 0)
                                {
                                    sesDuzeyiSirasi[0] = 0;
                                }
                                else
                                {
                                    sesDuzeyiSirasi[0]--;
                                }
                            }
                        }
                    }

                    if(imlecSirasi == 2)
                    {
                        if(tusBirakilmaDurumu)
                        {
                            tusBirakilmaDurumu = false;
                            if(sesDuzeyiSirasi[1] > -1)
                            {
                                if(sesDuzeyiSirasi[1] == 0)
                                {
                                    sesDuzeyiSirasi[1] = 0;
                                }
                                else
                                {
                                    sesDuzeyiSirasi[1]--;
                                }
                            }
                        }
                    }

                }
            }

            if(olay->type == SDL_KEYUP)
            {
                tusBirakilmaDurumu = true;
            }
            switch(imlecSirasi)
            {
                case 1:
                    imlecY = 100;
                    imlecX = 40;
                    break;
                case 2:
                    imlecY = 140;
                    imlecX = 40;
                    break;
                case 3:
                    imlecY = 180;
                    imlecX = 40;
                    break;
                case 4:
                    imlecY = 230;
                    imlecX = 40;
                    break;
                case 5:
                    imlecY = 438;
                    imlecX = 240;
                    break;
            }
            if(olay->key.keysym.sym == SDLK_z)
            {
                if(imlecSirasi == 5)
                {
                    kapat();
                    return 2;
                }
            }
            return 1;
        }
        ///
        ///
        ///
    private:
        Yazi yazilar[7];
        Doku imlecDoku;
        TTF_Font* buyukYazi = nullptr;
        TTF_Font* ortaYazi = nullptr;
        TTF_Font* kucukYazi = nullptr;

        SDL_Color ak = {0xFF,0xFF,0xFF,0xFF};
        SDL_Color kizil = {0xFF,0x00,0x00,0xFF};

        SDL_Rect sesSeviyesi[8];

        const int EKRAN_GENISLIK1 = 640;
        const int EKRAN_YUKSEKLIK1 = 480;
        bool gecilmeDurumu = true;
        bool tusBirakilmaDurumu = true;
        std::string dilSecenegi = "Türkçe";
        int imlecX, imlecY;
        public:
        int8_t imlecSirasi = 1, sesDuzeyiSirasi[2] = {4,4};
};

#endif // SECENEKLER_MENU_HPP
