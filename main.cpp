#include "App/VulkanApplication.h"

int main() {
    VulkanApplication app;

    app.Initialize();
    app.Run();
    app.Cleanup();

    return EXIT_SUCCESS;
}