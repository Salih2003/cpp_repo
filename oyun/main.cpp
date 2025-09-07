#include <locale.h>
bool cikis = false;
#include "ALANLAR/ana_menu.hpp"
#include "ALANLAR/secenekler_menu.hpp"
#include "ALANLAR/kayit_secim.hpp"

#include <streambuf>
#include <string>



class SDLLogStreamBuf : public std::streambuf {
public:
    SDLLogStreamBuf(SDL_LogPriority priority = SDL_LOG_PRIORITY_INFO)
        : logPriority(priority) {}

protected:
    int overflow(int ch) override {
        if (ch == EOF)
            return ch;

        char c = static_cast<char>(ch);
        buffer += c;

        if (c == '\n') {
            flushBuffer();
        }

        return ch;
    }

    int sync() override {
        flushBuffer();
        return 0;
    }

private:
    std::string buffer;
    SDL_LogPriority logPriority;

    void flushBuffer() {
        if (!buffer.empty()) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, logPriority, "%s", buffer.c_str());
            buffer.clear();
        }
    }
};



const int EKRAN_GENISLIK = 640;
const int EKRAN_YUKSEKLIK = 480;
int8_t tamEkranSayac = 0;
Uint32 fps;
#define KARE_ODU 1000 / 60
genelAyar ayar;
ANA_MENU ana_menu;
SECENEKLER_MENU sec_menu;
KAYIT_SECIM kayit_menu;

int main( int argc, char * argv[] )
{

    setlocale(LC_ALL, "Turkish");

SDLLogStreamBuf coutBuf(SDL_LOG_PRIORITY_INFO);
SDLLogStreamBuf cerrBuf(SDL_LOG_PRIORITY_ERROR);

// Yedekler
auto* oldCoutBuf = std::cout.rdbuf(&coutBuf);
auto* oldCerrBuf = std::cerr.rdbuf(&cerrBuf);

    ayar.giris("DENEME, PROJESİ",EKRAN_GENISLIK,EKRAN_YUKSEKLIK);
    ana_menu.tanimlamalar(ayar.isleyiciAl());
    sec_menu.tanimlamalar(ayar.isleyiciAl());
    kayit_menu.tanimlamalar(ayar.isleyiciAl(),&ayar.pencereBilgisi);
    //std::cout << "Ekranın genişlik: " << ayar.pencereBilgisi.ekranGenişliği << std::endl << "Ekranın yükseklik: " << ayar.pencereBilgisi.ekranYüksekliği << std::endl << "Pencere Standart Genişlik: " << ayar.pencereBilgisi.temelPencereGenişlik << std::endl <<  "Pencere Standart Yükseklik: " << ayar.pencereBilgisi.temelPencereYükseklik << std::endl;
    //std::cout << "OranlarGY: " << ayar.pencereBilgisi.pencereEkranGenişlikOranı << " " << ayar.pencereBilgisi.pencereEkranYükseklikOranı << std::endl;
    Uint32 kareBasla, kareÖdü;
    static int frameCount = 0;
    static Uint32 lastTime = 0;

    while(cikis == false)
    {   kareBasla = SDL_GetTicks();
        SDL_Event olay;
        while(SDL_PollEvent(&olay) != 0)
        {
            if((olay.type == SDL_QUIT) || (olay.type == SDL_KEYDOWN && olay.key.keysym.sym == SDLK_ESCAPE))
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
                    #ifdef NDEBUG
                    SDL_ShowCursor(SDL_DISABLE);
                    #endif // NDEBUG
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
        fps = currentTime - lastTime;
        if (fps >= 1000)
        { // Her bir saniyede FPS hesapla
            //std::printf("FPS: %d\n", frameCount);

            frameCount = 0;
            lastTime = currentTime;
        }

        kareÖdü = SDL_GetTicks() - kareBasla;
        if (KARE_ODU > kareÖdü) {
            SDL_Delay(KARE_ODU - kareÖdü);
            //std::cout << KARE_ODU - kareÖdü << std::endl;
        }
    }
    çıkışYeri:

    std::cout.rdbuf(oldCoutBuf);
    std::cerr.rdbuf(oldCerrBuf);
    return 0;
}
