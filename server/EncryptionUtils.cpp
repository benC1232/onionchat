#include "EncryptionUtils.h"

unsigned char* generate_AES_key() {
    const int key_size = 16;
    unsigned char* aes_key = new unsigned char[key_size];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    for (int i = 0; i < key_size; ++i) {
        aes_key[i] = static_cast<unsigned char>(dis(gen));
    }
    return aes_key;
}