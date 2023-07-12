#include <project_setup.hpp>
#include <exception>
#include "Project.hpp"

int main() {
    // Set loglevel for the debugger
    logSetLevel(LOG_LEVEL_DEBUG);

    Project app;
    logInfo("Vulkan project created");

    try {
        app.run();
    } catch (const std::exception& e) {
        logError(e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}