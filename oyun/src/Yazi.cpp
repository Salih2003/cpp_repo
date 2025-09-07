#include "Yazi.hpp"

bool Yazi::yaziOlustur(SDL_Renderer* isleyici, TTF_Font* font, const char* yazi, SDL_Color renk)
{
    return yaziOlustur(isleyici, font, std::string(yazi), renk);
}

bool Yazi::yaziOlustur(SDL_Renderer* isleyici, TTF_Font* font, std::string yazi, SDL_Color renk)
{
    kapat();  // varsa eski verileri temizle

    this->font = font;
    basarili = true;

    std::stringstream ss(yazi);
    std::string satir;
    while (std::getline(ss, satir, '\n'))
    {
        SDL_Surface* olusanYuzey = TTF_RenderUTF8_Solid(font, satir.c_str(), renk);
        if (olusanYuzey == nullptr)
        {
            std::cerr << "Yüzey oluşturulamadı! HATA: " << TTF_GetError() << std::endl;
            basarili = false;
            continue;
        }

        SDL_Texture* yeniDoku = SDL_CreateTextureFromSurface(isleyici, olusanYuzey);
        if (yeniDoku == nullptr)
        {
            std::cerr << "Doku oluşturulamadı! HATA: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(olusanYuzey);
            basarili = false;
            continue;
        }

        dokuListesi.push_back(yeniDoku);
        yukseklikListesi.push_back(olusanYuzey->h);

        SDL_FreeSurface(olusanYuzey);
    }

    return basarili;
}

Yazi::~Yazi()
{
    SDL_DestroyTexture(doku);
    doku = nullptr;
}

void Yazi::ciz(SDL_Renderer* isleyici, int x, int y)
{
    int yOffset = y;
    for (size_t i = 0; i < dokuListesi.size(); ++i)
    {
        int w = 0, h = 0;
        SDL_QueryTexture(dokuListesi[i], nullptr, nullptr, &w, &h);
        SDL_Rect hedef = {x, yOffset, w, h};
        SDL_RenderCopy(isleyici, dokuListesi[i], nullptr, &hedef);
        yOffset += yukseklikListesi[i];
    }
}

void Yazi::renkMod(Uint8 r, Uint8 g, Uint8 b)
{
    for (auto& doku : dokuListesi)
    {
        if (doku)
            SDL_SetTextureColorMod(doku, r, g, b);
    }
}

void Yazi::kapat(void)
{
    for (auto& doku : dokuListesi)
    {
        if (doku)
        {
            SDL_DestroyTexture(doku);
            doku = nullptr;
        }
    }
    dokuListesi.clear();
    yukseklikListesi.clear();
}
