#include "kilitle.hpp"

using namespace CryptoPP;

kilitle::kilitle(const SecByteBlock& aesKey, const SecByteBlock& hmacKey)
    : aesKey_(aesKey), hmacKey_(hmacKey)
    {
        if (aesKey.size() == 0 || aesKey.BytePtr() == nullptr ||
    hmacKey.size() == 0 || hmacKey.BytePtr() == nullptr) {
    throw std::invalid_argument("Anahtarlar boş ya da null olamaz.");
}

    }

// Yeni kurucu metot
kilitle::kilitle(const std::string& keyFilePath) {
    aesKey_.resize(AES::DEFAULT_KEYLENGTH);
    hmacKey_.resize(SHA256::DIGESTSIZE);

    if (LoadKeysFromFile(keyFilePath)) {
        std::cout << "Anahtarlar dosyadan başarıyla okundu." << std::endl;
    } else {
        std::cerr << "Anahtar dosyası bulunamadı. Yeni anahtarlar oluşturuluyor..." << std::endl;
        AutoSeededRandomPool prng;
        prng.GenerateBlock(aesKey_, aesKey_.size());
        prng.GenerateBlock(hmacKey_, hmacKey_.size());
        SaveKeysToFile(keyFilePath);
        std::cout << "Yeni anahtarlar oluşturuldu ve kaydedildi." << std::endl;
    }
}

void kilitle::GenerateIV(SecByteBlock& iv) {

//       const byte fixedIV[CryptoPP::AES::BLOCKSIZE] = {
//        0x00, 0x01, 0x02, 0x03,
//        0x04, 0x05, 0x06, 0x07,
//        0x08, 0x09, 0x0A, 0x0B,
//        0x0C, 0x0D, 0x0E, 0x0F
//    };
//    iv.Assign(fixedIV, CryptoPP::AES::BLOCKSIZE);

    AutoSeededRandomPool prng;
    iv.CleanNew(AES::BLOCKSIZE);
    prng.GenerateBlock(iv.BytePtr(), iv.size());
}

std::string kilitle::CalculateHMAC(const std::string& filepath, size_t dataLength) {
    std::cerr << "[DEBUG] HMAC hesaplanıyor: " << filepath << ", length: " << dataLength << std::endl;
 HMAC<CryptoPP::SHA256> hmac(hmacKey_, hmacKey_.size());
    std::string mac;

    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "Dosya açılamadı: " << filepath << std::endl;
        return "";
    }

    std::vector<byte> buffer(dataLength);
    file.read(reinterpret_cast<char*>(buffer.data()), dataLength);
    if (!file) {
        std::cerr << "Dosya tam okunamadı: " << filepath << std::endl;
        return "";
    }

    CryptoPP::StringSource ss(buffer.data(), buffer.size(), true,
        new CryptoPP::HashFilter(hmac,
            new CryptoPP::StringSink(mac)
        )
    );

    return mac;
}

bool kilitle::ConstantTimeCompare(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) return false;
    byte diff = 0;
    for (size_t i = 0; i < a.size(); ++i)
        diff |= a[i] ^ b[i];
    return diff == 0;
}

bool kilitle::EncryptFile(const std::string& inputFilename,
                          const std::string& outputFilename) {
    try {
        SecByteBlock iv;
        GenerateIV(iv);

        std::string tempEncrypted = outputFilename + ".tmp";

        CBC_Mode<AES>::Encryption encryptor(aesKey_, aesKey_.size(), iv);

        FileSource fs(inputFilename.c_str(), true,
            new StreamTransformationFilter(encryptor,
                new FileSink(tempEncrypted.c_str())
            )
        );

        // IV + şifreli veri yaz
        std::ofstream out(outputFilename, std::ios::binary);
        out.write((const char*)iv.BytePtr(), iv.size());

        std::ifstream inEnc(tempEncrypted, std::ios::binary);
        out << inEnc.rdbuf();
        out.flush();
        out.close();
        inEnc.close();

        // HMAC hesapla ve dosya sonuna ekle
        size_t dataLength = iv.size() + std::filesystem::file_size(tempEncrypted);
        std::string hmac = CalculateHMAC(outputFilename, dataLength);

        std::ofstream hmacOut(outputFilename, std::ios::app | std::ios::binary);
        hmacOut.write(hmac.data(), hmac.size());
        hmacOut.close();

        std::remove(tempEncrypted.c_str());
        return true;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Şifreleme hatası: " << e.what() << std::endl;
        return false;
    }
}

bool kilitle::DecryptFile(const std::string& encryptedFilename,
                          const std::string& outputFilename) {
    try {
        std::ifstream in(encryptedFilename, std::ios::binary);
        if (!in) return false;

        in.seekg(0, std::ios::end);
        size_t fileSize = in.tellg();
        in.seekg(0);

        constexpr size_t aesBlockSize = static_cast<size_t>(AES::BLOCKSIZE);
        constexpr size_t shaDigestSize = static_cast<size_t>(SHA256::DIGESTSIZE);

        if (fileSize < aesBlockSize + shaDigestSize) {
            std::cerr << "Geçersiz veya bozuk dosya." << std::endl;
            return false;
        }

        size_t dataLength = fileSize - shaDigestSize;

        // HMAC'i sondan oku
        in.seekg(dataLength);
        std::string storedMac(shaDigestSize, '\0');
        in.read(&storedMac[0], shaDigestSize);
        in.close();

        // HMAC doğrulama
        std::string calculatedMac = CalculateHMAC(encryptedFilename, dataLength);
        if (!ConstantTimeCompare(storedMac, calculatedMac)) {
            std::cerr << "[UYARI] HMAC doğrulaması başarısız! Dosya bozulmuş olabilir." << std::endl;
            return false;
        }

        // IV'yi oku
        std::ifstream encFile(encryptedFilename, std::ios::binary);
        SecByteBlock iv(aesBlockSize);
        encFile.read((char*)iv.BytePtr(), aesBlockSize);

        // Şifreli veriyi çöz
        CBC_Mode<AES>::Decryption decryptor(aesKey_, aesKey_.size(), iv);

        FileSource fs(encryptedFilename.c_str(), false,
            new StreamTransformationFilter(decryptor,
                new FileSink(outputFilename.c_str())
            )
        );

        fs.Pump(fileSize - aesBlockSize - shaDigestSize);
        return true;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Şifre çözme hatası: " << e.what() << std::endl;
        return false;
    }
}

bool kilitle::EncryptDataToFile(const std::string& data, const std::string& outputFilename) {
    try {
        SecByteBlock iv;
        GenerateIV(iv);

        std::string ciphertext;
        CBC_Mode<AES>::Encryption encryptor(aesKey_, aesKey_.size(), iv);

        StringSource ss(data, true,
            new StreamTransformationFilter(encryptor,
                new StringSink(ciphertext)
            )
        );

        // IV + ciphertext dosyaya yaz
        std::ofstream out(outputFilename, std::ios::binary);
        out.write((const char*)iv.BytePtr(), iv.size());
        out.write(ciphertext.data(), ciphertext.size());
        out.flush();
        out.close();

        // HMAC hesapla ve ekle
        size_t dataLength = iv.size() + ciphertext.size();
        std::string hmac = CalculateHMAC(outputFilename, dataLength);

        std::ofstream hmacOut(outputFilename, std::ios::app | std::ios::binary);
        hmacOut.write(hmac.data(), hmac.size());
        hmacOut.close();

        return true;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Bellek verisi şifreleme hatası: " << e.what() << std::endl;
        return false;
    }
}

bool kilitle::DecryptFileToData(const std::string& encryptedFilename, std::string& decryptedData) {
    try {
        std::ifstream in(encryptedFilename, std::ios::binary);
        if (!in) return false;

        in.seekg(0, std::ios::end);
        size_t fileSize = in.tellg();
        in.seekg(0);

        constexpr size_t aesBlockSize = static_cast<size_t>(AES::BLOCKSIZE);
        constexpr size_t shaDigestSize = static_cast<size_t>(SHA256::DIGESTSIZE);

        if (fileSize < aesBlockSize + shaDigestSize) {
            std::cerr << "Geçersiz dosya." << std::endl;
            return false;
        }

        size_t dataLength = fileSize - shaDigestSize;

        // HMAC doğrula
        in.seekg(dataLength);
        std::string storedMac(shaDigestSize, '\0');
        in.read(&storedMac[0], shaDigestSize);
        in.close();

        std::string calculatedMac = CalculateHMAC(encryptedFilename, dataLength);

        // DEBUG LOG
        std::cout << "fileSize: " << fileSize << ", dataLength: " << dataLength << std::endl;
        std::cout << "Stored MAC: ";
        for (auto c : storedMac) std::cout << std::hex << std::setw(2) << std::setfill('0') << (static_cast<unsigned int>(static_cast<unsigned char>(c)));
        std::cout << std::endl;

        std::cout << "Calculated MAC: ";
        for (auto c : calculatedMac) std::cout << std::hex << std::setw(2) << std::setfill('0') << (static_cast<unsigned int>(static_cast<unsigned char>(c)));
        std::cout << std::endl;

        if (!ConstantTimeCompare(storedMac, calculatedMac)) {
            std::cerr << "[UYARI] HMAC doğrulaması başarısız." << std::endl;
            return false;
        }

        // IV + ciphertext'i oku
        std::ifstream encFile(encryptedFilename, std::ios::binary);
        CryptoPP::SecByteBlock iv(aesBlockSize);
        encFile.read(reinterpret_cast<char*>(iv.BytePtr()), aesBlockSize);

        std::string ciphertext(dataLength - aesBlockSize, '\0');
        encFile.read(&ciphertext[0], ciphertext.size());
        encFile.close();

        CBC_Mode<AES>::Decryption decryptor(aesKey_, aesKey_.size(), iv);

        CryptoPP::StringSource ss(ciphertext, true,
            new CryptoPP::StreamTransformationFilter(decryptor,
                new CryptoPP::StringSink(decryptedData)
            )
        );

        return true;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Bellek verisi çözme hatası: " << e.what() << std::endl;
        return false;
    }
}

void kilitle::PrintHex(const std::string& label, const std::string& data) {
    std::cout << label << ": ";
    for (unsigned char c : data) {
        printf("%02x", c);
    }
    std::cout << std::endl;
}

bool kilitle::LoadKeysFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.read(reinterpret_cast<char*>(aesKey_.data()), aesKey_.size());
    file.read(reinterpret_cast<char*>(hmacKey_.data()), hmacKey_.size());
    return true;
}

void kilitle::SaveKeysToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(aesKey_.data()), aesKey_.size());
    file.write(reinterpret_cast<const char*>(hmacKey_.data()), hmacKey_.size());
}
