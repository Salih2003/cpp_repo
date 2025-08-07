#ifndef KILITLE_HPP
#define KILITLE_HPP

#include <cryptlib.h>
#include <secblock.h>
#include <aes.h>
#include <modes.h>
#include <filters.h>
#include <osrng.h>
#include <files.h>
#include <hmac.h>
#include <sha.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

class kilitle {
public:
    kilitle(const CryptoPP::SecByteBlock& aesKey,
            const CryptoPP::SecByteBlock& hmacKey);

        // Anahtar dosyası yolu ile yeni kurucu metot
    kilitle(const std::string& keyFilePath);

    bool EncryptFile(const std::string& inputFilename,
                     const std::string& outputFilename);

    bool DecryptFile(const std::string& encryptedFilename,
                     const std::string& outputFilename);

    bool EncryptDataToFile(const std::string& data,
                           const std::string& outputFilename);

    bool DecryptFileToData(const std::string& encryptedFilename,
                           std::string& decryptedData);


private:
    CryptoPP::SecByteBlock aesKey_;
    CryptoPP::SecByteBlock hmacKey_;

    void GenerateIV(CryptoPP::SecByteBlock& iv);
    std::string CalculateHMAC(const std::string& filepath, size_t dataLength);
    bool ConstantTimeCompare(const std::string& a, const std::string& b);
    void PrintHex(const std::string& label, const std::string& data);
    bool LoadKeysFromFile(const std::string& filename);
    void SaveKeysToFile(const std::string& filename);
};

#endif // KILITLE_HPP
