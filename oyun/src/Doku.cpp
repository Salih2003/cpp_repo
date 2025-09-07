#include "Doku.hpp"

//Doku::Doku()
//{
//    //ctor
//}

Doku::~Doku()
{
    SDL_DestroyTexture(doku);
    doku = nullptr;
}

void Doku::boyutAl(int w, int h)
{
    w = this->w;
    h = this->h;
}

void Doku::konumAl(int x, int y)
{
    x = this->x;
    y = this->y;
}
//sorunlu olabilir ^
void Doku::ciz(SDL_Renderer* isleyici,int x, int y)
{
    this->x = x;
    this->y = y;
    SDL_Rect kare = {this->x,this->y,w,h};
    SDL_RenderCopy(isleyici,doku,nullptr,&kare);
}

void Doku::ciz(SDL_Renderer* isleyici,int x, int y,int w,int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    SDL_Rect kare = {this->x,this->y,this->w,this->h};
    SDL_RenderCopy(isleyici,doku,nullptr,&kare);
}

void Doku::dokuYukle(SDL_Renderer* isleyici,const char* dosyaAdi)
{
    SDL_DestroyTexture(doku);
    doku = nullptr;
    SDL_Surface* yuklenenYuzey = IMG_Load(dosyaAdi);
    w = yuklenenYuzey->w;
    h = yuklenenYuzey->h;
    SDL_Texture* yeniDoku = SDL_CreateTextureFromSurface(isleyici,yuklenenYuzey);
    if(yeniDoku == NULL)
        std::cerr << "Doku oluşmadı HATA: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(yuklenenYuzey);
    yuklenenYuzey = nullptr;
    doku = yeniDoku;
}

void Doku::renkAyarla(Uint8 r,Uint8 g,Uint8 b)
{
    SDL_SetTextureColorMod(doku,r,g,b);
}
