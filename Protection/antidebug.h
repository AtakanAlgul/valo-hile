#pragma once
#include <Windows.h>

inline void AntiDebug(void) {}
inline int DebugString() { return 0; }
inline int HideThread() { return 0; }
inline int RemotePresent() { return 0; }
inline int ContextThread() { return 0; }
inline bool hide_thread(HANDLE thread) { return true; }
inline int thread_context() { return 0; }
inline int remote_is_present() { return 0; }
inline int is_debugger_presente() { return 0; }
inline bool debug_perms_check() { return false; }