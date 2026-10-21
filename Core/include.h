#include <thread>
#include <cstdlib>
#include <tchar.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <fstream>
#include <vector>
#include <dwmapi.h>
#include <psapi.h>
#include <math.h>
#include "Auth/skStr.h"
#include <d3d11.h>
#include <dxgi.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_dx11.h"
#include "ImGui/backends/imgui_impl_win32.h"
#include "driver.h"
#include "main.h"
#include "shared.hpp"
#include "cheat.h"
#include "Protection/vmprotect.h"
#include "Protection/antidebug.h"  


#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")


