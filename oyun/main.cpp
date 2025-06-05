#include <locale.h>
bool cikis = false;
#include "ALANLAR/ana_menu.hpp"
#include "ALANLAR/secenekler_menu.hpp"
#include "ALANLAR/kayit_secim.hpp"

const int EKRAN_GENISLIK = 640;
const int EKRAN_YUKSEKLIK = 480;
int8_t tamEkranSayac = 0;
#define KARE_ODU 1000 / 60
genelAyar ayar;
ANA_MENU ana_menu;
SECENEKLER_MENU sec_menu;
KAYIT_SECIM kayit_menu;
int main( int argc, char * argv[] )
{

    setlocale(LC_ALL, "Turkish");

    ayar.giris("DENEME, PROJESİ",EKRAN_GENISLIK,EKRAN_YUKSEKLIK);
    ana_menu.tanimlamalar(ayar.isleyiciAl());
    sec_menu.tanimlamalar(ayar.isleyiciAl());
    kayit_menu.tanimlamalar(ayar.isleyiciAl());

    Uint32 kareBasla, kareÖdü;
    static int frameCount = 0;
    static Uint32 lastTime = 0;

    while(cikis == false)
    {   kareBasla = SDL_GetTicks();
        SDL_Event olay;
        while(SDL_PollEvent(&olay) != 0)
        {
            if(olay.type == SDL_QUIT || olay.type == SDL_KEYDOWN && olay.key.keysym.sym == SDLK_ESCAPE)
            {
                kapanis:
                std::cout << "Program Kapatıldı :D" << std::endl;
                ana_menu.kapat();
                sec_menu.kapat();
                kayit_menu.kapat();
                cikis = true;
                goto çıkışYeri;
            }

            ///tam ekrana geçiş olayı yakalama
            if(olay.type == SDL_KEYDOWN && olay.key.keysym.sym == SDLK_F4)
            {
                if(tamEkranSayac % 2 == 0)
                {
                    ayar.tamEkran(1);
                    SDL_ShowCursor(SDL_DISABLE);
                    tamEkranSayac++;
                }
                else
                {
                    ayar.tamEkran(0);
                    SDL_ShowCursor(SDL_ENABLE);
                    tamEkranSayac++;
                }
            }

            if(!sec_menu.gecilmeDurumunuVer())
            {
                uint8_t sonuc = sec_menu.olayIsleyici(&olay);
                if(sonuc == 2)
                {
                    sec_menu.gecilmeDurumunuAyarla(true);
                    ana_menu.gecilmeDurumunuAyarla(false);
                }
            }
            if(!kayit_menu.gecilmeDurumuVer())
            {
                uint8_t sonuc = kayit_menu.olaylar(&olay);
                //std::cout << "kayit olay sonuc: " << sonuc << std::endl;
                if(sonuc == 2)
                {
                    ana_menu.gecilmeDurumunuAyarla(false);
                }
            }

        }

            if(!ana_menu.gecilmeDurumunuVer())
            {
                switch(ana_menu.olayYonetimi())
                {
                    case 0:
                        kayit_menu.gecilmeDurumuAyarla(false);
                        break;
                    case 1:
                        sec_menu.gecilmeDurumunuAyarla(false);
                        break;
                    case 2:
                        cikis = true;
                        goto kapanis;
                        break;

                }
            }

        ayar.ekranRengiAyarla(0,0,0);
        ayar.ekranTemizle();
        if(!cikis)
        {
            if(!ana_menu.gecilmeDurumunuVer())
            {
                ana_menu.ciz(ayar.isleyiciAl());
                sec_menu.imlecSirasi = 1;
                kayit_menu.siraSifirla();
            }
            if(!sec_menu.gecilmeDurumunuVer())
                sec_menu.ciz(ayar.isleyiciAl());
            if(!kayit_menu.gecilmeDurumuVer())
                kayit_menu.ciz();
        }
        ayar.ekranYenile();

        frameCount++;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= 1000)
        { // Her bir saniyede FPS hesapla
            std::printf("FPS: %d\n", frameCount);

            frameCount = 0;
            lastTime = currentTime;
        }

        kareÖdü = SDL_GetTicks() - kareBasla;
        if (KARE_ODU > kareÖdü) {
            SDL_Delay(KARE_ODU - kareÖdü);
            //std::cout << KARE_ODU - kareOdu << std::endl;
        }
    }
    çıkışYeri:


    return 0;
}
