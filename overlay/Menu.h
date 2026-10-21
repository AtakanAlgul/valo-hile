#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

namespace Settings {
	inline bool BoxEsp = true;
	inline bool CornerBox = true;
	inline bool Box3D = false;
	inline bool Skeleton = true;
	inline bool HealthBar = true;
	inline bool HeadBox = false;
	inline bool Snaplines = false;
	inline bool VisibilityCheck = false;
	inline bool TeamCheck = true;
	inline bool IgnoreDormant = true;
	inline bool Distance = true;
	inline bool BodyDot = false;
	inline bool SpikeTimer = false;
	inline bool MemoryRadar = false;
	inline bool ViewAngle = false;
	inline bool AgentIcons = false;
	inline bool RainbowSkeleton = false;
	inline float EspThickness = 1.0f;
	inline bool LegitEsp = false;
	inline bool Watermark = false;

	// Aimbot
	inline bool Aimbot = true;
	inline bool AimVisCheck = true;
	inline bool RecoilControl = true;
	inline bool DrawFov = true;
	inline bool FilledFov = false;
	inline float AimSmooth = 10.0f;
	inline float AimFov = 40.0f;
	inline int AimBone = 0;
	inline int AimKey = 0x01;
	inline bool Triggerbot = false;
	inline int TriggerDelay = 90;
	inline float RcsStrength = 0.6f;

	// Legit
	inline int LegitKey = 0x06;
	inline int LegitMode = 0;
	inline int LegitTime = 10;

	// Colors
	inline float BoxColor[4] = { 1.f, 0.f, 0.f, 1.f };
	inline float SnaplineColor[4] = { 1.f, 1.f, 1.f, 1.f };
	inline float HeadBoxColor[4] = { 1.f, 0.f, 0.f, 1.f };
	inline float BodyDotColor[4] = { 1.f, 0.f, 0.f, 1.f };
	inline float DistanceColor[4] = { 1.f, 1.f, 1.f, 1.f };
	inline float HPHighColor[4] = { 0.f, 1.f, 0.f, 1.f };
	inline float HPLowColor[4] = { 1.f, 0.f, 0.f, 1.f };
	inline float TeamColor[4] = { 0.f, 1.f, 0.f, 1.f };
}

namespace Menu {
	inline bool Open = true;
	void Init(ID3D11Device* device, ID3D11DeviceContext* ctx, IDXGISwapChain* swapChain, HWND hwnd);
	void Draw();
	void SaveConfig();
	void LoadConfig();
	void ResetConfig();
	void SyncToCfg();
	void SyncFromCfg();
}
