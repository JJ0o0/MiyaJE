#include <miya/core/engine.hpp>

int main() {
    miya::Engine engine;
    if (!engine.Initialize()) return 1;
    engine.Run();
    engine.Shutdown();

    return 0;
}