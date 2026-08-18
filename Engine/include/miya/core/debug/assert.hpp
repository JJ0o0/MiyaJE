#pragma once

#include <miya/core/logging/log.hpp>

#include <source_location>
#include <string_view>
#include <cstdlib>

namespace miya::detail {
    inline void AssertionFailed(
        const char* exp, std::string_view msg, 
        const std::source_location loc = std::source_location::current()
    ) {
        Log::Error(
            "Assertion failed: {}\n"
            "Message: {}\n"
            "File: {}:{}\n"
            "Function: {}",
            exp, msg, 
            loc.file_name(), loc.line(), loc.function_name()
        );

        std::abort();
    }
}

#ifdef MIYA_DEBUG
    #define MIYA_ASSERT(condition, msg)                             \
        do {                                                        \
            if (!(condition)) {                                     \
                ::miya::detail::AssertionFailed(#condition, msg);   \
            }                                                       \
        } while (false)
#else
    #define MIYA_ASSERT(condition, msg) ((void)0)
#endif