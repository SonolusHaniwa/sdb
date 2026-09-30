// Linux Compile Command: -lGL -lglfw -lX11
// Windows Compile Command: -lopengl32 -lglfw3

#define IMGUI_DEFINE_MATH_OPERATORS
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include"imgui/imgui.cpp"
#include"imgui/imgui_widgets.cpp"
#include"imgui/imgui_tables.cpp"
#include"imgui/imgui_impl_opengl3.cpp"
#include"imgui/imgui_impl_glfw.cpp"
#include"imgui/imgui_draw.cpp"
#include"imgui/imgui_demo.cpp"
#define GL_SILENCE_DEPRECATION
#include<GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

GLFWwindow *window = NULL;
ImGuiIO *io = NULL;
void initImGui(
    int width, int height, string title, 
    bool vsync = true, 
    bool dark = true, 
    float fontBase = 20.0f,
    vector<pair<int, int> > windowProperties = {}
) {
    glfwSetErrorCallback(glfw_error_callback);
    assert(glfwInit());

    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    for (auto v : windowProperties) glfwWindowHint(v.first, v.second);

    // Create window with graphics context
    window = glfwCreateWindow((int)(width * main_scale), (int)(height * main_scale), title.c_str(), nullptr, nullptr);
    assert(window != nullptr);
    glfwMakeContextCurrent(window);
    if (vsync) glfwSwapInterval(1);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    // io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    if (dark) ImGui::StyleColorsDark();
    else ImGui::StyleColorsLight();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)
    io->ConfigDpiScaleFonts = true;          // [Experimental] Automatically overwrite style.FontScaleDpi in Begin() when Monitor DPI changes. This will scale fonts but _NOT_ scale sizes/padding for now.
    io->ConfigDpiScaleViewports = true;      // [Experimental] Scale Dear ImGui and Platform Windows when Monitor DPI changes.
    style.FontSizeBase = fontBase;
    // io->Fonts->AddFontDefault();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    io->IniFilename = NULL;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

ImFont* addFont(string ttfPath, float fontBase = 20.0f) {
    // ImFontConfig icons_config;
    // icons_config.MergeMode = true;
    // io->Fonts->AddFontFromFileTTF(ttfPath.c_str(), fontBase, &icons_config, io->Fonts->GetGlyphRangesDefault());
    return io->Fonts->AddFontFromFileTTF(ttfPath.c_str(), fontBase);
}
ImFont* addFontFromMemory(const unsigned char* ttf, int ttf_length, float fontBase = 20.0f) {
    return io->Fonts->AddFontFromMemoryCompressedTTF(const_cast<unsigned char*>(ttf), ttf_length, fontBase);
}

void addIcon(string ttfpath, ImWchar min, ImWchar max, float fontBase = 20.0f) {
    static const ImWchar icons_ranges[] = { min, max, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = fontBase;
    io->Fonts->AddFontFromFileTTF(ttfpath.c_str(), fontBase, &icons_config, icons_ranges);
    io->Fonts->Build();
}
void addIconFromMemory(const unsigned char* ttf, int ttf_length, ImWchar min, ImWchar max, float fontBase = 20.0f) {
    static const ImWchar icons_ranges[] = { min, max, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = fontBase;
    io->Fonts->AddFontFromMemoryCompressedTTF(const_cast<unsigned char*>(ttf), ttf_length, fontBase, &icons_config, icons_ranges);
    io->Fonts->Build();
}

typedef void(*ImGuiFunc)();
ImVec4 bgColor = ImVec4(0.0f, 0.0f, 0.125f, 1);
ImGuiFunc render;

void renderImGui() {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    render();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(bgColor.x, bgColor.y, bgColor.z, bgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
}

void imGuiSizeSolver(GLFWwindow* window, int width, int height) { renderImGui(); }
void runImGui(ImGuiFunc render) {
	::render = render;
	
	glfwSetWindowSizeCallback(window, imGuiSizeSolver);
	
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        renderImGui();
    }
}

void cleanImGui() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

#define APIENTRY WINAPI