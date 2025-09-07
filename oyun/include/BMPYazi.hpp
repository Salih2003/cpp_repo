#ifndef BMPYAZI_HPP
#define BMPYAZI_HPP

#include "basliklar.hpp"

class BMPYazi
{
    public:
        BMPYazi(SDL_Renderer* isleyici,std::string BMPFontYolu, std::map<std::string, int> tablo, std::string yazi, uint8_t hucreW, uint8_t hucreH);
        BMPYazi();
        BMPYazi(const BMPYazi& yazi);
        BMPYazi& operator=(const BMPYazi& yazi);
        ~BMPYazi();

        bool yaziOlustur(SDL_Renderer* isleyici,std::string BMPFontYolu, std::map<std::string, int> tablo, std::string yazi, uint8_t hucreW, uint8_t hucreH);
        bool yaziOlustur(std::string BMPFontYolu, std::map<std::string, int> tablo, std::string yazi, uint8_t hucreW, uint8_t hucreH);
        bool yaziOlustur(std::string yazi = "");

        void yaziBoyasiDegistir(Uint8 r, Uint8 g, Uint8 b);
        void yaziBoyasiDegistir(SDL_Color boya);

        void konumAyarla(int _x, int _y){x = _x;y = _y;}

        void ciz();

    protected:

    private:

        void kapat(void);

        int x,y,w,h;
        uint8_t hucreW = 10, hucreH = 10;

        std::string BMPFontYolu;
        std::map <std::string,int> tanimlamaTablosu;

        SDL_Renderer* isleyici;
        SDL_Texture* doku;
        SDL_Rect karakterDortgenleri[2048];
};

#endif // BMPYAZI_HPP
