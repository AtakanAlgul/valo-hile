#pragma once

#define VMProtectBegin(x)
#define VMProtectBeginVirtualization(x)
#define VMProtectBeginMutation(x)
#define VMProtectBeginUltra(x)
#define VMProtectBeginVirtualizationLockByKey(x)
#define VMProtectBeginUltraLockByKey(x)
#define VMProtectEnd()

inline bool VMProtectIsProtected() { return false; }
inline bool VMProtectIsDebuggerPresent(bool) { return false; }
inline bool VMProtectIsVirtualMachinePresent() { return false; }
inline bool VMProtectIsValidImageCRC() { return true; }
inline const char* VMProtectDecryptStringA(const char* value) { return value; }
inline const wchar_t* VMProtectDecryptStringW(const wchar_t* value) { return value; }
inline bool VMProtectFreeString(const void*) { return true; }

#pragma pack(push, 1)
typedef struct
{
    unsigned short	wYear;
    unsigned char	bMonth;
    unsigned char	bDay;
} VMProtectDate;

typedef struct
{
    int				nState;
    wchar_t		    wUserName[256];
    wchar_t		    wEMail[256];
    VMProtectDate	dtExpire;
    VMProtectDate	dtMaxBuild;
    int				bRunningTime;
    unsigned char	nUserDataLength;
    unsigned char	bUserData[255];
} VMProtectSerialNumberData;
#pragma pack(pop)

inline int VMProtectSetSerialNumber(const char*) { return 0; }
inline int VMProtectGetSerialNumberState() { return 0; }
inline bool VMProtectGetSerialNumberData(VMProtectSerialNumberData* data, int size) { return false; }
inline int VMProtectGetCurrentHWID(char* hwid, int size) { if (size > 0) hwid[0] = '\0'; return 0; }
inline int VMProtectActivateLicense(const char*, char*, int) { return 0; }
inline int VMProtectDeactivateLicense(const char*) { return 0; }
inline int VMProtectGetOfflineActivationString(const char*, char*, int) { return 0; }
inline int VMProtectGetOfflineDeactivationString(const char*, char*, int) { return 0; }
