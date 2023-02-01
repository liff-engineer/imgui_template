#include <windows.h>


int main(int, char**);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    int exit_result = main(0, NULL);
    return exit_result;
}

#include "hello_imgui/hello_imgui.h"

int main(int, char**) {
    auto guiFunction = []() {
        ImGui::Text("Hello, ");
        HelloImGui::ImageFromAsset("world.jpg");
        if (ImGui::Button("Bye!")) {
            HelloImGui::GetRunnerParams()->appShallExit = true;
        }
    };

    HelloImGui::Run(guiFunction, "Hello, globe", true);
}
