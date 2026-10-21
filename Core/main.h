#pragma once

#include <sstream>
#include <mutex>
#include <fstream>
#include <unordered_map>
#include <shellapi.h>


#define M_PI (double)3.1415926535
#define actor_player 4



int AimKeyList[] = { VK_LBUTTON , VK_RBUTTON , VK_MBUTTON , VK_MENU , VK_CONTROL , VK_SHIFT , VK_XBUTTON1, VK_XBUTTON2 };

const char* optKey[] = { "Left Click", "Right Click", "MClick", "Alt", "Ctrl", "Shift", "MB 4", "MB 5" };

int MenuKeyList[] = { VK_INSERT, VK_DELETE, VK_HOME, VK_END, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9 };
const char* optMenuKey[] = { "Insert", "Delete", "Home", "End", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "Numpad 0", "Numpad 1", "Numpad 2", "Numpad 3", "Numpad 4", "Numpad 5", "Numpad 6", "Numpad 7", "Numpad 8", "Numpad 9" };


const char* aimbone[] = { "Head", "Neck", "Chest" };

const char* colors2[] = { "Red", "Black", "Cyan", "Green", "Rainbow" };


const char* type[] = { "Box", "Filled Box", "Corner Box" };


static int keyint = 0;
static int colorint = 0;


static bool recoilcontrol = false;

float skeletonfloat = 1.3f;

struct Config {

	INT aimbotkey = VK_RBUTTON;
	INT menubind = 0;
	bool AVERISTUTU = false;

	bool Riotname = false;

	bool CypherTraps = false;
	bool CypherCamera = false;
	bool CypherCage = false;

	bool KilljoyTurret = false;

	int LockMaw = { 1 };
	int aimmove = { 0 };

	int speed = 5;


	bool KilljoyAlarmBot = false;
	bool Triggerbat = false;
	bool KilljoyUltimate = false;
	bool KilljoyNades = false;

	bool Agenticons = false;
	bool AImLock = false;

	bool Niggerrr = false;
	bool sova_drone = false;

	bool nagagaga = false;

	bool visiblecheck = false;
	bool aimenable = false;
	bool spiketimerlineup = false;
	bool spiketimer = false;
	bool isPlanted = false;
	bool circlehead = false;
	int headespstyle = 0;
	bool FilledFOV = false;
	bool TeamCheck = false; // always off — not exposed in menu
	bool rcs = false;
	bool sticky = false;
	float RecoilStrength = 0.6f;
	bool Streamprooff = false;
	bool Spike = false;
	bool aimbot_constant = false;
	bool triggerbot = false;
	int  triggerbotkey = VK_LBUTTON; // hold key
	bool aimbot_draw_fov = false;
	bool Weapon = false;
	bool rainbowskeleton = false;
	bool Rendercount = false;
	bool GlowESP = false;
	bool RecoilCrosshair = false;
	bool aimbot_draw_target_line = false;
	bool aimbot_ignore_with_useless_weapons = false;

	float aimbot_fov = 20.f;

	float MaxDistanceE = 50.f;
	int flickdelay = 90;
	int RecoilSpeed = 5;
	float aimbot_smooth = 1.f;
	float aimbot_speed = 1.f;
	bool niggersmooth = false;
	float aim_constant_offset = 0.f;
	float fovchangervalue = 100.f;
	float legit_smooth = 5.f;
	float SkeletonThickness = 1.f;
	float CircleHeadThickness = 1.5f;
	float ESPBOXThickness = 1.f;
	float MaxDistance = 1.f;
	bool Antonat = false;
	bool VisibleCheckAveris = false;
	bool VisibleAimbotAveris = false;
	bool Vsync = false;
	bool FOV360 = false;
	bool FPSCheck = false;
	bool player_box = false;
	bool box_filled = false;
	float box_filled_alpha = 0.5f;
	ImColor box_filled_color = ImColor(255, 255, 255);

	bool AccountID = false;

	bool MapradarV2 = false;
	bool MaxDistancemeow = false;
	bool MapradarNormal = false;
	bool player_box_3d = false;
	bool player_skeleton = false;
	bool AbilitiesESP = false;
	bool player_snapline = false;
	bool player_view_angle = false;
	bool player_distance = false;
	bool player_healthbar = false;
	bool player_shieldbar = false;
	bool player_agent = false;
	bool player_weapon = false;
	bool glow = false;
	bool aGEntSwap = false;
	bool fresnel = false;
	bool DiscordActivity = false;
	bool characterr = false;

	bool fovchanger = false;
	bool player_ignore_dormant = true;

	int aimboness = 0;
	int bonees = 0;

	int skeletontypes = 0;

	int esptype = 0; // default: Box

	int Healthnigger = 1; // default: Bar Health
	int HealthPosition = 0; // 0=Left, 1=Right, 2=Top, 3=Bottom
	float HealthBarThickness = 3.1f;
	bool healthbar_gradient = true;
	bool WeaponIcon = false;
	float WeaponIconSize = 20.f;
	ImVec4 HealthGradTop = { 0.16f, 0.86f, 0.27f, 1.0f };
	ImVec4 HealthGradBottom = { 0.86f, 0.16f, 0.10f, 1.0f };
	ImVec4 health_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	int Shieldnigger = 0;
	int AgenticonPosition = 0;
	int SnaplineType = 0;
	ImColor headboxcolor = ImColor(255, 255, 255);
	ImColor FOVFillled = ImColor(255, 255, 255, 50);
	ImColor LINEENEMY = ImColor(255, 255, 255);
	ImColor NIGGAENNEMY = ImColor(255, 0, 0);

	ImColor espcolor = ImColor(255, 255, 255);
	ImColor AbilitiesColor = ImColor(255, 255, 255);
	ImColor RecoilCrosshairColor = ImColor(255, 255, 255);
	ImColor espvisiblecolor = ImColor(255, 0, 0);
	ImColor visibleSkeletonColor = ImColor(255, 0, 0);
	ImColor visibleHeadCircleColor = ImColor(255, 0, 0);
	ImColor visibleSnaplineColor = ImColor(255, 0, 0);


	ImVec4 snapcolor = { 1.0f, 1.0f, 1.0f, 1.0f };
	ImVec4 skeleton = { 1.0f, 1.0f, 1.0f, 1.0f };
	ImVec4 menu_accent = { 0.52f, 0.27f, 0.85f, 1.0f }; // menu accent rengi
};

Config config;

class Vector2 {
public:
	double x, y;

	Vector2(double x = 0, double y = 0) : x(x), y(y) {}

	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

};

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	double x;
	double y;
	double z;

	inline double Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline double Distance(Vector3 v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(double number) const {
		return Vector3(x * number, y * number, z * number);
	}

	Vector3 operator/(double number) const {
		return Vector3(x / number, y / number, z / number);
	}
};

inline std::atomic<bool> aimbot_running(false);
inline Vector2 target_position2d = { 0, 0 };
inline std::mutex target_mutex;

class Aimbot
{
public:
	void CursorTo(float x, float y);
	void AimbotThread();
	void StartAimbotThread();
	void StopAimbotThread();
};

inline Aimbot aim;


// ─── Base64 encode/decode (config dosyaları için) ───────────────────────────
namespace b64 {
    static const char* tbl = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    inline std::string encode(const std::string& in) {
        std::string out; out.reserve(((in.size()+2)/3)*4);
        int val=0,valb=-6;
        for(unsigned char c:in){
            val=(val<<8)+c; valb+=8;
            while(valb>=0){ out.push_back(tbl[(val>>valb)&0x3F]); valb-=6; }
        }
        if(valb>-6) out.push_back(tbl[((val<<8)>>(valb+8))&0x3F]);
        while(out.size()%4) out.push_back('=');
        return out;
    }
    inline std::string decode(const std::string& in) {
        std::string out;
        std::vector<int> T(256,-1);
        for(int i=0;i<64;i++) T[(unsigned char)tbl[i]]=i;
        int val=0,valb=-8;
        for(unsigned char c:in){
            if(T[c]==-1) break;
            val=(val<<6)+T[c]; valb+=6;
            if(valb>=0){ out.push_back(char((val>>valb)&0xFF)); valb-=8; }
        }
        return out;
    }
}

// ─── Config dosya sistemi — c:\spec\configs ─────────────────────────────────
static const std::string CONFIG_DIR = "C:\\spec\\configs\\";

inline void EnsureConfigDir() {
    CreateDirectoryA("C:\\spec", NULL);
    CreateDirectoryA("C:\\spec\\configs", NULL);
}

inline std::string ConfigFilePath(const std::string& name) {
    return CONFIG_DIR + name + ".ctx";
}

// Tüm .ctx dosyalarını listele
inline std::vector<std::string> ListConfigs() {
    std::vector<std::string> result;
    EnsureConfigDir();
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA((CONFIG_DIR + "*.ctx").c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return result;
    do {
        std::string fname(fd.cFileName);
        if (fname.size()>4) fname = fname.substr(0, fname.size()-4);
        result.push_back(fname);
    } while (FindNextFileA(h, &fd));
    FindClose(h);
    return result;
}
// Config'i JSON string olarak serialize et
inline std::string ConfigToJson() {
    std::ostringstream j;
    auto wb=[&](const char*k,bool v)  { j<<'"'<<k<<"\":" <<(v?"true":"false")<<','; };
    auto wi=[&](const char*k,int v)   { j<<'"'<<k<<"\":" <<v<<','; };
    auto wf=[&](const char*k,float v) { j<<'"'<<k<<"\":" <<v<<'f'<<','; };
    auto wc=[&](const char*k,const ImColor&c){ j<<'"'<<k<<"\":["<<(int)(c.Value.x*255)<<','<<(int)(c.Value.y*255)<<','<<(int)(c.Value.z*255)<<','<<(int)(c.Value.w*255)<<"],"; };
    auto wv=[&](const char*k,const ImVec4&v){ j<<'"'<<k<<"\":["<<v.x<<','<<v.y<<','<<v.z<<','<<v.w<<"],"; };
    j<<'{';
    wb("aimenable",config.aimenable); wi("aimbotkey",config.aimbotkey);
    wb("rcs",config.rcs); wf("RecoilStrength",config.RecoilStrength);
    wb("triggerbot",config.triggerbot); wi("flickdelay",config.flickdelay);
    wb("aimbot_draw_fov",config.aimbot_draw_fov); wb("FilledFOV",config.FilledFOV);
    wb("VisibleAimbotAveris",config.VisibleAimbotAveris);
    wf("aimbot_fov",config.aimbot_fov); wi("aimboness",config.aimboness);
    wb("player_box",config.player_box); wi("esptype",config.esptype);
    wf("ESPBOXThickness",config.ESPBOXThickness);
    wb("player_skeleton",config.player_skeleton); wf("SkeletonThickness",config.SkeletonThickness);
    wb("circlehead",config.circlehead); wf("CircleHeadThickness",config.CircleHeadThickness);
    wb("player_healthbar",config.player_healthbar); wi("Healthnigger",config.Healthnigger);
    wi("HealthPosition",config.HealthPosition); wf("HealthBarThickness",config.HealthBarThickness); wb("healthbar_gradient",config.healthbar_gradient);
    wb("WeaponIcon",config.WeaponIcon); wf("WeaponIconSize",config.WeaponIconSize);
    wv("HealthGradTop",config.HealthGradTop); wv("HealthGradBottom",config.HealthGradBottom);
    wv("health_color",config.health_color);
    wb("player_snapline",config.player_snapline); wi("SnaplineType",config.SnaplineType);
    wb("player_distance",config.player_distance);
    wb("Agenticons",config.Agenticons); wb("characterr",config.characterr);
    wb("Weapon",config.Weapon); wb("player_view_angle",config.player_view_angle);
    wb("VisibleCheckAveris",config.VisibleCheckAveris); wb("FPSCheck",config.FPSCheck);
    wb("AbilitiesESP",config.AbilitiesESP); wb("player_ignore_dormant",config.player_ignore_dormant);
    wb("MaxDistancemeow",config.MaxDistancemeow); wf("MaxDistanceE",config.MaxDistanceE);
    wb("spiketimer",config.spiketimer); wb("spiketimerlineup",config.spiketimerlineup);
    wb("MapradarV2",config.MapradarV2); wb("rainbowskeleton",config.rainbowskeleton);
    wb("box_filled",config.box_filled); wf("box_filled_alpha",config.box_filled_alpha);
    wc("box_filled_color",config.box_filled_color);
    wb("Streamprooff",config.Streamprooff);
    wc("espcolor",config.espcolor); wc("espvisiblecolor",config.espvisiblecolor);
    wc("headboxcolor",config.headboxcolor); wc("AbilitiesColor",config.AbilitiesColor);
    wv("snapcolor",config.snapcolor); wv("skeleton",config.skeleton);
    wv("menu_accent",config.menu_accent);
    wc("visibleSkeletonColor",config.visibleSkeletonColor);
    wc("visibleHeadCircleColor",config.visibleHeadCircleColor);
    wc("visibleSnaplineColor",config.visibleSnaplineColor);
    wc("FOVFillled",config.FOVFillled);
    // son virgülü kaldır
    std::string s = j.str();
    if(s.back()==',') s.back()='}'; else s+='}';
    return s;
}

// JSON parse helper — sadece basit key:value, array
inline void JsonToConfig(const std::string& json) {
    // Key-value parse: "key":value veya "key":[r,g,b,a]
    auto findVal = [&](const std::string& key) -> std::string {
        std::string pat = "\"" + key + "\":";
        auto p = json.find(pat);
        if(p==std::string::npos) return "";
        p+=pat.size();
        // array
        if(json[p]=='['){
            auto e=json.find(']',p); if(e==std::string::npos) return "";
            return json.substr(p+1,e-p-1);
        }
        // bool/number
        auto e=json.find_first_of(",}",p);
        return json.substr(p, e==std::string::npos?std::string::npos:e-p);
    };
    auto rb=[&](const char*k,bool&v){ auto s=findVal(k); if(!s.empty()) v=(s=="true"); };
    auto ri=[&](const char*k,int&v){ auto s=findVal(k); if(!s.empty()) try{v=std::stoi(s);}catch(...){} };
    auto rf=[&](const char*k,float&v){ auto s=findVal(k); if(!s.empty()) try{
        std::string t=s; if(!t.empty()&&t.back()=='f') t.pop_back(); v=std::stof(t);}catch(...){} };
    auto rc=[&](const char*k,ImColor&c){ auto s=findVal(k); if(s.empty()) return;
        int r=255,g=255,b=255,a=255; sscanf_s(s.c_str(),"%d,%d,%d,%d",&r,&g,&b,&a); c=ImColor(r,g,b,a); };
    auto rv=[&](const char*k,ImVec4&v){ auto s=findVal(k); if(s.empty()) return;
        sscanf_s(s.c_str(),"%f,%f,%f,%f",&v.x,&v.y,&v.z,&v.w); };

    rb("aimenable",config.aimenable); ri("aimbotkey",config.aimbotkey);
    rb("rcs",config.rcs); rf("RecoilStrength",config.RecoilStrength);
    rb("triggerbot",config.triggerbot); ri("flickdelay",config.flickdelay);
    rb("aimbot_draw_fov",config.aimbot_draw_fov); rb("FilledFOV",config.FilledFOV);
    rb("VisibleAimbotAveris",config.VisibleAimbotAveris);
    rf("aimbot_fov",config.aimbot_fov); ri("aimboness",config.aimboness);
    rb("player_box",config.player_box); ri("esptype",config.esptype);
    rf("ESPBOXThickness",config.ESPBOXThickness);
    rb("player_skeleton",config.player_skeleton); rf("SkeletonThickness",config.SkeletonThickness);
    rb("circlehead",config.circlehead); rf("CircleHeadThickness",config.CircleHeadThickness);
    rb("player_healthbar",config.player_healthbar); ri("Healthnigger",config.Healthnigger);
    ri("HealthPosition",config.HealthPosition); rf("HealthBarThickness",config.HealthBarThickness); rb("healthbar_gradient",config.healthbar_gradient);
    rb("WeaponIcon",config.WeaponIcon); rf("WeaponIconSize",config.WeaponIconSize);
    rv("HealthGradTop",config.HealthGradTop); rv("HealthGradBottom",config.HealthGradBottom);
    rv("health_color",config.health_color);
    rb("player_snapline",config.player_snapline); ri("SnaplineType",config.SnaplineType);
    rb("player_distance",config.player_distance);
    rb("Agenticons",config.Agenticons); rb("characterr",config.characterr);
    rb("Weapon",config.Weapon); rb("player_view_angle",config.player_view_angle);
    rb("VisibleCheckAveris",config.VisibleCheckAveris); rb("FPSCheck",config.FPSCheck);
    rb("AbilitiesESP",config.AbilitiesESP); rb("player_ignore_dormant",config.player_ignore_dormant);
    rb("MaxDistancemeow",config.MaxDistancemeow); rf("MaxDistanceE",config.MaxDistanceE);
    rb("spiketimer",config.spiketimer); rb("spiketimerlineup",config.spiketimerlineup);
    rb("MapradarV2",config.MapradarV2); rb("rainbowskeleton",config.rainbowskeleton);
    rb("box_filled",config.box_filled); rf("box_filled_alpha",config.box_filled_alpha);
    rc("box_filled_color",config.box_filled_color);
    rb("Streamprooff",config.Streamprooff);
    rc("espcolor",config.espcolor); rc("espvisiblecolor",config.espvisiblecolor);
    rc("headboxcolor",config.headboxcolor); rc("AbilitiesColor",config.AbilitiesColor);
    rv("snapcolor",config.snapcolor); rv("skeleton",config.skeleton);
    rv("menu_accent",config.menu_accent);
    rc("visibleSkeletonColor",config.visibleSkeletonColor);
    rc("visibleHeadCircleColor",config.visibleHeadCircleColor);
    rc("visibleSnaplineColor",config.visibleSnaplineColor);
    rc("FOVFillled",config.FOVFillled);
}

inline void SaveNamedConfig(const std::string& name) {
    EnsureConfigDir();
    std::string json = ConfigToJson();
    std::string encoded = b64::encode(json);
    std::ofstream f(ConfigFilePath(name));
    if(f) { f << encoded; f.close(); }
}

inline void LoadNamedConfig(const std::string& name) {
    std::ifstream f(ConfigFilePath(name));
    if(!f) return;
    std::string encoded((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();
    std::string json = b64::decode(encoded);
    if(!json.empty()) JsonToConfig(json);
}

std::string GetConfigPath() {
	char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	std::string s(path);
	return s.substr(0, s.find_last_of('\\') + 1) + "config.cfg";
}

void SaveAllConfig() {
	std::ofstream f(GetConfigPath());
	if (!f) return;

	auto wb = [&](const char* k, bool v) { f << k << "=" << v << "\n"; };
	auto wi = [&](const char* k, int v) { f << k << "=" << v << "\n"; };
	auto wf = [&](const char* k, float v) { f << k << "=" << v << "\n"; };
	auto wc = [&](const char* k, const ImColor& c) {
		f << k << "=" << (int)(c.Value.x*255) << "," << (int)(c.Value.y*255) << "," << (int)(c.Value.z*255) << "," << (int)(c.Value.w*255) << "\n";
	};
	auto wv = [&](const char* k, const ImVec4& v) {
		f << k << "=" << v.x << "," << v.y << "," << v.z << "," << v.w << "\n";
	};

	wi("aimbotkey", config.aimbotkey);
	wi("menubind", config.menubind);
	wb("AVERISTUTU", config.AVERISTUTU);
	wb("Riotname", config.Riotname);
	wb("CypherTraps", config.CypherTraps);
	wb("CypherCamera", config.CypherCamera);
	wb("CypherCage", config.CypherCage);
	wb("KilljoyTurret", config.KilljoyTurret);
	wi("LockMaw", config.LockMaw);
	wi("aimmove", config.aimmove);
	wi("speed", config.speed);
	wb("KilljoyAlarmBot", config.KilljoyAlarmBot);
	wb("Triggerbat", config.Triggerbat);
	wb("KilljoyUltimate", config.KilljoyUltimate);
	wb("KilljoyNades", config.KilljoyNades);
	wb("Agenticons", config.Agenticons);
	wb("AImLock", config.AImLock);
	wb("Niggerrr", config.Niggerrr);
	wb("sova_drone", config.sova_drone);
	wb("nagagaga", config.nagagaga);
	wb("visiblecheck", config.visiblecheck);
	wb("aimenable", config.aimenable);
	wb("spiketimerlineup", config.spiketimerlineup);
	wb("spiketimer", config.spiketimer);
	wb("circlehead", config.circlehead);
	wi("headespstyle", config.headespstyle);
	wb("FilledFOV", config.FilledFOV);
	//wb("TeamCheck", config.TeamCheck); // not saved — always false
	wb("rcs", config.rcs);
	wb("sticky", config.sticky);
	wf("RecoilStrength", config.RecoilStrength);
	wb("Streamprooff", config.Streamprooff);
	wb("Spike", config.Spike);
	wb("aimbot_constant", config.aimbot_constant);
	wb("triggerbot", config.triggerbot);
	wb("aimbot_draw_fov", config.aimbot_draw_fov);
	wb("Weapon", config.Weapon);
	wb("rainbowskeleton", config.rainbowskeleton);
	wb("Rendercount", config.Rendercount);
	wb("GlowESP", config.GlowESP);
	wb("RecoilCrosshair", config.RecoilCrosshair);
	wb("aimbot_draw_target_line", config.aimbot_draw_target_line);
	wb("aimbot_ignore_with_useless_weapons", config.aimbot_ignore_with_useless_weapons);
	wf("aimbot_fov", config.aimbot_fov);
	wf("MaxDistanceE", config.MaxDistanceE);
	wi("flickdelay", config.flickdelay);
	wi("RecoilSpeed", config.RecoilSpeed);
	wf("aimbot_smooth", config.aimbot_smooth);
	wf("aimbot_speed", config.aimbot_speed);
	wb("niggersmooth", config.niggersmooth);
	wf("aim_constant_offset", config.aim_constant_offset);
	wf("fovchangervalue", config.fovchangervalue);
	wf("legit_smooth", config.legit_smooth);
	wf("SkeletonThickness", config.SkeletonThickness);
	wf("CircleHeadThickness", config.CircleHeadThickness);
	wf("ESPBOXThickness", config.ESPBOXThickness);
	wf("MaxDistance", config.MaxDistance);
	wb("Antonat", config.Antonat);
	wb("VisibleCheckAveris", config.VisibleCheckAveris);
	wb("VisibleAimbotAveris", config.VisibleAimbotAveris);
	wb("Vsync", config.Vsync);
	wb("FOV360", config.FOV360);
	wb("FPSCheck", config.FPSCheck);
	wb("player_box", config.player_box);
	wb("box_filled", config.box_filled);
	wf("box_filled_alpha", config.box_filled_alpha);
	wc("box_filled_color", config.box_filled_color);
	wb("AccountID", config.AccountID);
	wb("MapradarV2", config.MapradarV2);
	wb("MaxDistancemeow", config.MaxDistancemeow);
	wb("MapradarNormal", config.MapradarNormal);
	wb("player_box_3d", config.player_box_3d);
	wb("player_skeleton", config.player_skeleton);
	wb("AbilitiesESP", config.AbilitiesESP);
	wb("player_snapline", config.player_snapline);
	wb("player_view_angle", config.player_view_angle);
	wb("player_distance", config.player_distance);
	wb("player_healthbar", config.player_healthbar);
	wb("player_shieldbar", config.player_shieldbar);
	wb("player_agent", config.player_agent);
	wb("player_weapon", config.player_weapon);
	wb("glow", config.glow);
	wb("aGEntSwap", config.aGEntSwap);
	wb("fresnel", config.fresnel);
	wb("DiscordActivity", config.DiscordActivity);
	wb("characterr", config.characterr);
	wb("fovchanger", config.fovchanger);
	wb("player_ignore_dormant", config.player_ignore_dormant);
	wi("aimboness", config.aimboness);
	wi("bonees", config.bonees);
	wi("skeletontypes", config.skeletontypes);
	wi("esptype", config.esptype);
	wi("Healthnigger", config.Healthnigger);
	wi("HealthPosition", config.HealthPosition);
	wf("HealthBarThickness", config.HealthBarThickness);
	wb("healthbar_gradient", config.healthbar_gradient);
	wb("WeaponIcon", config.WeaponIcon);
	wf("WeaponIconSize", config.WeaponIconSize);
	wv("HealthGradTop", config.HealthGradTop);
	wv("HealthGradBottom", config.HealthGradBottom);
	wv("health_color", config.health_color);
	wi("Shieldnigger", config.Shieldnigger);
	wi("AgenticonPosition", config.AgenticonPosition);
	wi("SnaplineType", config.SnaplineType);
	wc("headboxcolor", config.headboxcolor);
	wc("FOVFillled", config.FOVFillled);
	wc("LINEENEMY", config.LINEENEMY);
	wc("NIGGAENNEMY", config.NIGGAENNEMY);
	wc("espcolor", config.espcolor);
	wc("AbilitiesColor", config.AbilitiesColor);
	wc("RecoilCrosshairColor", config.RecoilCrosshairColor);
	wc("espvisiblecolor", config.espvisiblecolor);
	wc("visibleSkeletonColor", config.visibleSkeletonColor);
	wc("visibleHeadCircleColor", config.visibleHeadCircleColor);
	wc("visibleSnaplineColor", config.visibleSnaplineColor);
	wv("snapcolor", config.snapcolor);
	wv("skeleton", config.skeleton);

	f.close();
}

void LoadAllConfig() {
	std::ifstream f(GetConfigPath());
	if (!f) return;

	std::unordered_map<std::string, std::string> kv;
	std::string line;
	while (std::getline(f, line)) {
		auto eq = line.find('=');
		if (eq == std::string::npos) continue;
		kv[line.substr(0, eq)] = line.substr(eq + 1);
	}
	f.close();

	auto rb = [&](const char* k, bool& v) { auto it = kv.find(k); if (it != kv.end()) v = (it->second != "0"); };
	auto ri = [&](const char* k, int& v) { auto it = kv.find(k); if (it != kv.end()) try { v = std::stoi(it->second); } catch(...){} };
	auto riI = [&](const char* k, INT& v) { auto it = kv.find(k); if (it != kv.end()) try { v = std::stoi(it->second); } catch(...){} };
	auto rf = [&](const char* k, float& v) { auto it = kv.find(k); if (it != kv.end()) try { v = std::stof(it->second); } catch(...){} };
	auto rc = [&](const char* k, ImColor& c) {
		auto it = kv.find(k); if (it == kv.end()) return;
		int r=255,g=255,b=255,a=255;
		sscanf_s(it->second.c_str(), "%d,%d,%d,%d", &r, &g, &b, &a);
		c = ImColor(r, g, b, a);
	};
	auto rv = [&](const char* k, ImVec4& v) {
		auto it = kv.find(k); if (it == kv.end()) return;
		sscanf_s(it->second.c_str(), "%f,%f,%f,%f", &v.x, &v.y, &v.z, &v.w);
	};

	riI("aimbotkey", config.aimbotkey);
	riI("menubind", config.menubind);
	rb("AVERISTUTU", config.AVERISTUTU);
	rb("Riotname", config.Riotname);
	rb("CypherTraps", config.CypherTraps);
	rb("CypherCamera", config.CypherCamera);
	rb("CypherCage", config.CypherCage);
	rb("KilljoyTurret", config.KilljoyTurret);
	ri("LockMaw", config.LockMaw);
	ri("aimmove", config.aimmove);
	ri("speed", config.speed);
	rb("KilljoyAlarmBot", config.KilljoyAlarmBot);
	rb("Triggerbat", config.Triggerbat);
	rb("KilljoyUltimate", config.KilljoyUltimate);
	rb("KilljoyNades", config.KilljoyNades);
	rb("Agenticons", config.Agenticons);
	rb("AImLock", config.AImLock);
	rb("Niggerrr", config.Niggerrr);
	rb("sova_drone", config.sova_drone);
	rb("nagagaga", config.nagagaga);
	rb("visiblecheck", config.visiblecheck);
	rb("aimenable", config.aimenable);
	rb("spiketimerlineup", config.spiketimerlineup);
	rb("spiketimer", config.spiketimer);
	rb("circlehead", config.circlehead);
	ri("headespstyle", config.headespstyle);
	rb("FilledFOV", config.FilledFOV);
	//rb("TeamCheck", config.TeamCheck); // not loaded — always false
	rb("rcs", config.rcs);
	rb("sticky", config.sticky);
	rf("RecoilStrength", config.RecoilStrength);
	rb("Streamprooff", config.Streamprooff);
	rb("Spike", config.Spike);
	rb("aimbot_constant", config.aimbot_constant);
	rb("triggerbot", config.triggerbot);
	rb("aimbot_draw_fov", config.aimbot_draw_fov);
	rb("Weapon", config.Weapon);
	rb("rainbowskeleton", config.rainbowskeleton);
	rb("Rendercount", config.Rendercount);
	rb("GlowESP", config.GlowESP);
	rb("RecoilCrosshair", config.RecoilCrosshair);
	rb("aimbot_draw_target_line", config.aimbot_draw_target_line);
	rb("aimbot_ignore_with_useless_weapons", config.aimbot_ignore_with_useless_weapons);
	rf("aimbot_fov", config.aimbot_fov);
	rf("MaxDistanceE", config.MaxDistanceE);
	ri("flickdelay", config.flickdelay);
	ri("RecoilSpeed", config.RecoilSpeed);
	rf("aimbot_smooth", config.aimbot_smooth);
	rf("aimbot_speed", config.aimbot_speed);
	rb("niggersmooth", config.niggersmooth);
	rf("aim_constant_offset", config.aim_constant_offset);
	rf("fovchangervalue", config.fovchangervalue);
	rf("legit_smooth", config.legit_smooth);
	rf("SkeletonThickness", config.SkeletonThickness);
	rf("CircleHeadThickness", config.CircleHeadThickness);
	rf("ESPBOXThickness", config.ESPBOXThickness);
	rf("MaxDistance", config.MaxDistance);
	rb("Antonat", config.Antonat);
	rb("VisibleCheckAveris", config.VisibleCheckAveris);
	rb("VisibleAimbotAveris", config.VisibleAimbotAveris);
	rb("Vsync", config.Vsync);
	rb("FOV360", config.FOV360);
	rb("FPSCheck", config.FPSCheck);
	rb("player_box", config.player_box);
	rb("box_filled", config.box_filled);
	rf("box_filled_alpha", config.box_filled_alpha);
	rc("box_filled_color", config.box_filled_color);
	rb("AccountID", config.AccountID);
	rb("MapradarV2", config.MapradarV2);
	rb("MaxDistancemeow", config.MaxDistancemeow);
	rb("MapradarNormal", config.MapradarNormal);
	rb("player_box_3d", config.player_box_3d);
	rb("player_skeleton", config.player_skeleton);
	rb("AbilitiesESP", config.AbilitiesESP);
	rb("player_snapline", config.player_snapline);
	rb("player_view_angle", config.player_view_angle);
	rb("player_distance", config.player_distance);
	rb("player_healthbar", config.player_healthbar);
	rb("player_shieldbar", config.player_shieldbar);
	rb("player_agent", config.player_agent);
	rb("player_weapon", config.player_weapon);
	rb("glow", config.glow);
	rb("aGEntSwap", config.aGEntSwap);
	rb("fresnel", config.fresnel);
	rb("DiscordActivity", config.DiscordActivity);
	rb("characterr", config.characterr);
	rb("fovchanger", config.fovchanger);
	rb("player_ignore_dormant", config.player_ignore_dormant);
	ri("aimboness", config.aimboness);
	ri("bonees", config.bonees);
	ri("skeletontypes", config.skeletontypes);
	ri("esptype", config.esptype);
	ri("Healthnigger", config.Healthnigger);
	ri("HealthPosition", config.HealthPosition);
	rf("HealthBarThickness", config.HealthBarThickness);
	rb("healthbar_gradient", config.healthbar_gradient);
	rb("WeaponIcon", config.WeaponIcon);
	rf("WeaponIconSize", config.WeaponIconSize);
	rv("HealthGradTop", config.HealthGradTop);
	rv("HealthGradBottom", config.HealthGradBottom);
	rv("health_color", config.health_color);
	ri("Shieldnigger", config.Shieldnigger);
	ri("AgenticonPosition", config.AgenticonPosition);
	ri("SnaplineType", config.SnaplineType);
	rc("headboxcolor", config.headboxcolor);
	rc("FOVFillled", config.FOVFillled);
	rc("LINEENEMY", config.LINEENEMY);
	rc("NIGGAENNEMY", config.NIGGAENNEMY);
	rc("espcolor", config.espcolor);
	rc("AbilitiesColor", config.AbilitiesColor);
	rc("RecoilCrosshairColor", config.RecoilCrosshairColor);
	rc("espvisiblecolor", config.espvisiblecolor);
	rc("visibleSkeletonColor", config.visibleSkeletonColor);
	rc("visibleHeadCircleColor", config.visibleHeadCircleColor);
	rc("visibleSnaplineColor", config.visibleSnaplineColor);
	rv("snapcolor", config.snapcolor);
	rv("skeleton", config.skeleton);
}

void SaveConfig() { SaveAllConfig(); }
void SaveESPConfig() { SaveAllConfig(); }
void LoadESPConfig() { LoadAllConfig(); }
void LoadConfig() { LoadAllConfig(); }


INT legitkey;
INT legitbone;


bool IsVisible;




DWORD_PTR LocalPawn;
uintptr_t playerstate;
uintptr_t teamComponent;
int teamID;
uintptr_t UWorld;
uintptr_t game_instance;
uintptr_t persistent_level;
uintptr_t local_player;
uintptr_t actor_array;
INT32 actor_count;

int customX;
int customY;

//typedef PVOID(*name)();

uintptr_t base;


typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

class Color
{
public:
	RGBA moi_blue = { 0, 143, 209,255 };
	RGBA moi_red = { 241,34,34,255 };
	RGBA moi_green = { 0,209,91,255 };

	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen2 = { 26, 128, 0, 255 };
	RGBA darkgreen3 = { 6, 68, 0, 255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };

	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA red4 = { 255, 24, 101, 255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 0,0,0,200 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255, 95, 96, 255 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,180 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA orange2_ = { 255,100,0,180 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 180 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };


	RGBA Plum = { 221,160,221,160 };

};
Color Col;

class FLinearColor {
public:
	FLinearColor() : red(0.f), green(0.f), blue(0.f), alpha(0.f) {}
	FLinearColor(float red, float green, float blue, float alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

public:
	float red;
	float green;
	float blue;
	float alpha;
};

extern ImFont* AVERISONTOP;

inline void DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center)
{
	if (!pFont)
		pFont = AVERISONTOP;
	if (!pFont)
		pFont = ImGui::GetFont();
	if (!pFont)
		return;

	ImGui::PushFont(pFont);
	const char* str = text.c_str();
	ImDrawList* dl = ImGui::GetForegroundDrawList();

	ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, str);
	ImVec2 textPos = center ? ImVec2(pos.x - textSize.x * 0.5f, pos.y) : pos;

	dl->AddText(pFont, size, ImVec2(textPos.x + 1, textPos.y + 1), ImColor(0, 0, 0, 255), str);
	dl->AddText(pFont, size, textPos, ImGui::GetColorU32(color), str);

	ImGui::PopFont();
}


inline auto DrawLineNew(int x1, int y1, int x2, int y2, RGBA* color, int thickness) -> void
{
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

static auto DrawRect(int x, int y, int w, int h, RGBA* color, int thickness) -> void
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
}

inline auto DrawFilledRect2(float x, float y, float w, float h, ImColor color) -> void
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, NULL, NULL);
}

inline auto DrawFilledRect3(int x, int y, int w, int h, RGBA* color) -> void
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
}

inline auto DrawFilledRect4(float x, float y, float w, float h, ImColor color) -> void
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, NULL, NULL);
}

inline auto DrawBorder(float x, float y, float w, float h, float px, RGBA* BorderColor) -> void
{
	DrawRect(x, (y + h - px), w, px, BorderColor, 1 / 2);
	DrawRect(x, y, px, h, BorderColor, 1 / 2);
	DrawRect(x, y, w, px, BorderColor, 1 / 2);
	DrawRect((x + w - px), y, px, h, BorderColor, 1 / 2);
}


void DrawCircleFilled2(int x, int y, int radius, RGBA* color)
{
	ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}
namespace offsets
{
	// ───GLOBALS & CORE OFFSETS (Güncel Döküm) ───────────────────────────
	uintptr_t Stateaddy = 0xD1DD880,
		KeyAddy = Stateaddy + 0x38;

	constexpr uintptr_t MyHUD = 0x458;
	constexpr uintptr_t UWorld = 0xD1D1B40; // *** CIFT DEREF *** (Dikkat edilmeli)
	constexpr uintptr_t GWorldState = 0xCEC8500;
	constexpr uintptr_t RelativeScale3D = 0x60;
	constexpr uintptr_t WorldGuarded = 0x130;

	constexpr uintptr_t Angle = 0x170;
	constexpr uintptr_t actor_destroyed = 0x120;
	constexpr uintptr_t State = 0xD1DD880;
	constexpr uintptr_t Key = State + 0x38;
	constexpr uintptr_t vgk_pool_offset = 0x819C8;
	constexpr uintptr_t vgk_pool_offset1 = 0x27;

	constexpr uintptr_t defuse = 0x05D0;
	constexpr uintptr_t Inventory = 0xC08;
	constexpr uintptr_t CurrentEquip = 0x278;
	constexpr uintptr_t CurrentEquippableVFXState = 0x0E08;
	
	// ─── UWORLD & CHAIN OFFSETS ────────────────────────────────────────
	constexpr uintptr_t persistent_level = 0x38;     // UWorld + 0x38 -> Level
	constexpr uintptr_t game_instance = 0x1D8;      // UWorld + 0x1D8 -> GameInstance
	constexpr uintptr_t localplayer = 0x40;         // GameInstance + 0x40 -> LocalPlayers
	constexpr uintptr_t player_controller = 0x38;   // LocalPlayer + 0x38 -> PlayerController
	constexpr uintptr_t apawn = 0x518;              // PlayerController + 0x518 -> Pawn
	constexpr uintptr_t ViewInfo = 0x17C0;          // CameraManager + 0x17C0 (Dikkat: Location/Rotation artık DOUBLE!)
	constexpr uintptr_t root_component = 0x290;     // Pawn + 0x290
	constexpr uintptr_t root_position = 0x170;
	constexpr uintptr_t damage_handler = 0xC70;     // Pawn + 0xC70
	constexpr uintptr_t camera_position = 0x17C0;
	constexpr uintptr_t camera_manager = 0x528;     // PlayerController + 0x528
	constexpr uintptr_t Spikeplantedmaw = 0x05B8;
	constexpr uintptr_t IsBeingDestroyed = 0x011C;
	constexpr uintptr_t actor_array = 0xA0;         // Level + 0xA0
	constexpr uintptr_t actors_count = 0xA8;        // Level + 0xA8
	constexpr uintptr_t actor_id = 0x11C;
	constexpr uintptr_t actor_count = 0x8;

	constexpr uintptr_t key_pressed_bit = 0x8000;
	constexpr uintptr_t pm_remove = 0x0001;
	constexpr uintptr_t swp_noactivate = 0x0008;
	constexpr uintptr_t Sikreat = 0x0;
	constexpr uintptr_t AMBATKOM = 0x1;

	constexpr uintptr_t pawnpriv = 0x308;

	constexpr uintptr_t Spiketime = 0x05A8;
	constexpr uintptr_t fnameId = 0x18;
	constexpr uintptr_t unique_id = 0x38;
	constexpr uintptr_t Game_state = 0x178;
	constexpr uintptr_t team_component = 0x6a8;     // PlayerState + 0x6A8
	constexpr uintptr_t team_id = 0x00E8;           // TeamComponent + 0xE8 (Güncellendi)
	constexpr uintptr_t health = 0x200;             // DamageHandler + 0x200
	constexpr uintptr_t dormant = 0x225;
	constexpr uintptr_t player_state = 0x488;       // Pawn + 0x488
	constexpr uintptr_t control_rotation = 0x4E8;   // Doğrulanmamış (Dikkatli kullanılmalı)
	constexpr uintptr_t mesh = 0x4F0;               // Pawn + 0x4F0
	constexpr uintptr_t component_to_world = 0x0300;// Mesh + 0x300
	constexpr uintptr_t bone_array = 0x0760;        // Mesh + 0x760
	constexpr uintptr_t bone_count = 0x0768;        // Mesh + 0x768
	constexpr uintptr_t last_submit_time = 0x4A8;
	constexpr uintptr_t last_render_time = 0x4AC;
	constexpr uintptr_t outline_modee = 0x0351;
	constexpr uintptr_t wasally = 0xF58;

	constexpr uintptr_t get_ping = 0x46c;
	constexpr uintptr_t PlatformPlayer = 0x6a0;
	constexpr uintptr_t AccountLevel = 0x794;
	constexpr uintptr_t CompetitiveTier = 0x7A4;

	constexpr uintptr_t attach_children = 0x0100;
	constexpr uintptr_t attach_children_count = attach_children + 0x8;

	constexpr uintptr_t outline_ally_color = 0x52B0752;
	constexpr uintptr_t outline_enemy_color = 0x52B0759;

	constexpr uintptr_t FnamePool = 0xD3B6800;
	constexpr uintptr_t FnameState = 0xD1DD880;
}

