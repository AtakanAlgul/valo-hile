#pragma once

#ifdef _KERNEL_MODE
#include <ntddk.h>
#include <ntdef.h>
#include <xtr1common> 
#else
#include <Windows.h>
#include <utility>
#include <type_traits>
#include <cstdint>
#endif
#include <Intrin.h>

#define Spoof_Address AddressSpoofing::SpoofFunction spoof(_AddressOfReturnAddress());

#ifdef _KERNEL_MODE
#define SPOOF_CALL(ret_type, name) (AddressSpoofing::SafeCall(name))
#else
#define HIDE_ASM(name) (AddressSpoofing::SafeCall(name))
#define SPOOF_CALL(ret_type, name) (AddressSpoofing::SafeCall(name))
#endif

namespace AddressSpoofing
{
    // [FIX 1: Unbacked RWX bellek ayırma & Bozuk Stack Walk giderildi]
    // 1. Asla VirtualAlloc(PAGE_EXECUTE_READWRITE) ile unbacked bellek ayrılmaz.
    // 2. Asla dönüş adresi 0 (sıfır) yapılmaz! Dönüş adresi meşru ntdll.dll / kernel32.dll
    //    içindeki geçerli bir gadget ile maskelenir. Böylece Stack Walker'lar (RtlCaptureStackBackTrace)
    //    meşru bir modül adresi görür, stack unwinding bozulmaz ve anomali bayrağı kalkmaz.

    __forceinline uintptr_t GetLegitBackedGadget()
    {
#ifdef _KERNEL_MODE
        return 0;
#else
        static uintptr_t s_gadget = 0;
        if (s_gadget != 0) return s_gadget;

        HMODULE hMod = GetModuleHandleA("ntdll.dll");
        if (!hMod) hMod = GetModuleHandleA("kernel32.dll");
        if (!hMod) return 0;

        auto pDos = reinterpret_cast<PIMAGE_DOS_HEADER>(hMod);
        if (pDos->e_magic != IMAGE_DOS_SIGNATURE) return 0;

        auto pNt = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(hMod) + pDos->e_lfanew);
        if (pNt->Signature != IMAGE_NT_SIGNATURE) return 0;

        auto pSec = IMAGE_FIRST_SECTION(pNt);
        for (WORD i = 0; i < pNt->FileHeader.NumberOfSections; ++i, ++pSec)
        {
            if ((pSec->Characteristics & IMAGE_SCN_MEM_EXECUTE) && (pSec->Characteristics & IMAGE_SCN_CNT_CODE))
            {
                const uint8_t* base = reinterpret_cast<const uint8_t*>(hMod) + pSec->VirtualAddress;
                DWORD size = pSec->Misc.VirtualSize;
                for (DWORD j = 16; j < size - 1; ++j)
                {
                    // .text içinde meşru bir RET (0xC3) gadget'ı bul
                    if (base[j] == 0xC3)
                    {
                        s_gadget = reinterpret_cast<uintptr_t>(&base[j]);
                        return s_gadget;
                    }
                }
            }
        }
        return 0;
#endif
    }

    class SpoofFunction
    {
    public:
        uintptr_t original_ret = 0;
        void* ret_addr_in_stack = nullptr;

        __forceinline explicit SpoofFunction(void* addr) : ret_addr_in_stack(addr)
        {
            if (ret_addr_in_stack)
            {
                original_ret = *reinterpret_cast<uintptr_t*>(ret_addr_in_stack);
                uintptr_t gadget = GetLegitBackedGadget();
                // [FIX: Dönüş adresini 0 YAPMA!]
                // 0 yerine meşru ntdll/kernel32 modülü içindeki gadget atanır.
                // Anti-cheat / StackWalk yaptığında meşru bir Windows modülü görür.
                if (gadget != 0)
                {
                    *reinterpret_cast<uintptr_t*>(ret_addr_in_stack) = gadget;
                }
            }
        }

        __forceinline ~SpoofFunction()
        {
            // Fonksiyon tamamlanıp dönmeden önce orijinal dönüş adresi geri yüklenir
            if (ret_addr_in_stack && original_ret != 0)
            {
                *reinterpret_cast<uintptr_t*>(ret_addr_in_stack) = original_ret;
            }
        }
    };

    // [FIX 2: Unbacked RWX bellek tahsisi ve shellcode kopyalama tamamen kaldırıldı]
    // SafeCall artık unbacked bellek tahsis etmeden, meşru modül içinden güvenli çağrı yapar.
    template <typename Func>
    class SafeCall
    {
    private:
        Func funcPtr;

    public:
        __forceinline explicit SafeCall(Func func) : funcPtr(func) {}

        template <typename... Args>
        __forceinline decltype(auto) operator()(Args&&... args)
        {
            Spoof_Address;
            return funcPtr(std::forward<Args>(args)...);
        }
    };
}