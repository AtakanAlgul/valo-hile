
#include <Windows.h>

#include "theme.h"
#include "xor.h"
#include <string>
#include <iostream>
#include "Auth/skStr.h"
#include "Protection/lazy.h"
#include <set>
#include "LOGO.h"
#include "widgets_colors.h"
#include "custom_widgets.hpp"
#include "settings_menu.h"
#include "fonts.h"
#include "icons.h"
#include "fonthelper.h"
#include "images.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "agenticons.h"
#include <algorithm> 
#include <cmath> 
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include "call_spoof.h"
#include "heysup.h"
#include "inter_regular.h"
#include "inter_bold.h"
#include "kz_logo.h"
#include "ImGui/byte_array.h"
#include "ImGui/nav_elements.h"
#include "ImGui/etc_elements.h"
#include <cstdint>
#include <intrin.h> // for _rotl8
#include "check.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ImGui/imgui_internal.h"
#include "structs.h"
#include "Protection/vmprotect.h"
#include <timeapi.h>
#include <dwmapi.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dwmapi.lib")


uintptr_t rotation;
uintptr_t Game_state;
ImFont* Verdana;
ImFont* BoldFont;
ImFont* WeaponIconFont;
ImFont* IconFont;

// New menu fonts
ImFont* medium;
ImFont* bold;
ImFont* tab_icons;
ImFont* logo;
ImFont* tab_title;
ImFont* tab_title_icon;
ImFont* subtab_title;
ImFont* combo_arrow;
float Health;
bool smooth = false;
bool isaimbotting;
uintptr_t apawn;
float angleDegreeszz;
static auto    lastClickTime = std::chrono::steady_clock::now();
static bool    clickHeld = false;


bool is_locked = false;
bool TriggerbotLoced = false;
int currentFOV = 0;
std::mutex fovMutex;
float Maw_width = GetSystemMetrics(SM_CXSCREEN);
float Maw_height = GetSystemMetrics(SM_CYSCREEN);


void setColoAARAr(int color) {
	Spoof_Address;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

LPDIRECT3DTEXTURE9 ctxlogo_tex = NULL; // ctx logo — byte_array.h/ctxlogo
LPDIRECT3DTEXTURE9 logotwo = NULL;
LPDIRECT3DTEXTURE9 cypherlogo = NULL;
LPDIRECT3DTEXTURE9 jettlogo = NULL;
LPDIRECT3DTEXTURE9 sagelogo = NULL;
LPDIRECT3DTEXTURE9 viperlogo = NULL;
LPDIRECT3DTEXTURE9 brimstonelogo = NULL;
LPDIRECT3DTEXTURE9 isologo = NULL;
LPDIRECT3DTEXTURE9 clovelogo = NULL;
LPDIRECT3DTEXTURE9 neonlogo = NULL;
LPDIRECT3DTEXTURE9 phoenixlogo = NULL;
LPDIRECT3DTEXTURE9 reynalogo = NULL;
LPDIRECT3DTEXTURE9 botlogo = NULL;
LPDIRECT3DTEXTURE9 astralogo = NULL;
LPDIRECT3DTEXTURE9 breachlogo = NULL;
LPDIRECT3DTEXTURE9 chamberlogo = NULL;
LPDIRECT3DTEXTURE9 deadlocklogo = NULL;
LPDIRECT3DTEXTURE9 fadelogo = NULL;
LPDIRECT3DTEXTURE9 gekkologo = NULL;
LPDIRECT3DTEXTURE9 kayologo = NULL;
LPDIRECT3DTEXTURE9 killjoylogo = NULL;
LPDIRECT3DTEXTURE9 omenlogo = NULL;
LPDIRECT3DTEXTURE9 razelogo = NULL;
LPDIRECT3DTEXTURE9 skyelogo = NULL;
LPDIRECT3DTEXTURE9 sovalogo = NULL;
LPDIRECT3DTEXTURE9 harborlogo = NULL;
LPDIRECT3DTEXTURE9 yorulogo = NULL;
LPDIRECT3DTEXTURE9 vyselogo = NULL;
LPDIRECT3DTEXTURE9 tejologo = NULL;
LPDIRECT3DTEXTURE9 waylalogo = NULL;
LPDIRECT3DTEXTURE9 layreLogo = NULL;

ImFont* AVERISONTOP;

uintptr_t root_comp;
uintptr_t pawn;
uintptr_t baseee = 0x0;
int g_daysLeftGlobal = 0;

uintptr_t for_actor = 0;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;
int screen_width = GetSystemMetrics(SM_CXSCREEN);
int screen_height = GetSystemMetrics(SM_CYSCREEN);
static auto spike_plant_time = std::chrono::steady_clock::now();

float spiketime = 0.0f;
uintptr_t spikeactor;
bool resetspike = false;
DWORD64 image_base;
static HWND Window = NULL;
static LPDIRECT3DDEVICE9 D3dDevice;
static LPDIRECT3D9EX p_Object;
static D3DPRESENT_PARAMETERS d3dpp;
IDirect3DSwapChain9* TriBuf;
HWND hwndVAL = NULL;
RECT GameRect = { NULL };
const MARGINS Margin = { -1 };
DWORD ScreenCenterX = 960;
DWORD ScreenCenterY = 540;
MSG Message = { NULL };
bool menu_open = true;
bool first_time = true;
bool imguiStarted = false;
#define DegreeToRadian( Degree )	( ( Degree ) * ( M_PI / 180.0f ) )



LPDIRECT3DTEXTURE9 LoadPNGToTextureDX9(
	LPDIRECT3DDEVICE9 d3dDevice,
	unsigned char* pngData,
	int dataSize)
{
	Spoof_Address;
	LPDIRECT3DTEXTURE9 texture = NULL;
	HRESULT hr = D3DXCreateTextureFromFileInMemory(d3dDevice, pngData, dataSize, &texture);
	if (FAILED(hr))
		return NULL;
	return texture;
}

void debugPrint(const char* /*type*/, const char* /*any*/) {}
void debugPrint(const char* /*type*/, const uintptr_t /*any*/) {}

enum class EAresOutlineMode : uint8_t {
	None = 0,
	Outline = 1,
	Block = 2,
	Enemy = 3,
	AlwaysOutline = 4,
	AlwaysEnemy = 5,
	EAresOutlineMode_MAX = 6
};



struct FHealthValue {
	float Life;
	float MaximumLife;
};

auto isVisible(DWORD_PTR mesh) -> bool {
	float fLastSubmitTime = driver::read2<float>(mesh + offsets::last_submit_time);
	float fLastRenderTimeOnScreen = driver::read2<float>(mesh + offsets::last_render_time);

	const float fVisionTick = 0.05f;
	bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;

	return bVisible;
}


float Moruk = 0;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

enum class BombSiteEnum
{
	NewEnumerator0 = 0,
	NewEnumerator1 = 1,
	NewEnumerator2 = 2,
	BombSiteEnum_MAX = 3,
};


namespace game
{
	int center_x = GetSystemMetrics(0) / 2;
	int center_y = GetSystemMetrics(1) / 2;

	// Forward declarations
	void RenderVALORANT();
	void STOPTHERENDERVALORANT();
	bool DirectXVALORANT();

	double Width, Height = 0.f;
	class fvector {
	public:
		fvector() : x(0.f), y(0.f), z(0.f) {}
		fvector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
		~fvector() {}
			
		double x;
		double y;
		double z;

		inline double Dot(fvector v) {
			return x * v.x + y * v.y + z * v.z;
		}

		inline double distance(fvector v) {
			return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
		}

		inline float Distance23(fvector v)
		{
			double x = this->x - v.x;
			double y = this->y - v.y;
			double z = this->z - v.z;

			return sqrtf((x * x) + (y * y) + (z * z)) * 0.03048f;
		}

		fvector operator+(fvector v) {
			return fvector(x + v.x, y + v.y, z + v.z);
		}

		fvector operator-(fvector v) {
			return fvector(x - v.x, y - v.y, z - v.z);
		}
		fvector operator/(double flDiv) {
			return fvector(x / flDiv, y / flDiv, z / flDiv);
		}

		fvector operator*(double Scale) {

			return fvector(x * Scale, y * Scale, z * Scale);
		}
		inline double Length() {
			return sqrtf((x * x) + (y * y) + (z * z));
		}
		fvector operator-=(fvector v) {

			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
	};


	struct FVector2D
	{
	public:
		double x;
		double y;

		inline FVector2D() : x(0), y(0) {}
		inline FVector2D(double x, double y) : x(x), y(y) {}

		inline double Distance(FVector2D v) {
			return sqrtf(((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
		}

		inline FVector2D operator+(const FVector2D& v) const {
			return FVector2D(x + v.x, y + v.y);
		}

		inline FVector2D operator-(const FVector2D& v) const {
			return FVector2D(x - v.x, y - v.y);
		}

	};
	D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
	}

	struct FMinimalViewInfo {
		struct fvector Location;
		struct fvector Rotation;
		float FOV;
	};

	struct fquat {
		double x;
		double y;
		double z;
		double w;
	};

	struct ftransform {
		fquat rot;
		fvector translation;
		char pad[4];
		fvector scale;
		char pad1[4];
		D3DMATRIX ToMatrixWithScale() {
			D3DMATRIX m;
			m._41 = translation.x;
			m._42 = translation.y;
			m._43 = translation.z;

			float x2 = rot.x + rot.x;
			float y2 = rot.y + rot.y;
			float z2 = rot.z + rot.z;

			float xx2 = rot.x * x2;
			float yy2 = rot.y * y2;
			float zz2 = rot.z * z2;
			m._11 = (1.0f - (yy2 + zz2)) * scale.x;
			m._22 = (1.0f - (xx2 + zz2)) * scale.y;
			m._33 = (1.0f - (xx2 + yy2)) * scale.z;

			float yz2 = rot.y * z2;
			float wx2 = rot.w * x2;
			m._32 = (yz2 - wx2) * scale.z;
			m._23 = (yz2 + wx2) * scale.y;

			float xy2 = rot.x * y2;
			float wz2 = rot.w * z2;
			m._21 = (xy2 - wz2) * scale.y;
			m._12 = (xy2 + wz2) * scale.x;
			
			float xz2 = rot.x * z2;
			float wy2 = rot.w * y2;
			m._31 = (xz2 + wy2) * scale.z;
			m._13 = (xz2 - wy2) * scale.x;

			m._14 = 0.0f;
			m._24 = 0.0f;
			m._34 = 0.0f;
			m._44 = 1.0f;

			return m;
		}
	};
	fvector ControlRotation;
	namespace math
	{
		D3DMATRIX matrix(fvector rot, fvector origin = fvector(0, 0, 0)) {
			float radPitch = (rot.x * float(M_PI) / 180.f);
			float radYaw = (rot.y * float(M_PI) / 180.f);
			float radRoll = (rot.z * float(M_PI) / 180.f);

			float SP = sinf(radPitch);
			float CP = cosf(radPitch);
			float SY = sinf(radYaw);
			float CY = cosf(radYaw);
			float SR = sinf(radRoll);
			float CR = cosf(radRoll);

			D3DMATRIX matrix;
			matrix.m[0][0] = CP * CY;
			matrix.m[0][1] = CP * SY;
			matrix.m[0][2] = SP;
			matrix.m[0][3] = 0.f;

			matrix.m[1][0] = SR * SP * CY - CR * SY;
			matrix.m[1][1] = SR * SP * SY + CR * CY;
			matrix.m[1][2] = -SR * CP;
			matrix.m[1][3] = 0.f;

			matrix.m[2][0] = -(CR * SP * CY + SR * SY);
			matrix.m[2][1] = CY * SR - CR * SP * SY;
			matrix.m[2][2] = CR * CP;
			matrix.m[2][3] = 0.f;

			matrix.m[3][0] = origin.x;
			matrix.m[3][1] = origin.y;
			matrix.m[3][2] = origin.z;
			matrix.m[3][3] = 1.f;

			return matrix;
		}

		D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
		{
			D3DMATRIX pOut;
			pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
			pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
			pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
			pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
			pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
			pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
			pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
			pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
			pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
			pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
			pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
			pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
			pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
			pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
			pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
			pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

			return pOut;
		}
	}

	struct FNameEntryHandle {
		uint16_t bIsWide : 1;
		uint16_t Len : 15;
	};

	struct FNameEntry {

		int32_t ComparisonId;
		FNameEntryHandle Header;
		union
		{
			char    AnsiName[1024];
			wchar_t    WideName[1024];
		};


		wchar_t const* GetWideName() const { return WideName; }
		char const* GetAnsiName() const { return AnsiName; }
		bool IsWide() const { return Header.bIsWide; }
	};

	int LocalUID;


	static bool InsideCircle(float xc, float yc, float r, float x, float y)
	{

		float dx = xc - x;
		float dy = yc - y;
		return dx * dx + dy * dy <= r * r;
	}

	enum class EAresEquippableState : uint8_t
	{
		Unknown = 0,
		Idle = 1,
		Equipping = 2,
		Inspecting = 3,
		Attacking = 4,
		Firing = 5,
		Reloading = 6,
		ADS_Idle = 7,
		ADS_Firing = 8,
		Count = 9,
		EAresEquippableState_MAX = 10,
	};

	std::string GetEquippableVFXState(EAresEquippableState STATE) {
		static std::string strReloading = skCrypt("Reloading..").decrypt();
		static std::string strInspecting = skCrypt("Inspecting").decrypt();
		static std::string strShooting = skCrypt("Shooting").decrypt();
		static std::string strNotMoving = skCrypt("Not moving").decrypt();

		switch (STATE) {
		case EAresEquippableState::Reloading:
			return strReloading;
		case EAresEquippableState::Inspecting:
			return strInspecting;
		case EAresEquippableState::Firing:
		case EAresEquippableState::ADS_Firing:
		case EAresEquippableState::Attacking:
			return strShooting;
		default:
			return strNotMoving;
		}
	}


	double GetCrossDistance(double x1, double y1, double x2, double y2)
	{
		return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	}

	float CalculateDistanceW(const fvector& a, const fvector& b) {
		return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2) + powf(a.z - b.z, 2));
	}

	float CalculateDistance(int p1x, int p1y, int p2x, int p2y)
	{
		float diffY = p1y - p2y;
		float diffX = p1x - p2x;
		return sqrt((diffY * diffY) + (diffX * diffX));
	}

	float clamp(float value, float min, float max) {
		return (value < min) ? min : (value > max) ? max : value;
	}


	float Lerp(float start, float end, float t)
	{
		return start + t * (end - start);
	}

	struct BoneCache {
		uintptr_t actor;
		uintptr_t bone_array;
		INT32 bone_count;
		float last_health;
		DWORD64 last_update;
		bool is_bot;
	};
	std::vector<BoneCache> bone_cache;
	const DWORD64 CACHE_TIMEOUT = 30000; 

	static ULONG Widthee = GetSystemMetrics(SM_CXSCREEN) ;
	static ULONG Heightee = GetSystemMetrics(SM_CYSCREEN) ;

	static bool IsInScreen(fvector Pos) {
		if (((Pos.x <= 0 or Pos.x > Widthee) and (Pos.y <= 0 or Pos.y > Heightee)) or ((Pos.x <= 0 or Pos.x > Widthee) or (Pos.y <= 0 or Pos.y > Heightee))) {
			return false;
		}
		else {
			return true;
		}
	}

	static bool IsVec3Valid(fvector vec3)
	{
		return !(vec3.x == 0 && vec3.y == 0 && vec3.z == 0);
	}


	float DistanceBetweenCross(float X, float Y)
	{
		int ScreenCenterXEB = GetSystemMetrics(SM_CXSCREEN) / 2;
		int ScreenCenterYEB = GetSystemMetrics(SM_CYSCREEN) / 2;

		float ydist = (Y - ScreenCenterYEB);
		float xdist = (X - ScreenCenterXEB);
		float Hypotenuse = sqrt(pow(ydist, 2) + pow(xdist, 2));
		return Hypotenuse;
	}

	float Clamp(float value, float min, float max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	void AimAtPosV2(int screenwidth, int screenheight, float x, float y, float speed, float lock, bool smooth) {
		if (x == 0 && y == 0) return;

		float ScreenCenterX = screenwidth / 2.0f;
		float ScreenCenterY = screenheight / 2.0f;

		float deltaX = x - ScreenCenterX;
		float deltaY = y - ScreenCenterY;

		float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
		if (distance < 0.5f) return;

		static double overflowX = 0.0;
		static double overflowY = 0.0;
		static bool wasLocked = false;

		if (!is_locked && wasLocked) {
			overflowX = 0.0;
			overflowY = 0.0;
		}
		wasLocked = is_locked;

		if (smooth) {
			float smoothVal = config.aimbot_smooth;
			if (smoothVal < 1.0f) smoothVal = 1.0f;

			float strength;
			if (smoothVal <= 1.0f) {
				strength = 1.0f;
			}
			else {
				float base = 1.0f / smoothVal;
				if (distance > 100.0f) {
					strength = base * 1.8f;
				}
				else if (distance > 20.0f) {
					float t = (distance - 20.0f) / 80.0f;
					strength = base * (0.6f + 1.2f * t);
				}
				else {
					float t = distance / 20.0f;
					strength = base * (0.3f + 0.3f * t);
				}
			}

			double moveX = (double)deltaX * strength + overflowX;
			double moveY = (double)deltaY * strength + overflowY;

			int intX, intY;
			if (moveX >= 0) {
				intX = (int)moveX;
				overflowX = moveX - intX;
			}
			else {
				intX = (int)moveX;
				if (moveX != (double)intX) intX--;
				overflowX = moveX - intX;
			}
			if (moveY >= 0) {
				intY = (int)moveY;
				overflowY = moveY - intY;
			}
			else {
				intY = (int)moveY;
				if (moveY != (double)intY) intY--;
				overflowY = moveY - intY;
			}

			if (intX == 0 && intY == 0 && distance > 1.0f) {
				if (fabs(overflowX) > fabs(overflowY)) {
					intX = (overflowX > 0) ? 1 : -1;
					overflowX -= intX;
				}
				else {
					intY = (overflowY > 0) ? 1 : -1;
					overflowY -= intY;
				}
			}

			if (intX != 0 || intY != 0) {
				driver::move_mouse(intX, intY, 0);
			}
		}
		else {
			overflowX = 0.0;
			overflowY = 0.0;
			driver::move_mouse((int)deltaX, (int)deltaY, 0);
		}
	}

	float GetElapsedTime() {
		static LARGE_INTEGER frequency;
		static LARGE_INTEGER startTime;
		if (frequency.QuadPart == 0) {
			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&startTime);
		}
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return static_cast<float>(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
	}

	const char* healthtype[3] = { "Text Health", "Bar Health", "Both Health" };
	const char* healthposition[4] = { "Left", "Right", "Top", "Bottom" };
	const char* Snapline_type[3] = { "Top Snapline", "Crosshair Snapline", "Bottom Snapline" };
	const char* SkeletonType[2] = { "Skeleton Accurate", "Skeleton 2" };

	class PrecisePatternUWorldFinder {
	private:
		uintptr_t pml4_base;
		uintptr_t pattern_prefix;
		std::vector<uintptr_t> priority_offsets;

		void initializeOffsets() {
			priority_offsets.clear();

			priority_offsets.push_back(0x170);
			priority_offsets.push_back(0x100);
			priority_offsets.push_back(0x130);
			priority_offsets.push_back(0x160);
			priority_offsets.push_back(0x190);
			priority_offsets.push_back(0x40);
			priority_offsets.push_back(0xC0);
			priority_offsets.push_back(0xE0);
			priority_offsets.push_back(0xA0);
			priority_offsets.push_back(0xB0);
			priority_offsets.push_back(0xD0);
			priority_offsets.push_back(0xF0);
			priority_offsets.push_back(0x1a0);


			for (uintptr_t offset = 0x10; offset <= 0x300; offset += 0x10) {
				if (std::find(priority_offsets.begin(), priority_offsets.end(), offset) == priority_offsets.end()) {
					priority_offsets.push_back(offset);
				}
			}
		}

		bool matchesExactPattern(uintptr_t addr) {
			if (addr == 0) return false;
			if ((addr & 0x7) != 0) return false; 

			uintptr_t high_pattern = (addr >> 40) & 0xFFFFF;

			if (high_pattern == (pattern_prefix >> 40)) {
				return true;
			}

			return false;
		}

		bool isValidPointer(uintptr_t addr) {
			return (
				addr > (pml4_base + 0x1000) &&   
				addr < 0x7FFFFFFFFFFF &&      
				(addr & 0x7) == 0      
				);
		}
		
		bool verifyUWorld(uintptr_t candidate) {
			try {
				uintptr_t first_value = driver::read<uintptr_t>(candidate);
				return isValidPointer(first_value);
			}
			catch (...) {
				return false;
			}
		}

	
	public:
		PrecisePatternUWorldFinder(uintptr_t pml4) : pml4_base(pml4) {

			pattern_prefix = pml4_base & 0xFFFFF00000000;

			initializeOffsets();
		}

		bool isFromSameRegion(uintptr_t addr) {
			if (!isValidPointer(addr)) return false;

			return ((addr & 0xFFFFF00000000) == (pml4_base & 0xFFFFF00000000));
		}

		uintptr_t findUWorld() {

			for (uintptr_t offset : priority_offsets) {
				try {
					uintptr_t value = driver::read<uintptr_t>(pml4_base + offset);
					if (!isValidPointer(value)) continue;

					if (isFromSameRegion(value)) {
						if (verifyUWorld(value)) {
							return value;
						}
					}
				}
				catch (...) {}
			}

			// no valid UWorld found
			return 0;
		}

		void debugScan() {
			printf(skCrypt("\n[DEBUG] Scanning offsets for pattern 0x%llXXXXXXX:\n").decrypt(), pattern_prefix >> 40);

			for (size_t i = 0; i < 10 && i < priority_offsets.size(); i++) {
				uintptr_t offset = priority_offsets[i];
				try {
					uintptr_t value = driver::read<uintptr_t>(pml4_base + offset);
					if (value != 0) {
						// scan log removed
					}
				}
				catch (...) {}
			}
		}
	};
		
	//std::wstring get_riot_name(uint64_t actor) {
	//	const auto platform_player = driver::read<uint64_t>(actor + 0x608);

	//	const auto riot_user = driver::read<TArrayE>(platform_player + 0x3D8);

	//	wchar_t* buffer = new wchar_t[riot_user.count + 1];
	//	driver.read_physical(riot_user.data, (uintptr_t*)buffer, riot_user.count * sizeof(wchar_t));
	//	std::wstring ws(buffer);
	//	delete[] buffer;

	//	return ws;
	//}

	typedef          __int64 ll;
	typedef unsigned __int64 ull;
	typedef          char   int8;
	typedef   signed char   sint8;
	typedef unsigned char   uint8;
	typedef          short  int16;
	typedef   signed short  sint16;
	typedef unsigned short  uint16;
	typedef          int    int32;
	typedef   signed int    sint32;
	typedef unsigned int    uint32;
	typedef ll              int64;
	typedef ll              sint64;
	typedef ull             uint64;
	typedef unsigned int uint;


	// rotate left
	template<class T> T __ROL__(T value, int count)
	{
		const uint nbits = sizeof(T) * 8;

		if (count > 0)
		{
			count %= nbits;
			T high = value >> (nbits - count);
			if (T(-1) < 0) // signed value
				high &= ~((T(-1) << count));
			value <<= count;
			value |= high;
		}
		else
		{
			count = -count % nbits;
			T low = value << (nbits - count);
			value >>= count;
			value |= low;
		}
		return value;
	}
		
	inline uint8  __ROL1__(uint8  value, int count) { return __ROL__((uint8)value, count); }
	inline uint16 __ROL2__(uint16 value, int count) { return __ROL__((uint16)value, count); }
	inline uint32 __ROL4__(uint32 value, int count) { return __ROL__((uint32)value, count); }
	inline uint64 __ROL8__(uint64 value, int count) { return __ROL__((uint64)value, count); }
	inline uint8  __ROR1__(uint8  value, int count) { return __ROL__((uint8)value, -count); }
	inline uint16 __ROR2__(uint16 value, int count) { return __ROL__((uint16)value, -count); }
	inline uint32 __ROR4__(uint32 value, int count) { return __ROL__((uint32)value, -count); }
	inline uint64 __ROR8__(uint64 value, int count) { return __ROL__((uint64)value, -count); }

	
	uint64_t g_NameXorKey = 0;
	std::uint64_t decrypt_xor_keys(const uint32_t key, const uint64_t* state) {
		const uint64_t hash = 0x2545F4914F6CDD1DULL * (key ^ ((key ^ (key >> 15)) >> 12) ^ (key << 25));
		const uint64_t idx = hash % 7;
		uint64_t val = state[idx];
		const uint32_t hi = (uint32_t)(hash >> 32);
		const uint32_t mod7 = (uint32_t)(idx) % 7;

		if (mod7 == 0) {
			uint64_t step1 = (val >> 1) ^ (((val >> 1) ^ (2 * val)) & 0xAAAAAAAAAAAAAAAAULL);
			uint64_t step2 = (step1 >> 2) ^ (((step1 >> 2) ^ (4 * step1)) & 0xCCCCCCCCCCCCCCCCULL);
			uint64_t step3 = (step2 >> 4) ^ (((step2 >> 4) ^ (16 * step2)) & 0xF0F0F0F0F0F0F0F0ULL);
			uint64_t step4 = (step3 >> 8) ^ (((step3 >> 8) ^ (step3 << 8)) & 0xFF00FF00FF00FF00ULL);
			val = _rotr64(step4, 32) - hi;
		}
		else if (mod7 == 1) {
			uint8_t r = 63 * (uint8_t)(((int)hi + (int)idx) / 0x3F) - ((uint8_t)hi + (uint8_t)idx) + 63;
			uint8_t l = (uint8_t)(((int)hi + (int)idx) % 0x3F) + 1;
			val = (~val >> r) | (~val << l);
		}
		else if (mod7 == 2) {
			val = (~(uint64_t)(uint32_t)(hi + 2 * idx) ^ val) - (uint32_t)(hi + idx);
		}
		else if (mod7 == 3) {
			uint8_t r = 63 * (uint8_t)(((int)hi + 2 * (int)idx) / 0x3F) - ((uint8_t)hi + 2 * (uint8_t)idx) + 63;
			uint8_t l = (uint8_t)(((int)hi + 2 * (int)idx) % 0x3F) + 1;
			uint64_t temp = (val >> r) | (val << l);
			val = (temp >> 1) ^ (((temp >> 1) ^ (2 * temp)) & 0xAAAAAAAAAAAAAAAAULL);
		}
		else if (mod7 == 4) {
			uint8_t l = 63 * (uint8_t)(((int)hi + (int)idx) / 0x3F) - ((uint8_t)hi + (uint8_t)idx) + 63;
			uint8_t r = (uint8_t)(((int)hi + (int)idx) % 0x3F) + 1;
			val = (~val << l) | (~val >> r);
		}
		else if (mod7 == 5) {
			uint64_t temp = val - (uint32_t)(hi + 2 * idx);
			uint8_t l = 63 * (uint8_t)(((int)hi + (int)idx) / 0x3F) - ((uint8_t)hi + (uint8_t)idx) + 63;
			uint8_t r = (uint8_t)(((int)hi + (int)idx) % 0x3F) + 1;
			val = (temp << l) | (temp >> r);
		}
		else if (mod7 == 6) {
			val ^= (uint32_t)(hi + idx);
		}

		return val ^ key;
	}

	std::uint64_t decrypt_gworld(const uint32_t key, const uint64_t* state) {
		const uint64_t hash = 0x2545F4914F6CDD1DULL * (key ^ ((key ^ (key >> 15)) >> 12) ^ (key << 25));
		const uint64_t idx = hash % 7;
		uint64_t val = state[idx];
		const uint32_t hi = (uint32_t)(hash >> 32);
		const uint32_t mod7 = (uint32_t)(idx) % 7;

		if (mod7 == 0) {
			uint64_t temp = val + hi;
			uint64_t step1 = (temp >> 1) ^ (((temp >> 1) ^ (2 * temp)) & 0xAAAAAAAAAAAAAAAAULL);
			uint64_t step2 = (step1 >> 2) ^ (((step1 >> 2) ^ (4 * step1)) & 0xCCCCCCCCCCCCCCCCULL);
			uint64_t step3 = (step2 >> 4) ^ (((step2 >> 4) ^ (16 * step2)) & 0xF0F0F0F0F0F0F0F0ULL);
			uint64_t step4 = (step3 >> 8) ^ (((step3 >> 8) ^ (step3 << 8)) & 0xFF00FF00FF00FF00ULL);
			val = _rotr64(step4, 32);
		}
		else if (mod7 == 1) {
			uint8_t l = 63 * (uint8_t)(((int)hi + (int)idx) / 0x3F) - ((uint8_t)hi + (uint8_t)idx) + 63;
			uint8_t r = (uint8_t)(((int)hi + (int)idx) % 0x3F) + 1;
			val = ~((val << l) | (val >> r));
		}
		else if (mod7 == 2) {
			val = ~(uint64_t)(uint32_t)(hi + 2 * idx) ^ ((uint32_t)(hi + idx) + val);
		}
		else if (mod7 == 3) {
			uint64_t step1 = (val >> 1) ^ (((val >> 1) ^ (2 * val)) & 0xAAAAAAAAAAAAAAAAULL);
			uint8_t l = 63 * (uint8_t)(((int)hi + 2 * (int)idx) / 0x3F) - ((uint8_t)hi + 2 * (uint8_t)idx) + 63;
			uint8_t r = (uint8_t)(((int)hi + 2 * (int)idx) % 0x3F) + 1;
			val = (step1 << l) | (step1 >> r);
		}
		else if (mod7 == 4) {
			uint64_t temp = val - (uint32_t)(hi + idx);
			uint8_t r = 63 * (uint8_t)(((int)hi + 2 * (int)idx) / 0x3F) - ((uint8_t)hi + 2 * (uint8_t)idx) + 63;
			uint8_t l = (uint8_t)(((int)hi + 2 * (int)idx) % 0x3F) + 1;
			val = (temp >> r) | (temp << l);
		}
		else if (mod7 == 5) {
			uint64_t step1 = (val >> 1) ^ (((val >> 1) ^ (2 * val)) & 0xAAAAAAAAAAAAAAAAULL);
			uint64_t step2 = (step1 >> 2) ^ (((step1 >> 2) ^ (4 * step1)) & 0xCCCCCCCCCCCCCCCCULL);
			uint64_t step3 = (step2 >> 4) ^ (((step2 >> 4) ^ (16 * step2)) & 0xF0F0F0F0F0F0F0F0ULL);
			uint64_t step4 = (step3 >> 8) ^ (((step3 >> 8) ^ (step3 << 8)) & 0xFF00FF00FF00FF00ULL);
			val = _rotr64(step4, 32);
		}
		else if (mod7 == 6) {
			uint8_t r = 63 * (uint8_t)(((int)hi + (int)idx) / 0x3F) - ((uint8_t)hi + (uint8_t)idx) + 63;
			uint8_t l = (uint8_t)(((int)hi + (int)idx) % 0x3F) + 1;
			val = (uint32_t)(hi + 2 * idx) + ((val >> r) | (val << l));
		}

		return val ^ key;
	}

	bool InitNameDecryption() {
		uint64_t nameKeyAddr = driver::read2<uint64_t>(baseee + offsets::FnameState + 0x38);
		if (!nameKeyAddr) return false;
		struct State { uint64_t keys[7]; };
		State state = driver::read<State>(baseee + offsets::FnameState);
		uintptr_t xorAddr = decrypt_xor_keys(nameKeyAddr, (uint64_t*)&state);
		if (!xorAddr) return false;
		g_NameXorKey = driver::read2<uint64_t>(xorAddr);
		return (g_NameXorKey != 0);
	}

	inline uint32_t BruteForceFNameKey()
	{
		VMProtectBeginUltra(skCrypt("BruteForceFNameKey").decrypt());
		if (!offsets::FnamePool) return 0;

		uintptr_t chunkAddr = baseee + offsets::FnamePool + 2 * 8;
		uintptr_t pool0 = driver::read2<uintptr_t>(chunkAddr);
		if (!pool0 || pool0 < 0x1000000) return 0;

		FNameEntry nameEntry = driver::read<FNameEntry>(pool0);
		uint16_t len = nameEntry.Header.Len;
		if (len != 4) return 0;

		const char* plain = "None";
		uint8_t keyBytes[4] = { 0 };
		for (int i = 0; i < 4; i++) {
			keyBytes[i] = (uint8_t)nameEntry.AnsiName[i] ^ (uint8_t)plain[i] ^ (uint8_t)len;
		}

		return *reinterpret_cast<uint32_t*>(keyBytes);
	}

	bool InitNameDecryption2() {
		VMProtectBeginUltra(skCrypt("AverisFind").decrypt());
		constexpr int max_attempts = 50;
		for (int attempt = 0; attempt < max_attempts; attempt++)
		{
			g_NameXorKey = BruteForceFNameKey();
			if (g_NameXorKey)
				return true;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		return false;
	}

	std::string AVERISTY(int key) {
		uint32_t chunkOffset = (uint32_t)(key >> 16);
		uint16_t nameOffset = (uint16_t)key;
		if (chunkOffset > 8192) return "";
		uint64_t namePoolChunk = driver::read2<uint64_t>(baseee + offsets::FnamePool + ((chunkOffset + 2) * 8));
		if (!namePoolChunk || namePoolChunk < 0x10000) return "";
		uint64_t entryOffset = namePoolChunk + (uint64_t)(4 * nameOffset);
		if (entryOffset + 8 > namePoolChunk + 0x10000) return "";

		struct FNameEntryHeader {
			int32_t ComparisonId;
			FNameEntryHandle Header;
		};

		FNameEntryHeader entryHeader = driver::read<FNameEntryHeader>(entryOffset);
		uint16_t nameLength = entryHeader.Header.Len;
		if (nameLength == 0 || nameLength > 256) return "";
		if (entryOffset + 6 + (uint64_t)nameLength > namePoolChunk + 0x10000) return "";
		
		std::string name;
		name.resize(nameLength);
		driver::readvm((PVOID)(entryOffset + 6), &name[0], nameLength);

		if (nameLength <= 365) {
			for (uint16_t i = 0; i < nameLength; i++) {
				BYTE b = i & 3;
				name[i] ^= entryHeader.Header.Len ^ *((LPBYTE)&g_NameXorKey + b);
			}
		}

		size_t nullPos = name.find('\0');
		if (nullPos != std::string::npos) {
			name = name.substr(0, nullPos);
		}

		return name;
	}

	namespace guarded_pointers
	{
		uintptr_t guard_local_pawn = offsets::Sikreat;
		uintptr_t guard_controller = offsets::Sikreat;
	}
	namespace LocalPlayerSX
	{
		uintptr_t local_pawn;
		uintptr_t local_pawn_old;
		uintptr_t player_controller;
		uintptr_t camera_manager;
		fvector camera_position;
		int ping;
	}

	namespace camera
	{
		fvector location;
		fvector rotation;
		float fov;
	}

	namespace fonts {
		ImFont* standard_font;
		ImFont* intro_font;
	}

	struct player
	{
		uintptr_t for_actor;
		uintptr_t for_mesh;

		uintptr_t actor;
		uintptr_t mesh;
		uintptr_t bone_array;
		uintptr_t root_component;
		uintptr_t damage_handler;

		INT32 bone_count;
		INT32 ammo_count;

		std::string weapon_name;
		std::string agent_name;
		std::string player_name;

		float distance;
		float health;
		float shield;

		bool is_valid;
		bool is_damage_handler_guarded;
		bool is_mesh_guarded;

		bool is_ally;
		uintptr_t playerstate;
		int cached_agent_id;
		std::string cached_agent_raw;
		std::string cached_decrypted_agent;
		bool agent_cached;
		ImTextureID cached_agent_logo;
		bool logo_cached;

		uintptr_t cached_platform_player;
		bool platform_player_cached;
		int cached_competitive_tier;
		int32_t cached_account_level;
		uint16_t cached_ping;
		int stat_update_counter;

		float hp_smooth = 100.f;
		int weapon_icon_id = -1;

		bool isVisible() {
			float fLastSubmitTime = driver::read2<float>(mesh + offsets::last_submit_time);
			float fLastRenderTimeOnScreen = driver::read2<float>(mesh + offsets::last_render_time);

			const float fVisionTick = 0.05f;
			bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;

			return bVisible;
		}
	};



	std::vector<player> player_pawns;

	inline bool operator==(const player& a, const player& b) {
		return a.actor == b.actor;
	}

	fvector CalcAngle(fvector src, fvector dst)
	{
		fvector angle;
		angle.x = -atan2f(dst.x - src.y, dst.y - src.y) / M_PI * 180.0f + 180.0f;
		angle.y = asinf((dst.z - src.z) / src.distance(dst)) * 180.0f / M_PI;
		angle.z = 0.0f;

		return angle;
	}

	fvector CalcAngleBackSideRotation(fvector src, fvector dst)
	{
		fvector angle;
		fvector delta = fvector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

		double hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

		angle.x = atanf(delta.z / hyp) * (180.0f / hyp);
		angle.y = atanf(delta.y / delta.x) * (180.0f / M_PI);
		angle.z = 0;
		if (delta.x >= 0.0) angle.y += 180.0f;


		return angle;
	}

	void Clamp(fvector& Ang) {
		if (Ang.x < 0.f)
			Ang.x += 360.f;

		if (Ang.x > 360.f)
			Ang.x -= 360.f;

		if (Ang.y < 0.f) Ang.y += 360.f;
		if (Ang.y > 360.f) Ang.y -= 360.f;
		Ang.z = 0.f;
	}

	void draw_text(const char* content, ImVec2 screen_position, ImVec4 color, bool outlined, bool background) {
		ImVec2 text_size = ImGui::CalcTextSize(content);
		if (background) {
			ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(screen_position.x - 4, screen_position.y - 2), ImVec2(screen_position.x + text_size.x + 4, screen_position.y + text_size.y + 2), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 0.6f }), 4.f);
		}

		if (outlined) {
			ImGui::GetForegroundDrawList()->AddText(ImVec2(screen_position.x + 1, screen_position.y + 1), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), content);
		}

		ImGui::GetForegroundDrawList()->AddText(screen_position, ImGui::GetColorU32({ color.x, color.y, color.z, color.w }), content);
	}

	auto RectFilled(float x, float y, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags) -> void
	{
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
	}

	void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 153.0, color->B / 51.0, color->A / 255.0)), 0, 0);
	}


	uintptr_t context_cr3 = 0;

	typedef struct ShadowRegionsDataStructure
	{
		uintptr_t OriginalPML4_t;
		uintptr_t ClonedPML4_t;
		uintptr_t GameCr3;
		uintptr_t ClonedCr3;
		uintptr_t FreeIndex;
	} ShadowRegionsDataStructure;

	/*uintptr_t DecryptClonedCr3(uintptr_t VgkAddress, uintptr_t qword_1)
	{
		std::string ud = skCrypt("vgk.sys").decrypt();
		uintptr_t vgk = driver.KernelModule(ud);

		auto qword_2 = *(uintptr_t*)(vgk + 0x81B50);
		auto byte_1 = *(uint8_t*)(vgk + 0x81A90);

		uintptr_t v5 = (0x49B74B6480000000i64 * qword_1
			+ 0xC2D8B464B4418C6Cui64 * ~(unsigned __int64)(unsigned __int8)byte_1
			+ 0x66B8CDC1FFFFFFFFi64 * (unsigned __int8)byte_1
			+ 0x5C1FE6A2B4418C6Di64
			* ((unsigned __int8)(byte_1 & qword_1)
				- (qword_1 | ~(unsigned __int64)(unsigned __int8)byte_1)))
			* ((qword_1 ^ (unsigned __int8)byte_1)
				+ -2 * ((unsigned __int8)byte_1 ^ (qword_1 | (unsigned __int8)byte_1))
				+ 2
				* ((((unsigned __int8)byte_1 | 0xE8i64) ^ 0xFFFFFFFFFFFFFF17ui64)
					+ (~qword_1 | (unsigned __int8)byte_1 ^ 0xE8i64))
				- ((unsigned __int8)byte_1 ^ (unsigned __int64)~qword_1 ^ 0xE8)
				+ -3 * ~qword_1
				- 232);d

		uintptr_t v6 = ((qword_1 ^ (qword_1 * (0x13D0F34E00000000i64 * qword_1 + 0x483C4F8900000000i64))) << 63)
			+ qword_1
			* (0x7D90DC33C620C593i64 * (0x13D0F34E00000000i64 * qword_1 + 0x483C4F8900000000i64)
				+ 0x8000000000000000ui64)
			+ (qword_1
				* (0x55494E5B80000000i64 * qword_2
					+ 0xC83B18136241A38Dui64 * ~qword_2
					+ 0xCE3CE5E180000000ui64 * ~qword_1
					+ 0x72F1C9B7E241A38Di64 * ((qword_2 | 0xE8) - (231i64 - ((unsigned __int8)qword_2 & 0xE8))))
				+ 0x71C31A1E80000000i64)
			* (0x99BF7D2380CF6EC3ui64 * qword_2
				+ 0x664082DC7F30913Ei64 * (qword_1 | (unsigned __int8)byte_1)
				+ 0x19BF7D2380CF6EC2i64 * ~qword_2
				+ 0xE64082DC7F30913Eui64 * (~qword_1 & ~(unsigned __int64)(unsigned __int8)byte_1)
				+ ((qword_1
					+ ((unsigned __int8)byte_1 & (qword_2 ^ qword_1))
					+ (qword_2 | (unsigned __int8)byte_1)) << 63));

		uintptr_t DecryptedCr3 = 0x137FEEF6AB38CFB4i64 * v5
			+ ((~v5 ^ ~((0x8000000000000001ui64 * qword_2
				+ 0x2FDBF65F8A4AC9C9i64 * qword_1
				+ ((qword_2 ^ qword_1) << 63)
				+ 0x502409A075B53637i64 * qword_1)
				* (0xFD90DC33C620C592ui64
					* ~(qword_1 * (0x13D0F34E00000000i64 * qword_1 + 0x483C4F8900000000i64))
					+ v6
					+ 0x2183995CC620C592i64))) << 63)
			+ 0x6C80110954C7304Di64 * ((v5 & qword_2) - (~qword_2 & ~v5) - qword_2)
			- 0x7FFFFFFFFFFFFFFFi64
			* (0x8000000000000001ui64 * qword_2
				+ 0x2FDBF65F8A4AC9C9i64 * qword_1
				+ ((qword_2 ^ qword_1) << 63)
				+ 0x502409A075B53637i64 * qword_1)
			* (0xFD90DC33C620C592ui64 * ~(qword_1 * (0x13D0F34E00000000i64 * qword_1 + 0x483C4F8900000000i64))
				+ v6
				+ 0x2183995CC620C592i64)
			- 0x4F167C5CD4C7304Ei64;


		return DecryptedCr3;
	}*/

	auto decrypt_cloned_cr3_simplified(uintptr_t cloned_cr3) -> uintptr_t
	{
		uintptr_t Last = cloned_cr3 & 0xFFFFFFFFF;
		uintptr_t FirstDigit = Last >> 32 & 0xF;
		uintptr_t LastDigit = Last & 0xF;

		FirstDigit -= 1;
		LastDigit -= 1;

		return FirstDigit << 27 | Last & 0x0FFFFFFF0 | LastDigit;
	}


	struct ShadowData {
		uintptr_t DecryptedClonedCr3;
		uintptr_t PML4BASE;
	};



	uintptr_t get_uworld(uintptr_t pointer)
	{
		uintptr_t uworld_address = driver::read<uintptr_t>(pointer + offsets::WorldGuarded);
		uintptr_t uworld_offset = 0;
		 uworld_offset = uworld_address - 0x8000000000;
		return pointer + uworld_offset;
	}

	void DrawRightProgressBar(int x, int y, int w, int h, int thick, int m_health)
	{
		int G = (255 * m_health / 100);
		int R = 255 - G;
		RGBA healthcol = { R, G, 0, 255 };

		DrawFilledRect(x + (w / 2) - 25, y, thick, (h)*m_health / 100, &healthcol);
	}

	auto DrawHealthBar(float x, float y, float w, float h, int phealth, bool Outlined) -> void
	{
		auto vList = ImGui::GetForegroundDrawList();

		int healthValue = max(0, min(phealth, 100));

		ImColor barColor = ImColor
		(
			min(510 * (100 - healthValue) / 100, 255), min(510 * healthValue / 100, 255),
			25,
			255
		);
		if (Outlined)
			vList->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0.f, 0.f, 0.f), 0.0f, 0, 1.0f);

		RectFilled(x, y, x + w, y + (int)(((float)h / 100.0f) * (float)phealth), barColor, 0.0f, 0);
	}

	float read_visible(player _player, int num)
	{
		return driver::read<float>(_player.for_mesh + _player.mesh + num);
	}

	bool is_dormant(player _player)
	{
		return driver::read<bool>(_player.for_actor + _player.actor + offsets::dormant);
	}

	fvector WorldToScreen(fvector world_location) {
		float FovAngle = camera::fov;
		fvector ScreenLocation;
		D3DMATRIX tempMatrix = math::matrix(camera::rotation, fvector(0, 0, 0));
		fvector vAxisX, vAxisY, vAxisZ;
		vAxisX = fvector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = fvector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = fvector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
		fvector vDelta = world_location - camera::location;
		fvector vTransformed = fvector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
		if (vTransformed.z < 0.1f)
			vTransformed.z = 0.1f;

		float ScreenCenterX = center_x;
		float ScreenCenterY = center_y;

		float scale = ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f);

		ScreenLocation.x = ScreenCenterX + vTransformed.x * scale / vTransformed.z;
		ScreenLocation.y = ScreenCenterY - vTransformed.y * scale / vTransformed.z;
		return ScreenLocation;
	}
		

	void DrawLine1(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
	{
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
	}

	static void DrawLine(int x1, int y1, int x2, int y2, ImU32 color, int thickness)
	{
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thickness);
	}

	void BoxSpike(fvector Root, ImU32 ESPColor, int Thickness)
	{
		int xz = 40;
		int uzunluk = 40;
		fvector Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
		Pos0 = Root;
		Pos0.z = Pos0.z + 40;
		Pos1 = Pos0 + fvector(-xz, -xz, uzunluk);
		Pos2 = Pos0 + fvector(-xz, -xz, -uzunluk);
		Pos3 = Pos0 + fvector(xz, -xz, -uzunluk);
		Pos4 = Pos0 + fvector(xz, -xz, uzunluk);
		Pos5 = Pos0 + fvector(-xz, xz, uzunluk);
		Pos6 = Pos0 + fvector(-xz, xz, -uzunluk);
		Pos7 = Pos0 + fvector(xz, xz, -uzunluk);
		Pos8 = Pos0 + fvector(xz, xz, uzunluk);
		Pos0 = WorldToScreen(Pos0);
		Pos1 = WorldToScreen(Pos1);
		Pos2 = WorldToScreen(Pos2);
		Pos3 = WorldToScreen(Pos3);
		Pos4 = WorldToScreen(Pos4);
		Pos5 = WorldToScreen(Pos5);
		Pos6 = WorldToScreen(Pos6);
		Pos7 = WorldToScreen(Pos7);
		Pos8 = WorldToScreen(Pos8);
		DrawLine(Pos1.x, Pos1.y, Pos2.x, Pos2.y, ESPColor, Thickness);
		DrawLine(Pos2.x, Pos2.y, Pos3.x, Pos3.y, ESPColor, Thickness);
		DrawLine(Pos3.x, Pos3.y, Pos4.x, Pos4.y, ESPColor, Thickness);
		DrawLine(Pos4.x, Pos4.y, Pos1.x, Pos1.y, ESPColor, Thickness);
		DrawLine(Pos5.x, Pos5.y, Pos6.x, Pos6.y, ESPColor, Thickness);
		DrawLine(Pos6.x, Pos6.y, Pos7.x, Pos7.y, ESPColor, Thickness);
		DrawLine(Pos7.x, Pos7.y, Pos8.x, Pos8.y, ESPColor, Thickness);
		DrawLine(Pos8.x, Pos8.y, Pos5.x, Pos5.y, ESPColor, Thickness);
		DrawLine(Pos1.x, Pos1.y, Pos5.x, Pos5.y, ESPColor, Thickness);
		DrawLine(Pos2.x, Pos2.y, Pos6.x, Pos6.y, ESPColor, Thickness);
		DrawLine(Pos3.x, Pos3.y, Pos7.x, Pos7.y, ESPColor, Thickness);
		DrawLine(Pos4.x, Pos4.y, Pos8.x, Pos8.y, ESPColor, Thickness);
	}


	boolean in_rect(double centerX, double centerY, double radius, double x, double y) {
		return x >= centerX - radius && x <= centerX + radius &&
			y >= centerY - radius && y <= centerY + radius;
	}


	void normalize(fvector& in)
	{
		if (in.x > 89.f) in.x -= 360.f;
		else if (in.x < -89.f) in.x += 360.f;

		while (in.y > 180)in.y -= 360;
		while (in.y < -180)in.y += 360;
		in.z = 0;
	}

	void NormalizeAngles(fvector& angle)
	{
		while (angle.x > 89.0f)
			angle.x -= 180.f;

		while (angle.x < -89.0f)
			angle.x += 180.f;

		while (angle.y > 180.f)
			angle.y -= 360.f;

		while (angle.y < -180.f)
			angle.y += 360.f;
	}

	float GetFov(const fvector viewAngle, const fvector aimAngle)
	{
		fvector Delta = fvector(aimAngle.x - viewAngle.x, aimAngle.y - viewAngle.y, aimAngle.z - viewAngle.z);
		NormalizeAngles(Delta);
		return sqrt(pow(Delta.x, 2.0f) + pow(Delta.y, 2.0f));
	}

	void ShowWatermark(bool* OpenWindows, const char* Text, ImVec4 Color)
	{
		const float Distance = 10.0f;
		static int corner = 0;
		ImGuiIO& io = ImGui::GetIO();
		ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

		if (io.MousePos.x < 900.0f && io.MousePos.y < 800.0f)
		{
			if (corner != -1)
			{
				WindowFlags |= ImGuiWindowFlags_NoMove;
				ImVec2 WindowPosPivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
				ImVec2 WindowPos = ImVec2((corner & 1) ? io.DisplaySize.x - Distance : Distance, (corner & 2) ? io.DisplaySize.y - Distance : Distance);
				ImGui::SetNextWindowPos(WindowPos, ImGuiCond_Always, WindowPosPivot);

			}
			ImGui::SetNextWindowBgAlpha(0.05f);
			if (ImGui::Begin(skCrypt("Render").decrypt(), OpenWindows, WindowFlags))
			{
				ImGui::TextColored(Color, Text);
				ImGui::End();
			}
		}
		else
		{
			if (corner != -1)
			{
				WindowFlags |= ImGuiWindowFlags_NoMove;
				ImVec2 WindowPosPivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
				ImVec2 WindowPos = ImVec2((corner & 1) ? io.DisplaySize.x - Distance : Distance, (corner & 2) ? io.DisplaySize.y - Distance : Distance);
				ImGui::SetNextWindowPos(WindowPos, ImGuiCond_Always, WindowPosPivot);

			}
			ImGui::SetNextWindowBgAlpha(0.35f);
			if (ImGui::Begin(skCrypt("Render1").decrypt(), OpenWindows, WindowFlags))
			{
				ImGui::TextColored(Color, Text);
				ImGui::End();
			}
		}
	}

	fvector SmoothAim(fvector Camera_rotation, fvector Target, float SmoothFactor)
	{
		fvector diff = Target - Camera_rotation;
		normalize(diff);

		return Camera_rotation + diff / SmoothFactor;
	}




	//auto get_guarded_region() -> const std::uintptr_t
	//{
	//	const auto validate_region = [&](std::uintptr_t address) -> bool {
	//		static uintptr_t filter = 0xFFFFFFFF00000000;
	//		uintptr_t result = address & filter;

	//		return bool(result == 0x8000000000 || result == 0x10000000000);
	//		};

	//	std::string VGKnigger = skCrypt("vgk.sys").decrypt();

	//	const auto vgk_address = driver.KernelModule(VGKnigger);
	//	if (vgk_address) {
	//		auto allocated_pool = driver::read<std::uintptr_t>(vgk_address + offsets::vgk_pool_offset);
	//		if (allocated_pool) {
	//			if (validate_region(allocated_pool)) {
	//				return allocated_pool & 0xFFFFFF;
	//			}

	//			return allocated_pool;
	//		}
	//	}

	//	return 0;
	//}



	float degree_to_radian(float degree)
	{
		return degree * (M_PI / 180);
	}

	void angle_rotation(const fvector& angles, fvector* forward)
	{
		float	sp, sy, cp, cy;

		sy = sin(degree_to_radian(angles.y));
		cy = cos(degree_to_radian(angles.y));

		sp = sin(degree_to_radian(angles.x));
		cp = cos(degree_to_radian(angles.x));

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	fvector AVERISBONE(int index, player _player)
	{

		size_t size = sizeof(ftransform);
		ftransform first_bone = driver::read<ftransform>(_player.bone_array + (size * index));
		ftransform comp_to_world = driver::read<ftransform>(_player.mesh + offsets::component_to_world);
		D3DMATRIX matrix = math::MatrixMultiplication(first_bone.ToMatrixWithScale(), comp_to_world.ToMatrixWithScale());
		return fvector(matrix._41, matrix._42, matrix._43);
	}

	fvector AVERISBONE_CACHED(int index, player _player, const D3DMATRIX& c2w_matrix)
	{
		size_t size = sizeof(ftransform);
		ftransform first_bone = driver::read<ftransform>(_player.bone_array + (size * index));
		D3DMATRIX matrix = math::MatrixMultiplication(first_bone.ToMatrixWithScale(), c2w_matrix);
		return fvector(matrix._41, matrix._42, matrix._43);
	}

	fvector BoneFromBatch(int index, ftransform* bones, const D3DMATRIX& c2w_matrix)
	{
		D3DMATRIX matrix = math::MatrixMultiplication(bones[index].ToMatrixWithScale(), c2w_matrix);
		return fvector(matrix._41, matrix._42, matrix._43);
	}

	void RCS(fvector Target, fvector Camera_rotation, float SmoothFactor) {

		fvector ConvertRotation = Camera_rotation;
		normalize(ConvertRotation);

		auto ControlRotation = driver::read<fvector>(LocalPlayerSX::player_controller + offsets::control_rotation);
		fvector DeltaRotation = ConvertRotation - ControlRotation;
		normalize(DeltaRotation);

		ConvertRotation = Target - (DeltaRotation * SmoothFactor);
		normalize(ConvertRotation);

		fvector Smoothed = SmoothAim(Camera_rotation, ConvertRotation, SmoothFactor);
		Smoothed -= (DeltaRotation / SmoothFactor);
		Clamp(Smoothed);
		normalize(Smoothed);
		driver::write<fvector>(LocalPlayerSX::player_controller + offsets::control_rotation, (fvector)Smoothed);
		return;
	}


	//LPD3DXFONT font;

	void DrawString(int x, int y, DWORD color, const char* fmt, DWORD TRPE = 0)
	{
		ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y), color, fmt);
	}

	void DrawCircleFilled1(int x, int y, int radius, RGBA* color)
	{
		ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
	}

	void draw_3d_box(fvector base, fvector top_reach, float wide, ImColor col, float thickness)
	{

		fvector bottom_rect_1 = fvector(base.x + wide, base.y + wide, base.z);
		fvector bottom_rect_2 = fvector(base.x + wide, base.y - wide, base.z);
		fvector bottom_rect_3 = fvector(base.x - wide, base.y + wide, base.z);
		fvector bottom_rect_4 = fvector(base.x - wide, base.y - wide, base.z);

		fvector top_rect_1 = fvector(top_reach.x + wide, top_reach.y + wide, top_reach.z);
		fvector top_rect_2 = fvector(top_reach.x + wide, top_reach.y - wide, top_reach.z);
		fvector top_rect_3 = fvector(top_reach.x - wide, top_reach.y + wide, top_reach.z);
		fvector top_rect_4 = fvector(top_reach.x - wide, top_reach.y - wide, top_reach.z);

		bottom_rect_1 = WorldToScreen(bottom_rect_1);
		bottom_rect_2 = WorldToScreen(bottom_rect_2);
		bottom_rect_3 = WorldToScreen(bottom_rect_3);
		bottom_rect_4 = WorldToScreen(bottom_rect_4);

		top_rect_1 = WorldToScreen(top_rect_1);
		top_rect_2 = WorldToScreen(top_rect_2);
		top_rect_3 = WorldToScreen(top_rect_3);
		top_rect_4 = WorldToScreen(top_rect_4);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImVec2(bottom_rect_2.x, bottom_rect_2.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImVec2(bottom_rect_4.x, bottom_rect_4.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImVec2(bottom_rect_3.x, bottom_rect_3.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImVec2(bottom_rect_1.x, bottom_rect_1.y), col, thickness);

		ImGui::GetForegroundDrawList()->AddLine(ImVec2(top_rect_1.x, top_rect_1.y), ImVec2(top_rect_2.x, top_rect_2.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(top_rect_2.x, top_rect_2.y), ImVec2(top_rect_4.x, top_rect_4.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(top_rect_4.x, top_rect_4.y), ImVec2(top_rect_3.x, top_rect_3.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(top_rect_3.x, top_rect_3.y), ImVec2(top_rect_1.x, top_rect_1.y), col, thickness);

		ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImVec2(top_rect_1.x, top_rect_1.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImVec2(top_rect_2.x, top_rect_2.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImVec2(top_rect_3.x, top_rect_3.y), col, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImVec2(top_rect_4.x, top_rect_4.y), col, thickness);
	}

	void DrawFilledRect2(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.0f);
	}


	void DrawNormalBox(int x, int y, int w, int h, int borderPx, ImColor color)
	{
		ImDrawList* p = ImGui::GetForegroundDrawList();

		p->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0, 160), 0.0f, 0, 1.0f);
		p->AddRect(ImVec2(x + 1, y + 1), ImVec2(x + w - 1, y + h - 1), ImColor(0, 0, 0, 160), 0.0f, 0, 1.0f);
		p->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.0f, 0, borderPx);
	}

	fvector mathMULTIPLICATION(fvector src, fvector dst)
	{
		fvector angle;
		angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / M_PI * 180.0f + 180.0f;
		angle.y = asinf((dst.z - src.z) / src.distance(dst)) * 180.0f / M_PI;
		angle.z = 0.0f;

		return angle;
	}

	fvector CaadadalcAngle(fvector src, fvector dst)
	{
		fvector angle;
		fvector delta = fvector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

		double hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

		angle.x = atanf(delta.z / hyp) * (180.0f / hyp);
		angle.y = atanf(delta.y / delta.x) * (180.0f / M_PI);
		angle.z = 0;
		if (delta.x >= 0.0) angle.y += 180.0f;

		return angle;
	}

	void draw_corner_box(int x, int y, int w, int h, ImColor col, int thickness) {
		float lineW = (w / 4.0f); 
		float lineH = (h / 4.0f);
		ImDrawList* p = ImGui::GetForegroundDrawList();

		auto drawOutlinedLine = [&](ImVec2 start, ImVec2 end) {
			p->AddLine(start, end, ImColor(0, 0, 0, 150), thickness + 2.0f);
			p->AddLine(start, end, col, thickness);
		};

		drawOutlinedLine(ImVec2(x, y), ImVec2(x, y + lineH));
		drawOutlinedLine(ImVec2(x, y), ImVec2(x + lineW, y));
		drawOutlinedLine(ImVec2(x + w - lineW, y), ImVec2(x + w, y));
		drawOutlinedLine(ImVec2(x + w, y), ImVec2(x + w, y + lineH));
		drawOutlinedLine(ImVec2(x, y + h - lineH), ImVec2(x, y + h));
		drawOutlinedLine(ImVec2(x, y + h), ImVec2(x + lineW, y + h));
		drawOutlinedLine(ImVec2(x + w - lineW, y + h), ImVec2(x + w, y + h));
		drawOutlinedLine(ImVec2(x + w, y + h - lineH), ImVec2(x + w, y + h));
	}

	void draw_head_box_corners(float posX, float posY, float width, float height, ImColor color, float thickness) {
		float X = posX - (width / 2.0f);
		float Y = posY;
		float lW = width / 3.0f;
		float lH = height / 3.0f;

		auto* dl = ImGui::GetForegroundDrawList();
		dl->AddLine(ImVec2(X, Y), ImVec2(X, Y + lH), ImColor(0, 0, 0, 100), thickness + 1.0f);
		dl->AddLine(ImVec2(X, Y), ImVec2(X + lW, Y), ImColor(0, 0, 0, 100), thickness + 1.0f);
		dl->AddLine(ImVec2(X + width - lW, Y), ImVec2(X + width, Y), ImColor(0, 0, 0, 100), thickness + 1.0f);
		dl->AddLine(ImVec2(X + width, Y), ImVec2(X + width, Y + lH), ImColor(0, 0, 0, 100), thickness + 1.0f);
		dl->AddLine(ImVec2(X, Y + height - lH), ImVec2(X, Y + height), ImColor(0, 0, 0, 100), thickness + 1.0f);
		dl->AddLine(ImVec2(X, Y + height), ImVec2(X + lW, Y + height), ImColor(0, 0, 0, 100), thickness + 1.0f);
		dl->AddLine(ImVec2(X + width - lW, Y + height), ImVec2(X + width, Y + height), ImColor(0, 0, 0, 100), thickness + 1.0f);
		dl->AddLine(ImVec2(X + width, Y + height - lH), ImVec2(X + width, Y + height), ImColor(0, 0, 0, 100), thickness + 1.0f);

		dl->AddLine(ImVec2(X, Y), ImVec2(X, Y + lH), color, thickness);
		dl->AddLine(ImVec2(X, Y), ImVec2(X + lW, Y), color, thickness);
		dl->AddLine(ImVec2(X + width - lW, Y), ImVec2(X + width, Y), color, thickness);
		dl->AddLine(ImVec2(X + width, Y), ImVec2(X + width, Y + lH), color, thickness);
		dl->AddLine(ImVec2(X, Y + height - lH), ImVec2(X, Y + height), color, thickness);
		dl->AddLine(ImVec2(X, Y + height), ImVec2(X + lW, Y + height), color, thickness);
		dl->AddLine(ImVec2(X + width - lW, Y + height), ImVec2(X + width, Y + height), color, thickness);
		dl->AddLine(ImVec2(X + width, Y + height - lH), ImVec2(X + width, Y + height), color, thickness);
	}

	void RenderVALORANTK(fvector first_bone_position, fvector second_bone_position, ImColor color, float thinkness) {
		fvector first_bone_screen_position = WorldToScreen(first_bone_position);
		if (!IsInScreen(first_bone_screen_position)) return;
		ImVec2 fist_screen_position = ImVec2(first_bone_screen_position.x, first_bone_screen_position.y);
		
		fvector second_bone_screen_position = WorldToScreen(second_bone_position);
		if (!IsInScreen(second_bone_screen_position)) return;
		ImVec2 second_screen_position = ImVec2(second_bone_screen_position.x, second_bone_screen_position.y);
		
		ImGui::GetForegroundDrawList()->AddLine(fist_screen_position, second_screen_position, ImColor(0, 0, 0, 100), thinkness + 2.0f);
		ImGui::GetForegroundDrawList()->AddLine(fist_screen_position, second_screen_position, color, thinkness);
	}


	void draw_skeleton2(player _player, ImColor maw, float thickness)
	{


		fvector bone_head, bone_neck, bone_chest, bone_pelvis, bone_rshoulder, bone_relbow, bone_rhand, bone_rthigh, bone_rknee, bone_rfoot, bone_lshoulder, bone_lelbow, bone_lhand, bone_lthigh, bone_lknee, bone_lfoot;
		bone_head = AVERISBONE(8, _player);
		bone_chest = AVERISBONE(6, _player);
		bone_pelvis = AVERISBONE(3, _player);


		if (_player.bone_count == 101)
		{
			bone_neck = AVERISBONE(21, _player);

			bone_lshoulder = AVERISBONE(23, _player);
			bone_lelbow = AVERISBONE(24, _player);
			bone_lhand = AVERISBONE(25, _player);

			bone_rshoulder = AVERISBONE(49, _player);
			bone_relbow = AVERISBONE(50, _player);
			bone_rhand = AVERISBONE(51, _player);

			bone_lthigh = AVERISBONE(75, _player);
			bone_lknee = AVERISBONE(76, _player);
			bone_lfoot = AVERISBONE(78, _player);

			bone_rthigh = AVERISBONE(82, _player);
			bone_rknee = AVERISBONE(83, _player);
			bone_rfoot = AVERISBONE(85, _player);
		}
		else if (_player.bone_count == 103)
		{
			bone_neck = AVERISBONE(9, _player);

			bone_lshoulder = AVERISBONE(33, _player);
			bone_lelbow = AVERISBONE(30, _player);
			bone_lhand = AVERISBONE(32, _player);

			bone_rshoulder = AVERISBONE(58, _player);
			bone_relbow = AVERISBONE(55, _player);
			bone_rhand = AVERISBONE(57, _player);

			bone_lthigh = AVERISBONE(63, _player);
			bone_lknee = AVERISBONE(65, _player);
			bone_lfoot = AVERISBONE(69, _player);

			bone_rthigh = AVERISBONE(77, _player);
			bone_rknee = AVERISBONE(79, _player);
			bone_rfoot = AVERISBONE(83, _player);
		}
		else if (_player.bone_count == 104)
		{
			bone_neck = AVERISBONE(21, _player);

			bone_lshoulder = AVERISBONE(23, _player);
			bone_lelbow = AVERISBONE(24, _player);
			bone_lhand = AVERISBONE(25, _player);

			bone_rshoulder = AVERISBONE(49, _player);
			bone_relbow = AVERISBONE(50, _player);
			bone_rhand = AVERISBONE(51, _player);

			bone_lthigh = AVERISBONE(77, _player);
			bone_lknee = AVERISBONE(78, _player);
			bone_lfoot = AVERISBONE(80, _player);

			bone_rthigh = AVERISBONE(84, _player);
			bone_rknee = AVERISBONE(85, _player);
			bone_rfoot = AVERISBONE(87, _player);
		}

		bone_head = WorldToScreen(bone_head);
		bone_neck = WorldToScreen(bone_neck);
		bone_chest = WorldToScreen(bone_chest);
		bone_pelvis = WorldToScreen(bone_pelvis);
		bone_lshoulder = WorldToScreen(bone_lshoulder);
		bone_lelbow = WorldToScreen(bone_lelbow);
		bone_lhand = WorldToScreen(bone_lhand);
		bone_rshoulder = WorldToScreen(bone_rshoulder);
		bone_relbow = WorldToScreen(bone_relbow);
		bone_rhand = WorldToScreen(bone_rhand);
		bone_lthigh = WorldToScreen(bone_lthigh);
		bone_lknee = WorldToScreen(bone_lknee);
		bone_lfoot = WorldToScreen(bone_lfoot);
		bone_rthigh = WorldToScreen(bone_rthigh);
		bone_rknee = WorldToScreen(bone_rknee);
		bone_rfoot = WorldToScreen(bone_rfoot);

		if (!IsInScreen(bone_head) || !IsInScreen(bone_neck) || !IsInScreen(bone_chest) ||
			!IsInScreen(bone_pelvis) || !IsInScreen(bone_lshoulder) || !IsInScreen(bone_lelbow) ||
			!IsInScreen(bone_lhand) || !IsInScreen(bone_rshoulder) || !IsInScreen(bone_relbow) ||
			!IsInScreen(bone_rhand) || !IsInScreen(bone_lthigh) || !IsInScreen(bone_lknee) ||
			!IsInScreen(bone_lfoot) || !IsInScreen(bone_rthigh) || !IsInScreen(bone_rknee) ||
			!IsInScreen(bone_rfoot)) {
			return;
		}

		ImDrawList* draw = ImGui::GetForegroundDrawList();

		auto drawBoneLine = [&](ImVec2 start, ImVec2 end) {
			draw->AddLine(start, end, ImColor(0,0,0,255), thickness + 2.0f);
			draw->AddLine(start, end, maw, thickness);
		};

		drawBoneLine(ImVec2(bone_head.x, bone_head.y), ImVec2(bone_neck.x, bone_neck.y));
		drawBoneLine(ImVec2(bone_neck.x, bone_neck.y), ImVec2(bone_chest.x, bone_chest.y));
		drawBoneLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_pelvis.x, bone_pelvis.y));

		drawBoneLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_rshoulder.x, bone_rshoulder.y));
		drawBoneLine(ImVec2(bone_rshoulder.x, bone_rshoulder.y), ImVec2(bone_relbow.x, bone_relbow.y));
		drawBoneLine(ImVec2(bone_relbow.x, bone_relbow.y), ImVec2(bone_rhand.x, bone_rhand.y));

		drawBoneLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_lshoulder.x, bone_lshoulder.y));
		drawBoneLine(ImVec2(bone_lshoulder.x, bone_lshoulder.y), ImVec2(bone_lelbow.x, bone_lelbow.y));
		drawBoneLine(ImVec2(bone_lelbow.x, bone_lelbow.y), ImVec2(bone_lhand.x, bone_lhand.y));

		drawBoneLine(ImVec2(bone_pelvis.x, bone_pelvis.y), ImVec2(bone_rthigh.x, bone_rthigh.y));
		drawBoneLine(ImVec2(bone_rthigh.x, bone_rthigh.y), ImVec2(bone_rknee.x, bone_rknee.y));
		drawBoneLine(ImVec2(bone_rknee.x, bone_rknee.y), ImVec2(bone_rfoot.x, bone_rfoot.y));

		drawBoneLine(ImVec2(bone_pelvis.x, bone_pelvis.y), ImVec2(bone_lthigh.x, bone_lthigh.y));
		drawBoneLine(ImVec2(bone_lthigh.x, bone_lthigh.y), ImVec2(bone_lknee.x, bone_lknee.y));
		drawBoneLine(ImVec2(bone_lknee.x, bone_lknee.y), ImVec2(bone_lfoot.x, bone_lfoot.y));
	}


	void Bones(player _player, ImVec4 col, float thickness)
	{
		ImU32 lineColor = ImGui::GetColorU32({ col.x, col.y, col.z, col.w });
		ImDrawList* draw = ImGui::GetForegroundDrawList();

		fvector bones[16] = {};
		bones[0] = WorldToScreen(AVERISBONE(8, _player));  
		bones[1] = WorldToScreen(AVERISBONE(6, _player));  
		bones[2] = WorldToScreen(AVERISBONE(3, _player)); 

		const int HEAD = 0, CHEST = 1, PELVIS = 2, NECK = 3,
			LSHOULDER = 4, LELBOW = 5, LHAND = 6,
			RSHOULDER = 7, RELBOW = 8, RHAND = 9,
			LTHIGH = 10, LKNEE = 11, LFOOT = 12,
			RTHIGH = 13, RKNEE = 14, RFOOT = 15;

		switch (_player.bone_count) {
		case 101: { 
			bones[NECK] = WorldToScreen(AVERISBONE(21, _player));
			bones[LSHOULDER] = WorldToScreen(AVERISBONE(23, _player));
			bones[LELBOW] = WorldToScreen(AVERISBONE(24, _player));
			bones[LHAND] = WorldToScreen(AVERISBONE(25, _player));
			bones[RSHOULDER] = WorldToScreen(AVERISBONE(49, _player));
			bones[RELBOW] = WorldToScreen(AVERISBONE(50, _player));
			bones[RHAND] = WorldToScreen(AVERISBONE(51, _player));
			bones[LTHIGH] = WorldToScreen(AVERISBONE(75, _player));
			bones[LKNEE] = WorldToScreen(AVERISBONE(76, _player));
			bones[LFOOT] = WorldToScreen(AVERISBONE(78, _player));
			bones[RTHIGH] = WorldToScreen(AVERISBONE(82, _player));
			bones[RKNEE] = WorldToScreen(AVERISBONE(83, _player));
			bones[RFOOT] = WorldToScreen(AVERISBONE(85, _player));
			break;
		}
		case 103: { 
			bones[NECK] = WorldToScreen(AVERISBONE(9, _player));
			bones[LSHOULDER] = WorldToScreen(AVERISBONE(33, _player));
			bones[LELBOW] = WorldToScreen(AVERISBONE(30, _player));
			bones[LHAND] = WorldToScreen(AVERISBONE(32, _player));
			bones[RSHOULDER] = WorldToScreen(AVERISBONE(58, _player));
			bones[RELBOW] = WorldToScreen(AVERISBONE(55, _player));
			bones[RHAND] = WorldToScreen(AVERISBONE(57, _player));
			bones[LTHIGH] = WorldToScreen(AVERISBONE(63, _player));
			bones[LKNEE] = WorldToScreen(AVERISBONE(65, _player));
			bones[LFOOT] = WorldToScreen(AVERISBONE(69, _player));
			bones[RTHIGH] = WorldToScreen(AVERISBONE(77, _player));
			bones[RKNEE] = WorldToScreen(AVERISBONE(79, _player));
			bones[RFOOT] = WorldToScreen(AVERISBONE(83, _player));
			break;
		}
		case 104: {
			bones[NECK] = WorldToScreen(AVERISBONE(21, _player));
			bones[LSHOULDER] = WorldToScreen(AVERISBONE(23, _player));
			bones[LELBOW] = WorldToScreen(AVERISBONE(24, _player));
			bones[LHAND] = WorldToScreen(AVERISBONE(25, _player));
			bones[RSHOULDER] = WorldToScreen(AVERISBONE(49, _player));
			bones[RELBOW] = WorldToScreen(AVERISBONE(50, _player));
			bones[RHAND] = WorldToScreen(AVERISBONE(51, _player));
			bones[LTHIGH] = WorldToScreen(AVERISBONE(77, _player));
			bones[LKNEE] = WorldToScreen(AVERISBONE(78, _player));
			bones[LFOOT] = WorldToScreen(AVERISBONE(80, _player));
			bones[RTHIGH] = WorldToScreen(AVERISBONE(84, _player));
			bones[RKNEE] = WorldToScreen(AVERISBONE(85, _player));
			bones[RFOOT] = WorldToScreen(AVERISBONE(87, _player));
			break;
		}
		}

		auto drawBoneLine = [&](const fvector& start, const fvector& end) {
			if (start.x != 0.0f && start.y != 0.0f && end.x != 0.0f && end.y != 0.0f) {
				draw->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), ImColor(0,0,0,255), thickness + 2.0f);
				draw->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), lineColor, thickness);
			}
			};

		drawBoneLine(bones[NECK], bones[CHEST]);
		drawBoneLine(bones[CHEST], bones[PELVIS]);

		drawBoneLine(bones[CHEST], bones[RSHOULDER]);
		drawBoneLine(bones[RSHOULDER], bones[RELBOW]);
		drawBoneLine(bones[RELBOW], bones[RHAND]);

		drawBoneLine(bones[CHEST], bones[LSHOULDER]);
		drawBoneLine(bones[LSHOULDER], bones[LELBOW]);
		drawBoneLine(bones[LELBOW], bones[LHAND]);

		drawBoneLine(bones[PELVIS], bones[RTHIGH]);
		drawBoneLine(bones[RTHIGH], bones[RKNEE]);
		drawBoneLine(bones[RKNEE], bones[RFOOT]);

		drawBoneLine(bones[PELVIS], bones[LTHIGH]);
		drawBoneLine(bones[LTHIGH], bones[LKNEE]);
		drawBoneLine(bones[LKNEE], bones[LFOOT]);
	}

	auto DrawALine(const ImVec2& x, const ImVec2 y, ImU32 color, const FLOAT width)
	{
		ImGui::GetForegroundDrawList()->AddLine(x, y, color, width);
	}



	void draw_skeleton(player enemy, ImColor color, float thinkness, const D3DMATRIX& c2w_matrix, ftransform* bones = nullptr) {

		int maxBone = enemy.bone_count;
		if (maxBone < 90 || maxBone > 110) return;

		bool owned = false;
		if (!bones) {
			bones = (ftransform*)_alloca(sizeof(ftransform) * maxBone);
			driver::readvm((PVOID)enemy.bone_array, bones, sizeof(ftransform) * maxBone);
			owned = true;
		}

		fvector head_position = BoneFromBatch(8, bones, c2w_matrix);
		fvector neck_position = BoneFromBatch(7, bones, c2w_matrix);
		fvector chest_position = BoneFromBatch(6, bones, c2w_matrix);
		fvector stomach_position = BoneFromBatch(4, bones, c2w_matrix);
		fvector pelvis_position = BoneFromBatch(3, bones, c2w_matrix);
		fvector l_upper_arm_position;
		fvector l_fore_arm_position;
		fvector l_hand_position;
		fvector r_upper_arm_position;
		fvector r_fore_arm_position;
		fvector r_hand_position;
		fvector l_thigh_position;
		fvector l_knee_position;
		fvector l_foot_position;
		fvector r_thigh_position;
		fvector r_knee_position;
		fvector r_foot_position;

		if (enemy.bone_count == 104) {
			l_upper_arm_position = BoneFromBatch(25, bones, c2w_matrix);
			l_fore_arm_position = BoneFromBatch(26, bones, c2w_matrix);
			l_hand_position = BoneFromBatch(27, bones, c2w_matrix);
			r_upper_arm_position = BoneFromBatch(51, bones, c2w_matrix);
			r_fore_arm_position = BoneFromBatch(53, bones, c2w_matrix);
			r_hand_position = BoneFromBatch(53, bones, c2w_matrix);
			l_thigh_position = BoneFromBatch(79, bones, c2w_matrix);
			l_knee_position = BoneFromBatch(80, bones, c2w_matrix);
			l_foot_position = BoneFromBatch(82, bones, c2w_matrix);
			r_thigh_position = BoneFromBatch(86, bones, c2w_matrix);
			r_knee_position = BoneFromBatch(87, bones, c2w_matrix);
			r_foot_position = BoneFromBatch(89, bones, c2w_matrix);
		}
		else if (enemy.bone_count == 101) {
			l_upper_arm_position = BoneFromBatch(25, bones, c2w_matrix);
			l_fore_arm_position = BoneFromBatch(26, bones, c2w_matrix);
			l_hand_position = BoneFromBatch(27, bones, c2w_matrix);
			r_upper_arm_position = BoneFromBatch(51, bones, c2w_matrix);
			r_fore_arm_position = BoneFromBatch(53, bones, c2w_matrix);
			r_hand_position = BoneFromBatch(53, bones, c2w_matrix);
			l_thigh_position = BoneFromBatch(77, bones, c2w_matrix);
			l_knee_position = BoneFromBatch(78, bones, c2w_matrix);
			l_foot_position = BoneFromBatch(80, bones, c2w_matrix);
			r_thigh_position = BoneFromBatch(84, bones, c2w_matrix);
			r_knee_position = BoneFromBatch(85, bones, c2w_matrix);
			r_foot_position = BoneFromBatch(87, bones, c2w_matrix);
		}
		else if (enemy.bone_count == 103) {
			neck_position = BoneFromBatch(7, bones, c2w_matrix);
			l_upper_arm_position = BoneFromBatch(25, bones, c2w_matrix);
			l_fore_arm_position = BoneFromBatch(26, bones, c2w_matrix);
			l_hand_position = BoneFromBatch(27, bones, c2w_matrix);
			r_upper_arm_position = BoneFromBatch(50, bones, c2w_matrix);
			r_fore_arm_position = BoneFromBatch(51, bones, c2w_matrix);
			r_hand_position = BoneFromBatch(52, bones, c2w_matrix);
			l_thigh_position = BoneFromBatch(77, bones, c2w_matrix);
			l_knee_position = BoneFromBatch(78, bones, c2w_matrix);
			l_foot_position = BoneFromBatch(80, bones, c2w_matrix);
			r_thigh_position = BoneFromBatch(84, bones, c2w_matrix);
			r_knee_position = BoneFromBatch(85, bones, c2w_matrix);
			r_foot_position = BoneFromBatch(87, bones, c2w_matrix);
		}
		else if (enemy.bone_count == 106) {
			neck_position = BoneFromBatch(7, bones, c2w_matrix);
			l_upper_arm_position = BoneFromBatch(25, bones, c2w_matrix);
			l_fore_arm_position = BoneFromBatch(26, bones, c2w_matrix);
			l_hand_position = BoneFromBatch(27, bones, c2w_matrix);
			r_upper_arm_position = BoneFromBatch(51, bones, c2w_matrix);
			r_fore_arm_position = BoneFromBatch(52, bones, c2w_matrix);
			r_hand_position = BoneFromBatch(53, bones, c2w_matrix);
			l_thigh_position = BoneFromBatch(79, bones, c2w_matrix);
			l_knee_position = BoneFromBatch(80, bones, c2w_matrix);
			l_foot_position = BoneFromBatch(82, bones, c2w_matrix);
			r_thigh_position = BoneFromBatch(86, bones, c2w_matrix);
			r_knee_position = BoneFromBatch(87, bones, c2w_matrix);
			r_foot_position = BoneFromBatch(89, bones, c2w_matrix);
		}
		else {
			return;
		}

		RenderVALORANTK(head_position, neck_position, color, thinkness);
		RenderVALORANTK(neck_position, chest_position, color, thinkness);
		RenderVALORANTK(neck_position, l_upper_arm_position, color, thinkness);
		RenderVALORANTK(l_upper_arm_position, l_fore_arm_position, color, thinkness);
		RenderVALORANTK(l_fore_arm_position, l_hand_position, color, thinkness);
		RenderVALORANTK(neck_position, r_upper_arm_position, color, thinkness);
		RenderVALORANTK(r_upper_arm_position, r_fore_arm_position, color, thinkness);
		RenderVALORANTK(r_fore_arm_position, r_hand_position, color, thinkness);
		RenderVALORANTK(chest_position, stomach_position, color, thinkness);
		RenderVALORANTK(stomach_position, pelvis_position, color, thinkness);
		RenderVALORANTK(pelvis_position, l_thigh_position, color, thinkness);
		RenderVALORANTK(l_thigh_position, l_knee_position, color, thinkness);
		RenderVALORANTK(l_knee_position, l_foot_position, color, thinkness);
		RenderVALORANTK(pelvis_position, r_thigh_position, color, thinkness);
		RenderVALORANTK(r_thigh_position, r_knee_position, color, thinkness);
		RenderVALORANTK(r_knee_position, r_foot_position, color, thinkness);
	}


	void TextHealth(ImVec2 min, ImVec2 max, float health)
	{
		float health_percentage = health;
		health_percentage *= 0.01f;

		float length_top_to_bottom = max.y - min.y;
		length_top_to_bottom *= health_percentage;

		float healthbar_size_y = 7.f;

		float g = health_percentage * 255.f;
		float r = 255.f - g;
		float b = 0;

		r /= 255.f;
		g /= 255.f;
		b /= 255.f;

		char healthh[54];
		sprintf_s(healthh, "[H: %.f] ", health);
		std::string Out69 = healthh;

		Out69 = std::to_string(static_cast<int32_t>(health));
			ImVec2 TextSize = ImGui::CalcTextSize(Out69.c_str());

		ImVec2 text_position = ImVec2((min.x + max.x - TextSize.x) * 0.5f, min.y - 15.0f);
		ImVec4 text_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

		DrawOutlinedText(AVERISONTOP, Out69.c_str(), text_position, 13.0f, ImGui::GetColorU32({ r, g, b, 1.0f }), true);
	}
	void draw_health_bar_withtext(ImVec2 min, ImVec2 max, float health)
	{
		float health_percentage = health * 0.01f;
		float length_top_to_bottom = (max.y - min.y) * health_percentage;

		float g = health_percentage * 255.f;
		float r = 255.f - g;
		float b = 0.f;

		// Clean outline and background
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(min.x, min.y), ImVec2(max.x, max.y), IM_COL32(0, 0, 0, 100), 2.0f);
		ImGui::GetForegroundDrawList()->AddRect(ImVec2(min.x - 1, min.y - 1), ImVec2(max.x + 1, max.y + 1), IM_COL32(0, 0, 0, 180), 2.0f, 0, 1.0f);

		// Actual health gradient
		if (length_top_to_bottom > 1.0f) {
			ImVec2 p_min = ImVec2(min.x + 1, max.y - length_top_to_bottom + 1);
			ImVec2 p_max = ImVec2(max.x - 1, max.y - 1);
			ImU32 col_top = IM_COL32((int)r, (int)g, (int)b, 255);
			ImU32 col_bot = IM_COL32((int)max(r - 50.f, 0.f), (int)max(g - 50.f, 0.f), (int)b, 255);
			ImGui::GetForegroundDrawList()->AddRectFilledMultiColor(p_min, p_max, col_top, col_top, col_bot, col_bot);
		}

		std::string Out69 = std::to_string(static_cast<int32_t>(health));
		ImVec2 TextSize = ImGui::CalcTextSize(Out69.c_str());

		ImVec2 text_position = ImVec2((min.x + max.x - TextSize.x) * 0.5f, min.y - 16.0f);
		DrawOutlinedText(AVERISONTOP, Out69.c_str(), text_position, 13.0f, IM_COL32((int)r, (int)g, (int)b, 255), true);
	}

	void draw_health_bar(ImVec2 min, ImVec2 max, float health)
	{
		float health_percentage = health * 0.01f;
		if (health_percentage > 1.f) health_percentage = 1.f;
		if (health_percentage < 0.f) health_percentage = 0.f;
		float length_top_to_bottom = (max.y - min.y) * health_percentage;

		ImU32 barColor;
		if (health_percentage > 0.75f)
			barColor = IM_COL32(0, 255, 50, 255);
		else if (health_percentage > 0.5f)
			barColor = IM_COL32(180, 255, 0, 255);
		else if (health_percentage > 0.25f)
			barColor = IM_COL32(255, 200, 0, 255);
		else if (health_percentage > 0.f)
			barColor = IM_COL32(255, 50, 0, 255);
		else
			barColor = IM_COL32(80, 80, 80, 255);

		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(min.x, min.y), ImVec2(max.x, max.y), IM_COL32(0, 0, 0, 150), 2.0f);
		ImGui::GetForegroundDrawList()->AddRect(ImVec2(min.x - 1, min.y - 1), ImVec2(max.x + 1, max.y + 1), IM_COL32(20, 20, 20, 255), 2.0f, 0, 1.0f);

		if (length_top_to_bottom > 1.0f) {
			ImVec2 p_min = ImVec2(min.x + 1, max.y - length_top_to_bottom + 1);
			ImVec2 p_max = ImVec2(max.x - 1, max.y - 1);
			ImGui::GetForegroundDrawList()->AddRectFilled(p_min, p_max, barColor, 1.0f);
		}
	}

	void draw_health_bar_gradient(ImVec2 min, ImVec2 max, float display_health, float real_health, ImVec4 grad_top, ImVec4 grad_bottom, bool vertical)
	{
		ImDrawList* dl = ImGui::GetForegroundDrawList();

		float hp = display_health;
		if (hp > 100.f) hp = 100.f;
		if (hp < 0.f) hp = 0.f;
		float pct = hp * 0.01f;

		ImU32 c_top = ImGui::ColorConvertFloat4ToU32(grad_top);
		ImU32 c_bot = ImGui::ColorConvertFloat4ToU32(grad_bottom);

		if (vertical) {
			float filled_h = (max.y - min.y) * pct;
			if (filled_h > 1.f) {
				ImVec2 p_min = ImVec2(min.x, max.y - filled_h);
				ImVec2 p_max = ImVec2(max.x, max.y);
				dl->AddRectFilledMultiColor(p_min, p_max, c_top, c_top, c_bot, c_bot);
			}
			float real_h = (max.y - min.y) * (real_health * 0.01f);
			float ry = max.y - real_h;
			if (ry > min.y && ry < max.y)
				dl->AddLine(ImVec2(min.x, ry), ImVec2(max.x, ry), IM_COL32(255, 255, 0, 255), 1.0f);
		} 		else {
			float filled_w = (max.x - min.x) * pct;
			if (filled_w > 1.f) {
				ImVec2 p_min = ImVec2(min.x, min.y);
				ImVec2 p_max = ImVec2(min.x + filled_w, max.y);
				dl->AddRectFilledMultiColor(p_min, p_max, c_top, c_bot, c_bot, c_top);
			}
			float real_w = (max.x - min.x) * (real_health * 0.01f);
			float rx = min.x + real_w;
			if (rx > min.x && rx < max.x)
				dl->AddLine(ImVec2(rx, min.y), ImVec2(rx, max.y), IM_COL32(255, 255, 0, 255), 1.0f);
		}
	}

	void draw_health_bar_flat(ImVec2 min, ImVec2 max, float display_health, float real_health, ImVec4 color, bool vertical)
	{
		ImDrawList* dl = ImGui::GetForegroundDrawList();

		float hp = display_health;
		if (hp > 100.f) hp = 100.f;
		if (hp < 0.f) hp = 0.f;
		float pct = hp * 0.01f;
		ImU32 c = ImGui::ColorConvertFloat4ToU32(color);

		if (vertical) {
			float filled_h = (max.y - min.y) * pct;
			if (filled_h > 1.f)
				dl->AddRectFilled(ImVec2(min.x, max.y - filled_h), ImVec2(max.x, max.y), c);
			float real_h = (max.y - min.y) * (real_health * 0.01f);
			float ry = max.y - real_h;
			if (ry > min.y && ry < max.y)
				dl->AddLine(ImVec2(min.x, ry), ImVec2(max.x, ry), IM_COL32(255, 255, 0, 255), 1.0f);
		} else {
			float filled_w = (max.x - min.x) * pct;
			if (filled_w > 1.f)
				dl->AddRectFilled(ImVec2(min.x, min.y), ImVec2(min.x + filled_w, max.y), c);
			float real_w = (max.x - min.x) * (real_health * 0.01f);
			float rx = min.x + real_w;
			if (rx > min.x && rx < max.x)
				dl->AddLine(ImVec2(rx, min.y), ImVec2(rx, max.y), IM_COL32(255, 255, 0, 255), 1.0f);
		}
	}

	void draw_shield_bar(ImVec2 bar_min, ImVec2 bar_max, float shield)
	{
		float shield_clamped = shield < 0.f ? 0.f : (shield > 50.f ? 50.f : shield);
		float shield_percentage = shield_clamped / 50.f;
		float length_top_to_bottom = (bar_max.y - bar_min.y) * shield_percentage;

		// Clean outline and background
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(bar_min.x, bar_min.y), ImVec2(bar_max.x, bar_max.y), IM_COL32(0, 0, 0, 100), 2.0f);
		ImGui::GetForegroundDrawList()->AddRect(ImVec2(bar_min.x - 1, bar_min.y - 1), ImVec2(bar_max.x + 1, bar_max.y + 1), IM_COL32(0, 0, 0, 180), 2.0f, 0, 1.0f);

		// Actual shield gradient
		if (length_top_to_bottom > 1.0f) {
			ImVec2 p_min = ImVec2(bar_min.x + 1, bar_max.y - length_top_to_bottom + 1);
			ImVec2 p_max = ImVec2(bar_max.x - 1, bar_max.y - 1);
			ImU32 col_top = IM_COL32(30, 180, 255, 255);
			ImU32 col_bot = IM_COL32(20, 130, 200, 255);
			ImGui::GetForegroundDrawList()->AddRectFilledMultiColor(p_min, p_max, col_top, col_top, col_bot, col_bot);
		}
	}


	void Spikenigger() {
		if (resetspike == true) return;
		using namespace std::chrono;
		static auto lastUpdateTime = high_resolution_clock::now();
		static double lastValue = driver::read2<double>(spikeactor + offsets::Spiketime);
		while (true) {
			auto currentValue = driver::read2<double>(spikeactor + offsets::Spiketime);
			auto now = high_resolution_clock::now();

			if (currentValue != lastValue) {
				lastUpdateTime = now;
				lastValue = currentValue;
			}
			else if (duration_cast<seconds>(now - lastUpdateTime).count() >= 6) {
				resetspike = true;	
				break;
			}
			std::this_thread::sleep_for(milliseconds(100));
		}
	}

	auto RelativeLocation(uintptr_t APawn) -> fvector {
		auto RootComponent = driver::read2<uintptr_t>(APawn + offsets::root_component);
		return driver::read<fvector>(RootComponent + offsets::root_position);
	}

	auto RelativeScale(uintptr_t APawn) -> fvector {
		auto RootComponent = driver::read2<uintptr_t>(APawn + offsets::root_component);
		return driver::read<fvector>(RootComponent + offsets::RelativeScale3D);
	}

	int Width4 = GetSystemMetrics(SM_CXSCREEN);
	int Height4 = GetSystemMetrics(SM_CYSCREEN);

	inline void DrawTracers2(fvector Target, ImColor Color)
	{
		ImVec2 start(Width4 / 2, Height4 / 2);
		ImVec2 end(Target.x, Target.y);

		ImGui::GetForegroundDrawList()->AddLine(start, end, Color, 2.0f);
	}

	ImVec4 InterpolateColor(ImVec4 color1, ImVec4 color2, float ratio)
	{
		return ImVec4(
			color1.x + ratio * (color2.x - color1.x),
			color1.y + ratio * (color2.y - color1.y),
			color1.z + ratio * (color2.z - color1.z),
			color1.w + ratio * (color2.w - color1.w)
		);
	}


	inline void DrawCrosshair(int x, int y, int radius, ImVec4 col)
	{
		ImDrawList* draw_list = ImGui::GetForegroundDrawList();
		ImU32 color = ImGui::GetColorU32({ col.x, col.y, col.z, col.w });

		// Draw the outer circle
		draw_list->AddCircle(ImVec2(x, y), radius, color, 100, 2);

		// Draw the inner circle (half the radius of the outer circle)
		draw_list->AddCircle(ImVec2(x, y), radius / 2, color, 100, 2);

		// Draw the vertical line (top to bottom)
		draw_list->AddLine(ImVec2(x, y - radius), ImVec2(x, y + radius), color, 2);

		// Draw the horizontal line (left to right)
		draw_list->AddLine(ImVec2(x - radius, y), ImVec2(x + radius, y), color, 2);
	}


	void spike_esp() {
		if (!config.spiketimer && !config.spiketimerlineup) return;
		if (!spikeactor) return;

		spiketime = resetspike ? 0 : driver::read2<double>(uintptr_t(spikeactor) + offsets::Spiketime);
		if (spiketime <= 0) return;

		auto RelativeLocationn2 = RelativeLocation(spikeactor);

		if (config.spiketimer) {
			ImDrawList* dl = ImGui::GetForegroundDrawList();
			int center_x = screen_width / 2;
			float panelW = 220.0f;
			float barH = 6.0f;
			float panelY = 80.0f;
			float rnd = 6.0f;

			float progress = spiketime / 45.0f;
			if (progress < 0) progress = 0;
			if (progress > 1) progress = 1;

			BombSiteEnum site = driver::read<BombSiteEnum>(uintptr_t(spikeactor) + offsets::Spikeplantedmaw);
			const char* plantedside = "?";
			if (site == BombSiteEnum::NewEnumerator0) plantedside = "A";
			if (site == BombSiteEnum::NewEnumerator1) plantedside = "B";
			if (site == BombSiteEnum::NewEnumerator2) plantedside = "C";

			float defuse = driver::read2<double>(uintptr_t(spikeactor) + offsets::defuse);
			float defusePct = defuse * 100.0f / 6.984602f;
			if (defusePct < 0) defusePct = 0;
			if (defusePct > 100) defusePct = 100;
			bool isDefusing = defuse > 0.01f;

			char timeStr[32];
			snprintf(timeStr, sizeof(timeStr), "%.1fs", spiketime);
			char siteStr[32];
			snprintf(siteStr, sizeof(siteStr), "SPIKE  -  SITE %s", plantedside);

			ImGui::PushFont(AVERISONTOP);

			ImVec2 siteSz = AVERISONTOP->CalcTextSizeA(13.0f, FLT_MAX, 0, siteStr);
			ImVec2 timeSz = AVERISONTOP->CalcTextSizeA(16.0f, FLT_MAX, 0, timeStr);

			float contentH = 13.0f + 6.0f + timeSz.y + 8.0f + barH + (isDefusing ? 20.0f : 0.0f) + 10.0f;
			float panelX = center_x - panelW / 2.0f;
			ImVec2 pMin(panelX, panelY);
			ImVec2 pMax(panelX + panelW, panelY + contentH);

			dl->AddRectFilled(pMin, pMax, IM_COL32(12, 12, 16, 210), rnd);
			dl->AddRect(pMin, pMax, IM_COL32(255, 70, 70, 80), rnd, 15, 1.0f);

			float curY = panelY + 10.0f;
			dl->AddText(AVERISONTOP, 13.0f, ImVec2(center_x - siteSz.x / 2, curY), IM_COL32(200, 200, 200, 200), siteStr);
			curY += 13.0f + 6.0f;

			ImVec4 timeCol;
			if (spiketime > 20) timeCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			else if (spiketime > 10) timeCol = ImVec4(1.0f, 0.85f, 0.3f, 1.0f);
			else timeCol = ImVec4(1.0f, 0.25f, 0.25f, 1.0f);

			dl->AddText(AVERISONTOP, 16.0f, ImVec2(center_x - timeSz.x / 2, curY), ImGui::GetColorU32(timeCol), timeStr);
			curY += timeSz.y + 8.0f;

			float barX = panelX + 12.0f;
			float barW = panelW - 24.0f;
			ImVec2 barMin(barX, curY);
			ImVec2 barMax(barX + barW, curY + barH);
			dl->AddRectFilled(barMin, barMax, IM_COL32(40, 40, 50, 180), barH / 2);

			ImU32 barColL = IM_COL32(255, 60, 60, 255);
			ImU32 barColR = IM_COL32(255, 180, 40, 255);
			if (progress > 0.01f) {
				ImVec2 fillMax(barX + barW * progress, curY + barH);
				dl->AddRectFilled(barMin, fillMax, barColL, barH / 2);
				dl->AddRectFilledMultiColor(barMin, fillMax, barColL, barColR, barColR, barColL);
			}
			curY += barH;

			if (isDefusing) {
				curY += 6.0f;
				char defStr[32];
				snprintf(defStr, sizeof(defStr), "DEFUSING  %.0f%%", defusePct);
				ImVec2 defSz = AVERISONTOP->CalcTextSizeA(12.0f, FLT_MAX, 0, defStr);
				dl->AddText(AVERISONTOP, 12.0f, ImVec2(center_x - defSz.x / 2, curY), IM_COL32(100, 200, 255, 255), defStr);
			}

			ImGui::PopFont();

			auto RelativeLocationProjected2 = WorldToScreen(RelativeLocationn2);
			char worldStr[64];
			snprintf(worldStr, sizeof(worldStr), "%.0fs", spiketime);
			DrawOutlinedText(AVERISONTOP, worldStr, ImVec2(RelativeLocationProjected2.x, RelativeLocationProjected2.y - 20), 14, ImColor(255, 255, 255), true);
		}

		if (config.spiketimerlineup)
		{
					int keyy = driver::read<int>(pawn + offsets::actor_id);
					std::string MyFname = AVERISTY(keyy);

					float distance1 = 50.0f, angle1 = 90.0f;
					float distance2 = 100.0f, angle2 = 76.0f;
					float distance3 = 150.0f, angle3 = 66.0f;
					float distance4 = 200.0f, angle4 = 63.0f;
					float distance5 = 250.0f, angle5 = 48.0f;
					float distance6 = 300.0f, angle6 = 38.0f;
					// Define min and max distances
					float minDistance = 50.0f;
					float maxDistance = 300.0f;

					if (MyFname.find("BountyHunter_PC_C") != std::string::npos) 
					{
						// printf(_("Fade\n"));
						distance1 = 50.0f, angle1 = 50.500f;
						distance2 = 60.0f, angle2 = 40.948f;
						distance3 = 150.0f, angle3 = 40.948f;
						distance4 = 200.0f, angle4 = 40.948f;
						distance5 = 250.0f, angle5 = 40.948f;
						distance6 = 300.0f, angle6 = 40.948f;

						minDistance = 50.0f;
						maxDistance = 60.0f;
					}
					else if (MyFname.find("Sarge_PC_C") != std::string::npos) 
					{
						distance1 = 50.0f, angle1 = 83.501f;
						distance2 = 100.0f, angle2 = 78.293f;
						distance3 = 150.0f, angle3 = 72.214f;
						distance4 = 200.0f, angle4 = 64.395f;
						distance5 = 250.0f, angle5 = 53.105f;
						distance6 = 300.0f, angle6 = 40.079f;

						minDistance = 50.0f;
						maxDistance = 250.0f;
					}

					else if (MyFname.find("Hunter_PC_C") != std::string::npos)
					{
						distance1 = 50.0f, angle1 = 85.237f;
						distance2 = 100.0f, angle2 = 80.895f;
						distance3 = 150.0f, angle3 = 78.290f;
						distance4 = 200.0f, angle4 = 75.100f;
						distance5 = 250.0f, angle5 = 72.212f;
						distance6 = 300.0f, angle6 = 69.606f;

						minDistance = 50.0f;
						maxDistance = 300.0f;
					}
					else if (MyFname.find("Pandemic_PC_C") != std::string::npos) 
					{
						// printf(_("Viper\n"));
						distance1 = 50.0f, angle1 = 82.632f;
						distance2 = 100.0f, angle2 = 76.553f;
						distance3 = 150.0f, angle3 = 68.737f;
						distance4 = 200.0f, angle4 = 58.315f;
						distance5 = 250.0f, angle5 = 42.684f;
						distance6 = 300.0f, angle6 = 31.606f;

						minDistance = 50.0f;
						maxDistance = 250.0f;
					}
					else if (MyFname.find("AggroBot_PC_C") != std::string::npos) // Gekko
					{
						// printf(_("Gekko\n"));
						distance1 = 50.0f, angle1 = 77.421f;
						distance2 = 100.0f, angle2 = 66.131f;
						distance3 = 150.0f, angle3 = 41.815f;
						distance4 = 200.0f, angle4 = 37.315f;
						distance5 = 250.0f, angle5 = 27.684f;
						distance6 = 300.0f, angle6 = 20.606f;

						minDistance = 50.0f;
						maxDistance = 150.0f;
					}
					else if (MyFname.find("Grenadier_PC_C") != std::string::npos) // KAY/O
					{
						// printf(_("KAY/O\n"));
						distance1 = 50.0f, angle1 = 80.896f;
						distance2 = 100.0f, angle2 = 74.818f;
						distance3 = 150.0f, angle3 = 68.739f;
						distance4 = 200.0f, angle4 = 63.526f;
						distance5 = 250.0f, angle5 = 58.316f;
						distance6 = 300.0f, angle6 = 53.106f;

						minDistance = 50.0f;
						maxDistance = 300.0f;
					}
					else if (MyFname.find("Killjoy_PC_C") != std::string::npos) // Killjoy
					{
						// printf(_("Killjoy\n"));
						distance1 = 50.0f, angle1 = 78.290f;
						distance2 = 100.0f, angle2 = 65.263f;
						distance3 = 150.0f, angle3 = 40.946f;
						distance4 = 200.0f, angle4 = 33.999f;
						distance5 = 250.0f, angle5 = 33.999f;
						distance6 = 300.0f, angle6 = 33.999f;

						minDistance = 50.0f;
						maxDistance = 150.0f;
					}
					else if (MyFname.find("Phoenix_PC_C") != std::string::npos) // Phoenix
					{
						//printf(_("Phoenix\n"));
						distance1 = 50.0f, angle1 = 52.236f;
						distance2 = 80.0f, angle2 = 29.657f;
						distance3 = 150.0f, angle3 = 29.657f;
						distance4 = 200.0f, angle4 = 29.657f;
						distance5 = 250.0f, angle5 = 29.657f;
						distance6 = 300.0f, angle6 = 29.657f;

						minDistance = 50.0f;
						maxDistance = 80.0f;
					}
					else if (MyFname.find("Thorne_PC_C") != std::string::npos) // Sage
					{
						//printf(_("Sage\n"));
						distance1 = 50.0f, angle1 = 82.631f;
						distance2 = 100.0f, angle2 = 76.552f;
						distance3 = 150.0f, angle3 = 68.737f;
						distance4 = 200.0f, angle4 = 58.316f;
						distance5 = 250.0f, angle5 = 33.132f;
						distance6 = 300.0f, angle6 = 16.632f;

						minDistance = 50.0f;
						maxDistance = 250.0f;
					}
					else if (MyFname.find("Gumshoe_PC_C") != std::string::npos) // Cypher
					{
						//printf(_("Cypher\n"));
						distance1 = 50.0f, angle1 = 67.001f;
						distance2 = 80.0f, angle2 = 31.395f;
						distance3 = 150.0f, angle3 = 31.395f;
						distance4 = 200.0f, angle4 = 31.395f;
						distance5 = 250.0f, angle5 = 31.395f;
						distance6 = 300.0f, angle6 = 31.395f;

						minDistance = 50.0f;
						maxDistance = 80.0f;
					}


					auto MyRelativeLocationz = RelativeLocation(pawn);


					float SpikeDistance = MyRelativeLocationz.Distance23(RelativeLocationn2);
					angleDegreeszz = angle6; // Default to the furthest angle


					if (SpikeDistance <= distance1)
					{
						angleDegreeszz = angle1;
					}
					else if (SpikeDistance <= distance2)
					{
						float t = (SpikeDistance - distance1) / (distance2 - distance1);
						angleDegreeszz = angle1 + t * (angle2 - angle1);
					}
					else if (SpikeDistance <= distance3)
					{
						float t = (SpikeDistance - distance2) / (distance3 - distance2);
						angleDegreeszz = angle2 + t * (angle3 - angle2);
					}
					else if (SpikeDistance <= distance4)
					{
						float t = (SpikeDistance - distance3) / (distance4 - distance3);
						angleDegreeszz = angle3 + t * (angle4 - angle3);
					}
					else if (SpikeDistance <= distance5)
					{
						float t = (SpikeDistance - distance4) / (distance5 - distance4);
						angleDegreeszz = angle4 + t * (angle5 - angle4);
					}
					else if (SpikeDistance <= distance6)
					{
						float t = (SpikeDistance - distance5) / (distance6 - distance5);
						angleDegreeszz = angle5 + t * (angle6 - angle5);
					}

					const float angleRadians = angleDegreeszz * (M_PI / 180.0f);
					fvector direction = RelativeLocationn2 - MyRelativeLocationz;
					float horizontalDistance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

					const float ScalingFactor = 1.0f;
					float verticalOffset = horizontalDistance * std::tan(angleRadians) * ScalingFactor;

					fvector aimingPosition = RelativeLocationn2;
					aimingPosition.z += verticalOffset;

					fvector aimingPositionW2S = WorldToScreen(aimingPosition);

					// Define colors for min and max distances
					ImVec4 colorMax = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red for close
					ImVec4 colorMin = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Green for far

					float ratio = (SpikeDistance - minDistance) / (maxDistance - minDistance);

					ImVec4 interpolatedColor = InterpolateColor(colorMin, colorMax, ratio);

					if (aimingPositionW2S.x > 0 && aimingPositionW2S.y > 0)
					{
						DrawCrosshair(aimingPositionW2S.x, aimingPositionW2S.y, 10, interpolatedColor);
					}
		}
	}

	float ComputeDistance(ImVec2 point1, ImVec2 point2) {
		return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	}


	std::string DecryptAgent(const std::string& agentEncryptedName) {
		static const std::unordered_map<std::string, std::string> agentMap = {
			{skCrypt("Wushu_PC_C").decrypt(), "Jett"},
			{skCrypt("Rift_PC_C").decrypt(), "Astra"},
			{skCrypt("Grenadier_PC_C").decrypt(), "Kay/O"},
			{skCrypt("Breach_PC_C").decrypt(), "Breach"},
			{skCrypt("Sarge_PC_C").decrypt(), "Brimstone"},
			{skCrypt("Deadeye_PC_C").decrypt(), "Chamber"},
			{skCrypt("Gumshoe_PC_C").decrypt(), "Cypher"},
			{skCrypt("Killjoy_PC_C").decrypt(), "Killjoy"},
			{skCrypt("Sprinter_PC_C").decrypt(), "Neon"},
			{skCrypt("Wraith_PC_C").decrypt(), "Omen"},
			{skCrypt("Phoenix_PC_C").decrypt(), "Phoenix"},
			{skCrypt("Clay_PC_C").decrypt(), "Raze"},
			{skCrypt("Vampire_PC_C").decrypt(), "Reyna"},
			{skCrypt("Thorne_PC_C").decrypt(), "Sage"},
			{skCrypt("Guide_PC_C").decrypt(), "Skye"},
			{skCrypt("Pandemic_PC_C").decrypt(), "Viper"},
			{skCrypt("BountyHunter_PC_C").decrypt(), "Fade"},
			{skCrypt("Stealth_PC_C").decrypt(), "Yoru"},
			{skCrypt("Hunter_PC_C").decrypt(), "Sova"},
			{skCrypt("TrainingBot").decrypt(), "Bot"},
			{skCrypt("AggroBot_PC_C").decrypt(), "Gekko"},
			{skCrypt("Mage_PC_C").decrypt(), "Harbor"},
			{skCrypt("Cable_PC_C").decrypt(), "Deadlock"},
			{skCrypt("Sequoia_PC_C").decrypt(), "Iso"},
			{skCrypt("Smonk_PC_C").decrypt(), "Clove"},
			{skCrypt("Nox_PC_C").decrypt(), "Vyse"},
			{skCrypt("Cashew_PC_C").decrypt(), "Tejo"},
			{skCrypt("Terra_PC_C").decrypt(), "Wayla"},
		};

		for (const auto& [key, value] : agentMap) {
			if (agentEncryptedName.find(key) != std::string::npos) {
				return value.c_str();
			}
		}

		return skCrypt("Unknown").decrypt();
	}

	std::string DecryptWeapon(const std::string& weaponEncryptedName) {
		static const std::unordered_map<std::string, std::string> weaponMap = {
			{skCrypt("Ability_Melee_Base_C").decrypt(), "Melee"},
			{skCrypt("BasePistol_C").decrypt(), "Classic"},
			{skCrypt("DanceHallPistol_C").decrypt(), "Classic"},
			{skCrypt("SawedOffShotgun_C").decrypt(), "Shorty"},
			{skCrypt("AutomaticPistol_C").decrypt(), "Frenzy"},
			{skCrypt("LugerPistol_C").decrypt(), "Ghost"},
			{skCrypt("RevolverPistol_C").decrypt(), "Sheriff"},
			{skCrypt("Vector_C").decrypt(), "Stinger"},
			{skCrypt("SubMachineGun_MP5_C").decrypt(), "Spectre"},
			{skCrypt("AutomaticShotgun_C").decrypt(), "Judge"},
			{skCrypt("PumpShotgun_C").decrypt(), "Bucky"},
			{skCrypt("AssaultRifle_Burst_C").decrypt(), "Bulldog"},
			{skCrypt("DMR_C").decrypt(), "Guardian"},
			{skCrypt("AssaultRifle_ACR_C").decrypt(), "Phantom"},
			{skCrypt("AssaultRifle_AK_C").decrypt(), "Vandal"},
			{skCrypt("LeverSniperRifle_C").decrypt(), "Marshal"},
			{skCrypt("BoltSniper_C").decrypt(), "Operator"},
			{skCrypt("LightMachineGun_C").decrypt(), "Ares"},
			{skCrypt("HeavyMachineGun_C").decrypt(), "Odin"},
			{skCrypt("DS_Gun_C").decrypt(), "Outlaw"},
			{skCrypt("Bomb_C").decrypt(), "Spike"},
		};

		for (const auto& [key, value] : weaponMap) {
			if (weaponEncryptedName.find(key) != std::string::npos) {
				return value.c_str();
			}
		}

		return skCrypt("Abilities").decrypt();
	}

	// Maps a weapon name (friendly or raw FName) to the ValorantGunIcons glyph letter (A-T).
	char WeaponIconChar(const std::string& wname) {
		if (wname.find("Ares") != std::string::npos) return 'A';
		if (wname.find("Bandit") != std::string::npos) return 'B';
		if (wname.find("Bulldog") != std::string::npos) return 'C';
		if (wname.find("Classic") != std::string::npos) return 'D';
		if (wname.find("Frenzy") != std::string::npos) return 'E';
		if (wname.find("Ghost") != std::string::npos) return 'F';
		if (wname.find("Guardian") != std::string::npos) return 'G';
		if (wname.find("Judge") != std::string::npos) return 'H';
		if (wname.find("Melee") != std::string::npos || wname.find("Knife") != std::string::npos ||
		    wname.find("Blade storm") != std::string::npos || wname.find("Overdrive") != std::string::npos) return 'I';
		if (wname.find("Marshal") != std::string::npos) return 'J';
		if (wname.find("Odin") != std::string::npos) return 'K';
		if (wname.find("Operator") != std::string::npos || wname.find("Sniper") != std::string::npos ||
		    wname.find("Tour de force") != std::string::npos) return 'L';
		if (wname.find("Outlaw") != std::string::npos) return 'M';
		if (wname.find("Phantom") != std::string::npos) return 'N';
		if (wname.find("Bucky") != std::string::npos) return 'O';
		if (wname.find("Sheriff") != std::string::npos || wname.find("Headhunter") != std::string::npos) return 'P';
		if (wname.find("Shorty") != std::string::npos) return 'Q';
		if (wname.find("Spectre") != std::string::npos) return 'R';
		if (wname.find("Stinger") != std::string::npos) return 'S';
		if (wname.find("Vandal") != std::string::npos) return 'T';
		return 'D';
	}


	void DrawAgentLogo(const ImVec2& head_w2s, ImTextureID logo)
	{
		ImVec2 position = ImVec2(head_w2s.x - 15, head_w2s.y - 35);
		ImVec2 size = ImVec2(25, 25);
		ImGui::GetForegroundDrawList()->AddImage(
			logo,
			position,
			ImVec2(position.x + size.x, position.y + size.y),
			ImVec2(0, 0),
			ImVec2(1, 1),
			ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f))
		);
	}

	void RenderAgentIcon(const std::string& agentName, const ImVec2& head_w2s)
	{
		static std::unordered_map<std::string, ImTextureID> agentLogoMap = {
			{ skCrypt("Wushu_PC_C").decrypt(),       jettlogo },
			{ skCrypt("Sarge_PC_C").decrypt(),       brimstonelogo },
			{ skCrypt("Gumshoe_PC_C").decrypt(),     cypherlogo },
			{ skCrypt("Sprinter_PC_C").decrypt(),    neonlogo },
			{ skCrypt("Phoenix_PC_C").decrypt(),     phoenixlogo },
			{ skCrypt("Vampire_PC_C").decrypt(),     reynalogo },
			{ skCrypt("Thorne_PC_C").decrypt(),      sagelogo },
			{ skCrypt("Pandemic_PC_C").decrypt(),    viperlogo },
			{ skCrypt("TrainingBot").decrypt(),      botlogo },
			{ skCrypt("Breach_PC_C").decrypt(),      breachlogo },
			{ skCrypt("Rift_PC_C").decrypt(),        astralogo },
			{ skCrypt("Deadeye_PC_C").decrypt(),     chamberlogo },
			{ skCrypt("Killjoy_PC_C").decrypt(),     killjoylogo },
			{ skCrypt("Wraith_PC_C").decrypt(),      omenlogo },
			{ skCrypt("Clay_PC_C").decrypt(),        razelogo },
			{ skCrypt("Guide_PC_C").decrypt(),       skyelogo },
			{ skCrypt("BountyHunter_PC_C").decrypt(),fadelogo },
			{ skCrypt("Hunter_PC_C").decrypt(),      sovalogo },
			{ skCrypt("Stealth").decrypt(),          yorulogo },
			{ skCrypt("AggroBot_PC_C").decrypt(),    gekkologo },
			{ skCrypt("Smonk_PC_C").decrypt(),       clovelogo },
		};

		for (const auto& [agent, logo] : agentLogoMap)
		{
			if (agentName.find(agent) != std::string::npos)
			{
				DrawAgentLogo(head_w2s, logo);
				break;
			}
		}
	}


	struct Agent {
		struct Ability {
			fvector location;
			uintptr_t actor_id;
			std::string objname;
			bool reset = false;
			Ability(uintptr_t actor_id, std::string objname) : actor_id(actor_id), objname(objname) {}
		};

		std::vector<Ability> c, q, e, x;
		void addC(uintptr_t actor_id, std::string objname) {
			c.emplace_back(actor_id, objname);
		}

		void addQ(uintptr_t actor_id, std::string objname) {
			q.emplace_back(actor_id, objname);
		}

		void addE(uintptr_t actor_id, std::string objname) {
			e.emplace_back(actor_id, objname);
		}
		void addX(uintptr_t actor_id, std::string objname) {
			x.emplace_back(actor_id, objname);
		}

		void removeC(uintptr_t actor_id) {
			removeAbility(c, actor_id);
		}

		void removeQ(uintptr_t actor_id) {
			removeAbility(q, actor_id);
		}

		void removeE(uintptr_t actor_id) {
			removeAbility(e, actor_id);
		}

		void removeX(uintptr_t actor_id) {
			removeAbility(x, actor_id);
		}

		static void removeAbility(std::vector<Ability>& abilities, uintptr_t actor_id) {
			abilities.erase(
				std::remove_if(abilities.begin(), abilities.end(),
					[actor_id](const Ability& ability) {
						return ability.actor_id == actor_id;
					}),
				abilities.end());
		}

		void clear() {
			c.clear();
			q.clear();
			e.clear();
			x.clear();
		}
	};


	Agent cyper;
	Agent killjoy;
	Agent sova;
	Agent jett;
	Agent astra;
	Agent brimstone;
	Agent chamber;
	Agent reynaagent;
	Agent sage;
	Agent viper;
	Agent yoru;
	Agent clove;
	Agent deadlock;
	Agent omen;
	Agent gekko;
	Agent Kayo;
	Agent Skye;
	Agent Phoenix;
	Agent vyse;

	void clearAllAbilities() {
		cyper.clear();
		killjoy.clear();
		sova.clear();
		jett.clear();
		astra.clear();
		brimstone.clear();
		chamber.clear();
		reynaagent.clear();
		sage.clear();
		viper.clear();
		yoru.clear();
		clove.clear();
		deadlock.clear();
		omen.clear();
		gekko.clear();
		Kayo.clear();
		Skye.clear();
		Phoenix.clear();
		vyse.clear();
	}
	
	bool findSpike(uintptr_t actor, const std::string& FnameSL) {
		if (FnameSL == "TimedBomb_C")
		{
			resetspike = false;
			spikeactor = actor;

			HANDLE hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Spikenigger, NULL, NULL, NULL);
			if (hThread) {
				typedef long(NTAPI* pNtSetInformationThread)(HANDLE, ULONG, PVOID, ULONG);
				auto NtSetInfo = (pNtSetInformationThread)GetProcAddress(GetModuleHandleA(skCrypt("ntdll.dll").decrypt()), skCrypt("NtSetInformationThread").decrypt());
				if (NtSetInfo) NtSetInfo(hThread, 0x11, NULL, 0);
			}

			return true;
		}

		return false;
	}

	fvector ability_w2s(uintptr_t actor) {
		auto RelativeLocationn2 = RelativeLocation(actor);
		auto RelativePosition2 = RelativeLocationn2 - camera::location;
		return WorldToScreen(RelativeLocationn2);
	}

	uintptr_t findObjectByName(uintptr_t actor, std::string name) {
		int fname_keyy = driver::read2<int>(actor + offsets::fnameId);
		std::string fnamee = AVERISTY(fname_keyy);

		if (fnamee.find(name) != std::string::npos)
		{
			return actor;
		}
		return 0;
	}

	void updateObject(Agent& agent, const std::string& objectTypeName, const std::string& objectName, uintptr_t actor) {
		uintptr_t objectID = findObjectByName(actor, objectName.c_str());
		if (objectID != 0) {
			agent.removeC(objectID);
			agent.addC(objectID, objectTypeName);
		}
	}

	void updateObjectX(Agent& agent, const std::string& objectTypeName, const std::string& objectName, uintptr_t actor) {
		uintptr_t objectID = findObjectByName(actor, objectName.c_str());
		if (objectID != 0) {
			agent.removeX(objectID);
			agent.addX(objectID, objectTypeName);
		}
	}

	void updateObjectE(Agent& agent, const std::string& objectTypeName, const std::string& objectName, uintptr_t actor) {
		uintptr_t objectID = findObjectByName(actor, objectName.c_str());
		if (objectID != 0) {
			agent.removeE(objectID);
			agent.addE(objectID, objectTypeName);
		}
	}

	void updateObjectQ(Agent& agent, const std::string& objectTypeName, const std::string& objectName, uintptr_t actor) {
		uintptr_t objectID = findObjectByName(actor, objectName.c_str());
		if (objectID != 0) {
			agent.removeQ(objectID);
			agent.addQ(objectID, objectTypeName);
		}
	}

	void DrawCircleWithConsistentSize(ImVec2 objectScreenPos, fvector zero, float baseRadius, ImColor color) {
		float distance = camera::location.distance(zero) / 100.f;
		float adjustedRadius = baseRadius * (20.0f / distance);
		ImGui::GetForegroundDrawList()->AddCircleFilled(objectScreenPos, adjustedRadius > 2 ? 2 : adjustedRadius, color, 100);
	}

	bool readActorIsBeingDestroyedFlag(uint64_t baseAddress) {
		uint16_t flagWord = driver::read2<uint16_t>(baseAddress + 0x11C);
		return (flagWord & (1 << 2)) != 0;
	}


	void DrawHeadBox(ImVec2 position, float width, float height, ImU32 color)
	{
		float X = position.x - (width / 2);
		float Y = position.y;
		float lineW = width / 3;
		float lineH = height / 3;

		ImDrawList* draw_list = ImGui::GetForegroundDrawList();

		draw_list->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), color, 1.5f);
		draw_list->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), color, 1.5f);

		draw_list->AddLine(ImVec2(X + width - lineW, Y), ImVec2(X + width, Y), color, 1.5f);
		draw_list->AddLine(ImVec2(X + width, Y), ImVec2(X + width, Y + lineH), color, 1.5f);

		draw_list->AddLine(ImVec2(X, Y + height - lineH), ImVec2(X, Y + height), color, 1.5f);
		draw_list->AddLine(ImVec2(X, Y + height), ImVec2(X + lineW, Y + height), color, 1.5f);

		draw_list->AddLine(ImVec2(X + width - lineW, Y + height), ImVec2(X + width, Y + height), color, 1.5f);
		draw_list->AddLine(ImVec2(X + width, Y + height - lineH), ImVec2(X + width, Y + height), color, 1.5f);
	}

	void DrawTextWithBackground(ImDrawList* draw_list, const char* text, ImVec2 position, ImColor textColor, ImColor bgColor = ImColor(0, 0, 0, 150)) {
		ImVec2 textSize = ImGui::CalcTextSize(text);
		ImVec2 padding(5.0f, 3.0f);
		ImVec2 bg_min = ImVec2(position.x - padding.x, position.y - padding.y);
		ImVec2 bg_max = ImVec2(position.x + textSize.x + padding.x, position.y + textSize.y + padding.y);

		draw_list->AddRectFilled(bg_min, bg_max, bgColor);
		DrawOutlinedText(AVERISONTOP, text, position, 13.0f, textColor, false);
	}

	bool checkanddrawability(Agent::Ability ability) {
		bool IsBeingDestroyed = readActorIsBeingDestroyedFlag(ability.actor_id);
		if (!IsBeingDestroyed)
		{
			fvector endpoint = ability_w2s(ability.actor_id);
			ImVec2 text_pos = ImVec2(endpoint.x, endpoint.y - 30);
			ImVec2 cameraScreenPos = ImVec2(camera::location.x, camera::location.y);

			ImVec2 objectScreenPos = ImVec2(endpoint.x, endpoint.y);
			ImColor circleColor = ImColor(255, 255, 0);

			DrawCircleWithConsistentSize(objectScreenPos, endpoint, 20.0f, config.AbilitiesColor);
			DrawTextWithBackground(ImGui::GetForegroundDrawList(), ability.objname.c_str(), text_pos, config.AbilitiesColor);
			return true;
		}

		else return false;
	}

	bool checkanddrawability18(Agent::Ability ability) {
		char IsBeingDestroyed = driver::read2<char>(ability.actor_id + offsets::IsBeingDestroyed);

		if (IsBeingDestroyed == 18)
		{

			fvector endpoint = ability_w2s(ability.actor_id);
			ImVec2 text_pos = ImVec2(endpoint.x, endpoint.y - 30);
			ImVec2 cameraScreenPos = ImVec2(camera::location.x, camera::location.y);

			ImVec2 objectScreenPos = ImVec2(endpoint.x, endpoint.y);
			ImColor circleColor = ImColor(255, 255, 0);

			DrawCircleWithConsistentSize(objectScreenPos, endpoint, 20.0f, config.AbilitiesColor);
			DrawTextWithBackground(ImGui::GetForegroundDrawList(), ability.objname.c_str(), text_pos, ImColor(255, 255, 0));
			return true;
		}
		else return false;
	}

	void cypertraps() {

		for (size_t i = 0; i < cyper.c.size(); i += 2) {
			if (i + 1 >= cyper.c.size()) break;

			Agent::Ability c1 = cyper.c[i];
			Agent::Ability c2 = cyper.c[i + 1];

			fvector endpoint1 = ability_w2s(c1.actor_id);
			fvector endpoint2 = ability_w2s(c2.actor_id);

			char IsBeingDestroyed1 = driver::read2<char>(c1.actor_id + offsets::IsBeingDestroyed);

			bool IsBeingDestroyed = readActorIsBeingDestroyedFlag(c1.actor_id);

			if (!IsBeingDestroyed) {
				ImVec2 text_pos = ImVec2(endpoint1.x, endpoint1.y - 30);
				ImVec2 objectScreenPos = ImVec2(endpoint1.x, endpoint1.y);
				ImVec2 objectScreenPos2 = ImVec2(endpoint2.x, endpoint2.y);

				ImColor circleColor = ImColor(255, 255, 0);

				DrawCircleWithConsistentSize(objectScreenPos, endpoint1, 20.0f, config.AbilitiesColor);
				DrawCircleWithConsistentSize(objectScreenPos2, endpoint2, 20.0f, config.AbilitiesColor);
				DrawTextWithBackground(ImGui::GetForegroundDrawList(), "Trip wire", text_pos, config.AbilitiesColor);
			}
			else {
				cyper.removeC(c1.actor_id);
				cyper.removeE(c1.actor_id);
				cyper.removeQ(c1.actor_id);
				cyper.removeX(c1.actor_id);
			}
		}

		for (Agent::Ability e : cyper.e) {
			if (!checkanddrawability(e))
				cyper.removeE(e.actor_id);
		}

		for (Agent::Ability q : cyper.q) {
			if (!checkanddrawability(q))
				cyper.removeQ(q.actor_id);
		}
	}



	void removeInvalidAbilitiesOfType(Agent& agent) {

		for (Agent::Ability ability : agent.q)
		{
			if (!checkanddrawability(ability)) {
				agent.removeQ(ability.actor_id);
			}
		}
		for (Agent::Ability ability : agent.c)
		{
			if (!checkanddrawability(ability)) {
				agent.removeC(ability.actor_id);
			}
		}
		for (Agent::Ability ability : agent.e)
		{
			if (!checkanddrawability(ability)) {
				agent.removeE(ability.actor_id);
			}
		}
		for (Agent::Ability ability : agent.x)
		{
			if (!checkanddrawability(ability)) {
				agent.removeX(ability.actor_id);
			}
		}
	}

	void removeInvalidAbilities(Agent& agent) {
		removeInvalidAbilitiesOfType(agent);
	}

	void otherabilities() {
		removeInvalidAbilities(killjoy);
		removeInvalidAbilities(jett);
		removeInvalidAbilities(astra);
		removeInvalidAbilities(brimstone);
		removeInvalidAbilities(chamber);
		removeInvalidAbilities(reynaagent);
		removeInvalidAbilities(sage);
		removeInvalidAbilities(viper);
		removeInvalidAbilities(yoru);
		removeInvalidAbilities(clove);
		removeInvalidAbilities(deadlock);
		removeInvalidAbilities(omen);
		removeInvalidAbilities(gekko);
		removeInvalidAbilities(Kayo);
		removeInvalidAbilities(Skye);
		removeInvalidAbilities(Phoenix);
		removeInvalidAbilities(vyse);

	}

	ImFont* DefaultFont = nullptr;

	std::string GetExeDir() {
		char path[MAX_PATH];
		GetModuleFileNameA(NULL, path, MAX_PATH);
		std::string s(path);
		return s.substr(0, s.find_last_of('\\') + 1);
	}

	void FontXs() {
		ImGuiIO& io = ImGui::GetIO();

		// ── Glyph ranges (Basic Latin + Cyrillic + icon private area) ─────────
		static const ImWchar ranges[] = {
			0x0020, 0x00FF,
			0x0400, 0x052F,
			0x2DE0, 0x2DFF,
			0xA640, 0xA69F,
			0xE000, 0xE226,
			0,
		};

		ImFontConfig font_cfg;
		font_cfg.PixelSnapH          = false;
		font_cfg.OversampleH         = 5;
		font_cfg.OversampleV         = 5;
		font_cfg.RasterizerMultiply  = 1.2f;
		font_cfg.FontDataOwnedByAtlas = false;
		font_cfg.GlyphRanges         = ranges;

		// ── New menu fonts (from ImGui/byte_array.h) ──────────────────────────
		medium        = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium,  sizeof(PTRootUIMedium),  15.0f, &font_cfg, ranges);
		bold          = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold,    sizeof(PTRootUIBold),    15.0f, &font_cfg, ranges);
		
		::fonts::sans_font = io.Fonts->AddFontFromMemoryTTF(sans, sizeof(sans), 18.0f, &font_cfg, ranges);
		::fonts::sans_font_small = io.Fonts->AddFontFromMemoryTTF(sans, sizeof(sans), 14.0f, &font_cfg, ranges);

		tab_icons     = io.Fonts->AddFontFromMemoryTTF(clarityfont,     sizeof(clarityfont),     15.0f, &font_cfg, ranges);
		logo          = io.Fonts->AddFontFromMemoryTTF(clarityfont,     sizeof(clarityfont),     21.0f, &font_cfg, ranges);
		tab_title     = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold,    sizeof(PTRootUIBold),    19.0f, &font_cfg, ranges);
		tab_title_icon= io.Fonts->AddFontFromMemoryTTF(clarityfont,     sizeof(clarityfont),     18.0f, &font_cfg, ranges);
		subtab_title  = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold,    sizeof(PTRootUIBold),    15.0f, &font_cfg, ranges);
		combo_arrow   = io.Fonts->AddFontFromMemoryTTF(combo,           sizeof(combo),            9.0f, &font_cfg, ranges);

		// ── Legacy / overlay fonts ────────────────────────────────────────────
		ImFontConfig fc;
		fc.OversampleH = 3; fc.OversampleV = 2; fc.PixelSnapH = true;
		fc.RasterizerMultiply = 1.0f; fc.FontDataOwnedByAtlas = false;
		DefaultFont = io.Fonts->AddFontFromMemoryTTF((void*)inter_regular_data, inter_regular_size, 14.0f, &fc);

		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		ImFontConfig ic; ic.MergeMode = true; ic.PixelSnapH = true; ic.OversampleH = 2;
		io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 14.f, &ic, icons_ranges);
		ImFontConfig ifc; ifc.OversampleH = 2; ifc.OversampleV = 2; ifc.PixelSnapH = true;
		IconFont = io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 26.f, &ifc, icons_ranges);
		io.Fonts->AddFontFromMemoryCompressedTTF(trebucbd_compressed_data, trebucbd_compressed_size, 30, nullptr, io.Fonts->GetGlyphRangesDefault());
		AVERISONTOP = io.Fonts->AddFontFromMemoryTTF((void*)font_binary, sizeof(font_binary), 16.f);

		ImFontConfig wfc;
		wfc.OversampleH = 3; wfc.OversampleV = 3; wfc.PixelSnapH = false;
		wfc.FontDataOwnedByAtlas = false;
		WeaponIconFont = io.Fonts->AddFontFromMemoryTTF((void*)ValorantGunIcons, sizeof(ValorantGunIcons), 20.f, &wfc);

		ImFontConfig fc2;
		fc2.OversampleH = 3; fc2.OversampleV = 2; fc2.PixelSnapH = true;
		fc2.FontDataOwnedByAtlas = false;
		Verdana = io.Fonts->AddFontFromMemoryTTF((void*)inter_regular_data, inter_regular_size, 14.0f, &fc2);

		ImFontConfig fc3;
		fc3.OversampleH = 3; fc3.OversampleV = 2; fc3.PixelSnapH = true;
		fc3.FontDataOwnedByAtlas = false;
		BoldFont = io.Fonts->AddFontFromMemoryTTF((void*)inter_bold_data, inter_bold_size, 14.0f, &fc3);
	}

	
	std::string to_string_with_precision(float value, int precision = 0) {
		std::ostringstream out;
		out << std::fixed << std::setprecision(precision) << value;
		return out.str();
	}



	void fimdabilities(uintptr_t actor, const std::string& fnamee) {

		struct Ability {
			Agent& agent;
			std::string abilityName;
			std::string objectName;
		};

		static std::vector<Ability> abilities = {
		{jett, "[Jett] Smoke", "GameObject_Wushu_4_SmokeZone_C"},
		{sova, "Drone", "Ability_Hunter_E_DeployDrone_C"},
		{sova, "[Sova] Drone", "Pawn_Hunter_E_Drone_C"},
		{sova, "[Sova] Arrow", "Projectile_Hunter_4_ExplosiveBolt_PrototypeBalance_C"},
		{sova, "[Sova] Arrow", "Projectile_Hunter_Q_RevealBolt_C"},
		{killjoy, "Nanoswarm", "Projectile_Killjoy_4_RemoteBees_MultiDetonate_C"},
		{killjoy, "Lockdown", "GameObject_Killjoy_X_Bomb_C"},
		{killjoy, "Turret", "Pawn_Killjoy_E_Turret"},
		{killjoy, "Alarmbot", "Pawn_Killjoy_Q_StealthAlarmbot"},
		{cyper, "Trip Wire", "GameObject_Gumshoe_E_TripWire_SecondWire_C"},
		{cyper, "Trip Wire", "GameObject_Gumshoe_E_TripWire_C"},
		{astra, "Star", "GameObject_Rift_X_Markers_C"},
		{astra, "Gravity Well", "GameObject_Rift_4_BlackHole_C"},
		{astra, "Nova Puls", "GameObject_Rift_Q_FlashBurst_C"},
		{astra, "[Astra] Smoke", "GameObject_Rift_E_SmokeZone_C"},
		{brimstone, "Stim Beacon", "GameObject_Sarge_E_SpeedStim_C"},
		{brimstone, "[Brimstone] Molly", "Patch_Sarge_Q_Molotov_Production_C"},
		{brimstone, "[Brimstone] Smoke", "GameObject_Sarge_4_Smoke_ProductionNEW_C"},
		{deadlock, "[Deadlock] SoundSensor", "GameObject_StealthingTrap_SoundSensor_C"},
		{chamber, "[Chamber] Trap", "GameObject_Deadeye_E_Trap_C"},
		{chamber, "[Chamber] Teleport", "GameObject_Deadeye_E_Teleporter_Tether_C"},
		{reynaagent, "[Reyna] Blind", "GameObject_Vampire_4_NearsightAOE_Source_C"},
		{viper, "[Viper] Smoke", "Projectile_Pandemic_4_SmokeGrenade_C"},
		{viper, "[Viper] Snake Kiss", "Patch_Pandemic_AcidMolotov_NewMolotov_C"},
		{omen, "[Omen] Smoke", "Zone_Wraith_4_Smoke_C"},
		{clove, "[Clove] Smoke", "GameObject_Smonk_NewSmoke_C"},
		{gekko, "[Gekko] Wingman", "Pawn_Aggrobot_SeekerNade_C"},
		{gekko, "[Gekko] Abilities", "Patch_Aggrobot_C_ExplodeyPatch_C"},
		{yoru, "[Yoru] Decoy Spawner", "GameObject_Stealth_DecoySpawner_C"},
		{yoru, "[Yoru] Decoy", "Pawn_Stealth_4_Decoy_V2_C"},
		{yoru, "[Yoru] Teleport", "Pawn_Stealth_E_TeleporterMoving_FakeTP_C"},
		{yoru, "[Yoru] Teleport", "Pawn_Stealth_E_TeleporterStationary_FakeTP_C"},
		{yoru, "[Vyse] Flash", "GameObject_Nox_StealthingTrap_Flash_2_C"},
		{yoru, "[Vyse] Trap", "GameObject_Nox_WallTrap_C"},
		{yoru, "[Vyse] Wire", "GameObject_Nox_BarbedWire_C"},
		{Skye, "[Skye] Flash", "Projectile_Guide_E_HawkFlash_C"},
		{Skye, "[Skye] Dog", "Pawn_Guide_Q_PossessableScout_C"},
		{Skye, "[Skye] Ult", "Pawn_Guide_X_Pack_C"},
		{sage, "[Sage] Ice Wall", "GameObject_Thorne_E_Wall_Fortifying_C"},
		{sage, "[Sage] Thin ice", "Patch_Thorne_4_SlowField_Production_C"},
		{Kayo, "[K/O] Flashbang", "Projectile_C_Grenadier_Flash_C"},
		{Kayo, "[K/O] Grenade", "Projectile_Grenadier_Q_SemtexBasic_C"},
		{Phoenix, "[Phoenix] Molotov", "Patch_Phoenix_MolotovFire_C"},
		{Phoenix, "[Flame Wall] Phoenix", "GameObject_Phoenix_Q_FlameWallManager_Production_C"},
		};

		if (fnamee.empty()) return;

		for (const auto& ability : abilities) {
			if (fnamee.find(ability.objectName) != std::string::npos) {
				ability.agent.removeC(actor);
				ability.agent.addC(actor, ability.abilityName);
			}
		}
	}

	void moreAbilities(uintptr_t actor) {
		if (!config.spiketimer && !config.spiketimerlineup && !config.AbilitiesESP) return;

		int fname_keyy = driver::read2<int>(actor + offsets::fnameId);
		std::string fnamee = AVERISTY(fname_keyy);
		if (fnamee.empty()) return;

		if (config.spiketimer || config.spiketimerlineup) {
			findSpike(actor, fnamee);
		}

		if (config.AbilitiesESP) {
			fimdabilities(actor, fnamee);
		}
	}	


	struct GWorld
	{


		uintptr_t GameInstance(uintptr_t GameWorld) {
			uintptr_t gameinstancert = driver::read2<uintptr_t>(GameWorld + offsets::game_instance); 
			gameinstancert = check::validate_pointer(gameinstancert); 
			return gameinstancert;
		};

		uintptr_t ULevel(uintptr_t World) {
			uintptr_t UlevelSL = driver::read2<uintptr_t>(World + offsets::persistent_level); 
			UlevelSL = check::validate_pointer(UlevelSL); 
			return UlevelSL;
		};

		uintptr_t ULocalPlayer(uintptr_t UGameInstance) {
			auto ULocalPlayerArray = driver::read2<uintptr_t>(UGameInstance + offsets::localplayer);
			if (!ULocalPlayerArray) return 0;
			return driver::read2<uintptr_t>(ULocalPlayerArray);
		};

		uintptr_t AHUD(uintptr_t APlayerController) {
			return driver::read2<uintptr_t>(APlayerController + offsets::MyHUD);
		};

		uintptr_t APlayerController(uintptr_t ULocalPlayer) {
			return driver::read2<uintptr_t>(ULocalPlayer + offsets::player_controller);
		};
	};
		
	struct GPlayerController {
		uintptr_t APlayerCameraManager(uintptr_t APlayerController) {
			return driver::read2<uintptr_t>(APlayerController + offsets::camera_manager);
		};
		uintptr_t AHUD(uintptr_t APlayerController) {
			return driver::read2<uintptr_t>(APlayerController + offsets::MyHUD);
		};
		uintptr_t APawn(uintptr_t APlayerController) {
			return driver::read2<uintptr_t>(APlayerController + offsets::apawn);
		};
	};

	struct GPrivatePawn {
		uintptr_t USkeletalMeshComponent(uintptr_t Pawn) {
			return driver::read2<uintptr_t>(Pawn + offsets::mesh);
		};
	};

	GPlayerController* APlayerController;
	GWorld* UWorldS;
	GPrivatePawn* APrivatePawn;

	uintptr_t base = driver::FindProcessBaseByPID(driver::processid);

	bool hvci = false;
	bool vgksysmethod = false;


	struct State {
		uintptr_t keys[7];
	};

	uint64_t decrypt(uint64_t addr) {
		unsigned long long uworld_offset;

		if (addr > 0x10000000000)
		{
			uworld_offset = addr - 0x10000000000;
		}
		else {
			uworld_offset = addr - 0x8000000000;
		}
		return uworld_offset;
	}

	//void mawnigger() {
	//	
	//	uint64_t mawnigger = AverisGuard();
	//	uint64_t vgk_uworld_offset = driver::read<uint64_t>(mawnigger + offsets::WorldGuarded);
	//	uint64_t uworld = driver::read<uint64_t>(mawnigger + decrypt(vgk_uworld_offset));
	//}

	/*auto GetWorld(uintptr_t Pointer) -> uintptr_t
	{
		std::uintptr_t uworld_addr = driver::read<uintptr_t>(Pointer + 0x60);

		ULONGLONG uworld_offset;

		if (uworld_addr > 0x10000000000)
		{
			uworld_offset = uworld_addr - 0x10000000000;
		}
		else {
			uworld_offset = uworld_addr - 0x8000000000;
		}

		return Pointer + uworld_offset;
	}*/
	uintptr_t TEST;

	uintptr_t persistent_level;





	class OutlineColors
	{
	public:
		static void ally_outline_color1(flinearcolor color)
		{
			driver::write<flinearcolor>(baseee + offsets::outline_ally_color, color);
		}
		static flinearcolor ally_outline_color()
		{
			return driver::read<flinearcolor>(baseee + offsets::outline_ally_color);
		}
		static void enemy_outline_color1(flinearcolor color)
		{
			driver::write<flinearcolor>(baseee + offsets::outline_enemy_color, color);
		}
		static flinearcolor enemy_outline_color()
		{
			return driver::read<flinearcolor>(baseee + offsets::outline_enemy_color);
		}
	};
	bool BoolChecks;


	static uint64_t last_key = 0;


	void AverisFind()
	{
		
		bool negritoeee = true;

		static uint64_t last_name_key = 0; 

		bool printed_once = false;

		HIDE_ASM(InitNameDecryption2)();

		while (true)
		{
			uintptr_t GWORLD;
			DWORD64 current_time = GetTickCount64();
			uintptr_t uworld_ptr = driver::read2<uintptr_t>(baseee + offsets::UWorld);
			if (!driver::is_valid(uworld_ptr)) {
				Sleep(300);
				continue;
			}
			// In Valorant UWorld can be double dereferenced or direct pointer depending on build/dump
			GWORLD = driver::read2<uintptr_t>(uworld_ptr);
			if (!driver::is_valid(GWORLD)) {
				// Try direct pointer if double deref failed
				GWORLD = uworld_ptr;
			}
			if (!driver::is_valid(GWORLD)) {
				Sleep(300);
				continue;
			}

			Game_state = driver::read2<uintptr_t>(GWORLD + offsets::Game_state);
			
			game_instance = driver::read2<uintptr_t>(GWORLD + offsets::game_instance);
			if (!driver::is_valid(game_instance)) {
				Sleep(300);
				continue;
			}

			uintptr_t local_players = driver::read2<uintptr_t>((uintptr_t(game_instance) + 0x40));
			if (!driver::is_valid(local_players)) {
				Sleep(300);
				continue;
			}
	
			local_player = driver::read2<uintptr_t>(local_players);
	
			LocalPlayerSX::player_controller = UWorldS->APlayerController(local_player);

			ControlRotation = driver::read<fvector>(LocalPlayerSX::player_controller + offsets::control_rotation);

			pawn = driver::read2<uintptr_t>(LocalPlayerSX::player_controller + offsets::apawn);

			playerstate = driver::read2<uintptr_t>(pawn + offsets::player_state);

			teamComponent = driver::read2<uintptr_t>(playerstate + offsets::team_component);

			teamID = driver::read<int>(teamComponent + offsets::team_id);

			LocalPlayerSX::local_pawn = pawn;
			LocalPlayerSX::ping = (int)driver::read<uint16_t>(playerstate + offsets::get_ping);
			if (!LocalPlayerSX::local_pawn) {
				Sleep(200);
				continue;
			}
			if (LocalPlayerSX::local_pawn != LocalPlayerSX::local_pawn_old) {
				if (!player_pawns.empty())
					player_pawns.clear();

				clearAllAbilities();
				LocalPlayerSX::local_pawn_old = LocalPlayerSX::local_pawn;
			}

			LocalPlayerSX::camera_manager = APlayerController->APlayerCameraManager(LocalPlayerSX::player_controller);
			LocalPlayerSX::camera_position = driver::read<fvector>(LocalPlayerSX::camera_manager + offsets::camera_position);

			actor_array = driver::read2<uintptr_t>(Game_state + offsets::actor_array);
			actor_count = driver::read2<INT32>(Game_state + offsets::actors_count);

			// Fallback: If GameState doesn't hold actors, read from PersistentLevel->Actors (ULevel 0xA0 / 0xA8)
			if (!actor_array || actor_count <= 0 || actor_count > 4096) {
				uintptr_t p_level = driver::read2<uintptr_t>(GWORLD + offsets::persistent_level);
				if (driver::is_valid(p_level)) {
					uintptr_t lvl_actors = driver::read2<uintptr_t>(p_level + offsets::actor_array);
					INT32 lvl_count = driver::read2<INT32>(p_level + offsets::actors_count);
					if (driver::is_valid(lvl_actors) && lvl_count > 0 && lvl_count <= 4096) {
						actor_array = lvl_actors;
						actor_count = lvl_count;
					}
				}
			}

			if (!actor_array || actor_count <= 0) continue;

			for (int count = 0; count < actor_count; count++)
			{
				uintptr_t actor = driver::read2<uintptr_t>(actor_array + (count * offsets::actor_count));
				if (!actor) continue;

				moreAbilities(actor);

				INT32 unique_id = driver::read2<INT32>(actor + offsets::unique_id);

				if (actor == LocalPlayerSX::local_pawn) continue;

				// player pawn class candidates (if unique_id check fails after game update, rely on mesh & damage_handler)
				bool is_player_class = (unique_id == 18743553 /* 0x11E0101 */ ||
				                        unique_id == 18809088 /* 0x11F0100 */);

				// If hardcoded ID does not match, don't drop the actor yet - validate via mesh & damage_handler below

				uintptr_t mesh = driver::read2<uintptr_t>(actor + offsets::mesh);
				if (!mesh) continue;

				uintptr_t bone_array = driver::read2<uintptr_t>(mesh + offsets::bone_array);
				INT32 bone_count = driver::read2<INT32>(mesh + offsets::bone_count);

				// Fallback to ComponentSpaceTransforms (0xB28 / 0xB30) if 0x760 yields invalid pointer or count
				if (!bone_array || bone_count <= 0 || bone_count > 512) {
					uintptr_t alt_bone_array = driver::read2<uintptr_t>(mesh + 0xB28);
					INT32 alt_bone_count = driver::read2<INT32>(mesh + 0xB30);
					if (alt_bone_array && alt_bone_count > 0 && alt_bone_count <= 512) {
						bone_array = alt_bone_array;
						bone_count = alt_bone_count;
					}
				}

				if (!bone_array || bone_count <= 0) continue;

				uintptr_t root_componegro = driver::read2<uintptr_t>(actor + offsets::root_component);
				uintptr_t damage_handler = driver::read2<uintptr_t>(actor + offsets::damage_handler);

				bool is_ally = driver::read2<bool>(actor + offsets::wasally);
				if (config.TeamCheck && is_ally)
					continue;

				float health = damage_handler ? driver::read2<float>(damage_handler + offsets::health) : 0.f;
				if (health <= 0) continue;

				uintptr_t actor_playerstate = driver::read2<uintptr_t>(actor + offsets::player_state);
				{
					uintptr_t actor;
					uintptr_t mesh;
					uintptr_t bone_array;
					uintptr_t root_component;
					uintptr_t damage_handler;

					INT32 bone_count;
					INT32 ammo_count;

					std::string weapon_name;
					std::string agent_name;
					std::string player_name;

					float distance;
					float health;
					float shield;

					bool is_valid;
					bool is_damage_handler_guarded;
					bool is_mesh_guarded;
				};
				uintptr_t for_actor = offsets::AMBATKOM, for_mesh = offsets::AMBATKOM;
				bool is_damage_handler_guarded = false, is_mesh_guarded = false;
				player this_player{
					for_actor,
					for_mesh,
					actor,
					mesh,
					bone_array,
					root_componegro,
					damage_handler,
					bone_count,
					0,
					"",
					"",
					"",
					0.f,
					health,
					0.f,
					true,
					is_damage_handler_guarded,
					is_mesh_guarded,
					is_ally,
					actor_playerstate,
					0,
					"",
					"",
					false,
					0,
					false,
					0,
					0,
					0,
					0
				};

				if (!player_pawns.empty()) {
					auto found_player = std::find(player_pawns.begin(), player_pawns.end(), this_player);
					if (found_player == player_pawns.end())
					{
						player_pawns.push_back(this_player);
					}
				}
				else
				{
					player_pawns.push_back(this_player);
				}
			}
			Sleep(300);
		}
	}

	void RenderOverlayImage(LPDIRECT3DDEVICE9 d3dDevice, LPDIRECT3DTEXTURE9 texture, float posX, float posY) {
		ImGui::GetForegroundDrawList()->AddImage((void*)texture, ImVec2(posX, posY), ImVec2(posX + 100, posY + 100));
	}

	void DrawCircleFilled(int x, int y, int radius, ImColor color, float segments)
	{
		ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImColor(color), segments);
	}
	
	FVector2D WorldRadar(fvector srcPos, fvector distPos, float yaw, float radarX, float radarY, float size)
	{
		auto cosYaw = cos(DegreeToRadian(yaw));
		auto sinYaw = sin(DegreeToRadian(yaw));

		auto deltaX = srcPos.x - distPos.x;
		auto deltaY = srcPos.y - distPos.y;

		auto locationX = (float)(deltaY * cosYaw - deltaX * sinYaw) / 45.f;
		auto locationY = (float)(deltaX * cosYaw + deltaY * sinYaw) / 45.f;

		if (locationX > (size - 2.f))
			locationX = (size - 2.f);	
		else if (locationX < -(size - 2.f))
			locationX = -(size - 2.f);

		if (locationY > (size - 6.f))
			locationY = (size - 6.f);
		else if (locationY < -(size - 6.f))
			locationY = -(size - 6.f);

		return FVector2D((int)(-locationX + radarX), (int)(locationY + radarY));
	}

	static fvector pRadar;
	void CAMERAMATRIX()
	{
		uintptr_t base = LocalPlayerSX::camera_manager + offsets::ViewInfo;
		char buf[0x34];
		driver::readvm((PVOID)base, buf, 0x34);

		fvector raw_loc = *(fvector*)(buf + 0x0);
		fvector raw_rot = *(fvector*)(buf + 0x18);

		camera::location = raw_loc;
		camera::fov = *(float*)(buf + 0x30);
		camera::rotation = raw_rot;
	}

	auto TeamID(uintptr_t APawn) -> int {
		auto PlayerState = driver::read<uintptr_t>(APawn + offsets::player_state);
		auto TeamComponent = driver::read<uintptr_t>(PlayerState + offsets::team_component);
		return driver::read<int>(TeamComponent + offsets::team_id);
	};
	bool teamswap = false;
	void DrawRadarBackground()
	{
		float sw = screen_width / 2.0f;
		float sh = screen_height / 2.0f;
		pRadar.x = sw + 450;
		pRadar.y = sw - sh / 2 - 300;

		float radarSize = 270.0f;
		float halfSize = radarSize / 2.0f;
		float cx = pRadar.x + halfSize;
		float cy = pRadar.y + halfSize;

		ImDrawList* dl = ImGui::GetForegroundDrawList();

		// Dark navy background with slight transparency
		ImU32 bgColor = IM_COL32(8, 12, 22, 230);
		ImU32 borderColor = IM_COL32(40, 55, 80, 200);
		ImU32 crossColor = IM_COL32(30, 42, 65, 180);
		ImU32 cardinalColor = IM_COL32(140, 160, 190, 200);
		ImU32 zoomColor = IM_COL32(160, 180, 210, 220);

		// Background fill
		dl->AddRectFilled(ImVec2(pRadar.x, pRadar.y), ImVec2(pRadar.x + radarSize, pRadar.y + radarSize), bgColor, 4.0f);

		// Subtle border
		dl->AddRect(ImVec2(pRadar.x, pRadar.y), ImVec2(pRadar.x + radarSize, pRadar.y + radarSize), borderColor, 4.0f, 0, 1.5f);

		// Crosshair lines (subtle dark)
		dl->AddLine(ImVec2(cx, pRadar.y + 1), ImVec2(cx, pRadar.y + radarSize - 1), crossColor, 1.0f);
		dl->AddLine(ImVec2(pRadar.x + 1, cy), ImVec2(pRadar.x + radarSize - 1, cy), crossColor, 1.0f);

		// Cardinal direction labels
		dl->AddText(ImVec2(cx - 3, pRadar.y + 4), cardinalColor, "N");
		dl->AddText(ImVec2(cx - 4, pRadar.y + radarSize - 18), cardinalColor, "S");
		dl->AddText(ImVec2(pRadar.x + radarSize - 14, cy - 7), cardinalColor, "E");
		dl->AddText(ImVec2(pRadar.x + 4, cy - 7), cardinalColor, "W");

		// Zoom / distance text at top corners
		dl->AddText(ImVec2(pRadar.x + 6, pRadar.y + 4), zoomColor, "7.0x");
		char distBuf[16];
		sprintf_s(distBuf, "25m");
		dl->AddText(ImVec2(pRadar.x + radarSize - 28, pRadar.y + 4), zoomColor, distBuf);

		// Local player triangle (blue) pointing up
		ImU32 triColor = IM_COL32(60, 120, 255, 255);
		float triH = 7.0f;
		float triW = 5.0f;
		dl->AddTriangleFilled(
			ImVec2(cx, cy - triH),          // top
			ImVec2(cx - triW, cy + triH),   // bottom-left
			ImVec2(cx + triW, cy + triH),   // bottom-right
			triColor
		);
	}

	fvector cached_local_pos;
	bool local_pos_cached = false;

	void DrawRadar(fvector EntityPos, player _thisplayer, bool Visible)
	{
		float radarSize = 270.0f;
		float halfSize = radarSize / 2.0f;
		auto radar_posX = pRadar.x + halfSize;
		auto radar_posY = pRadar.y + halfSize;
		if (pawn == 0) return;
		if (!local_pos_cached) {
			uint64_t LocalRootComp = driver::read<uint64_t>(pawn + offsets::root_component);
			cached_local_pos = driver::read<fvector>(LocalRootComp + offsets::root_position);
			local_pos_cached = true;
		}
		auto Radar2D = WorldRadar(cached_local_pos, EntityPos, camera::rotation.y, radar_posX, radar_posY, halfSize);

		// Clamp dot inside radar bounds
		if (Radar2D.x < pRadar.x + 3) Radar2D.x = pRadar.x + 3;
		if (Radar2D.x > pRadar.x + radarSize - 3) Radar2D.x = pRadar.x + radarSize - 3;
		if (Radar2D.y < pRadar.y + 3) Radar2D.y = pRadar.y + 3;
		if (Radar2D.y > pRadar.y + radarSize - 3) Radar2D.y = pRadar.y + radarSize - 3;

		ImDrawList* dl = ImGui::GetForegroundDrawList();
		ImU32 dotColorVis = IM_COL32(255, 60, 60, 255);   // red visible
		ImU32 dotColorHid = IM_COL32(80, 220, 80, 255);    // green hidden
		ImU32 dotOutline = IM_COL32(0, 0, 0, 200);
		float dotRadius = 4.0f;

		ImU32 dotColor = dotColorHid;
		if (config.VisibleCheckAveris && Visible) {
			dotColor = dotColorVis;
		}

		// Draw dot with dark outline for visibility
		dl->AddCircleFilled(ImVec2(Radar2D.x, Radar2D.y), dotRadius + 1.0f, dotOutline, 16);
		dl->AddCircleFilled(ImVec2(Radar2D.x, Radar2D.y), dotRadius, dotColor, 16);
	}

	float get_distance(const fvector& lhs, const fvector& rhs)
	{
		const float distanceX = lhs.x - rhs.x;
		const float distanceY = lhs.y - rhs.y;
		const float distanceZ = lhs.z - rhs.z;
		return std::sqrt((distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ));
	}


	int g_width  = 0;
	int g_height = 0;


	void render_players()
	{
		CAMERAMATRIX();
		local_pos_cached = false;
		if (config.AbilitiesESP) {
			otherabilities();
			cypertraps();
		}

		spike_esp();

		if (config.MapradarV2) {
			DrawRadarBackground();
		}

		int locked_player;
		int AVERIS1337 = 1337;
		float DISTANCEMAXIMUATION = FLT_MAX;
		ImVec2 textPos = ImVec2(600, 200);

		float fdistance = 0;

		for (int pawns = 0; pawns < (int)player_pawns.size(); pawns++)
		{
			player& playerenemy = player_pawns[pawns];

			if (pawn == playerenemy.actor) continue;
			if (!playerenemy.actor) continue;

			// refresh cached pointers each frame (players respawn, mesh recreates)
			uintptr_t live_mesh = driver::read2<uintptr_t>(playerenemy.actor + offsets::mesh);
			uintptr_t live_dh   = driver::read2<uintptr_t>(playerenemy.actor + offsets::damage_handler);
			if (!live_mesh || !live_dh || live_mesh < 0x10000 || live_dh < 0x10000) continue;
			uintptr_t live_ba   = driver::read2<uintptr_t>(live_mesh + offsets::bone_array);
			INT32     live_bc   = driver::read2<INT32>(live_mesh + offsets::bone_count);
			if (!live_ba || live_bc <= 0 || live_bc > 512) {
				uintptr_t alt_ba = driver::read2<uintptr_t>(live_mesh + 0xB28);
				INT32     alt_bc = driver::read2<INT32>(live_mesh + 0xB30);
				if (alt_ba && alt_bc > 0 && alt_bc <= 512) {
					live_ba = alt_ba;
					live_bc = alt_bc;
				}
			}
			if (!live_ba || live_bc <= 0 || live_bc > 512) continue;
			playerenemy.mesh           = live_mesh;
			playerenemy.damage_handler = live_dh;
			playerenemy.bone_array     = live_ba;
			playerenemy.bone_count     = live_bc;

			float health = driver::read2<float>(playerenemy.damage_handler + offsets::health);
			if (health <= 0.f || health > 999.f) continue;
			playerenemy.health = health;
			float hdt = ImGui::GetIO().DeltaTime;
			playerenemy.hp_smooth += (health - playerenemy.hp_smooth) * (1.0f - expf(-9.0f * hdt));
			if (fabsf(health - playerenemy.hp_smooth) < 0.05f)
				playerenemy.hp_smooth = health;
			if (playerenemy.hp_smooth < 0.f) playerenemy.hp_smooth = 0.f;
			if (playerenemy.hp_smooth > 100.f) playerenemy.hp_smooth = 100.f;

			// refresh team flag each frame (spectator swap, agent select)
			playerenemy.is_ally = driver::read2<bool>(playerenemy.actor + offsets::wasally);
			if (config.TeamCheck && playerenemy.is_ally) continue;

			uintptr_t mesh = playerenemy.mesh;
			ftransform c2w_raw = driver::read<ftransform>(mesh + offsets::component_to_world);
			D3DMATRIX c2w = c2w_raw.ToMatrixWithScale();

			int maxBone = playerenemy.bone_count;
			bool full_read = config.player_skeleton && maxBone >= 90 && maxBone <= 110;
			ftransform small_batch[9];
			ftransform* bone_batch;
			if (full_read) {
				bone_batch = (ftransform*)_alloca(sizeof(ftransform) * maxBone);
				driver::readvm((PVOID)playerenemy.bone_array, bone_batch, sizeof(ftransform) * maxBone);
			} else {
				bone_batch = small_batch;
				driver::readvm((PVOID)playerenemy.bone_array, bone_batch, sizeof(ftransform) * 9);
			}
			fvector zero = BoneFromBatch(0, bone_batch, c2w);
			fvector head = BoneFromBatch(8, bone_batch, c2w);

			if (config.MaxDistancemeow) {
				fdistance = camera::location.distance(head) / 100.f;
				if (fdistance > config.MaxDistanceE)
					continue;
			}

			fvector head_w2s = WorldToScreen(head);
			fvector zero_r = fvector(zero.x, zero.y, zero.z - 5);
			fvector vBaseBoneOut = WorldToScreen(zero);
			fvector vBaseBoneOut2 = WorldToScreen(fvector(zero.x, zero.y, zero.z - 15));
			fvector vHeadBoneOut = head_w2s;
			fvector vHeadBoneOut2 = WorldToScreen(fvector(head.x, head.y, head.z + 15));

			float BoxHeight = abs(vHeadBoneOut2.y - vBaseBoneOut.y);
			float BoxWidth = BoxHeight * 0.55;

			if (!IsInScreen(vBaseBoneOut) || !IsInScreen(head_w2s) || !IsInScreen(vHeadBoneOut2)) {
				continue;
			}

			// Box bottom = real foot bones (single read, only when player is on screen)
			fvector feet_world = fvector(zero.x, zero.y, zero.z - 5);
			{
				int foot_l = 82, foot_r = 89; // 104/106 skeletons: feet = 82/89 (80/87 are knees)
				if (playerenemy.bone_count == 101 || playerenemy.bone_count == 103) { foot_l = 80; foot_r = 87; }
				if (maxBone > foot_r) {
					fvector lw, rw;
					if (full_read) {
						lw = BoneFromBatch(foot_l, bone_batch, c2w);
						rw = BoneFromBatch(foot_r, bone_batch, c2w);
					} else {
						ftransform foot_batch[24] = {};
						driver::readvm((PVOID)(playerenemy.bone_array + sizeof(ftransform) * foot_l), foot_batch, sizeof(ftransform) * (foot_r - foot_l + 1));
						D3DMATRIX ml = math::MatrixMultiplication(foot_batch[0].ToMatrixWithScale(), c2w);
						D3DMATRIX mr = math::MatrixMultiplication(foot_batch[foot_r - foot_l].ToMatrixWithScale(), c2w);
						lw = fvector(ml._41, ml._42, ml._43);
						rw = fvector(mr._41, mr._42, mr._43);
					}
					if (lw.z != 0.f && rw.z != 0.f && fabsf(lw.z - zero.z) < 350.f && fabsf(rw.z - zero.z) < 350.f)
						feet_world = fvector((lw.x + rw.x) * 0.5f, (lw.y + rw.y) * 0.5f, (lw.z + rw.z) * 0.5f - 10.f);
				}
			}
			fvector feet_w2s = WorldToScreen(feet_world);

			// Shared ESP box geometry: box, healthbar and text flags all use this,
			// so they always stick to each other exactly. Tiny pad (2px) on top/bottom.
			float espTop = vHeadBoneOut2.y - 2.f;
			float espBot = feet_w2s.y + 2.f;
			float espH   = espBot - espTop;
			float espW   = espH * 0.45f;
			float espCX  = head_w2s.x;
			float espL   = espCX - espW * 0.5f;
			float espR   = espCX + espW * 0.5f;

			fvector bone = head_w2s;
			
			float ScreenCenterX = Width / 2.0f;
			float ScreenCenterY = Height / 2.0f;
			fvector zero_w2s_r = WorldToScreen(zero_r);
			fvector RelativeLocation = zero;

			auto distance = camera::location.distance(RelativeLocation);
			int Width = screen_width;
			int Height = screen_height;
			if (config.player_ignore_dormant) {
				bool active = is_dormant(playerenemy);
				if (!active) continue;
			}

			bool bVisible = false;
			if (config.VisibleCheckAveris) {
				float fLastSubmitTime = driver::read<float>(mesh + offsets::last_submit_time);
				float fLastRenderTimeOnScreen = driver::read<float>(mesh + offsets::last_render_time);
				bVisible = fLastRenderTimeOnScreen + 0.05f >= fLastSubmitTime;
			}

			if (config.MapradarV2) {
				DrawRadar(RelativeLocation, playerenemy, bVisible);
			}

			if (config.Rendercount) {
				ShowWatermark(&config.Rendercount, "Player Render", ImVec4(255, 255, 255, 255));
			}

			static float time = 0.0f;
			time += ImGui::GetIO().DeltaTime;
			float loopTime = time - static_cast<int>(time);

			float r = (std::sin(loopTime * 6.28318f) + 1.0f) / 2.0f;
			float g = (std::sin(loopTime * 6.28318f + 2.09439f) + 1.0f) / 2.0f;
			float b = (std::sin(loopTime * 6.28318f + 4.18879f) + 1.0f) / 2.0f;


			ImVec2 head_at_screen = ImVec2(vHeadBoneOut.x, vHeadBoneOut.y);
			float distance_modifier = camera::location.distance(head) * 0.001F;
			bool averisVisible = bVisible;
			if (config.circlehead)
			{
				ImColor targetColor;
				if (config.rainbowskeleton) {
					targetColor = (config.VisibleCheckAveris && averisVisible) ? config.visibleHeadCircleColor : ImColor(r, g, b);
				} else {
					targetColor = (config.VisibleCheckAveris && averisVisible) ? config.visibleHeadCircleColor : config.headboxcolor;
				}

				if (playerenemy.bone_count == 104 || playerenemy.bone_count == 101 || playerenemy.bone_count == 103 || playerenemy.bone_count == 106) {
					fvector neck_w2s = WorldToScreen(BoneFromBatch(7, bone_batch, c2w));
					float headToNeck = sqrtf(powf(head_w2s.x - neck_w2s.x, 2) + powf(head_w2s.y - neck_w2s.y, 2));
					float radius = headToNeck * 0.9f;
					if (radius < 2.0f) radius = 2.0f;
					float headX = head_w2s.x;
					float headY = head_w2s.y - (radius * 0.3f);

					if (config.headespstyle == 0) {
						ImGui::GetForegroundDrawList()->AddCircle(ImVec2(headX, headY), radius, targetColor, 32, 1.5f);
					} else {
						float half = radius;
						ImGui::GetForegroundDrawList()->AddRect(
							ImVec2(headX - half, headY - half),
							ImVec2(headX + half, headY + half),
							targetColor, 0.0f, 0, 1.0f);
					}
				}
			}

			if (config.player_healthbar) {
				float boxTopY = espTop;
				float boxBotY = espBot;
				float boxH = espH;
				float boxW = espW;
				float boxCX = espCX;

				float barThick = 3.1f;
				float gap = 0.f;

				ImVec2 bar_min, bar_max;
				bool vertical = true;

				switch (config.HealthPosition) {
				case 1: // Right
					bar_min = ImVec2(boxCX + boxW / 2 + gap, boxTopY);
					bar_max = ImVec2(bar_min.x + barThick, boxBotY);
					break;
				case 2: // Top
					vertical = false;
					bar_min = ImVec2(boxCX - boxW / 2, boxTopY - barThick - gap);
					bar_max = ImVec2(boxCX + boxW / 2, bar_min.y + barThick);
					break;
				case 3: // Bottom
					vertical = false;
					bar_min = ImVec2(boxCX - boxW / 2, boxBotY + gap);
					bar_max = ImVec2(boxCX + boxW / 2, bar_min.y + barThick);
					break;
				default: // Left
					bar_min = ImVec2(boxCX - boxW / 2 - barThick - gap, boxTopY);
					bar_max = ImVec2(bar_min.x + barThick, boxBotY);
					break;
				}

				switch (config.Healthnigger) {
				case 0: // Text only
				{
					char hbuf[32];
					sprintf_s(hbuf, "%.0f", health);
					ImVec2 ts = ImGui::CalcTextSize(hbuf);
					DrawOutlinedText(AVERISONTOP, hbuf, ImVec2(espR + 4, espTop - 16), 13.0f, ImGui::GetColorU32(config.health_color), true);
					break;
				}
				case 2: // Bar + text
				{
					if (config.healthbar_gradient)
						draw_health_bar_gradient(bar_min, bar_max, playerenemy.hp_smooth, health, config.HealthGradTop, config.HealthGradBottom, vertical);
					else
						draw_health_bar_flat(bar_min, bar_max, playerenemy.hp_smooth, health, config.health_color, vertical);
					char hbuf[32];
					sprintf_s(hbuf, "%.0f", health);
					ImVec2 ts = ImGui::CalcTextSize(hbuf);
					DrawOutlinedText(AVERISONTOP, hbuf, ImVec2(espR + 4, espTop - 16), 13.0f, ImGui::GetColorU32(config.health_color), true);
					break;
				}
				default: // Bar only
					if (config.healthbar_gradient)
						draw_health_bar_gradient(bar_min, bar_max, playerenemy.hp_smooth, health, config.HealthGradTop, config.HealthGradBottom, vertical);
					else
						draw_health_bar_flat(bar_min, bar_max, playerenemy.hp_smooth, health, config.health_color, vertical);
					break;
				}
			}

	
			int bottom_text_offset = 2;

			bool VisibleChackchack = bVisible;

			if (config.player_snapline) {
				ImColor lineColor;

				if (config.VisibleCheckAveris && VisibleChackchack)
					lineColor = ImColor(config.visibleSnaplineColor);
				else
					lineColor = ImGui::GetColorU32(config.snapcolor);

				switch (config.SnaplineType) {
				case 0:
					ImGui::GetForegroundDrawList()->AddLine(
						ImVec2(Width / 2, Height - 1075),
						ImVec2(vHeadBoneOut2.x, vHeadBoneOut2.y - 20),
						lineColor,
						0.5f
					);
					break;

				case 1:
					if (!config.VisibleCheckAveris || VisibleChackchack) {
						ImGui::GetForegroundDrawList()->AddLine(
							ImVec2(Width / 2, Height - 540),
							ImVec2(vHeadBoneOut.x, vHeadBoneOut.y),
							lineColor,
							0.5f
						);
					}
					break;

				case 2:
					ImGui::GetForegroundDrawList()->AddLine(
						ImVec2(center_x, center_y * 2),
						ImVec2(zero_w2s_r.x, zero_w2s_r.y + bottom_text_offset),
						lineColor,
						1.f
					);
					break;

				default:
					break;
				}
			}


			uintptr_t cached_InventoryE = 0;
			uintptr_t cached_CurrentEquipE = 0;
			int cached_objID = 0;
			std::string cached_NAMEOFAGENT;
			std::string cached_enemyWeapon;

			if (config.Agenticons || config.characterr || config.Weapon) {
				if (!playerenemy.agent_cached) {
					int actorKeyy = driver::read<int>(playerenemy.actor + offsets::actor_id);
					playerenemy.cached_agent_id = actorKeyy;
					playerenemy.cached_agent_raw = AVERISTY(actorKeyy);
					playerenemy.cached_decrypted_agent = DecryptAgent(playerenemy.cached_agent_raw);
					playerenemy.agent_cached = true;
					playerenemy.logo_cached = false;
				}
				cached_NAMEOFAGENT = playerenemy.cached_agent_raw;
			}

			if (config.characterr || config.Weapon || config.WeaponIcon) {
				cached_InventoryE = driver::read<uintptr_t>(playerenemy.actor + offsets::Inventory);
				if (cached_InventoryE) {
					cached_CurrentEquipE = driver::read<uintptr_t>(cached_InventoryE + offsets::CurrentEquip);
					if (cached_CurrentEquipE) {
						cached_objID = driver::read<int>(cached_CurrentEquipE + offsets::fnameId);
						cached_enemyWeapon = AVERISTY(cached_objID);
					}
				}
			}

			if (config.Agenticons) {
				if (!playerenemy.logo_cached) {
					static std::unordered_map<std::string, ImTextureID> agentLogos = {
						{ skCrypt("Wushu_PC_C").decrypt(),        jettlogo },
						{ skCrypt("Sarge_PC_C").decrypt(),        brimstonelogo },
						{ skCrypt("Gumshoe_PC_C").decrypt(),      cypherlogo },
						{ skCrypt("Sprinter_PC_C").decrypt(),     neonlogo },
						{ skCrypt("Phoenix_PC_C").decrypt(),      phoenixlogo },
						{ skCrypt("Vampire_PC_C").decrypt(),      reynalogo },
						{ skCrypt("Thorne_PC_C").decrypt(),       sagelogo },
						{ skCrypt("Pandemic_PC_C").decrypt(),     viperlogo },
						{ skCrypt("TrainingBot").decrypt(),       botlogo },
						{ skCrypt("Breach_PC_C").decrypt(),       breachlogo },
						{ skCrypt("Rift_PC_C").decrypt(),         astralogo },
						{ skCrypt("Deadeye_PC_C").decrypt(),      chamberlogo },
						{ skCrypt("Killjoy_PC_C").decrypt(),      killjoylogo },
						{ skCrypt("Wraith_PC_C").decrypt(),       omenlogo },
						{ skCrypt("Clay_PC_C").decrypt(),         razelogo },
						{ skCrypt("Guide_PC_C").decrypt(),        skyelogo },
						{ skCrypt("BountyHunter_PC_C").decrypt(), fadelogo },
						{ skCrypt("Hunter_PC_C").decrypt(),       sovalogo },
						{ skCrypt("Stealth").decrypt(),           yorulogo },
						{ skCrypt("AggroBot_PC_C").decrypt(),     gekkologo},
						{ skCrypt("Smonk_PC_C").decrypt(),        clovelogo }
					};
					playerenemy.cached_agent_logo = nullptr;
					for (const auto& [agentKey, logo] : agentLogos) {
						if (cached_NAMEOFAGENT.find(agentKey) != std::string::npos) {
							playerenemy.cached_agent_logo = logo;
							break;
						}
					}
					playerenemy.logo_cached = true;
				}

				if (playerenemy.cached_agent_logo) {
					float iconRadius = 14.0f;
					ImVec2 center(espCX, espTop - 34);
					ImDrawList* dl = ImGui::GetForegroundDrawList();
					dl->AddCircleFilled(center, iconRadius + 2.0f, IM_COL32(0, 0, 0, 180), 24);
					dl->AddCircle(center, iconRadius + 2.0f, IM_COL32(255, 255, 0, 255), 24, 1.5f);
					dl->AddImage(
						reinterpret_cast<ImTextureID>(playerenemy.cached_agent_logo),
						ImVec2(center.x - iconRadius, center.y - iconRadius),
						ImVec2(center.x + iconRadius, center.y + iconRadius)
					);
				}
			}


			if (config.characterr)
			{
				std::string& NAMEOFAGENT = playerenemy.cached_decrypted_agent;
				std::string enemyWeapon = DecryptWeapon(cached_enemyWeapon);

				std::string WEAR = NAMEOFAGENT + " [" + enemyWeapon + "] ";
				ImVec2 Sizetanginamo = ImGui::CalcTextSize(WEAR.c_str());
				bool averisVisabal = bVisible;

				ImVec2 wearPos(espCX - Sizetanginamo.x / 2, espTop - 16);

				if (config.VisibleCheckAveris) {
					if (averisVisabal) {
						DrawOutlinedText(AVERISONTOP, WEAR.c_str(), wearPos, 15, ImColor(config.espvisiblecolor), true);
					}
					else {
						DrawOutlinedText(AVERISONTOP, WEAR.c_str(), wearPos, 15, ImColor(config.espcolor), true);

					}
				}
				else {
					DrawOutlinedText(AVERISONTOP, WEAR.c_str(), wearPos, 15, ImColor(config.espcolor), true);
				}
			}

			if (config.Antonat) {
				char Text[64];
				sprintf_s(Text, "");
				std::string Out13377 = Text;
				ImVec2 TextSize = ImGui::CalcTextSize(Out13377.c_str());
				ImGui::GetForegroundDrawList()->AddText(ImVec2(vBaseBoneOut2.x - TextSize.x / 2, vBaseBoneOut2.y - 15 - TextSize.y / 4), ImGui::GetColorU32({ 239, 0, 255, 255 }), Out13377.c_str());
			}

			if (config.Weapon) {
				if (cached_CurrentEquipE) {
					EAresEquippableState CurrentEquippableVFXState = driver::read<EAresEquippableState>(cached_CurrentEquipE + offsets::CurrentEquippableVFXState);
					std::string Out1 = GetEquippableVFXState(CurrentEquippableVFXState);
					ImVec2 TextSize = ImGui::CalcTextSize(Out1.c_str());

					ImColor textColor = (config.VisibleCheckAveris && bVisible) ? config.espvisiblecolor : config.espcolor;

					DrawOutlinedText(AVERISONTOP, Out1.c_str(), ImVec2(espL - TextSize.x - 6, espTop - 16), 13.0f, textColor, true);
				}
			}

			if (config.WeaponIcon && WeaponIconFont) {
				if (cached_CurrentEquipE) {
					std::string friendlyWeapon = DecryptWeapon(cached_enemyWeapon);
					char glyph[2] = { WeaponIconChar(friendlyWeapon + "|" + cached_enemyWeapon), 0 };
					if (glyph[0]) {
						float boxTopY = vHeadBoneOut2.y;
						float boxBotY = feet_w2s.y;
						float boxH = boxBotY - boxTopY;
						float boxW = boxH * 0.45f;

						float iconSize = config.WeaponIconSize > 4.f ? config.WeaponIconSize : 20.f;
						float iconGap = 5.f;
						float iconY = boxBotY + iconGap;
						if (config.player_healthbar && config.HealthPosition == 3)
							iconY += 3.1f + 3.f;

						ImDrawList* dl = ImGui::GetForegroundDrawList();

						ImColor iconColor = (config.VisibleCheckAveris && bVisible) ? config.espvisiblecolor : config.espcolor;

						float iconW = WeaponIconFont->CalcTextSizeA(iconSize, FLT_MAX, 0.f, glyph).x;
						ImVec2 iconPos(head_w2s.x - iconW / 2, iconY);
						dl->AddText(WeaponIconFont, iconSize, ImVec2(iconPos.x + 1, iconPos.y + 1), IM_COL32(0, 0, 0, 255), glyph);
						dl->AddText(WeaponIconFont, iconSize, iconPos, iconColor, glyph);
					}
				}
			}

			uintptr_t playerstate = playerenemy.playerstate;
			if ((config.FPSCheck || config.AccountID) && playerstate) {
				bool needs_update = (playerenemy.stat_update_counter <= 0);
				if (needs_update) {
					playerenemy.stat_update_counter = 30;
					uintptr_t ps = playerstate;
					if (!playerenemy.platform_player_cached) {
						playerenemy.cached_platform_player = driver::read<uintptr_t>(ps + offsets::PlatformPlayer);
						playerenemy.platform_player_cached = true;
						if (playerenemy.cached_platform_player)
							playerenemy.cached_account_level = driver::read<int32_t>(playerenemy.cached_platform_player + offsets::AccountLevel);
					}
					playerenemy.cached_ping = driver::read<uint16_t>(ps + offsets::get_ping);
					if (playerenemy.cached_platform_player)
						playerenemy.cached_competitive_tier = driver::read<int32_t>(playerenemy.cached_platform_player + offsets::CompetitiveTier);
				}
				playerenemy.stat_update_counter--;

				if (config.FPSCheck) {
					char FpsInfo[128];
					sprintf_s(FpsInfo, "Level: %d | Ping: %dms", playerenemy.cached_account_level, playerenemy.cached_ping);
					ImVec2 fpsSize = ImGui::CalcTextSize(FpsInfo);
					DrawOutlinedText(AVERISONTOP, FpsInfo, ImVec2(espL - fpsSize.x - 6, espTop - 34), 14.0f, ImColor(255, 255, 255), true);
				}
			}

			if (config.AccountID) {
				if (playerenemy.cached_platform_player) {
					uintptr_t platform_player_ptr = playerenemy.cached_platform_player;
					if (platform_player_ptr) {
						int32_t competitive_tier = playerenemy.cached_competitive_tier;

						const char* rank_name = "UNRANKED";
						flinearcolor rank_color = flinearcolor(1.0, 1.0, 1.0, 1.0);

						switch (static_cast<ECompetitiveTier>(competitive_tier)) {
						case ECompetitiveTier::ECompetitiveTier__Iron1:     rank_name = "Iron 1";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Iron2:     rank_name = "Iron 2";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Iron3:     rank_name = "Iron 3";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;

						case ECompetitiveTier::ECompetitiveTier__Bronze1:   rank_name = "Bronze 1";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Bronze2:   rank_name = "Bronze 2";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Bronze3:   rank_name = "Bronze 3";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;

						case ECompetitiveTier::ECompetitiveTier__Silver1:   rank_name = "Silver 1";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Silver2:   rank_name = "Silver 2";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Silver3:   rank_name = "Silver 3";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;

						case ECompetitiveTier::ECompetitiveTier__Gold1:     rank_name = "Gold 1";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Gold2:     rank_name = "Gold 2";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Gold3:     rank_name = "Gold 3";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;

						case ECompetitiveTier::ECompetitiveTier__Platinum1: rank_name = "Platinum 1"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Platinum2: rank_name = "Platinum 2"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Platinum3: rank_name = "Platinum 3"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;

						case ECompetitiveTier::ECompetitiveTier__Diamond1:  rank_name = "Diamond 1";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Diamond2:  rank_name = "Diamond 2";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Diamond3:  rank_name = "Diamond 3";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;

						case ECompetitiveTier::ECompetitiveTier__Immortal1: rank_name = "Immortal 1"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Immortal2: rank_name = "Immortal 2"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;
						case ECompetitiveTier::ECompetitiveTier__Immortal3: rank_name = "Immortal 3"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;

						case ECompetitiveTier::ECompetitiveTier__Radiant:   rank_name = "Radiant";    rank_color = { 1.0, 0.78, 0.04, 1.0 }; break;

						default:                                            rank_name = "UNRANKED";  rank_color = { 0.71, 0.71, 0.71, 1.0 }; break;
						}


						std::string label = "[ " + std::string(rank_name) + " ]";
						ImVec2 rankSize = ImGui::CalcTextSize(label.c_str());

						DrawOutlinedText(AVERISONTOP, label, ImVec2(espL - rankSize.x - 6, espTop - 52), 14.0f, ImGui::GetColorU32(ImVec4(rank_color.r, rank_color.g, rank_color.b, rank_color.a)), true);
					}
				}


			}

			if (config.player_box) {
				ImColor boxColor;
				if (config.VisibleCheckAveris && averisVisible) {
					boxColor = config.espvisiblecolor;
				}
				else {
					boxColor = config.espcolor;
				}

				float esp_box_x = 0, esp_box_y = 0, esp_box_w = 0, esp_box_h = 0;

				switch (config.esptype) {
				case 0: { // Box — normal outline
					DrawNormalBox((int)espL, (int)espTop, (int)espW, (int)espH, config.ESPBOXThickness, boxColor);
					esp_box_x = espL; esp_box_y = espTop; esp_box_w = espW; esp_box_h = espH;
					break;
				}
				case 1: { // Filled Box — fill + outline
					{
						ImColor fc = config.box_filled_color;
						fc.Value.w *= config.box_filled_alpha;
						ImGui::GetForegroundDrawList()->AddRectFilled(
							ImVec2(espL, espTop), ImVec2(espL + espW, espTop + espH), fc, 0.f);
					}
					DrawNormalBox((int)espL, (int)espTop, (int)espW, (int)espH, config.ESPBOXThickness, boxColor);
					esp_box_x = espL; esp_box_y = espTop; esp_box_w = espW; esp_box_h = espH;
					break;
				}
				case 2: { // Corner Box — outline
					draw_corner_box((int)espL, (int)espTop, (int)espW, (int)espH, boxColor, config.ESPBOXThickness);
					esp_box_x = espL; esp_box_y = espTop; esp_box_w = espW; esp_box_h = espH;
					break;
				}

				default:
					break;
				}

			}

			if (config.player_skeleton) {
				ImColor baseColor;
				if (config.rainbowskeleton) {
					baseColor = ImColor(r, g, b);
				}
				else {
					baseColor = ImColor(config.skeleton);
				}

				if (config.VisibleCheckAveris && averisVisible) {
					baseColor = config.visibleSkeletonColor;
				}
				draw_skeleton(playerenemy, baseColor, config.SkeletonThickness, c2w, full_read ? bone_batch : nullptr);
			}

			if (config.player_distance) {
				float distance = camera::location.distance(zero) / 100.f;
				char distance_text[256];
				sprintf_s(distance_text, "%.fM", distance);
				ImVec2 text_size = ImGui::CalcTextSize(distance_text);

				ImColor textColor = (config.VisibleCheckAveris && averisVisible) ? config.espvisiblecolor : config.espcolor;

				DrawOutlinedText(AVERISONTOP, distance_text, ImVec2(espCX - text_size.x / 2, espTop - 52), 13, textColor, true);
			}

			if (config.player_view_angle) {

				fvector view_angle = driver::read<fvector>(playerenemy.root_component + 0x170);

				fvector test2, headpos;

				headpos = head;

				angle_rotation(view_angle, &test2);
				test2.x *= 260;
				test2.y *= 260;
				test2.z *= 260;

				fvector end = headpos + test2;
				fvector test1, test3;
				test1 = WorldToScreen(headpos);
				test3 = WorldToScreen(end);

				ImColor lineColor = (config.VisibleCheckAveris && averisVisible) ? config.NIGGAENNEMY : config.LINEENEMY;
				ImGui::GetForegroundDrawList()->AddLine(ImVec2(test1.x, test1.y), ImVec2(test3.x, test3.y), lineColor, 1.f);
			}

			if (config.aimenable) {
				float delta_x = head_w2s.x - (Width / 2.f);
				float delta_y = head_w2s.y - (Height / 2.f);
				float dist = sqrtf(delta_x * delta_x + delta_y * delta_y);
				float fovdist = CalculateDistance(Width / 2, Height / 2, head_w2s.x, head_w2s.y);

				if (!is_locked && fovdist < config.aimbot_fov) {
					if (dist < DISTANCEMAXIMUATION) {
						DISTANCEMAXIMUATION = dist;
						AVERIS1337 = pawns;
					}
				}
			}
		}

		if (config.aimenable && AVERIS1337 != 1337 && AVERIS1337 < (int)player_pawns.size()) {
			if (!is_locked) {
				locked_player = AVERIS1337;
				is_locked = true;
			}

			if (locked_player >= 0 && locked_player < (int)player_pawns.size()) {
				player& playere = player_pawns[locked_player];

				uintptr_t aim_mesh = playere.mesh;
				ftransform aim_c2w_raw = driver::read<ftransform>(aim_mesh + offsets::component_to_world);
				D3DMATRIX aim_c2w = aim_c2w_raw.ToMatrixWithScale();
				fvector aimpos_head_top = AVERISBONE_CACHED(8, playere, aim_c2w);
				fvector aimpos_neck = AVERISBONE_CACHED(21, playere, aim_c2w);
				fvector aimpos_chest = AVERISBONE_CACHED(6, playere, aim_c2w);

				fvector aimpos_head;
				aimpos_head.x = aimpos_head_top.x * 0.85f + aimpos_neck.x * 0.15f;
				aimpos_head.y = aimpos_head_top.y * 0.85f + aimpos_neck.y * 0.15f;
				aimpos_head.z = (aimpos_head_top.z * 0.85f + aimpos_neck.z * 0.15f) + 2.5f;

				fvector selected_bone;
				switch (config.aimboness) {
				case 0: selected_bone = WorldToScreen(aimpos_head); break;
				case 1: selected_bone = WorldToScreen(aimpos_neck); break;
				case 2: selected_bone = WorldToScreen(aimpos_chest); break;
				default: selected_bone = WorldToScreen(aimpos_head); break;
				}

				float aim_lst = driver::read<float>(aim_mesh + offsets::last_submit_time);
				float aim_lrt = driver::read<float>(aim_mesh + offsets::last_render_time);
				bool visEIEIE = aim_lrt + 0.05f >= aim_lst;

				int screen_widthEE = screen_width;
				int screen_heightEE = screen_height;

				bool aimKeyHeld = !menu_open && (HIDE_ASM(GetAsyncKeyState)(config.aimbotkey) & offsets::key_pressed_bit);

				if (aimKeyHeld) {
					double cross = GetCrossDistance(selected_bone.x, selected_bone.y, screen_widthEE / 2, screen_heightEE / 2);
					bool crossvalid = cross <= config.aimbot_fov;
					if ((config.VisibleAimbotAveris && visEIEIE) || !config.VisibleAimbotAveris) {
						if (crossvalid) {
							HIDE_ASM(AimAtPosV2)(screen_widthEE, screen_heightEE, selected_bone.x, selected_bone.y, config.aimbot_speed, 0, true);
						}
					}
				}
				else {
					is_locked = false;
					AVERIS1337 = FLT_MAX;
				}
			}
			else {
				is_locked = false;
				AVERIS1337 = FLT_MAX;
			}
		}
		else if (config.aimenable) {
			is_locked = false;
		}

		float fov_cx = screen_width / 2.0f;
		float fov_cy = screen_height / 2.0f;
		if (config.aimbot_draw_fov)
		{
			ImGui::GetForegroundDrawList()->AddCircle(ImVec2(fov_cx - 2.0f, fov_cy - 2.0f), config.aimbot_fov, ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), 64, 1.f);
		}

		if (config.FilledFOV) {
			DrawCircleFilled(fov_cx - 2.0f, fov_cy - 2.0f, config.aimbot_fov, ImColor(config.FOVFillled), 10000);
		}

		// ── Triggerbot ────────────────────────────────────────────────────────
		if (config.triggerbot && !menu_open) {
			bool holdKeyDown = (HIDE_ASM(GetAsyncKeyState)(config.triggerbotkey) & 0x8000) != 0;
			if (holdKeyDown) {
				static float trig_timer = 0.f;
				trig_timer += ImGui::GetIO().DeltaTime;
				float delay_s = config.flickdelay / 1000.f;

				// crosshair altındaki player'ı bul
				float cx = screen_width  / 2.f;
				float cy = screen_height / 2.f;
				const float TRIG_BOX = 6.f; // crosshair hassasiyet (pixel)

				bool on_target = false;
				for (auto& pe : player_pawns) {
					if (!pe.mesh) continue;
					ftransform c2w_t = driver::read<ftransform>(pe.mesh + offsets::component_to_world);
					D3DMATRIX m = c2w_t.ToMatrixWithScale();
					fvector hpos = AVERISBONE_CACHED(8, pe, m);
					fvector hs = WorldToScreen(hpos);
					if (hs.z < 0.f) continue;
					if (fabsf(hs.x - cx) < TRIG_BOX && fabsf(hs.y - cy) < TRIG_BOX) {
						on_target = true;
						break;
					}
				}

				if (on_target && trig_timer >= delay_s) {
					trig_timer = 0.f;
					driver::move_mouse(0, 0, 0x0001); // MOUSE_LEFT_BUTTON_DOWN
					Sleep(12);
					driver::move_mouse(0, 0, 0x0002); // MOUSE_LEFT_BUTTON_UP
				}
				if (!on_target) trig_timer = 0.f;
			}
		}

	}

	namespace AverisUI {
		inline ImVec4 accent_color = ImVec4(0.40f, 0.20f, 0.60f, 1.0f);

		bool ToggleRow(const char* label, const char* desc, bool* v, float rowWidth = -1.f) {
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems) return false;

			ImGuiContext& g = *GImGui;
			const ImGuiID id = window->GetID(label);

			const float toggleW = 38.0f;
			const float toggleH = 20.0f;
			const float toggleR = toggleH * 0.5f;
			float avail = (rowWidth > 0) ? rowWidth : ImGui::GetContentRegionAvail().x;
			const float rowH = desc ? 38.0f : 22.0f;

			const ImVec2 pos = window->DC.CursorPos;
			const ImRect total_bb(pos, ImVec2(pos.x + avail, pos.y + rowH));

			ImGui::ItemSize(total_bb, 0);
			if (!ImGui::ItemAdd(total_bb, id)) return false;

			bool hovered, held;
			bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
			if (pressed) { *v = !(*v); ImGui::MarkItemEdited(id); }

			float anim_t = window->StateStorage.GetFloat(id, *v ? 1.0f : 0.0f);
			anim_t = ImLerp(anim_t, *v ? 1.0f : 0.0f, g.IO.DeltaTime * 12.0f);
			window->StateStorage.SetFloat(id, anim_t);

			// Label + desc on left
			ImFont* fnt = ImGui::GetFont();
			float labelY = desc ? (pos.y + 2.0f) : (pos.y + (rowH - fnt->FontSize) * 0.5f);
			window->DrawList->AddText(fnt, fnt->FontSize, ImVec2(pos.x + 4, labelY),
				ImGui::GetColorU32(ImVec4(0.85f, 0.85f, 0.88f, 1.0f)), label);
			if (desc) {
				window->DrawList->AddText(fnt, fnt->FontSize - 1, ImVec2(pos.x + 4, labelY + fnt->FontSize + 2),
					ImGui::GetColorU32(ImVec4(0.40f, 0.40f, 0.45f, 1.0f)), desc);
			}

			// Square checkbox on right
			const float box_sz = 16.0f;
			const float box_rounding = 3.0f;
			float tx = pos.x + avail - box_sz - 4.0f;
			float ty = pos.y + (rowH - box_sz) * 0.5f;

			ImVec4 bg_off = hovered ? ImVec4(0.28f, 0.28f, 0.33f, 1.0f) : ImVec4(0.20f, 0.20f, 0.24f, 1.0f);
			ImVec4 border_col = hovered ? ImVec4(0.45f, 0.45f, 0.50f, 1.0f) : ImVec4(0.35f, 0.35f, 0.40f, 1.0f);
			ImVec4 bg;
			bg.x = ImLerp(bg_off.x, accent_color.x, anim_t);
			bg.y = ImLerp(bg_off.y, accent_color.y, anim_t);
			bg.z = ImLerp(bg_off.z, accent_color.z, anim_t);
			bg.w = 1.0f;
			window->DrawList->AddRectFilled(ImVec2(tx, ty), ImVec2(tx + box_sz, ty + box_sz), ImGui::GetColorU32(bg), box_rounding);
			if (anim_t < 0.5f) {
				window->DrawList->AddRect(ImVec2(tx, ty), ImVec2(tx + box_sz, ty + box_sz), ImGui::GetColorU32(border_col), box_rounding, 0, 1.2f);
			}
			if (anim_t > 0.01f) {
				float pad = 3.0f;
				ImVec2 p1 = ImVec2(tx + pad, ty + box_sz * 0.5f);
				ImVec2 p2 = ImVec2(tx + box_sz * 0.4f, ty + box_sz - pad);
				ImVec2 p3 = ImVec2(tx + box_sz - pad, ty + pad);
				ImU32 check_col = ImGui::GetColorU32(ImVec4(1, 1, 1, anim_t));
				window->DrawList->AddLine(p1, p2, check_col, 2.0f);
				window->DrawList->AddLine(p2, p3, check_col, 2.0f);
			}

			return pressed;
		}

		bool Checkbox(const char* label, bool* v) {
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems) return false;

			ImGuiContext& g = *GImGui;
			const ImGuiStyle& style = g.Style;
			const ImGuiID id = window->GetID(label);
			const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

			const float box_sz = 18.0f;
			const float rounding = 5.0f;
			const float left_pad = 14.0f;
			const ImVec2 pos = window->DC.CursorPos;
			const ImVec2 box_min = ImVec2(pos.x + left_pad, pos.y + 2.0f);
			const ImVec2 box_max = ImVec2(box_min.x + box_sz, box_min.y + box_sz);
			const float total_w = left_pad + box_sz + (label_size.x > 0.0f ? 8.0f + label_size.x : 0.0f) + 4.0f;
			const ImRect total_bb(pos, pos + ImVec2(total_w, ImMax(box_sz + 4.0f, label_size.y + 4.0f)));

			ImGui::ItemSize(total_bb, style.FramePadding.y);
			if (!ImGui::ItemAdd(total_bb, id)) return false;

			bool hovered, held;
			bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
			if (pressed) {
				*v = !(*v);
				ImGui::MarkItemEdited(id);
			}

			float anim_t = window->StateStorage.GetFloat(id, *v ? 1.0f : 0.0f);
			anim_t = ImLerp(anim_t, *v ? 1.0f : 0.0f, g.IO.DeltaTime * 12.0f);
			window->StateStorage.SetFloat(id, anim_t);

			ImVec4 bg_off = hovered ? ImVec4(0.24f, 0.24f, 0.28f, 1.0f) : ImVec4(0.16f, 0.16f, 0.20f, 1.0f);
			ImVec4 bg;
			bg.x = ImLerp(bg_off.x, accent_color.x, anim_t);
			bg.y = ImLerp(bg_off.y, accent_color.y, anim_t);
			bg.z = ImLerp(bg_off.z, accent_color.z, anim_t);
			bg.w = 1.0f;

			window->DrawList->AddRectFilled(box_min, box_max, ImGui::GetColorU32(bg), rounding);
			ImVec4 border_col = hovered ? ImVec4(0.38f, 0.38f, 0.43f, 1.0f) : ImVec4(0.28f, 0.28f, 0.33f, 1.0f);
			ImVec4 brd;
			brd.x = ImLerp(border_col.x, accent_color.x, anim_t * 0.5f);
			brd.y = ImLerp(border_col.y, accent_color.y, anim_t * 0.5f);
			brd.z = ImLerp(border_col.z, accent_color.z, anim_t * 0.5f);
			brd.w = 1.0f;
			window->DrawList->AddRect(box_min, box_max, ImGui::GetColorU32(brd), rounding, 15, 1.0f);

			if (label_size.x > 0.0f) {
				ImVec2 label_pos = ImVec2(box_max.x + 8.0f, pos.y + (total_bb.GetHeight() - label_size.y) * 0.5f);
				float brightness = 0.75f + anim_t * 0.15f;
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(brightness, brightness, brightness + 0.04f, 1.0f));
				ImGui::RenderText(label_pos, label);
				ImGui::PopStyleColor();
			}

			return pressed;
		}

		bool ColorPicker(const char* label, float* col) {
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems) return false;

			ImGuiContext& g = *GImGui;
			const ImGuiStyle& style = g.Style;
			const ImGuiID id = window->GetID(label);

			const float left_pad = 14.0f;
			const float w = ImGui::CalcItemWidth();
			const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

			const float square_sz = 16.0f;
			const float row_h = ImMax(label_size.y, square_sz);
			const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(left_pad + w, row_h));

			ImGui::ItemSize(frame_bb, style.FramePadding.y);
			if (!ImGui::ItemAdd(frame_bb, id)) return false;

			bool hovered, held;
			bool pressed = ImGui::ButtonBehavior(frame_bb, id, &hovered, &held);

			ImVec2 label_pos = ImVec2(frame_bb.Min.x + left_pad, frame_bb.Min.y + (row_h - label_size.y) * 0.5f);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
			ImGui::RenderText(label_pos, label);
			ImGui::PopStyleColor();
			
			ImVec2 square_pmin = ImVec2(frame_bb.Max.x - square_sz, frame_bb.Min.y + (frame_bb.GetHeight() - square_sz) / 2.0f);
			ImVec2 square_pmax = ImVec2(square_pmin.x + square_sz, square_pmin.y + square_sz);
			
			ImVec4 col4(col[0], col[1], col[2], col[3]);
			
			window->DrawList->AddRectFilled(square_pmin, square_pmax, ImGui::GetColorU32(ImVec4(0.2f, 0.2f, 0.2f, 1.0f)), 4.0f);
			window->DrawList->AddRectFilled(square_pmin, square_pmax, ImGui::GetColorU32(col4), 4.0f);
			
			ImU32 border_col = ImGui::GetColorU32(hovered ? ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.8f) : ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
			window->DrawList->AddRect(square_pmin, square_pmax, border_col, 4.0f, 0, hovered ? 1.5f : 1.0f);

			if (pressed) {
				ImGui::OpenPopup(label);
			}

			bool value_changed = false;
			
			ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.08f, 0.08f, 0.10f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.40f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));
			
			if (ImGui::BeginPopup(label)) {
				value_changed = ImGui::ColorPicker4(label, col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
				ImGui::EndPopup();
			}
			
			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);

			return value_changed;
		}

		bool BeginCombo(const char* label, const char* preview_value) {
			ImGuiContext& g = *GImGui;
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems) return false;

			const ImGuiStyle& style = g.Style;
			const ImGuiID id = window->GetID(label);
			const float w = ImGui::CalcItemWidth();
			const float left_pad = 14.0f;
			const float frame_h = 22.0f;

			const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
			const ImVec2 cursor = window->DC.CursorPos;

			float label_w = label_size.x > 0.0f ? label_size.x + 8.0f : 0.0f;
			const ImRect total_bb(cursor, cursor + ImVec2(left_pad + label_w + w, ImMax(frame_h + 2.0f, label_size.y + 4.0f)));
			const ImVec2 frame_min(cursor.x + left_pad + label_w, cursor.y + 1.0f);
			const ImRect frame_bb(frame_min, frame_min + ImVec2(w, frame_h));

			ImGui::ItemSize(total_bb, style.FramePadding.y);
			if (!ImGui::ItemAdd(total_bb, id, &frame_bb)) return false;

			bool hovered, held;
			bool pressed = ImGui::ButtonBehavior(frame_bb, id, &hovered, &held);
			bool popup_open = ImGui::IsPopupOpen(id, ImGuiPopupFlags_None);

			if (pressed || g.NavActivateId == id) {
				if (!popup_open) {
					ImGui::OpenPopupEx(id);
					popup_open = true;
				} else {
					ImGui::ClosePopupToLevel(g.BeginPopupStack.Size, true);
					popup_open = false;
				}
			}

			float anim_t = window->StateStorage.GetFloat(id, 0.0f);
			anim_t = ImLerp(anim_t, popup_open ? 1.0f : 0.0f, g.IO.DeltaTime * 14.0f);
			window->StateStorage.SetFloat(id, anim_t);

			ImU32 frame_col = ImGui::GetColorU32(hovered ? ImVec4(0.14f, 0.14f, 0.18f, 1.0f) : ImVec4(0.10f, 0.10f, 0.14f, 1.0f));
			window->DrawList->AddRectFilled(frame_bb.Min, frame_bb.Max, frame_col, 5.0f);

			ImVec4 brd = popup_open ? ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.6f)
			                        : (hovered ? ImVec4(0.30f, 0.30f, 0.35f, 1.0f) : ImVec4(0.22f, 0.22f, 0.27f, 1.0f));
			window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(brd), 5.0f, 0, 1.0f);

			ImGui::RenderTextClipped(frame_bb.Min + ImVec2(4.0f, 0), frame_bb.Max - ImVec2(18.0f, 0), preview_value, NULL, NULL, ImVec2(0.5f, 0.5f));

			if (label_size.x > 0) {
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.75f, 0.75f, 0.79f, 1.0f));
				ImGui::RenderText(ImVec2(cursor.x + left_pad, cursor.y + (total_bb.GetHeight() - label_size.y) * 0.5f), label);
				ImGui::PopStyleColor();
			}

			float chevY = frame_bb.Min.y + (frame_h - 6.0f) * 0.5f;
			float chevX = frame_bb.Max.x - 14.0f;
			ImU32 chevron_col = ImGui::GetColorU32(ImVec4(0.50f + anim_t * 0.40f, 0.50f + anim_t * 0.40f, 0.55f + anim_t * 0.35f, 1.0f));
			if (popup_open) {
				window->DrawList->AddLine(ImVec2(chevX, chevY + 4.0f), ImVec2(chevX + 4.0f, chevY), chevron_col, 1.5f);
				window->DrawList->AddLine(ImVec2(chevX + 4.0f, chevY), ImVec2(chevX + 8.0f, chevY + 4.0f), chevron_col, 1.5f);
			} else {
				window->DrawList->AddLine(ImVec2(chevX, chevY), ImVec2(chevX + 4.0f, chevY + 4.0f), chevron_col, 1.5f);
				window->DrawList->AddLine(ImVec2(chevX + 4.0f, chevY + 4.0f), ImVec2(chevX + 8.0f, chevY), chevron_col, 1.5f);
			}

			if (!popup_open) return false;

			float popup_h_est = 8 * frame_h;
			float space_below = g.IO.DisplaySize.y - frame_bb.Max.y;
			bool open_upward = (space_below < popup_h_est) && (frame_bb.Min.y > popup_h_est);

			if (open_upward) {
				ImGui::SetNextWindowPos(ImVec2(frame_bb.Min.x, frame_bb.Min.y - 3.0f), 0, ImVec2(0.0f, 1.0f));
			} else {
				ImGui::SetNextWindowPos(ImVec2(frame_bb.Min.x, frame_bb.Max.y + 3.0f));
			}
			ImGui::SetNextWindowSize(ImVec2(w, 0.0f));

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6.0f, 6.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 1.0f);
			ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.09f, 0.09f, 0.12f, 0.98f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.22f, 0.22f, 0.27f, 1.0f));

			bool is_open = ImGui::BeginPopupEx(id, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

			if (!is_open) {
				ImGui::PopStyleColor(2);
				ImGui::PopStyleVar(3);
				return false;
			}

			return true;
		}

		void EndCombo() {
			ImGui::EndPopup();
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(3);
		}

		bool Combo(const char* label, int* current_item, const char* const items[], int items_count) {
			const char* preview_value = NULL;
			if (*current_item >= 0 && *current_item < items_count)
				preview_value = items[*current_item];

			if (!BeginCombo(label, preview_value)) return false;

			bool value_changed = false;
			for (int i = 0; i < items_count; i++) {
				ImGui::PushID((void*)(intptr_t)i);
				const bool item_selected = (i == *current_item);
				
				ImVec4 accent = AverisUI::accent_color;
				ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(accent.x, accent.y, accent.z, 0.20f));
				ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(accent.x, accent.y, accent.z, 0.45f));
				ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(accent.x, accent.y, accent.z, 0.70f));
				
				if (ImGui::Selectable(items[i], item_selected)) {
					*current_item = i;
					value_changed = true;
				}
				
				ImGui::PopStyleColor(3);

				if (item_selected) {
					ImGui::SetItemDefaultFocus();
				}
				ImGui::PopID();
			}

			EndCombo();
			return value_changed;
		}

		static const char* VKToName(int vk) {
			switch (vk) {
			case VK_LBUTTON:  return "Mouse 1";
			case VK_RBUTTON:  return "Mouse 2";
			case VK_MBUTTON:  return "Mouse 3";
			case VK_XBUTTON1: return "Mouse 4";
			case VK_XBUTTON2: return "Mouse 5";
			case VK_MENU:     return "Alt";
			case VK_CONTROL:  return "Ctrl";
			case VK_SHIFT:    return "Shift";
			case VK_CAPITAL:  return "Caps";
			case VK_TAB:      return "Tab";
			case VK_SPACE:    return "Space";
			case VK_ESCAPE:   return "Esc";
			default:
				if (vk >= 0x30 && vk <= 0x39) { static char buf[2]; buf[0] = (char)vk; buf[1] = 0; return buf; }
				if (vk >= 0x41 && vk <= 0x5A) { static char buf[2]; buf[0] = (char)vk; buf[1] = 0; return buf; }
				if (vk >= VK_F1 && vk <= VK_F12) { static char buf[4]; sprintf_s(buf, "F%d", vk - VK_F1 + 1); return buf; }
				return "?";
			}
		}

		bool KeyBind(const char* label, int* key) {
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems) return false;

			ImGuiContext& g = *GImGui;
			const ImGuiStyle& style = g.Style;
			const ImGuiID id = window->GetID(label);
			const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

			const float left_pad = 14.0f;
			const float btn_w = 80.0f;
			const float btn_h = 22.0f;
			const ImVec2 pos = window->DC.CursorPos;
			float label_w = label_size.x > 0.0f ? label_size.x + 8.0f : 0.0f;
			const ImRect total_bb(pos, pos + ImVec2(left_pad + label_w + btn_w, ImMax(btn_h + 2.0f, label_size.y + 4.0f)));

			ImGui::ItemSize(total_bb, style.FramePadding.y);
			if (!ImGui::ItemAdd(total_bb, id)) return false;

			static ImGuiID active_bind = 0;
			bool waiting = (active_bind == id);

			bool hovered, held;
			bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);

			if (pressed && !waiting) {
				active_bind = id;
			}

			if (waiting) {
				for (int vk = 1; vk < 256; vk++) {
					if (vk == VK_ESCAPE) {
						if (HIDE_ASM(GetAsyncKeyState)(VK_ESCAPE) & 0x8000) {
							active_bind = 0;
							break;
						}
						continue;
					}
					if (HIDE_ASM(GetAsyncKeyState)(vk) & 0x8000) {
						*key = vk;
						active_bind = 0;
						break;
					}
				}
			}

			if (label_size.x > 0.0f) {
				ImVec2 lbl_pos = ImVec2(pos.x + left_pad, pos.y + (total_bb.GetHeight() - label_size.y) * 0.5f);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.75f, 0.75f, 0.79f, 1.0f));
				ImGui::RenderText(lbl_pos, label);
				ImGui::PopStyleColor();
			}

			const char* btn_text = waiting ? "..." : VKToName(*key);
			ImVec2 btn_pos = ImVec2(pos.x + left_pad + label_w, pos.y + 1.0f);
			ImRect btn_bb(btn_pos, btn_pos + ImVec2(btn_w, btn_h));

			ImVec4 bg_col = waiting ? ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.25f)
			                        : (hovered ? ImVec4(0.18f, 0.18f, 0.22f, 1.0f) : ImVec4(0.12f, 0.12f, 0.16f, 1.0f));
			window->DrawList->AddRectFilled(btn_bb.Min, btn_bb.Max, ImGui::GetColorU32(bg_col), 5.0f);
			ImVec4 brd = waiting ? ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.6f) : ImVec4(0.25f, 0.25f, 0.30f, 1.0f);
			window->DrawList->AddRect(btn_bb.Min, btn_bb.Max, ImGui::GetColorU32(brd), 5.0f, 0, 1.0f);

			ImVec2 txt_sz = ImGui::CalcTextSize(btn_text);
			ImVec2 txt_pos = btn_bb.Min + ImVec2((btn_w - txt_sz.x) * 0.5f, (btn_h - txt_sz.y) * 0.5f);
			ImU32 txt_col = ImGui::GetColorU32(waiting ? ImVec4(accent_color.x, accent_color.y, accent_color.z, 1.0f)
			                                          : ImVec4(0.78f, 0.78f, 0.82f, 1.0f));
			window->DrawList->AddText(ImGui::GetFont(), ImGui::GetFont()->FontSize, txt_pos, txt_col, btn_text);

			return !waiting && pressed;
		}

		bool CheckboxWithColor(const char* label, bool* v, float* col) {
			bool changed = Checkbox(label, v);
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems) return changed;

			float sq = 14.0f;
			ImVec2 lineStart = window->DC.CursorPos;
			float rightEdge = window->Pos.x + ImGui::GetWindowContentRegionMax().x;
			ImVec2 sqMin(rightEdge - sq - 4.0f, lineStart.y - sq - 6.0f);
			ImVec2 sqMax(sqMin.x + sq, sqMin.y + sq);

			ImVec4 c4(col[0], col[1], col[2], col[3]);
			window->DrawList->AddRectFilled(sqMin, sqMax, ImGui::GetColorU32(c4), 3.0f);
			window->DrawList->AddRect(sqMin, sqMax, ImGui::GetColorU32(ImVec4(1, 1, 1, 0.15f)), 3.0f);

			ImGuiID pid = window->GetID((std::string(label) + "##cpk").c_str());
			ImRect sqBB(sqMin, sqMax);
			if (ImGui::IsMouseHoveringRect(sqMin, sqMax) && ImGui::IsMouseClicked(0)) {
				ImGui::OpenPopupEx(pid);
			}

			ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.08f, 0.08f, 0.10f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.40f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
			if (ImGui::BeginPopupEx(pid, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings)) {
				ImGui::ColorPicker4("##inline_cp", col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);

			return changed;
		}

		void Tooltip(const char* text) {
			if (ImGui::IsItemHovered()) {
				ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.10f, 0.10f, 0.13f, 0.95f));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.3f));
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 5));
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(220.0f);
				ImGui::TextUnformatted(text);
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
				ImGui::PopStyleVar(2);
				ImGui::PopStyleColor(2);
			}
		}

		void DrawPreviewSkeleton(ImDrawList* dl, ImVec2 origin, float scale, bool showBox, int boxType, bool showSkeleton, bool showHead, int headStyle, bool showSnap, ImVec4 col) {
			ImU32 c = ImGui::GetColorU32(col);
			ImU32 cDim = ImGui::GetColorU32(ImVec4(col.x, col.y, col.z, 0.4f));

			ImVec2 head = origin + ImVec2(0, -55 * scale);
			ImVec2 neck = origin + ImVec2(0, -45 * scale);
			ImVec2 chest = origin + ImVec2(0, -30 * scale);
			ImVec2 pelvis = origin + ImVec2(0, 0);
			ImVec2 lShoulder = origin + ImVec2(-18 * scale, -40 * scale);
			ImVec2 rShoulder = origin + ImVec2(18 * scale, -40 * scale);
			ImVec2 lElbow = origin + ImVec2(-25 * scale, -25 * scale);
			ImVec2 rElbow = origin + ImVec2(25 * scale, -25 * scale);
			ImVec2 lHand = origin + ImVec2(-22 * scale, -10 * scale);
			ImVec2 rHand = origin + ImVec2(22 * scale, -10 * scale);
			ImVec2 lKnee = origin + ImVec2(-10 * scale, 20 * scale);
			ImVec2 rKnee = origin + ImVec2(10 * scale, 20 * scale);
			ImVec2 lFoot = origin + ImVec2(-12 * scale, 40 * scale);
			ImVec2 rFoot = origin + ImVec2(12 * scale, 40 * scale);

			if (showBox) {
				float boxH = 100 * scale;
				float boxW = boxH * 0.45f;
				ImVec2 tl(origin.x - boxW / 2, origin.y - 60 * scale);
				ImVec2 br(origin.x + boxW / 2, origin.y + 42 * scale);
				if (boxType == 0) {
					float lw = boxW / 3; float lh = boxH / 3;
					dl->AddLine(tl, ImVec2(tl.x + lw, tl.y), c, 1.2f);
					dl->AddLine(tl, ImVec2(tl.x, tl.y + lh), c, 1.2f);
					dl->AddLine(ImVec2(br.x, tl.y), ImVec2(br.x - lw, tl.y), c, 1.2f);
					dl->AddLine(ImVec2(br.x, tl.y), ImVec2(br.x, tl.y + lh), c, 1.2f);
					dl->AddLine(ImVec2(tl.x, br.y), ImVec2(tl.x + lw, br.y), c, 1.2f);
					dl->AddLine(ImVec2(tl.x, br.y), ImVec2(tl.x, br.y - lh), c, 1.2f);
					dl->AddLine(br, ImVec2(br.x - lw, br.y), c, 1.2f);
					dl->AddLine(br, ImVec2(br.x, br.y - lh), c, 1.2f);
				} else {
					dl->AddRect(tl, br, c, 0, 0, 1.2f);
				}
			}

			if (showSkeleton) {
				dl->AddLine(head, neck, c, 1.2f);
				dl->AddLine(neck, chest, c, 1.2f);
				dl->AddLine(chest, pelvis, c, 1.2f);
				dl->AddLine(neck, lShoulder, c, 1.2f);
				dl->AddLine(neck, rShoulder, c, 1.2f);
				dl->AddLine(lShoulder, lElbow, c, 1.2f);
				dl->AddLine(rShoulder, rElbow, c, 1.2f);
				dl->AddLine(lElbow, lHand, c, 1.2f);
				dl->AddLine(rElbow, rHand, c, 1.2f);
				dl->AddLine(pelvis, lKnee, c, 1.2f);
				dl->AddLine(pelvis, rKnee, c, 1.2f);
				dl->AddLine(lKnee, lFoot, c, 1.2f);
				dl->AddLine(rKnee, rFoot, c, 1.2f);
			}

			if (showHead) {
				float r = 6.0f * scale;
				if (headStyle == 0)
					dl->AddCircle(head, r, c, 24, 1.2f);
				else
					dl->AddRect(ImVec2(head.x - r, head.y - r), ImVec2(head.x + r, head.y + r), c, 0, 0, 1.2f);
			}

			if (showSnap) {
				dl->AddLine(ImVec2(origin.x, origin.y + 65 * scale), lFoot, cDim, 1.0f);
			}
		}
	}

	void AnimatedButton(const char* buttonText, int& tab, const char* icon, int tabIndex, ImVec4 buttonColor, ImVec4 hoverColor, ImVec4 activeColor) {
		ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);

		if (ImGui::Button(buttonText, ImVec2(120, 40))) {
			tab = tabIndex;
			if (ImGui::IsItemHovered()) {
				ImVec2 start = ImGui::GetItemRectMin();
				ImVec2 end = ImVec2(start.x + ImGui::GetItemRectSize().x, start.y);
				ImGui::GetWindowDrawList()->AddLine(start, end, ImColor(255, 255, 255, 255));
			}
		}
		ImGui::SameLine();

		ImGui::PopStyleColor(3);
	}

	int windowstate = 1;
	void ChangeClickability(bool canclick, HWND ownd)
	{
		long style = GetWindowLong(
			ownd, GWL_EXSTYLE);
		if (canclick) {
			style &= ~WS_EX_LAYERED;
			SetWindowLong(ownd,
				GWL_EXSTYLE, style);
			SetForegroundWindow(ownd);
			windowstate = 1;
		}
		else {
			style |= WS_EX_LAYERED;
			SetWindowLong(ownd,
				GWL_EXSTYLE, style);
			windowstate = 0;
		}
	}

	void ApplyPresetLegit() {
		config.player_box = true; config.esptype = 0;
		config.player_snapline = false; config.player_distance = true;
		config.player_healthbar = true; config.VisibleCheckAveris = true;
		config.aimenable = true; config.aimbot_fov = 30.f; config.aimbot_smooth = 15.f;
		config.aimbot_draw_fov = false; config.FilledFOV = false;
		config.VisibleAimbotAveris = true; config.TeamCheck = false;
		config.Streamprooff = false; config.box_filled = false;
	}
	void ApplyPresetRage() {
		config.player_box = true; config.esptype = 1; // Filled Box
		config.player_snapline = true; config.SnaplineType = 2;
		config.player_distance = true; config.player_healthbar = true;
		config.VisibleCheckAveris = true; config.Agenticons = true;
		config.aimenable = true; config.aimbot_fov = 150.f; config.aimbot_smooth = 1.f;
		config.aimbot_draw_fov = true; config.FilledFOV = false;
		config.VisibleAimbotAveris = false; config.TeamCheck = false;
		config.box_filled = true; config.box_filled_alpha = 0.15f;
	}
	void ApplyPresetStream() {
		config.player_box = true; config.esptype = 0;
		config.player_skeleton = false; config.circlehead = false;
		config.player_snapline = false; config.player_distance = false;
		config.player_healthbar = true; config.VisibleCheckAveris = true;
		config.aimenable = true; config.aimbot_fov = 25.f; config.aimbot_smooth = 20.f;
		config.aimbot_draw_fov = false; config.FilledFOV = false;
		config.VisibleAimbotAveris = true; config.TeamCheck = false;
		config.Streamprooff = true; config.Agenticons = false;
		config.characterr = false; config.box_filled = false;
	}

	const int numParticles = 150;
	const float particleSize = 4.0f;
	const float gravity = 100.0f; 
	const float maxDistance = 100.0f;

	struct Particle {
		ImVec2 position;
		ImVec2 velocity;
		float lifespan;
	};

	std::vector<Particle> particles;
	bool initialized = false;


	// Ã¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢Â
	//  PREMIUM SIDEBAR NAV BUTTON
	// Ã¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢ÂÃ¢â€¢Â
	void NewSidebarButton(const char* icon, const char* btnLabel, int& currentTab,
		int tabIndex, const ImVec2& size, float ar, float ag, float ab)
	{
		bool isActive = (currentTab == tabIndex);
		ImGuiWindow* win = ImGui::GetCurrentWindow();
		ImGuiID id = win->GetID(btnLabel);

		float& anim = *win->StateStorage.GetFloatRef(id, 0.0f);
		ImVec2 bpos = win->DC.CursorPos;
		bool hov = ImGui::IsMouseHoveringRect(bpos, bpos + size);
		anim = ImLerp(anim, isActive ? 1.0f : (hov ? 0.45f : 0.0f), ImGui::GetIO().DeltaTime * 12.0f);

		ImDrawList* dl = win->DrawList;

		// Glow background pill
		if (anim > 0.01f) {
			dl->AddRectFilled(bpos + ImVec2(4, 2), bpos + size - ImVec2(4, 2),
				ImGui::GetColorU32(ImVec4(ar * 0.35f, ag * 0.25f, ab * 0.55f, 0.22f * anim)), 8.0f);
		}
		// Left accent glow bar
		if (anim > 0.01f) {
			dl->AddRectFilled(bpos + ImVec2(4, 8), bpos + ImVec2(7, size.y - 8),
				ImGui::GetColorU32(ImVec4(ar, ag, ab, anim)), 2.0f);
			// soft wider glow behind bar
			dl->AddRectFilled(bpos + ImVec2(4, 8), bpos + ImVec2(10, size.y - 8),
				ImGui::GetColorU32(ImVec4(ar, ag, ab, 0.15f * anim)), 2.0f);
		}

		float tc = 0.38f + anim * 0.62f;
		ImU32 col = ImGui::GetColorU32(ImVec4(tc, tc, tc + 0.08f, 1.0f));
		float ty = bpos.y + (size.y - ImGui::GetTextLineHeight()) * 0.5f;
		std::string full = std::string(icon) + "  " + btnLabel;
		dl->AddText(ImVec2(bpos.x + 16, ty), col, full.c_str());

		ImGui::InvisibleButton(btnLabel, size);
		if (ImGui::IsItemClicked()) currentTab = tabIndex;
		ImGui::Dummy(ImVec2(0, 3));
	}

	auto menu() {
		Spoof_Address;

		// ── Smooth fade ────────────────────────────────────────────────────────
		static float g_menu_alpha = 0.f;
		g_menu_alpha = ImLerp(g_menu_alpha, menu_open ? 1.f : 0.f,
		                      ImGui::GetIO().DeltaTime * 20.f);
		if (g_menu_alpha < 0.005f) return;
		const float fa = g_menu_alpha;

		const ImVec4 colAccent = config.menu_accent;
		e_elements::accent     = colAccent;
		e_elements::fade_alpha = fa;

		// ── Layout sabitleri ──────────────────────────────────────────────────
		static const float WIN_W     = 730.f;
		static const float WIN_H     = 460.f;
		static const float ICON_W    = 47.f;
		static const float SUB_W     = 163.f;
		static const float SIDEBAR_W = ICON_W + SUB_W;
		static const float HDR_H     = 47.f;
		static const float CONTENT_X = SIDEBAR_W;
		static const float CONTENT_W = WIN_W - SIDEBAR_W;
		static const float CHILD_PAD = 8.f;

		static int tab    = 0;
		static int subtab = 0;

		// ── Style ─────────────────────────────────────────────────────────────
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 6.f; style.ChildRounding = 5.f;
		style.FrameRounding  = 4.f; style.PopupRounding  = 4.f;
		style.GrabRounding   = 3.f;
		style.ItemSpacing    = ImVec2(6.f, 5.f);
		style.FramePadding   = ImVec2(8.f, 4.f);
		style.ScrollbarSize  = 6.f;

		// THE correct way: set style.Alpha once before drawing anything.
		// Every widget reads this — checkbox, slider, combo, text, all of them.
		style.Alpha = fa;

		// 18 colors — alpha values handled by style.Alpha

		ImGui::SetNextWindowSize({ WIN_W, WIN_H });

		// --- SKEET UI REPLACEMENT ---
		RECT screen_rect;
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		auto x = float(screen_rect.right - 640) / 2.f;
		auto y = float(screen_rect.bottom - 520) / 2.f;

		ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
		ImGui::SetNextWindowSize(settings::size_menu);
		ImGui::Begin("RENAGLOBAL", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);

		const auto& pos = ImGui::GetWindowPos();
		const auto& draw_list = ImGui::GetWindowDrawList();

		{
			style.Colors[ImGuiCol_WindowBg] = menu::window_bg;
			style.Colors[ImGuiCol_Border] = menu::border;
			style.Colors[ImGuiCol_WindowShadow] = menu::border_shadow;
			style.Colors[ImGuiCol_ScrollbarGrab] = menu::scrollbar;
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = menu::scrollbar_hovered;
			style.Colors[ImGuiCol_ScrollbarGrabActive] = colors::accent_color;
			style.Colors[ImGuiCol_ScrollbarBg] = menu::scrollbar_bg;
			style.ItemSpacing = settings::item_spacing;
			style.WindowPadding = settings::item_padding;
			style.WindowRounding = menu::window_rounding;
			style.ScrollbarSize = menu::scroll_size;
			style.Alpha = fa;
		}

		{
			draw_list->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 700, pos.y + 40), ImGui::GetColorU32(menu::line), menu::window_rounding, ImDrawCornerFlags_Top);
			draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 40), ImVec2(pos.x + 700, pos.y + 41), ImGui::GetColorU32(menu::line2));
			draw_list->AddText(ImVec2(pos.x + 20, pos.y + 13), ImGui::GetColorU32(colors::accent_color), "RENAGLOBAL");
		}

		{
			ImGui::SetCursorPos(ImVec2(15, 55));
			ImGui::BeginGroup();
			{
				if (custom::Tab(skCrypt("Aimbot").decrypt(), pictures::aim_img, 0 == misc::tab_count)) misc::tab_count = 0;
				if (custom::Tab(skCrypt("Visuals").decrypt(), pictures::visual_img, 1 == misc::tab_count)) misc::tab_count = 1;
				if (custom::Tab(skCrypt("Settings").decrypt(), pictures::setting_img, 2 == misc::tab_count)) misc::tab_count = 2;
			}
			ImGui::EndGroup();
		}

		misc::alpha_child = ImLerp(misc::alpha_child, (misc::tab_count == misc::active_tab_count) ? 1.f : 0.f, 15.f * ImGui::GetIO().DeltaTime);
		if (misc::alpha_child < 0.01f && misc::child_add < 0.01f) misc::active_tab_count = misc::tab_count;

		ImGui::SetCursorPos(ImVec2(95, 55));
		ImGui::BeginChild("General", ImVec2(597, 445));
		{
			ImGui::SetCursorPos(ImVec2(0, 100 - (misc::alpha_child * 100)));
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, misc::alpha_child * style.Alpha);

			// AIMBOT TAB
			if (misc::active_tab_count == 0) {
				ImGui::BeginGroup();
				{
					custom::BeginChild(nullptr, skCrypt("Aimbot").decrypt(), ImVec2(285, 260));
					{
						custom::Checkbox("Enable##aim", &config.aimenable);
						custom::Checkbox("Draw FOV", &config.aimbot_draw_fov);
						custom::Checkbox("Filled FOV", &config.FilledFOV);
						if (config.FilledFOV) {
							ImGui::ColorEdit4("Fill Color", (float*)&config.FOVFillled, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
						}
						custom::Checkbox("Visibility Check", &config.VisibleAimbotAveris);
						custom::Checkbox("Recoil Control", &config.rcs);
					}
					custom::EndChild();
					custom::Spacing(10.f);
					custom::BeginChild(nullptr, "Triggerbot", ImVec2(285, 175));
					{
						custom::Checkbox("Enable##trig", &config.triggerbot);
						custom::SliderInt("Delay", &config.flickdelay, 0, 500, "%d ms");
					}
					custom::EndChild();
				}
				ImGui::EndGroup();
				ImGui::SetCursorPos(ImVec2(295, 100 - (misc::alpha_child * 100)));
				ImGui::BeginGroup();
				{
					custom::BeginChild(nullptr, "Settings", ImVec2(285, 445));
					{
						ImGui::PushItemWidth(200.f);
						ImGui::Combo("Target Bone", &config.aimboness, aimbone, IM_ARRAYSIZE(aimbone));
						custom::SliderFloat("FOV", &config.aimbot_fov, 1.f, 150.f, "%.0f");
						custom::SliderFloat("Smooth", &config.aimbot_smooth, 1.f, 30.f, "%.1f");
						if (config.rcs) {
							custom::SliderFloat("RCS Strength", &config.RecoilStrength, 0.f, 1.f, "%.2f");
						}
						ImGui::PopItemWidth();
					}
					custom::EndChild();
				}
				ImGui::EndGroup();
			}

			// VISUALS TAB
			else if (misc::active_tab_count == 1) {
				ImGui::BeginGroup();
				{
					custom::BeginChild(nullptr, "Players", ImVec2(285, 445));
					{
						static bool esp_enabled = false;
						custom::Checkbox("Enable ESP", &esp_enabled);
						if (esp_enabled) {
							custom::Checkbox("Box", &config.player_box);
							custom::ColorEdit4("Box Color", (float*)&config.espcolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

							custom::Checkbox("Skeleton", &config.player_skeleton);
							custom::ColorEdit4("Skel Color", (float*)&config.skeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							
							custom::Checkbox("Head Circle", &config.circlehead);
							custom::ColorEdit4("Head Color", (float*)&config.headboxcolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							
							custom::Checkbox("Health Bar", &config.player_healthbar);
							if (config.player_healthbar) {
								ImGui::Combo("Type", &config.Healthnigger, healthtype, IM_ARRAYSIZE(healthtype));
								ImGui::Combo("Position", &config.HealthPosition, healthposition, IM_ARRAYSIZE(healthposition));
							}
							
							custom::Checkbox("Snaplines", &config.player_snapline);
							if (config.player_snapline) {
								ImGui::Combo("Snapline Type", &config.SnaplineType, Snapline_type, IM_ARRAYSIZE(Snapline_type));
							}

							custom::Checkbox("Distance", &config.player_distance);
							custom::Checkbox("Agent Icons", &config.Agenticons);
							custom::Checkbox("Weapon Action", &config.Weapon);
							custom::Checkbox("View Angle", &config.player_view_angle);
							custom::Checkbox("Rank / Ping", &config.FPSCheck);
							
							custom::Checkbox("Visible Check", &config.VisibleCheckAveris);
							if (config.VisibleCheckAveris) {
								custom::ColorEdit4("Visible", (float*)&config.espvisiblecolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
								custom::ColorEdit4("Invisible", (float*)&config.espcolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							}
						}
					}
					custom::EndChild();
				}
				ImGui::EndGroup();
				ImGui::SetCursorPos(ImVec2(295, 100 - (misc::alpha_child * 100)));
				ImGui::BeginGroup();
				{
					custom::BeginChild(nullptr, "Box Style", ImVec2(285, 445));
					{
						ImGui::Combo("Box Type", &config.esptype, type, IM_ARRAYSIZE(type));
						if (config.esptype == 1) {
							custom::ColorEdit4("Fill Color", (float*)&config.box_filled_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							custom::SliderFloat("Fill Alpha", &config.box_filled_alpha, 0.f, 1.f, "%.2f");
						}
						custom::SliderFloat("Box W", &config.ESPBOXThickness, 0.5f, 8.f, "%.1f");
						custom::SliderFloat("Skel W", &config.SkeletonThickness, 0.5f, 8.f, "%.1f");
						custom::SliderFloat("Head W", &config.CircleHeadThickness, 0.5f, 8.f, "%.1f");
						
						custom::Spacing(10.f);
						custom::Checkbox("Spike Timer", &config.spiketimer);
						custom::Checkbox("Spike Line Up", &config.spiketimerlineup);
						custom::Checkbox("Memory Radar", &config.MapradarV2);
						custom::Checkbox("Rainbow Skel.", &config.rainbowskeleton);
					}
					custom::EndChild();
				}
				ImGui::EndGroup();
			}

			// SETTINGS TAB
			else if (misc::active_tab_count == 2) {
				ImGui::BeginGroup();
				{
					custom::BeginChild(nullptr, "General", ImVec2(285, 445));
					{
						custom::Checkbox("Stream Proof", &config.Streamprooff);
						custom::ColorEdit4("Accent Color", (float*)&config.menu_accent, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
						
						static std::vector<std::string> cfg_list;
						static int cfg_sel = -1;
						static char cfg_name[64] = "";
						static bool cfg_dirty = true;
						if (cfg_dirty) { cfg_list = ListConfigs(); cfg_dirty = false; }
						
						if (ImGui::BeginListBox("##cfglist", ImVec2(265.f, 120.f))) {
							for (int i = 0; i < (int)cfg_list.size(); i++) {
								bool sel = (cfg_sel == i);
								if (ImGui::Selectable(cfg_list[i].c_str(), sel)) {
									cfg_sel = i;
									strncpy_s(cfg_name, cfg_list[i].c_str(), sizeof(cfg_name)-1);
								}
							}
							ImGui::EndListBox();
						}
						ImGui::InputText("##cfgname", cfg_name, sizeof(cfg_name));
						if (custom::Button("Create", ImVec2(130.f, 24.f))) {
							if (strlen(cfg_name)>0) { SaveNamedConfig(cfg_name); cfg_dirty=true; }
						}
						ImGui::SameLine();
						if (custom::Button("Load", ImVec2(130.f, 24.f))) {
							if (cfg_sel>=0 && cfg_sel<(int)cfg_list.size()) LoadNamedConfig(cfg_list[cfg_sel]);
						}
						if (custom::Button("Save", ImVec2(130.f, 24.f))) {
							if (cfg_sel>=0 && cfg_sel<(int)cfg_list.size()) SaveNamedConfig(cfg_list[cfg_sel]);
						}
						ImGui::SameLine();
						if (custom::Button("Open Folder", ImVec2(130.f, 24.f))) {
							EnsureConfigDir();
							ShellExecuteA(NULL,"open","C:\spec\configs",NULL,NULL,SW_SHOWNORMAL);
						}
						if (custom::Button("Refresh", ImVec2(265.f, 24.f))) {
							cfg_list = ListConfigs(); cfg_sel = -1;
						}
					}
					custom::EndChild();
				}
				ImGui::EndGroup();
			}

			ImGui::PopStyleVar();
		}
		ImGui::EndChild();
		ImGui::End();

		style.Alpha = 1.f;
	}

		bool staticassnigga = false;

	void AverisRender() {
		Spoof_Address;
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
			
		static float time = 0.0f;
		time += ImGui::GetIO().DeltaTime;

		float loopTime = time - static_cast<int>(time);

		float r = (std::sin(loopTime * 6.28318f) + 1.0f) / 2.0f; 
		float g = (std::sin(loopTime * 6.28318f + 2.09439f) + 1.0f) / 2.0f; 
		float b = (std::sin(loopTime * 6.28318f + 4.18879f) + 1.0f) / 2.0f;

		{
			static bool last_stream_proof = !config.Streamprooff;
			if (last_stream_proof != config.Streamprooff) {
				last_stream_proof = config.Streamprooff;
				HIDE_ASM(SetWindowDisplayAffinity)(Window, config.Streamprooff ? WDA_EXCLUDEFROMCAPTURE : 0);
			}
		}

		{
			static float fps = 0.f;
			static float fpsTimer = 0.f;
			static int frameCount = 0;
			frameCount++;
			fpsTimer += ImGui::GetIO().DeltaTime;
			if (fpsTimer >= 0.5f) {
				fps = frameCount / fpsTimer;
				frameCount = 0;
				fpsTimer = 0.f;
			}

			char statsText[128];
			//sprintf_s(statsText, "CORTEX SOFTWARE | FPS: %.0f", fps, LocalPlayerSX::ping);
			//DrawOutlinedText(AVERISONTOP, statsText, ImVec2(10, 10), 16.0f, ImColor(200, 200, 200), false);

		}

		if (config.RecoilCrosshair) {
			auto ctrlRot = driver::read<fvector>(LocalPlayerSX::player_controller + offsets::control_rotation);
			float sw = (float)screen_width;
			float sh = (float)screen_height;

			fvector punch;
			punch.x = camera::rotation.x - ctrlRot.x;
			punch.y = camera::rotation.y - ctrlRot.y;
			while (punch.y > 180.f) punch.y -= 360.f;
			while (punch.y < -180.f) punch.y += 360.f;
			while (punch.x > 180.f) punch.x -= 360.f;
			while (punch.x < -180.f) punch.x += 360.f;

			float cx = sw / 2.0f + (sw / 90.0f * punch.y * 0.75f);
			float cy = sh / 2.0f - (sh / 90.0f * punch.x * 0.75f);

			ImGui::GetForegroundDrawList()->AddCircle(ImVec2(cx, cy), 5, config.RecoilCrosshairColor, 64, 2);
		}

		int menuKeyIndex = config.menubind;
		if (menuKeyIndex < 0 || menuKeyIndex >= (int)(sizeof(MenuKeyList) / sizeof(MenuKeyList[0]))) {
			menuKeyIndex = 0;
		}

		// Insert veya Delete ile menu aç/kapat, menubind seçimi kaldırıldı
		if ((HIDE_ASM(GetAsyncKeyState)(VK_INSERT) & 1) || (HIDE_ASM(GetAsyncKeyState)(VK_DELETE) & 1))
			menu_open = !menu_open;

		static bool last_menu_state = false;
		if (menu_open != last_menu_state) {
			last_menu_state = menu_open;
			if (Window) {
				if (menu_open) {
					SetWindowLongA(Window, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
					SetFocus(Window);
				} else {
					SetWindowLongA(Window, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
				}
			}
		}

		menu();
		render_players();

		D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		if (D3dDevice->BeginScene() >= 0) {
			ImGui::Render();

			D3dDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
			D3dDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
			D3dDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
			D3dDevice->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_MAX);

			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

			D3dDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);

			D3dDevice->EndScene();
		}

		HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			D3dDevice->Reset(&d3dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	bool MyIsWindowVisible(HWND hwnd) {
		Spoof_Address;
		if (hwnd == NULL) return false;
		LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);

		WINDOWPLACEMENT placement;
		HIDE_ASM(GetWindowPlacement)(hwnd, &placement);

		return (style & WS_VISIBLE) && (placement.showCmd != SW_HIDE);
	}

	void RenderVALORANT() {

		VMProtectBeginUltra(skCrypt("LoopInstead").decrypt());
		Spoof_Address;
		timeBeginPeriod(1);
		static RECT old_rc;
		ZeroMemory(&Message, sizeof(MSG));

		while (Message.message != WM_QUIT)
		{
			if (PeekMessage(&Message, Window, 0, 0, offsets::pm_remove))
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}

			HWND hwnd_active = GetForegroundWindow();
			static bool was_topmost = false;
			if (hwnd_active == hwndVAL) {
				if (!was_topmost) {
					SetWindowPos(Window, HWND_TOPMOST, 2, 2, -3, -3, 0x0002 | 0x0001);
					was_topmost = true;
				}
			} else {
				was_topmost = false;
			}

			RECT rc;
			POINT xy;
			ZeroMemory(&rc, sizeof(RECT));
			ZeroMemory(&xy, sizeof(POINT));
			GetClientRect(hwndVAL, &rc);
			ClientToScreen(hwndVAL, &xy);
			rc.left = xy.x;
			rc.top = xy.y;

			ImGuiIO& io = ImGui::GetIO();
			io.ImeWindowHandle = hwndVAL;

			static LARGE_INTEGER lastTime = {};
			static LARGE_INTEGER freq = {};
			if (freq.QuadPart == 0) { QueryPerformanceFrequency(&freq); QueryPerformanceCounter(&lastTime); }
			LARGE_INTEGER nowTime;
			QueryPerformanceCounter(&nowTime);
			io.DeltaTime = (float)(nowTime.QuadPart - lastTime.QuadPart) / (float)freq.QuadPart;
			if (io.DeltaTime <= 0.f) io.DeltaTime = 1.f / 60.f;
			lastTime = nowTime;

			POINT p;
			GetCursorPos(&p);
			io.MousePos.x = p.x - xy.x;
			io.MousePos.y = p.y - xy.y;

			if (HIDE_ASM(GetAsyncKeyState)(VK_LBUTTON)) {
				io.MouseDown[0] = true;
				io.MouseClicked[0] = true;
				io.MouseClickedPos[0].x = io.MousePos.x;
				io.MouseClickedPos[0].y = io.MousePos.y;
			}
			else
				io.MouseDown[0] = false;

			if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
			{
				old_rc = rc;

				Width = rc.right;
				Height = rc.bottom;

					d3dpp.BackBufferWidth = Width;
				d3dpp.BackBufferHeight = Height;
				SetWindowPos(Window, (HWND)0, xy.x + 2, xy.y + 2, Width - 3, Height - 3, offsets::swp_noactivate);
				D3dDevice->Reset(&d3dpp);
			}

			AverisRender();
		}
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		DestroyWindow(Window);
	}


	static std::wstring s_randomClassName;

	static void generateClassName() {
		if (!s_randomClassName.empty()) return;
		srand((unsigned)(__rdtsc() & 0xFFFFFFFF));
		const wchar_t chars[] = L"abcdefghijklmnopqrstuvwxyz";
		int len = 8 + (rand() % 6);
		for (int i = 0; i < len; i++)
			s_randomClassName += chars[rand() % 26];
	}

	void STOPTHERENDERVALORANT() {
		VMProtectBeginUltra(skCrypt("STOPTHERENDERVALORANT").decrypt());
		Spoof_Address;
		TriBuf->Release();
		D3dDevice->Release();
		p_Object->Release();

		DestroyWindow(Window);
		UnregisterClassW(s_randomClassName.c_str(), NULL);
	}

	bool DirectXVALORANT() {

		VMProtectBeginUltra(skCrypt("DirectX").decrypt());
		Spoof_Address;

		if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
			return false;

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = Width;
		d3dpp.BackBufferHeight = Height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.hDeviceWindow = Window;
		d3dpp.Windowed = TRUE;
		d3dpp.BackBufferCount = 1;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr; // imgui.ini dosyası oluşturma
		ImGui_ImplWin32_Init(Window);
		ImGui_ImplDX9_Init(D3dDevice);
		p_Object->Release();

		auto GWORLD = driver::read2<uintptr_t>(driver::read2<uintptr_t>(baseee + offsets::UWorld));
		setColoAARAr(7);

		logotwo = LoadPNGToTextureDX9(D3dDevice, xxssd, sizeof(xxssd));
		cypherlogo = LoadPNGToTextureDX9(D3dDevice, cypher, sizeof(cypher));
		reynalogo = LoadPNGToTextureDX9(D3dDevice, reyna, sizeof(reyna));
		neonlogo = LoadPNGToTextureDX9(D3dDevice, neon, sizeof(neon));
		isologo = LoadPNGToTextureDX9(D3dDevice, iso, sizeof(iso));
		phoenixlogo = LoadPNGToTextureDX9(D3dDevice, phoenixblackpeople, sizeof(phoenixblackpeople));
		jettlogo = LoadPNGToTextureDX9(D3dDevice, jettx, sizeof(jettx));
		viperlogo = LoadPNGToTextureDX9(D3dDevice, viperx, sizeof(viperx));
		brimstonelogo = LoadPNGToTextureDX9(D3dDevice, brimstonex, sizeof(brimstonex));
		clovelogo = LoadPNGToTextureDX9(D3dDevice, clovex, sizeof(clovex));
		botlogo = LoadPNGToTextureDX9(D3dDevice, logobothaha, sizeof(logobothaha));
		astralogo = LoadPNGToTextureDX9(D3dDevice, astrax, sizeof(astrax));
		breachlogo = LoadPNGToTextureDX9(D3dDevice, breachx, sizeof(breachx));
		chamberlogo = LoadPNGToTextureDX9(D3dDevice, chamberx, sizeof(chamberx));
		deadlocklogo = LoadPNGToTextureDX9(D3dDevice, deadlockx, sizeof(deadlockx));
		harborlogo = LoadPNGToTextureDX9(D3dDevice, harborx, sizeof(harborx));
		fadelogo = LoadPNGToTextureDX9(D3dDevice, fadex, sizeof(fadex));
		gekkologo = LoadPNGToTextureDX9(D3dDevice, gekkox, sizeof(gekkox));
		omenlogo = LoadPNGToTextureDX9(D3dDevice, omenx, sizeof(omenx));
		killjoylogo = LoadPNGToTextureDX9(D3dDevice, killjoyx, sizeof(killjoyx));
		razelogo = LoadPNGToTextureDX9(D3dDevice, razex, sizeof(razex));
		skyelogo = LoadPNGToTextureDX9(D3dDevice, skyex, sizeof(skyex));
		yorulogo = LoadPNGToTextureDX9(D3dDevice, yorux, sizeof(yorux));
		sovalogo = LoadPNGToTextureDX9(D3dDevice, sovax, sizeof(sovax));
		sagelogo = LoadPNGToTextureDX9(D3dDevice, sagex, sizeof(sagex));
		kayologo = LoadPNGToTextureDX9(D3dDevice, kayox, sizeof(kayox));
		vyselogo = LoadPNGToTextureDX9(D3dDevice, Vyseicon, sizeof(Vyseicon));
		waylalogo = LoadPNGToTextureDX9(D3dDevice, waylalogonigger, sizeof(waylalogonigger));
		tejologo = LoadPNGToTextureDX9(D3dDevice, tejologong, sizeof(tejologong));
		layreLogo   = LoadPNGToTextureDX9(D3dDevice, (unsigned char*)kz_logo_data, (int)kz_logo_size);
		ctxlogo_tex = LoadPNGToTextureDX9(D3dDevice, ctxlogo, sizeof(ctxlogo));
		pictures::aim_img = LoadPNGToTextureDX9(D3dDevice, images_data::img_aim, sizeof(images_data::img_aim));
		pictures::visual_img = LoadPNGToTextureDX9(D3dDevice, images_data::img_visual, sizeof(images_data::img_visual));
		pictures::setting_img = LoadPNGToTextureDX9(D3dDevice, images_data::img_setting, sizeof(images_data::img_setting));
		FontXs();
		LoadAllConfig();
		HANDLE hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)AverisFind, NULL, NULL, NULL);
		if (hThread) {
			typedef long(NTAPI* pNtSetInformationThread)(HANDLE, ULONG, PVOID, ULONG);
			auto NtSetInfo = (pNtSetInformationThread)GetProcAddress(GetModuleHandleA(crypt("ntdll.dll").decrypt()), crypt("NtSetInformationThread").decrypt());
			if (NtSetInfo) NtSetInfo(hThread, 0x11, NULL, 0);
		}

		RenderVALORANT();
		STOPTHERENDERVALORANT();
	}

	LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		VMProtectBeginUltra(skCrypt("WinProc").decrypt());

		Spoof_Address;
		if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
			return true;

		switch (Message)
		{
		case WM_DESTROY:
			SaveAllConfig();
			STOPTHERENDERVALORANT();
			PostQuitMessage(0);
			exit(4);
			break;
		case WM_SIZE:
			if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				ImGui_ImplDX9_InvalidateDeviceObjects();
				d3dpp.BackBufferWidth = LOWORD(lParam);
				d3dpp.BackBufferHeight = HIWORD(lParam);
				HRESULT hr = D3dDevice->Reset(&d3dpp);
				if (hr == D3DERR_INVALIDCALL)
					IM_ASSERT(0);
				ImGui_ImplDX9_CreateDeviceObjects();
			}
			break;
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		return 0;
	}

	bool amd = true;
	bool nvidia = false;

	void WINDOWNIGGA() {

		VMProtectBeginUltra(skCrypt("WindowHandle").decrypt());

		Spoof_Address;
		generateClassName();
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.lpszClassName = s_randomClassName.c_str();
		wc.lpfnWndProc = WinProc;
		RegisterClassEx(&wc);

		if (hwndVAL)
		{
			Spoof_Address;
			HIDE_ASM(GetClientRect)(hwndVAL, &GameRect);
			POINT xy = { 0 };
			HIDE_ASM(ClientToScreen)(hwndVAL, &xy);
			GameRect.left = xy.x;
			GameRect.top = xy.y;
			Width = GameRect.right;
			Height = GameRect.bottom;

		}
		else {
			exit(2);
		}

		// Create standalone transparent overlay
		Window = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW, s_randomClassName.c_str(), s_randomClassName.c_str(), WS_POPUP, 2, 2, Width - 2, Height - 2, 0, 0, 0, 0);
		if (!Window) {
			exit(4);
		}

		SetLayeredWindowAttributes(Window, RGB(0, 0, 0), 255, LWA_ALPHA);
		HIDE_ASM(DwmExtendFrameIntoClientArea)(Window, &Margin);

		SetWindowLong(Window, (-20), WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW);

		ShowWindow(Window, SW_SHOW);
		UpdateWindow(Window);
	}

	
	void StartAveris() {
		while (!hwndVAL) {
			std::cout << skCrypt("[*] Valorant penceresi icin [ENTER] tusuna basin...\n").decrypt();
			std::cin.get();
			hwndVAL = HIDE_ASM(FindWindowA)((LPCSTR)nullptr, skCrypt("VALORANT  ").decrypt());
			if (!hwndVAL) {
				hwndVAL = HIDE_ASM(FindWindowA)(skCrypt("UnrealWindow").decrypt(), skCrypt("VALORANT").decrypt());
			}
			if (!hwndVAL) {
				hwndVAL = HIDE_ASM(FindWindowA)((LPCSTR)nullptr, skCrypt("VALORANT").decrypt());
			}
			if (!hwndVAL) {
				hwndVAL = HIDE_ASM(FindWindowA)(skCrypt("UnrealWindow").decrypt(), (LPCSTR)nullptr);
			}
			if (!hwndVAL) {
				std::cout << skCrypt("[-] Valorant bulunamadi! Oyunu acip tekrar [ENTER] tusuna basin.\n").decrypt();
			}
		}

		Sleep(2000);
		setColoAARAr(7);

		WINDOWNIGGA();
		DirectXVALORANT();
	}
}
