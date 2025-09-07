#ifndef BASLANGIC_ODASI_HPP
#define BASLANGIC_ODASI_HPP

#include "../../alan_basliklar.hpp"

class BASLANGIC_ODASI
{
    public:
        BASLANGIC_ODASI(SDL_Renderer* renderer, uint8_t kayit_dosyasi_hangi);
        ~BASLANGIC_ODASI();

        bool başlat();
        void kapat(void);

        void gecilmeDurumuAyarla(bool durum);
        bool gecilmeDurumuVer();

        uint8_t olayİsleyici(const SDL_Event& event);
        void ciz();

    private:
        bool gecilmeDurumu = true;
        uint8_t hangiKayıtDosyası;
        long long int gecenSureMiliSaniye;

        b2Timer ödleyici;
        b2Timer YaziÖdleyici;

        Yazi* yazilar = new Yazi[YAZİ_TAM_DİZELGE_BOYUTU];
        Doku* dokular = new Doku[DOKU_TAM_DİZELGE_BOYUTU];

        TTF_Font* fontlar[6];
        SDL_Renderer* isleyici;

        std::string kayıtStringi;
        std::ifstream ayarDos;
        std::ofstream ayarKayit;
        std::ifstream dilDos[3];

        json dilJson[3];
        json ayarJson;
        json kayitJSONlari[3];
    private:
        enum YaziDizelgesi
        {
            ACIKLAMA_TUMCESI_01,
            ACIKLAMA_TUMCESI_02,
            ACIKLAMA_TUMCESI_03,
            ACIKLAMA_TUMCESI_04,
            YAZİ_TAM_DİZELGE_BOYUTU
        };
        enum DokuDizelgesi
        {
            DOKU_TAM_DİZELGE_BOYUTU
        };
        void dilDegisimi();
        SDL_Color ak = {255,255,255,255};
        SDL_Color kızıl = {255,0,0,255};
        SDL_Color gökçe = {0x00,0x00,0xFF,0xFF};
};

#endif // BASLANGIC_ODASI_HPP
