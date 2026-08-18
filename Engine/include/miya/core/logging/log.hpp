#pragma once

#include <string_view>
#include <utility>
#include <format>

namespace miya {
    class Log {
        public:
            static void Info(std::string_view msg);
            static void Warning(std::string_view msg);
            static void Error(std::string_view msg);

            template<typename... Args>
            static inline void Info(std::format_string<Args...> fmt, Args&&... args) {
                Info(std::format(fmt, std::forward<Args>(args)...));
            }

            template<typename... Args>
            static inline void Warning(std::format_string<Args...> fmt, Args&&... args) {
                Warning(std::format(fmt, std::forward<Args>(args)...));
            }

            template<typename... Args>
            static inline void Error(std::format_string<Args...> fmt, Args&&... args) {
                Error(std::format(fmt, std::forward<Args>(args)...));
            }
    };
}