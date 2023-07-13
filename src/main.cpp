#include "game/game_main.hpp"
#include <exception>
#include <log.h>

int main() {
    // Set loglevel for the debugger
    logSetLevel(LOG_LEVEL_DEBUG);

    GameMain app;
    logInfo("Starting vulkan project");

    try {
        app.run();
    } catch (const std::exception& e) {
        logError(e.what());
        return EXIT_FAILURE;
    }
    logInfo("Execution success");
    return EXIT_SUCCESS;
}