#pragma once

#include <miya/graphics/color.hpp>

namespace miya::OpenGL {
    class GLContext {
        public:
            bool Initialize();
            void Destroy();

            void Clear(const Color& color, bool clearDepth = true);
        private:
            bool m_initialized = false;
    };
}