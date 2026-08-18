#include <miya/core/engine.hpp>

int main() {
    miya::Engine engine;
    engine.Initialize();
    engine.Run();
    engine.Shutdown();

    return 0;
}