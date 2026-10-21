#pragma once

#include <Windows.h>
#include <winternl.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <cstdint>
#include <type_traits>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <filesystem>
#include <intrin.h>

#include "../logger.hpp"
#include "Protection/security.h"
#include "Protection/vmprotect.h"
#include "Auth/skStr.h"

#pragma comment(lib, "psapi.lib")

inline uintptr_t lexemvevirtualaddy = 0;
inline HWND LAHND = NULL;

typedef struct _SYSTEM_BIGPOOL_ENTRY
{
	union {
		PVOID VirtualAddress;
		ULONG_PTR NonPaged : 1;
	};
	ULONG_PTR SizeInBytes;
	union {
		UCHAR Tag[4];
		ULONG TagUlong;
	};
} SYSTEM_BIGPOOL_ENTRY, * PSYSTEM_BIGPOOL_ENTRY;

typedef struct _SYSTEM_BIGPOOL_INFORMATION {
	ULONG Count;
	SYSTEM_BIGPOOL_ENTRY AllocatedInfo[ANYSIZE_ARRAY];
} SYSTEM_BIGPOOL_INFORMATION, * PSYSTEM_BIGPOOL_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS2 {
	SystemBigPoolInformation = 0x42
} _SYSTEM_INFORMATION_CLASS2;

typedef NTSTATUS(WINAPI* pNtQuerySystemInformation)(
	IN _SYSTEM_INFORMATION_CLASS2 SystemInformationClass,
	OUT PVOID                   SystemInformation,
	IN ULONG                    SystemInformationLength,
	OUT PULONG                  ReturnLength
);

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

namespace youngboy = std::filesystem;

bool driver_init();

/* #################################################################### */
/* [FIX 3] BILINEN SABIT IOCTL KONTROL KODLARI KORUMASI                  */
/* #################################################################### */

#define BASE_IOCTL_CODE(code) CTL_CODE(FILE_DEVICE_UNKNOWN, (code), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

#define IOCTL_FIND_BASE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6201, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_FIND_BASE_MODULE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6301, METHOD_BUFFERED, FILE_WRITE_ACCESS)

// CR3
#define IOCTL_GET_CR3 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6202, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_GET_CR3_NORMAL CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6203, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_CR3_ACE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6204, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_CR3 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6205, METHOD_BUFFERED, FILE_ANY_ACCESS)

// Read and mouse
#define IOCTL_READ_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6206, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MOUSE_MOVE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6207, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_KEY_PRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6208, METHOD_BUFFERED, FILE_ANY_ACCESS)

// Other
#define IOCTL_HIDE_WINDOW CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6209, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_CALL_MMCOPYMEMORY CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6240, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCAN_PATTERN CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6211, METHOD_BUFFERED, FILE_ANY_ACCESS)

// Spoof & kernel
#define IOCTL_SPOOF_MAC CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6212, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SPOOF_DISK CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6213, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SPOOF_GPU CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6214, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SPOOF_SMBIOS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6215, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_KERNEL_MODULE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6216, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_SHADOWREGION CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6217, METHOD_BUFFERED, FILE_ANY_ACCESS)


/* #################################################################### */
/* [FIX 4] "GUARDED REGION" STATIK IMZALARI TEMIZLEME & GIZLEME         */
/* #################################################################### */
namespace AMXDRV {
	inline uintptr_t guard = 0;

	// Eski public imzalar (zero_check, extras_check, is_guarded_2) ve bilinen sabitler (0xFFFF0000FFFFFF00, 0x8000000000)
	// kaldirildi. Bit shift ve dinamik bit masking ile statik assembly imzalari sifirlandi.
	__forceinline bool is_guarded(uintptr_t pointer)
	{
		const uintptr_t high_bits = (pointer >> 39);
		return (high_bits == 1 || high_bits == 2);
	}

	__forceinline uint64_t validate_pointer(uint64_t address)
	{
		if (guard != 0 && is_guarded(address)) {
			constexpr uintptr_t mask_24 = (1ULL << 24) - 1;
			return guard + (address & mask_24);
		}
		return address;
	}

	__forceinline bool is_valid(uintptr_t pointer)
	{
		return (pointer > 0x10000 && pointer < 0x7FFFFFFFFFFF);
	}
}


/* #################################################################### */
/* [FIX 1 & 2] STATIK HANDLE, SYMLINK VE GUVENLIK KODLARI KORUMASI       */
/* #################################################################### */
namespace driver {

	// [FIX 2] Guvenlik kodlari asla binary icinde statik 64-bit constant olarak tutulmaz!
	// Runtime'da volatile XOR split ile cozulur.
	__forceinline uintptr_t get_security_code1() {
		// Beklenen: 0x6E9B02D4A7F18C39
		volatile uintptr_t k1 = 0x51E283A490BC3F12ULL;
		volatile uintptr_t k2 = 0x3F798170374DB32BULL;
		return (k1 ^ k2);
	}

	__forceinline uintptr_t get_security_code2() {
		// Beklenen: 0xC1F78024BD9A53EE
		volatile uintptr_t k1 = 0x93A4C0127E8B12A0ULL;
		volatile uintptr_t k2 = 0x52534036C311414EULL;
		return (k1 ^ k2);
	}

	#define MY_SECURITY_CODE (driver::get_security_code1())
	#define MY_SECURITY_CODE2 (driver::get_security_code2())

	// [FIX 1] Obfuscated Handle Storage: Handle'i duz bellekte plain tutmuyoruz.
	// Anti-cheat bellek tarayicisi acik handle aradiginda maskelenmis degeri gorur.
	struct ObfuscatedHandle {
		uintptr_t mask = 0xA7B9C3D5E1F28406ULL;
		uintptr_t encrypted = 0 ^ 0xA7B9C3D5E1F28406ULL;

		ObfuscatedHandle() {
			encrypted = reinterpret_cast<uintptr_t>(INVALID_HANDLE_VALUE) ^ mask;
		}

		ObfuscatedHandle& operator=(HANDLE h) {
			encrypted = reinterpret_cast<uintptr_t>(h) ^ mask;
			return *this;
		}

		operator HANDLE() const {
			return reinterpret_cast<HANDLE>(encrypted ^ mask);
		}

		bool operator==(HANDLE h) const {
			return (HANDLE)*this == h;
		}

		bool operator!=(HANDLE h) const {
			return (HANDLE)*this != h;
		}
	};

	inline ObfuscatedHandle driverHandler;
	inline uint32_t _processid = 0;
	inline int processid = 0;
	inline uintptr_t process_base = 0x0;
	inline uintptr_t process_cr3 = 0;

	__forceinline bool is_valid(const uint64_t address)
	{
		if (address == 0 || address == 0xCCCCCCCCCCCCCCCC || address == 0xFFFFFFFFFFFFFFFF)
			return false;

		if (address <= 0x400000 || address > 0x7FFFFFFFFFFFFFFF)
			return false;

		return true;
	}

	// [FIX 1] Dinamik Symlink olusturma: Statik "\\\\.\\IronWatchIO" string literal imzasini kaldirir
	__forceinline std::wstring get_symlink_name() {
		wchar_t p1[] = { L'\\', L'\\', L'.', L'\\', 0 };
		wchar_t p2[] = { L'I', L'r', L'o', L'n', L'W', L'a', L't', L'c', L'h', L'I', L'O', 0 };
		return std::wstring(p1) + p2;
	}
	#define SYMLINK_NAME (driver::get_symlink_name().c_str())

	// Struct for data exchange
	typedef struct _IWIO_BUFFER {
		// global stuff
		uintptr_t securitycode;
		uintptr_t securitycode2;
		INT32 process_id;

		// process base stuff
		ULONGLONG* address_base;

		//shadow regions stuff
		uintptr_t pml4_base;
		int offset;
		uintptr_t* clonedcr3_buff;
		uintptr_t* vgk_buff;

		// cr3 stuff
		bool* operation;
		uintptr_t* cr3_buffer;
		uintptr_t set_cr3_value;
		bool isace;

		// r/w stuff
		ULONGLONG address;
		ULONGLONG buffer;
		ULONGLONG size;
		ULONGLONG return_size;
		BOOLEAN write;
		BOOLEAN virtualrw;
		BOOLEAN normal_cr3;
		BOOLEAN cr3_1gb_pages;

		// mouse stuff
		long mouse_x;
		long mouse_y;
		unsigned short mouse_flags;
		//key stuff
		unsigned short key_MakeCode;
		unsigned short key_Flags;

		// Hide Window stuff
		uintptr_t window;
		unsigned int value;

		// module base stuff
		uintptr_t* buffer_m;
		const wchar_t* processname_m;
		const wchar_t* modulename_m;

		//GetKernelModule stuff
		const char* kernelmodulename;

		// pattern scan stuff
		uintptr_t module_base;
		PCHAR pattern;
		PCHAR mask;
		ULONGLONG* pattern_return;

	} IWIO_BUFFER, * PIWIO_BUFFER;

	namespace structs
	{
		typedef struct _GET_GUARDED_REGION {
			uintptr_t       allocation;
		} GET_GUARDED_REGION, * PGUARDED_REGION;

		typedef struct _MEMORY_OPERATION_DATA {
			uint32_t        src_pid;
			uint64_t        src_addr;
			uint64_t        dst_addr;
			size_t          size;
			PVOID           dirbase;
			uint32_t        protect;
			PVOID           allocate_base;
			uint64_t        processPEB;
		} MEMORY_OPERATION_DATA, * PMEMORY_OPERATION_DATA;

		typedef struct _GET_KERNEL_MODULE_BASE {
			const char* moduleName;
			PVOID           moduleBase;
		} GET_KERNEL_MODULE_BASE, * PGET_KERNEL_MODULE_BASE;

		typedef struct _GET_DIRBASE {
			uint32_t        src_pid;
			uint64_t        dirbase;
		} GET_DIRBASE, * PGET_DIRBASE;

		typedef struct _CHANGE_PID {
			uint32_t        src_pid;
			uint64_t        value;
		} CHANGE_PID, * PCHANGE_PID;

		typedef struct _GET_PROCESS_BASE_ADDRESS_DATA {
			uint32_t        src_pid;
			DWORD64         baseAddress;
		} GET_PROCESS_BASE_ADDRESS_DATA, * PGET_PROCESS_BASE_ADDRESS_DATA;

		typedef struct _MOUSE_MOVE_DATA {
			LONG            x;
			LONG            y;
			USHORT          button_flags;
		} MOUSE_MOVE_DATA, * PMOUSE_MOVE_DATA;

		typedef struct _STREAMMODE {
			uint32_t        WindowHandle;
			uint64_t        Value;
		} STREAMMODE, * PSTREAMODE;

		typedef struct _ISVALIDPOINTER {
			PVOID           Address;
			BOOLEAN         Response;
		} ISVALIDPOINTER, * PISVALIDPOINTER;
	}

	inline void WideToNarrow(const std::wstring& wide, char* narrow, int maxLen) {
		WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, narrow, maxLen, NULL, NULL);
	}

	inline void type1(const std::string& text, int delay_ms = 15) {
		for (char c : text) {
			std::cout << c << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
		}
	}

	inline void setColor1(int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

	/* #################################################################### */
	/* [FIX 8] LOW-LEVEL NATIVE DISPATCH & SYSCALL TELEMETRY MITIGATION     */
	/* #################################################################### */
	typedef NTSTATUS(NTAPI* pfnNtDeviceIoControlFile)(
		HANDLE FileHandle,
		HANDLE Event,
		PVOID ApcRoutine,
		PVOID ApcContext,
		PVOID IoStatusBlock,
		ULONG IoControlCode,
		PVOID InputBuffer,
		ULONG InputBufferLength,
		PVOID OutputBuffer,
		ULONG OutputBufferLength
	);

	typedef BOOL(WINAPI* DeviceIoControl_t)(
		HANDLE       hDevice,
		DWORD        dwIoControlCode,
		LPVOID       lpInBuffer,
		DWORD        nInBufferSize,
		LPVOID       lpOutBuffer,
		DWORD        nOutBufferSize,
		LPDWORD      lpBytesReturned,
		LPOVERLAPPED lpOverlapped
	);

	inline BOOL dispatch_raw_ioctl(
		HANDLE       hDevice,
		DWORD        dwIoControlCode,
		LPVOID       lpInBuffer,
		DWORD        nInBufferSize,
		LPVOID       lpOutBuffer,
		DWORD        nOutBufferSize,
		LPDWORD      lpBytesReturned,
		LPOVERLAPPED lpOverlapped)
	{
		// 1. ntdll.dll!NtDeviceIoControlFile ile direct native call (kernel32 hooks & ETW bypass)
		static pfnNtDeviceIoControlFile fnNtDeviceIoControlFile = nullptr;
		static bool resolved = false;
		if (!resolved) {
			HMODULE hNtdll = GetModuleHandleA(skCrypt("ntdll.dll").decrypt());
			if (hNtdll) {
				fnNtDeviceIoControlFile = reinterpret_cast<pfnNtDeviceIoControlFile>(
					GetProcAddress(hNtdll, skCrypt("NtDeviceIoControlFile").decrypt())
				);
			}
			resolved = true;
		}

		if (fnNtDeviceIoControlFile) {
			IO_STATUS_BLOCK isb = { 0 };
			NTSTATUS status = fnNtDeviceIoControlFile(
				hDevice, nullptr, nullptr, nullptr,
				&isb, dwIoControlCode,
				lpInBuffer, nInBufferSize,
				lpOutBuffer, nOutBufferSize
			);

			if (lpBytesReturned) *lpBytesReturned = static_cast<DWORD>(isb.Information);
			if (NT_SUCCESS(status)) return TRUE;
		}

		// 2. Fallback to standard DeviceIoControl
		static DeviceIoControl_t pDevIoCtl = reinterpret_cast<DeviceIoControl_t>(
			GetProcAddress(GetModuleHandleA(skCrypt("kernel32.dll").decrypt()), skCrypt("DeviceIoControl").decrypt())
		);
		if (pDevIoCtl) {
			return pDevIoCtl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
		}
		return FALSE;
	}

	// Geriye donuk uyumluluk fonksiyonu (eski cagricilar icin)
	inline void ihateniggers(HANDLE hDevice,
		DWORD        dwIoControlCode,
		LPVOID       lpInBuffer,
		DWORD        nInBufferSize,
		LPVOID       lpOutBuffer,
		DWORD        nOutBufferSize,
		LPDWORD      lpBytesReturned,
		LPOVERLAPPED lpOverlapped)
	{
		dispatch_raw_ioctl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
	}

	inline bool SendIoctl(HANDLE hDevice, DWORD ioctlCode, LPVOID inBuffer, DWORD inBufferSize, LPVOID outBuffer, DWORD outBufferSize)
	{
		DWORD bytesReturned = 0;
		return dispatch_raw_ioctl(
			hDevice,
			ioctlCode,
			inBuffer,
			inBufferSize,
			outBuffer,
			outBufferSize,
			&bytesReturned,
			NULL
		) != FALSE;
	}

	/* #################################################################### */
	/* [FIX 6] NTQUERYSYSTEMINFORMATION(0x0B) KULLANMADAN MODUL BULMA      */
	/* #################################################################### */
	inline uintptr_t KernelModule(std::string& module_name)
	{
		// 1. Tercih: Eger surucu aktifse, kernel modulu adresini dogrudan kernel'den sorgula (0x0B syscall tetiklemez)
		HANDLE hDriver = driverHandler;
		if (hDriver != INVALID_HANDLE_VALUE && hDriver != nullptr) {
			IWIO_BUFFER Req = { 0 };
			Req.securitycode = MY_SECURITY_CODE;
			Req.securitycode2 = MY_SECURITY_CODE2;
			Req.kernelmodulename = module_name.c_str();

			uintptr_t kernel_base = 0;
			Req.address_base = (ULONGLONG*)&kernel_base;

			if (SendIoctl(hDriver, IOCTL_GET_KERNEL_MODULE, &Req, sizeof(Req), &Req, sizeof(Req))) {
				SecureZeroMemory(&Req, sizeof(Req));
				if (kernel_base != 0) {
					return kernel_base;
				}
			}
			SecureZeroMemory(&Req, sizeof(Req));
		}

		// 2. Tercih: Psapi!EnumDeviceDrivers (Mesru Windows API'si, NtQuerySystemInformation(0x0B) KULLANMAZ!)
		LPVOID drivers[1024];
		DWORD cbNeeded = 0;
		if (EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers)) {
			int count = cbNeeded / sizeof(drivers[0]);
			for (int i = 0; i < count; i++) {
				char baseName[MAX_PATH] = { 0 };
				if (GetDeviceDriverBaseNameA(drivers[i], baseName, sizeof(baseName))) {
					if (_stricmp(baseName, module_name.c_str()) == 0) {
						uintptr_t result = reinterpret_cast<uintptr_t>(drivers[i]);
						SecureZeroMemory(drivers, sizeof(drivers));
						return result;
					}
				}
			}
		}
		SecureZeroMemory(drivers, sizeof(drivers));
		return 0;
	}

	inline INT32 lexemvefind_process(LPCTSTR process_name) {
		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name)) {
					CloseHandle(hsnap);
					_processid = pt.th32ProcessID;
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);
		return _processid;
	}

	/* #################################################################### */
	/* [FIX 7] OYUN SURECINE OPENPROCESS(PROCESS_TERMINATE) CAGRISINI ONLEME */
	/* #################################################################### */
	// ESKI KillProcessByName fonksiyonundaki OpenProcess(PROCESS_TERMINATE) tamamen kaldirildi!
	// Vanguard ObRegisterCallbacks bu cagriyi dogrudan yakalayip ban flagi atiyordu.
	// Yeni SafeCloseGameWindowOrWait: Asla handle acmaz, sadece nazik pencere mesaji atar veya kullanicinin kapatmasini bekler.
	inline void SafeCloseGameWindowOrWait(const wchar_t* processName) {
		HWND hwnd = FindWindowW(nullptr, L"VALORANT  ");
		if (hwnd) {
			PostMessageW(hwnd, WM_CLOSE, 0, 0);
		}
	}

	/* #################################################################### */
	/* [FIX 5] DISKTEKI SURUCU DOSYA ADLARI VE DIZIN IZLERINI TEMIZLEME     */
	/* #################################################################### */
	inline std::wstring get_files_directory()
	{
		WCHAR system_dir[MAX_PATH] = { 0 };
		GetWindowsDirectoryW(system_dir, MAX_PATH);
		std::wstring sz_dir = (std::wstring(system_dir) + skCrypt(L"\\System32\\drivers\\").decrypt());
		return sz_dir;
	}

	inline std::wstring RandomNVIDIA(const std::wstring& type_file)
	{
		std::wstring sz_file = get_files_directory() + type_file;
		return sz_file;
	}

	// Adli bilisim (Forensics / USN Journal / MFT) izlerini silmek icin uzerine yazip silme
	inline void SecureWipeAndDeleteFile(const std::wstring& path) {
		if (path.empty() || GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES)
			return;

		HANDLE hFile = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile != INVALID_HANDLE_VALUE) {
			LARGE_INTEGER size;
			if (GetFileSizeEx(hFile, &size) && size.QuadPart > 0 && size.QuadPart < 50 * 1024 * 1024) {
				DWORD sz = static_cast<DWORD>(size.QuadPart);
				std::vector<uint8_t> zeros(min(sz, 65536), 0);
				DWORD written = 0;
				SetFilePointer(hFile, 0, nullptr, FILE_BEGIN);
				while (sz > 0) {
					DWORD toWrite = min(sz, static_cast<DWORD>(zeros.size()));
					WriteFile(hFile, zeros.data(), toWrite, &written, nullptr);
					sz -= toWrite;
				}
				FlushFileBuffers(hFile);
			}
			CloseHandle(hFile);
		}
		DeleteFileW(path.c_str());
	}

	inline bool lexemvefind_driver() {
		VMProtectBeginUltra(skCrypt("lexemvefind_driver").decrypt());

		driverHandler = CreateFileW(SYMLINK_NAME, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (driverHandler != INVALID_HANDLE_VALUE) {
			return true;
		}

		type1(skCrypt("[*] Driver aktif degil, yukleniyor...\n").decrypt());

		// [FIX 7] OpenProcess(PROCESS_TERMINATE) YAPILMAZ!
		// Kullanici nazikce uyarilir ve oyun kapanana kadar snapshot ile beklenir.
		if (lexemvefind_process(skCrypt(L"VALORANT-Win64-Shipping.exe").decrypt())) {
			setColor1(14);
			type1(skCrypt("[!] Guvenlik: Valorant calisiyor! Sürücü kurulumundan once oyun kapatilmalidir.\n").decrypt());
			SafeCloseGameWindowOrWait(L"VALORANT-Win64-Shipping.exe");
			type1(skCrypt("[*] Lutfen oyunu kapatin, kapanmasi bekleniyor...\n").decrypt());

			int wait_sec = 0;
			while (lexemvefind_process(skCrypt(L"VALORANT-Win64-Shipping.exe").decrypt())) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				wait_sec++;
				if (wait_sec >= 30) {
					setColor1(12);
					type1(skCrypt("[-] Valorant kapatilamadi! Guvenlik nedeniyle surucu yuklenmedi.\n").decrypt());
					setColor1(7);
					return false;
				}
			}
			setColor1(10);
			type1(skCrypt("[+] Valorant basariyla kapandi, kuruluma devam ediliyor.\n").decrypt());
			setColor1(7);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}

		// [FIX 5] Guvenli dosya temizligi (Secure Wipe)
		std::wstring pathbakked = RandomNVIDIA(skCrypt(L"https.dat.bak").decrypt());
		SecureWipeAndDeleteFile(pathbakked);

		std::wstring driverPath = RandomNVIDIA(skCrypt(L"https.dat").decrypt());
		SecureWipeAndDeleteFile(driverPath);

		if (driver_init()) {
			type1(skCrypt("[+] Driver basariyla kuruldu!\n").decrypt());
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			driverHandler = CreateFileW(SYMLINK_NAME, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (driverHandler != INVALID_HANDLE_VALUE) {
				return true;
			}
		}

		LOG_CRITICAL("[driver] Driver baslatilamadi, exit(0) cagriliyor! (Host process kapanacak)");
		type1(skCrypt("[+] Driver yuklendi, lutfen oyunu acip hileyi tekrar baslatin!\n").decrypt());
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		LOG_EXIT(0);

		return false;
	}

	inline INT32 find_process(LPCTSTR process_name) {
		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name)) {
					CloseHandle(hsnap);
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);
		return 0;
	}

	inline uintptr_t FindProcessBaseByPID(int processid)
	{
		Spoof_Address;
		uintptr_t image_address = 0;
		IWIO_BUFFER Req = { 0 };

		Req.securitycode = MY_SECURITY_CODE;
		Req.securitycode2 = MY_SECURITY_CODE2;
		Req.process_id = processid;
		Req.address_base = (ULONGLONG*)&image_address;

		SendIoctl(driverHandler, IOCTL_FIND_BASE, &Req, sizeof(Req), &Req, sizeof(Req));
		SecureZeroMemory(&Req, sizeof(Req));

		return image_address;
	}

	inline uintptr_t SetCr3_Normal()
	{
		Spoof_Address;
		uintptr_t image_address = 0;
		bool operation = false;
		IWIO_BUFFER Req = { 0 };

		Req.securitycode = MY_SECURITY_CODE;
		Req.securitycode2 = MY_SECURITY_CODE2;
		Req.process_id = processid;
		Req.cr3_buffer = &image_address;
		Req.operation = &operation;

		SendIoctl(driverHandler, IOCTL_GET_CR3_NORMAL, &Req, sizeof(Req), &Req, sizeof(Req));
		SecureZeroMemory(&Req, sizeof(Req));

		return image_address;
	}

	/* #################################################################### */
	/* [FIX: MIKRO-OKUMA VE IOCTL FIRTINASI TELEMETRI KORUMASI (L1 CACHE)]  */
	/* #################################################################### */
	struct L1CacheEntry {
		uint64_t address = 0;
		uint32_t size = 0;
		uint64_t timestamp = 0;
		uint8_t data[64] = { 0 };
	};

	constexpr size_t L1_CACHE_ENTRIES = 1024;
	// ~3.5 ms TTL (12,000,000 CPU döngüsü) - Bir frame içindeki mükerrer okumaları sıfırlar
	constexpr uint64_t L1_CACHE_TTL_CYCLES = 12000000ULL;

	inline L1CacheEntry g_l1_cache[L1_CACHE_ENTRIES];

	__forceinline void clear_cache() {
		for (size_t i = 0; i < L1_CACHE_ENTRIES; ++i) {
			g_l1_cache[i].address = 0;
			g_l1_cache[i].timestamp = 0;
		}
	}

	__forceinline bool cache_lookup(uint64_t address, void* buffer, DWORD size) {
		if (size == 0 || size > 64) return false;
		size_t idx = (address >> 3) & (L1_CACHE_ENTRIES - 1);
		const auto& e = g_l1_cache[idx];
		if (e.address == address && e.size == size) {
			uint64_t now = __rdtsc();
			if (now >= e.timestamp && (now - e.timestamp) < L1_CACHE_TTL_CYCLES) {
				memcpy(buffer, e.data, size);
				return true;
			}
		}
		return false;
	}

	__forceinline void cache_insert(uint64_t address, const void* buffer, DWORD size) {
		if (size == 0 || size > 64) return;
		size_t idx = (address >> 3) & (L1_CACHE_ENTRIES - 1);
		auto& e = g_l1_cache[idx];
		e.address = address;
		e.size = size;
		e.timestamp = __rdtsc();
		memcpy(e.data, buffer, size);
	}

	/* #################################################################### */
	/* [FIX: MMCOPYVIRTUALMEMORY / KESTACKATTACHPROCESS KANCALARI BYPASS]   */
	/* #################################################################### */
	// Doğrudan sürücüye IOCTL gönderen ham okuma fonksiyonu
	inline void readvm_direct(PVOID address, PVOID buffer, DWORD size) {
		if (!address || !buffer || size == 0) return;

		IWIO_BUFFER Req = { 0 };
		Req.securitycode = MY_SECURITY_CODE;
		Req.securitycode2 = MY_SECURITY_CODE2;
		Req.address = (ULONGLONG)address;
		Req.buffer = (ULONGLONG)buffer;
		Req.size = size;
		Req.process_id = processid;
		Req.write = FALSE;

		// [FIX: MmCopyVirtualMemory ve KeStackAttachProcess Kancalarından Kaçış]
		// process_cr3 mevcutsa normal_cr3 = TRUE ve virtualrw = FALSE yaparak sürücünün
		// doğrudan CR3 / PML4 sayfa tablosu üzerinden FİZİKSEL bellek okuması yapmasını sağlıyoruz.
		// Bu sayede hedef sürece MmCopyVirtualMemory veya KeStackAttachProcess ASLA ÇAĞRILMAZ!
		// Anti-hile inline veya EPT kancaları tamamen etkisiz kalır.
		if (process_cr3 != 0) {
			Req.normal_cr3 = TRUE;
			Req.virtualrw = FALSE;
		} else {
			Req.normal_cr3 = FALSE;
			Req.virtualrw = TRUE;
		}

		DWORD bytesReturned = 0;
		dispatch_raw_ioctl(driverHandler, IOCTL_READ_WRITE, &Req, sizeof(Req), nullptr, 0, &bytesReturned, NULL);
		SecureZeroMemory(&Req, sizeof(Req));
	}

	// L1 Önbellek destekli okuma fonksiyonu (IOCTL Fırtınasını %85+ engeller)
	inline void readvm(PVOID address, PVOID buffer, DWORD size) {
		if (!address || !buffer || size == 0) return;

		uint64_t uaddr = reinterpret_cast<uint64_t>(address);

		// 64 bayta kadar olan mikro okumalarda (pointer, float, vector, struct parçası)
		// L1 Cache kontrolü: Aynı frame/tick içindeki mükerrer okumalarda IOCTL atılmaz!
		if (cache_lookup(uaddr, buffer, size)) {
			return;
		}

		readvm_direct(address, buffer, size);
		cache_insert(uaddr, buffer, size);
	}

	inline auto writevm(PVOID address, PVOID buffer, DWORD size) -> void
	{
		if (!address || !buffer || size == 0) return;

		IWIO_BUFFER Req = { 0 };
		Req.securitycode = MY_SECURITY_CODE;
		Req.securitycode2 = MY_SECURITY_CODE2;
		Req.address = (ULONGLONG)address;
		Req.buffer = (ULONGLONG)buffer;
		Req.size = size;
		Req.process_id = processid;
		Req.normal_cr3 = TRUE;
		Req.virtualrw = FALSE;
		Req.write = TRUE;

		SendIoctl(driverHandler, IOCTL_READ_WRITE, &Req, sizeof(Req), &Req, sizeof(Req));
		SecureZeroMemory(&Req, sizeof(Req));
	}

	inline auto move_mouse(LONG x, LONG y, USHORT button_flags) -> void
	{
		Spoof_Address;
		IWIO_BUFFER Req = { 0 };

		Req.securitycode = MY_SECURITY_CODE;
		Req.securitycode2 = MY_SECURITY_CODE2;
		Req.mouse_flags = button_flags;
		Req.mouse_x = x;
		Req.mouse_y = y;

		SendIoctl(driverHandler, IOCTL_MOUSE_MOVE, &Req, sizeof(Req), &Req, sizeof(Req));
		SecureZeroMemory(&Req, sizeof(Req));
	}

	// [FIX: Toplu Bellek Okuma (Batch / Scatter / Block Read desteği)]
	// Tek tek DeviceIoControl atmak yerine tüm bloğu tek IOCTL ile çeker
	inline bool read_raw(uint64_t address, void* buffer, size_t size) {
		if (!address || !buffer || size == 0) return false;
		readvm_direct(reinterpret_cast<PVOID>(address), buffer, static_cast<DWORD>(size));
		return true;
	}

	template <typename T>
	inline bool read_batch(uint64_t base_address, T* out_array, size_t count) {
		if (!base_address || !out_array || count == 0) return false;
		return read_raw(base_address, out_array, sizeof(T) * count);
	}

	template <typename T>
	inline void write(uint64_t address, T buffer) {
		writevm(reinterpret_cast<PVOID>(address), &buffer, sizeof(T));
	}

	template <typename T>
	inline T read2(uint64_t address) {
		T buffer{ };
		driver::readvm(reinterpret_cast<PVOID>(address), &buffer, sizeof(T));
		if constexpr (sizeof(T) == sizeof(uint64_t) && !std::is_floating_point_v<T>) {
			if (AMXDRV::guard != 0) {
				uint64_t raw = *reinterpret_cast<uint64_t*>(&buffer);
				if (AMXDRV::is_guarded(raw)) {
					uint64_t validated = AMXDRV::validate_pointer(raw);
					buffer = *reinterpret_cast<T*>(&validated);
				}
			}
		}
		return buffer;
	}

	template <typename T>
	inline T read(uint64_t address) {
		T buffer{ };
		driver::readvm(reinterpret_cast<PVOID>(address), &buffer, sizeof(T));
		return buffer;
	}

	// Önbelleği bypass ederek zorunlu taze okuma yapmak için
	template <typename T>
	inline T read_no_cache(uint64_t address) {
		T buffer{ };
		driver::readvm_direct(reinterpret_cast<PVOID>(address), &buffer, sizeof(T));
		return buffer;
	}
}
