// Anagram Detector is a tool for detecting if the given input can be rearanged to form a new word
// Building on top of the example code from DearImgui so we can not waste time reinventing the wheel
// ImGui - standalone example application for SDL2 + OpenGL
// If you are new to ImGui, see documentation at the top of libs/imgui/imgui.cpp
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include "anagramdetector.h"
#include <algorithm>
#include <stdio.h>
#include <string>
#include <GL/gl3w.h>    // This is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <SDL.h>

void CleanInput(char *);

int main(int, char**)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_Window *window = SDL_CreateWindow("Anagram Detector", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 300, SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    gl3wInit();

    // Setup ImGui binding
    ImGui_ImplSdlGL3_Init(window);

    // Setup style
    ImGui::StyleColorsDark();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //Show Window Variables
    bool show_main_window = true;

    //Varibles
    static char userInput[128] = "listen";
    static char output[1024*16] = "Results";
    static int results = 0;
    // Main loop
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSdlGL3_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }
        ImGui_ImplSdlGL3_NewFrame(window);

        //Display Main Window
        if(show_main_window)
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(600,300), ImGuiCond_Always);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);    //Disable Window Rounding
            ImGui::Begin("MainMenu", &show_main_window, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            //First Section
            {
                ImGui::Text("Input Word:");
                ImGui::SameLine();
                ImGui::InputText("##inputtext", userInput, IM_ARRAYSIZE(userInput), ImGuiInputTextFlags_CharsNoBlank);
                ImGui::SameLine();
                if (ImGui::Button("Check"))
                {
                    CleanInput(userInput);
                    results = AnagramCheck(userInput,output);
                }
            }
            ImGui::InputTextMultiline("##source", output, IM_ARRAYSIZE(output), ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_ReadOnly);
            ImGui::Text("Number of anagrams found: %d",results);
            ImGui::End();
            ImGui::PopStyleVar();
        }
        // Rendering
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplSdlGL3_Shutdown();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//Cleans input by removing non alpha characters
void CleanInput(char *inputFromUser)
{
    std::string userString(inputFromUser);
    for(int i = 0; i<userString.length(); i++)
    {
        if(!isalpha(userString[i]))
        {
            userString.erase(userString.begin() + i);
            //We want to remain in the same spot in case of two non alpha characters next to each other 
            i--;
        }
    }
    std::transform(userString.begin(), userString.end(), userString.begin(), ::tolower);
    userString += '\0';
    //Clean out inputFromUser of characters that might be stuck past \0 when we copy back in
    for(int i = 0; i < 128; i++)
    {
        inputFromUser[i] = '\0';
    }
    strncpy(inputFromUser, userString.c_str(), userString.length());
    return;
}