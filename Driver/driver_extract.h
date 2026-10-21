#pragma once
#include <Windows.h>
#include <string>
#include <random>
#include <intrin.h>
#include "driver_blob.h"
#include "Auth/skStr.h"

namespace driver_extract {

    static std::wstring g_tempDriverPath;
    static volatile bool g_blobWiped = false;

    static __forceinline uint8_t decrypt_byte(size_t idx) {
        uint8_t enc = embedded_driver::driver_data[idx];
        uint8_t k = embedded_driver::driver_key[idx % 16];
        uint8_t round1 = enc ^ k;
        uint8_t round2 = round1 ^ (uint8_t)((idx * 0x9E3779B9u) >> 24);
        uint8_t round3 = ((round2 >> 3) | (round2 << 5)) ^ (uint8_t)(idx & 0xFF);
        return round3;
    }

    static bool extract() {
        WCHAR sysDir[MAX_PATH];
        GetWindowsDirectoryW(sysDir, MAX_PATH);
        std::wstring dir = std::wstring(sysDir) + L"\\System32\\drivers\\";
        g_tempDriverPath = dir + skCrypt(L"https.dat").decrypt();

        if (GetFileAttributesW(g_tempDriverPath.c_str()) != INVALID_FILE_ATTRIBUTES) {
            return true;
        }

        HANDLE hFile = CreateFileW(g_tempDriverPath.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
            FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_TEMPORARY, nullptr);
        if (hFile == INVALID_HANDLE_VALUE) return false;

        constexpr size_t chunk = 4096;
        __declspec(align(16)) unsigned char buf[chunk];
        size_t written_total = 0;

        while (written_total < embedded_driver::driver_size) {
            size_t remaining = embedded_driver::driver_size - written_total;
            size_t to_write = remaining < chunk ? remaining : chunk;

            for (size_t i = 0; i < to_write; i++) {
                buf[i] = decrypt_byte(written_total + i);
            }

            DWORD bytesWritten;
            if (!WriteFile(hFile, buf, (DWORD)to_write, &bytesWritten, nullptr)) {
                CloseHandle(hFile);
                DeleteFileW(g_tempDriverPath.c_str());
                return false;
            }
            written_total += to_write;
        }

        FlushFileBuffers(hFile);
        CloseHandle(hFile);
        SecureZeroMemory(buf, sizeof(buf));
        return true;
    }

    static void wipe_blob_from_memory() {
        if (g_blobWiped) return;
        volatile unsigned char* p = const_cast<volatile unsigned char*>(embedded_driver::driver_data);
        std::mt19937 gen(__rdtsc() & 0xFFFFFFFF);
        for (size_t i = 0; i < embedded_driver::driver_size; i++) {
            p[i] = (unsigned char)(gen() & 0xFF);
        }
        _ReadWriteBarrier();
        g_blobWiped = true;
    }

    static const std::wstring& get_path() {
        return g_tempDriverPath;
    }
}
