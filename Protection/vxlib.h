#pragma once

#include <string>
#include <array>
#include <type_traits>
#include <cstdint>

#define VL_OBFUSCATION_BEGIN
#define VL_OBFUSCATION_END

namespace vx_crypt {

    // Derleme zamanında her build'de farklı anahtar üreten FNV-1a tohum üreteci
    constexpr uint32_t seed_from_time() {
        uint32_t hash = 0x811c9dc5;
        const char time_str[] = __TIME__;
        for (char c : time_str) {
            hash = (hash ^ static_cast<uint32_t>(c)) * 0x01000193;
        }
        return hash;
    }

    // Derleme zamanı (compile-time) XOR şifreleme sınıfı
    template <typename CharT, size_t N, uint32_t Seed>
    class XorString {
    private:
        std::array<CharT, N> encrypted_data{};
        static constexpr CharT key = static_cast<CharT>((Seed ^ 0x5A) & 0xFF);

    public:
        // Constexpr constructor: Metin binary'e girmeden önce DERLEME ANINDA şifrelenir
        constexpr XorString(const CharT* str) {
            for (size_t i = 0; i < N; ++i) {
                CharT k = static_cast<CharT>(key + (i * 7) + 0x33);
                encrypted_data[i] = static_cast<CharT>(str[i] ^ k);
            }
        }

        using StringType = typename std::conditional<std::is_same_v<CharT, wchar_t>, std::wstring, std::string>::type;

        // Çalışma zamanında (runtime) stack üzerinde anlık çözme
        __forceinline StringType decrypt() const {
            StringType result;
            result.resize(N - 1);
            for (size_t i = 0; i < N - 1; ++i) {
                CharT k = static_cast<CharT>(key + (i * 7) + 0x33);
                result[i] = static_cast<CharT>(encrypted_data[i] ^ k);
            }
            return result;
        }

        __forceinline operator StringType() const {
            return decrypt();
        }
    };

    template <typename CharT, size_t N, uint32_t Seed>
    constexpr auto make_xor_string(const CharT(&str)[N]) {
        return XorString<CharT, N, Seed>(str);
    }
}

// [FIX] xorstr_ makrosu: Metinleri binary'e açık basmak yerine derleme zamanında şifreler,
// çalışma zamanında stack üzerinde güvenle çözer.
#define xorstr_(s) ([]() { \
    using CharType = std::remove_cv_t<std::remove_reference_t<decltype(s[0])>>; \
    constexpr auto _crypted = vx_crypt::make_xor_string<CharType, sizeof(s) / sizeof(s[0]), vx_crypt::seed_from_time() + __LINE__ * 17>(s); \
    return _crypted.decrypt(); \
}())