#include "genelAyar.hpp"

bool genelAyar::giris(string ad, int genislik = 640, int yukseklik = 480)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "SDL VIDEO altyapısı çalışmadı HATA: " << SDL_GetError() << endl;
        basarili = false;
    }
    else
    {
        if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            cerr << "IMG PNG başarısız HATA: " << IMG_GetError() << endl;
            basarili = false;
        }
        else
        {
            TTF_Init();
            cout << "Alt yapılar hazır!!!!!!!!!!!!!!!!!!!" << endl;
            EKRAN_GENISLIK = genislik;
            EKRAN_YUKSEKLIK = yukseklik;
            pencere = SDL_CreateWindow(ad.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,EKRAN_GENISLIK,EKRAN_YUKSEKLIK,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            if(pencere == nullptr)
            {
                cerr << "Pencere oluşumu başarısız HATA: " << SDL_GetError() << endl;
                basarili = false;
            }
            else
            {
                gorsellestirici = SDL_CreateRenderer(pencere,-1,SDL_RENDERER_ACCELERATED);
                if(gorsellestirici == nullptr)
                {
                    cerr << "İşleyici çalışmaz HATA: " << SDL_GetError() << endl;
                    basarili = false;
                }
                else
                {
                    cout << "Pencere kullanıma hazır!!!!!!!!!!!" << endl;

                }
            }
        }
    }
SDL_RenderSetLogicalSize(gorsellestirici,640,480);
//    SDL_GetCurrentDisplayMode(0,&mod);
//    pencereBilgisi.ekranGenişliği = mod.w;
//    pencereBilgisi.ekranYüksekliği = mod.h;
    pencereBilgisi.temelPencereGenişlik = EKRAN_GENISLIK;
    pencereBilgisi.temelPencereYükseklik = EKRAN_YUKSEKLIK;
//    pencereBilgisi.pencereEkranGenişlikOranı = (double)pencereBilgisi.ekranGenişliği / pencereBilgisi.temelPencereGenişlik;
//    pencereBilgisi.pencereEkranYükseklikOranı = (double)pencereBilgisi.ekranYüksekliği / pencereBilgisi.temelPencereYükseklik;
    pencereBilgisi.ekranBayrağı = SDL_GetWindowFlags(pencere);
//    mod.w = EKRAN_GENISLIK;
//    mod.h = EKRAN_YUKSEKLIK;
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
    SDL_RenderPresent(gorsellestirici);pencereBilgisi.ekranBayrağı = SDL_GetWindowFlags(pencere);
}

void genelAyar::ekranRengiAyarla(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(gorsellestirici,r,g,b,0xFF);
}

SDL_DisplayMode *genelAyar::ekranModuAl()
{
    return &mod;
}
