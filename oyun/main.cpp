#include <locale.h>
bool cikis = false;
#include "ALANLAR/ana_menu.hpp"
#include "ALANLAR/secenekler_menu.hpp"
#include "ALANLAR/kayit_secim.hpp"
const int EKRAN_GENISLIK = 640;
const int EKRAN_YUKSEKLIK = 480;
int8_t tamEkranSayac = 0;
genelAyar ayar;
ANA_MENU menu;
SECENEKLER_MENU s_menu;
KAYIT_SECIM kayit;
int main( int argc, char * argv[] )
{
    setlocale(LC_ALL, "Turkish");
    ayar.giris("DENEME PROJESİ",EKRAN_GENISLIK,EKRAN_YUKSEKLIK);
    menu.tanimlamalar(ayar.isleyiciAl());
    s_menu.tanimlamalar(ayar.isleyiciAl());
    kayit.tanimlamalar(ayar.isleyiciAl());
    while(cikis == false)
    {
        SDL_Event olay;
        while(SDL_PollEvent(&olay) != 0)
        {
            if(olay.type == SDL_QUIT || olay.type == SDL_KEYDOWN && olay.key.keysym.sym == SDLK_ESCAPE)
            {
                cikis = true;
                menu.kapat();
                s_menu.kapat();
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
            ///tam ekrana geçiş olayı yakalama sonu
            if(!s_menu.gecilmeDurumunuVer())
            {
                if(s_menu.olayIsleyici(&olay) == 2)
                {
                    s_menu.gecilmeDurumunuAyarla(true);
                    menu.gecilmeDurumunuAyarla(false);
                }
            }
        }

        ///menu olay kontrol başlangıcı
        if(!menu.gecilmeDurumunuVer())
        {
            switch(menu.olayYonetimi())
            {
                case 0:
                    kayit.gecilmeDurumuAyarla(false);
                    break;
                case 1:
                    s_menu.gecilmeDurumunuAyarla(false);
                    break;
                case 2:
                    cikis = true;
                    break;
            }
        }

        ///menu olay kontrol sonu!
        if(cikis == false)
        {
        ayar.ekranRengiAyarla(0x00,0x00,0x00);
        ayar.ekranTemizle();
        ///render baslangic
        if(menu.gecilmeDurumunuVer() == false)
        {
            menu.ciz(ayar.isleyiciAl());
            s_menu.imlecSirasi = 1;
        }
        if(s_menu.gecilmeDurumunuVer() == false)
        {
            s_menu.ciz(ayar.isleyiciAl());
        }
        if(kayit.gecilmeDurumuVer() == false)
        {
            kayit.ciz();
        }
        ///render son
        ayar.ekranYenile();
        }
    }

    return 0;
}
