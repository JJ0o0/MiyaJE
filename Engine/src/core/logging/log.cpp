#include <miya/core/logging/log.hpp>
#include <iostream>

namespace miya {
    void Log::Info(std::string_view msg) {
        std::cout << "[MiyaJE] INFO: " << msg << "\n";
    }

    void Log::Warning(std::string_view msg) {
        std::cerr << "[MiyaJE] WARNING: " << msg << "\n";
    }

    void Log::Error(std::string_view msg) {
        std::cerr << "[MiyaJE] ERROR: " << msg << "\n";
    }
}