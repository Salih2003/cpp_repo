#include "genelAyar.hpp"

bool genelAyar::giris(string ad, int genislik, int yukseklik)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "SDL VIDEO altyap�s� �al��mad� HATA: " << SDL_GetError() << endl;
        basarili = false;
    }
    else
    {
        if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            cerr << "IMG PNG ba�ar�s�z HATA: " << IMG_GetError() << endl;
            basarili = false;
        }
        else
        {
            TTF_Init();
            cout << "Alt yap�lar haz�r!!!!!!!!!!!!!!!!!!!" << endl;
            EKRAN_GENISLIK = genislik;
            EKRAN_YUKSEKLIK = yukseklik;
            pencere = SDL_CreateWindow(ad.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,EKRAN_GENISLIK,EKRAN_YUKSEKLIK,SDL_WINDOW_SHOWN);
            if(pencere == nullptr)
            {
                cerr << "Pencere olu�umu ba�ar�s�z HATA: " << SDL_GetError() << endl;
                basarili = false;
            }
            else
            {
                gorsellestirici = SDL_CreateRenderer(pencere,-1,SDL_RENDERER_ACCELERATED);
                if(gorsellestirici == nullptr)
                {
                    cerr << "��leyici �al��maz HATA: " << SDL_GetError() << endl;
                    basarili = false;
                }
                else
                {
                    cout << "Pencere kullan�ma haz�r!!!!!!!!!!!" << endl;

                }
            }
        }
    }
    return basarili;
}

genelAyar::~genelAyar()
{
    SDL_DestroyWindow(pencere);
    pencere = nullptr;
    SDL_DestroyRenderer(gorsellestirici);
    gorsellestirici = nullptr;
    SDL_Quit();
    IMG_Quit();
}

SDL_Renderer* genelAyar::isleyiciAl()
{
    return gorsellestirici;
}

int genelAyar::ekranGenislikAl(void)
{
    return EKRAN_GENISLIK;
}

int genelAyar::ekranYukseklikAl(void)
{
    return EKRAN_YUKSEKLIK;
}

void genelAyar::ekranTemizle()
{
    SDL_RenderClear(gorsellestirici);
}

void genelAyar::ekranYenile()
{
    SDL_RenderPresent(gorsellestirici);
}

void genelAyar::ekranRengiAyarla(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(gorsellestirici,r,g,b,0xFF);
}
