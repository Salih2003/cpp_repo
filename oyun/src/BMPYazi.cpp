#include "BMPYazi.hpp"

BMPYazi::BMPYazi(SDL_Renderer* isleyici,std::string BMPFontYolu, std::map<std::string, int> tablo, std::string yazi, uint8_t hucreW, uint8_t hucreH)
{
    this->isleyici = isleyici;
    this->hucreW = hucreW;
    this->hucreH = hucreH;
    SDL_Surface* yuzey = IMG_Load(yazi.c_str());
    SDL_Texture* yeniDoku = SDL_CreateTextureFromSurface(this->isleyici,yuzey);
    if(yeniDoku == NULL)
    {
        std::cerr << "BMPYazı boş kaldı. ERR: " << SDL_GetError() << std::endl;
    }
    else
    {
        SDL_FreeSurface(yuzey);
        yuzey = NULL;

    }
}

BMPYazi::BMPYazi()
{

}

BMPYazi::BMPYazi(const BMPYazi& yazi)
{

}

BMPYazi& BMPYazi::operator=(const BMPYazi& yazi)
{

}

BMPYazi::~BMPYazi()
{
    kapat();
}

void BMPYazi::kapat(void)
{
    x = 0, y = 0, w = 0, h = 0;
    SDL_DestroyTexture(doku);
    doku = NULL;
    SDL_DestroyRenderer(isleyici);
    isleyici = NULL;
    return;
}

bool BMPYazi::yaziOlustur(SDL_Renderer* isleyici,std::string BMPFontYolu, std::map<std::string, int> tablo, std::string yazi, uint8_t hucreW, uint8_t hucreH)
{
    return true;
}

bool BMPYazi::yaziOlustur(std::string BMPFontYolu, std::map<std::string, int> tablo, std::string yazi, uint8_t hucreW, uint8_t hucreH)
{
    return true;
}

bool BMPYazi::yaziOlustur(std::string yazi)
{
    return true;
}
