#ifndef GENELAYAR_HPP
#define GENELAYAR_HPP

#include "basliklar.hpp"

using namespace std;
class genelAyar
{
    public:
        bool giris(string ad,int genislik, int yukseklik);
        void ekranYenile();
        void ekranTemizle();
        SDL_Renderer* isleyiciAl();
        int ekranGenislikAl(void);
        int ekranYukseklikAl(void);
        void ekranRengiAyarla(Uint8 r, Uint8 g, Uint8 b);
        ~genelAyar();
        void tamEkran(int karar)
        {
            SDL_GetCurrentDisplayMode(0,&mod);
            if(karar == 1)
            {
                SDL_SetWindowSize(pencere,mod.w,mod.h);
                SDL_SetWindowFullscreen(pencere,SDL_WINDOW_FULLSCREEN);
            }
            if(karar == 0)
            {
                SDL_SetWindowSize(pencere,EKRAN_GENISLIK,EKRAN_YUKSEKLIK);
                SDL_SetWindowFullscreen(pencere,SDL_WINDOW_SHOWN);
                mod.w = EKRAN_GENISLIK;
                mod.h = EKRAN_YUKSEKLIK;
            }
        }
        SDL_DisplayMode *ekranModuAl();
        //pencereBilgi *pencBilgiDöndür(){return *pencereBilgisi;};
        pencereBilgi pencereBilgisi;
    protected:

    private:
        SDL_Window* pencere = nullptr;
        SDL_Renderer* gorsellestirici = nullptr;
        int EKRAN_YUKSEKLIK = 640, EKRAN_GENISLIK = 480;
        bool basarili = true;
        SDL_DisplayMode mod;
};


#endif // GENELAYAR_HPP
