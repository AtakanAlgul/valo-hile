#pragma once
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <chrono>

class Encryption {
private:
    static std::string generateToken(size_t length) {
        const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, sizeof(charset) - 2);

        std::string token;
        token.reserve(length);
        for (size_t i = 0; i < length; ++i) {
            token += charset[dis(gen)];
        }
        return token;
    }

    static std::string xorEncrypt(const std::string& data, const std::string& key) {
        std::string encrypted;
        for (size_t i = 0; i < data.length(); ++i) {
            encrypted += data[i] ^ key[i % key.length()];
        }
        return encrypted;
    }

    static std::string toHex(const std::string& data) {
        std::stringstream ss;
        for (unsigned char c : data) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
        }
        return ss.str();
    }

    static std::string fromHex(const std::string& hex) {
        std::string result;
        for (size_t i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            result += (char)std::stoi(byteString, nullptr, 16);
        }
        return result;
    }

public:
    static std::string calculateHMAC(const std::string& data, const std::string& key) {
        std::string hmac;
        unsigned char k_ipad[64] = { 0 };
        unsigned char k_opad[64] = { 0 };

        // Prepare key
        if (key.length() > 64) {
            // If key is longer than 64 bytes, use its hash
            hmac = key.substr(0, 64);
        }
        else {
            hmac = key;
        }

        // XOR key with ipad and opad values
        for (size_t i = 0; i < hmac.length(); i++) {
            k_ipad[i] = hmac[i] ^ 0x36;
            k_opad[i] = hmac[i] ^ 0x5c;
        }

        // Fill remaining bytes
        for (size_t i = hmac.length(); i < 64; i++) {
            k_ipad[i] = 0x36;
            k_opad[i] = 0x5c;
        }

        // Combine with the message
        std::string inner = std::string((char*)k_ipad, 64) + data;
        std::string outer = std::string((char*)k_opad, 64) + inner;

        // Final hash
        return toHex(xorEncrypt(outer, key));
    }

    static std::pair<std::string, std::string> encryptData(const std::string& data) {
        std::string token = generateToken(32);
        std::string encrypted = xorEncrypt(data, token);
        return { token, toHex(encrypted) };
    }

    static std::string decryptData(const std::string& encryptedHex, const std::string& token) {
        std::string encrypted = fromHex(encryptedHex);
        return xorEncrypt(encrypted, token); // XOR is its own inverse
    }
};