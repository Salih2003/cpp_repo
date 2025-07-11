#include "Yazi.hpp"

bool Yazi::yaziOlustur(SDL_Renderer* isleyici,TTF_Font* font,const char* yazi,SDL_Color renk)
{
    SDL_DestroyTexture(doku);
    doku = nullptr;
    this->font = font;
    SDL_Surface* olusanYuzey = TTF_RenderUTF8_Solid(font,yazi,renk);
    if(olusanYuzey == nullptr)
    {
        std::cerr << "Yüzey sıkıntılı HATA: " << TTF_GetError() << std::endl;
    }
    SDL_Texture* yeniDoku = SDL_CreateTextureFromSurface(isleyici,olusanYuzey);
    if(yeniDoku == nullptr)
    {
        std::cerr << "Yazı oluşmadı HATA: " << TTF_GetError() << std::endl;
        basarili = false;
    }
    w = olusanYuzey->w;
    h = olusanYuzey->h;
    SDL_FreeSurface(olusanYuzey);
    olusanYuzey = nullptr;
    doku = yeniDoku;
    if(doku == nullptr)
        std::cerr << "hata " << SDL_GetError() << std::endl;
    return basarili;
}

bool Yazi::yaziOlustur(SDL_Renderer* isleyici,TTF_Font* font,std::string yazi,SDL_Color renk)
{
    SDL_DestroyTexture(doku);
    doku = nullptr;
    this->font = font;
    SDL_Surface* olusanYuzey = TTF_RenderUTF8_Solid(font,yazi.c_str(),renk);
    if(olusanYuzey == nullptr)
    {
        std::cerr << "Yüzey sıkıntılı HATA: " << TTF_GetError() << std::endl;
    }
    SDL_Texture* yeniDoku = SDL_CreateTextureFromSurface(isleyici,olusanYuzey);
    if(yeniDoku == nullptr)
    {
        std::cerr << "Yazı oluşmadı HATA: " << TTF_GetError() << std::endl;
        basarili = false;
    }
    w = olusanYuzey->w;
    h = olusanYuzey->h;
    SDL_FreeSurface(olusanYuzey);
    olusanYuzey = nullptr;
    doku = yeniDoku;
    if(doku == nullptr)
        std::cerr << "hata " << SDL_GetError() << std::endl;
    return basarili;
}

Yazi::~Yazi()
{
    SDL_DestroyTexture(doku);
    doku = nullptr;
}

void Yazi::ciz(SDL_Renderer* isleyici,int x, int y)
{
    this->x = x;
    this->y = y;
    SDL_Rect kare = {this->x,this->y,w,h};
    SDL_RenderCopy(isleyici,doku,nullptr,&kare);
}

void Yazi::renkMod(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(doku,r,g,b);
    return;
}

void Yazi::kapat(void)
{
    SDL_DestroyTexture(doku);
    doku = nullptr;
}
