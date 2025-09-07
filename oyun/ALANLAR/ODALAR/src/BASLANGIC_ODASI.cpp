#include "BASLANGIC_ODASI.hpp"

BASLANGIC_ODASI::BASLANGIC_ODASI(SDL_Renderer* renderer, uint8_t kayit_dosyasi_hangi)
{
    hangiKayıtDosyası = kayit_dosyasi_hangi;
    isleyici = nullptr;
    isleyici = renderer;
    yazilar = new Yazi[YAZİ_TAM_DİZELGE_BOYUTU];
    dokular = new Doku[DOKU_TAM_DİZELGE_BOYUTU];
    fontlar[0] = TTF_OpenFont("VARLIKLAR/TTF/Poco.ttf",28);
    fontlar[1] = TTF_OpenFont("VARLIKLAR/TTF/Poco.ttf",56);
    fontlar[2] = TTF_OpenFont("VARLIKLAR/TTF/Poco.ttf",112);
    fontlar[3] = TTF_OpenFont("VARLIKLAR/TTF/custom.ttf",28);
    fontlar[4] = TTF_OpenFont("VARLIKLAR/TTF/custom.ttf",56);
    fontlar[5] = TTF_OpenFont("VARLIKLAR/TTF/custom.ttf",112);
    for(int i = 0; i < 3; ++i)
    {
        if(fontlar[i] == NULL)
        {
            std::cerr << "HATA: Font konumları bulunamadı... Arandığı konum:\n\"VARLIKLAR/TTF/custom.ttf|Poco.ttf\"\n";
        }
    }
    gecilmeDurumu = true;
    ayarDos.open("DOSYALAR/ayar.json");
    if(!ayarDos.is_open())
    {
        std::cerr << "Dosya açılamadı... Dosyanın arandığı konum: \"DOSYALAR/ayar.json\"\n";
    }
    else
    {
        ayarDos.seekg(0,std::ios::end);
        if(ayarDos.tellg() == 0)
        {
            std::cout << "Dosya boş" << std::endl;
            #if defined(_WIN64)
            system("type nul > DOSYALAR/ayarlar.json");
            #endif // _WIN64
            #if defined(__linux__) || defined(linux) || defined( __linux)
            system("touch DOSYALAR/ayarlar.json");
            #endif // __linux__
            #if defined(__APPLE__)
            system("touch DOSYALAR/ayarlar.json");
            #endif // __APPLE__
            ayarJson["dil"] = "Türkçe";
            ayarJson["ses1"] = 4;
            ayarJson["ses2"] = 4;
            ayarDos.seekg(0,std::ios::beg);
        }
        else
        {
            ayarDos.seekg(0,std::ios::beg);
            ayarDos >> ayarJson;
            dilDos[0].open("DOSYALAR/turkce.json");
            dilDos[0] >> dilJson[0];
            dilDos[1].open("DOSYALAR/english.json");
            dilDos[1] >> dilJson[1];
            dilDos[2].open("DOSYALAR/custom.json");
            dilDos[2] >> dilJson[2];
            for(int i; i < 3; ++i)
            {
                if(!dilDos[i].is_open())
                {
                    #ifdef DEBUG
                    std::cerr << i << " sayılı dosya açılamadı...\nDosya sayıları sırası ile \n0 = turkce.json, 1 = english.json, 2 = custom.json\n";
                    #endif // DEBUG
                    #ifdef NDEBUG
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "File Err: Dosya bulunamadı...",std::string(std::to_string(i)+" sayılı dosya açılamadı...\nDosya sayıları sırası ile \n0 = turkce.json, 1 = english.json, 2 = custom.json\n").c_str(),NULL);
                    #endif // NDEBUG
                }
            }
            ödleyici.Reset();

        }
        ayarKayit.open("DOSYALAR/ayarlar.json");
        #ifdef DEBUG
        if(!ayarKayit.is_open())
        {
            std::cerr << "Kayıt işlemi yapılamamakta!\n";
        }
        #endif // DEBUG
        else
        {
            ayarKayit.seekp(0,std::ios::beg);
            ayarKayit << std::flush;
            ayarKayit.seekp(0,std::ios::beg);
            ayarKayit << ayarJson.dump(4);
        }
    }
}

BASLANGIC_ODASI::~BASLANGIC_ODASI()
{
    kapat();
}

void BASLANGIC_ODASI::kapat(void)
{
    delete[] yazilar;
    delete[] dokular;
    yazilar = nullptr;
    dokular = nullptr;
    ayarDos.close();
    for(int i = 0; i < 3; ++i)
        dilDos[i].close();
    SDL_DestroyRenderer(isleyici);
    isleyici = NULL;
    ayarKayit.close();
}

void BASLANGIC_ODASI::dilDegisimi()
{
    if(ayarJson["dil"] == "Türkçe")
    {
        yazilar[ACIKLAMA_TUMCESI_01].kapat();
        yazilar[ACIKLAMA_TUMCESI_02].kapat();
        yazilar[ACIKLAMA_TUMCESI_03].kapat();
        yazilar[ACIKLAMA_TUMCESI_04].kapat();

        yazilar[ACIKLAMA_TUMCESI_01].yaziOlustur(isleyici,fontlar[0],dilJson[0]["oyun_açıklama_tümcesi_1"],ak);
        yazilar[ACIKLAMA_TUMCESI_02].yaziOlustur(isleyici,fontlar[0],dilJson[0]["oyun_açıklama_tümcesi_2"],ak);
        yazilar[ACIKLAMA_TUMCESI_03].yaziOlustur(isleyici,fontlar[0],dilJson[0]["oyun_açıklama_tümcesi_3"],ak);
        yazilar[ACIKLAMA_TUMCESI_04].yaziOlustur(isleyici,fontlar[0],dilJson[0]["oyun_açıklama_tümcesi_4"],ak);
    }
    else if(ayarJson["dil"] == "English")
    {
        yazilar[ACIKLAMA_TUMCESI_01].kapat();
        yazilar[ACIKLAMA_TUMCESI_02].kapat();
        yazilar[ACIKLAMA_TUMCESI_03].kapat();
        yazilar[ACIKLAMA_TUMCESI_04].kapat();

        yazilar[ACIKLAMA_TUMCESI_01].yaziOlustur(isleyici,fontlar[0],dilJson[1]["oyun_açıklama_tümcesi_1"],ak);
        yazilar[ACIKLAMA_TUMCESI_02].yaziOlustur(isleyici,fontlar[0],dilJson[1]["oyun_açıklama_tümcesi_2"],ak);
        yazilar[ACIKLAMA_TUMCESI_03].yaziOlustur(isleyici,fontlar[0],dilJson[1]["oyun_açıklama_tümcesi_3"],ak);
        yazilar[ACIKLAMA_TUMCESI_04].yaziOlustur(isleyici,fontlar[0],dilJson[1]["oyun_açıklama_tümcesi_4"],ak);
    }
    else
    {
        yazilar[ACIKLAMA_TUMCESI_01].kapat();
        yazilar[ACIKLAMA_TUMCESI_02].kapat();
        yazilar[ACIKLAMA_TUMCESI_03].kapat();
        yazilar[ACIKLAMA_TUMCESI_04].kapat();
//font 3 çevrilecek
        yazilar[ACIKLAMA_TUMCESI_01].yaziOlustur(isleyici,fontlar[0],dilJson[2]["oyun_açıklama_tümcesi_1"],ak);
        yazilar[ACIKLAMA_TUMCESI_02].yaziOlustur(isleyici,fontlar[0],dilJson[2]["oyun_açıklama_tümcesi_2"],ak);
        yazilar[ACIKLAMA_TUMCESI_03].yaziOlustur(isleyici,fontlar[0],dilJson[2]["oyun_açıklama_tümcesi_3"],ak);
        yazilar[ACIKLAMA_TUMCESI_04].yaziOlustur(isleyici,fontlar[0],dilJson[2]["oyun_açıklama_tümcesi_4"],ak);
    }
    return;
}
