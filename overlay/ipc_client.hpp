#pragma once
// ipc_client.hpp — Forward declarations only
// Implementasyon: ipc_client.cpp (winsock2 izole orada tutulur)
#include "../shared.hpp"

namespace ipc_client {
    bool init(SharedESPData* esp_data);
    void send_ping();
    void send_settings(const SharedSettings& s);
    bool is_connected();
    void shutdown_client();
}
