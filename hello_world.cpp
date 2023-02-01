#include <windows.h>


int main(int, char**);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    int exit_result = main(0, NULL);
    return exit_result;
}

#include "hello_imgui/hello_imgui.h"
int main(int, char *[])
{
    HelloImGui::Run(
        []
        { ImGui::Text("Hello, world!"); }, // Gui code
        "Hello!",                          // Window title
        true                               // Window size auto
    );
    return 0;
}
