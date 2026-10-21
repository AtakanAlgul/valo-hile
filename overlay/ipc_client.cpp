// ipc_client.cpp — Tek DLL mimarisi: Soket ve ag katmani kaldirildi, dogrudan bellek baglantisi aktif.
#include "ipc_client.hpp"

namespace ipc_client {

    bool init(SharedESPData* esp_data) {
        if (esp_data) {
            esp_data->overlay_connected = true;
        }
        return true;
    }

    void send_ping() {
        // Tek DLL: Ag soketi ve ping gerekmez
    }

    void send_settings(const SharedSettings& s) {
        if (g_esp_data) {
            g_esp_data->settings = s;
        }
    }

    bool is_connected() {
        return true;
    }

    void shutdown_client() {
        // No-op
    }

} // namespace ipc_client
