#include <filesystem>
#include <iostream>


// Import daily modules
import Day1;
import Day2;
import Day3;
import Day4;
import Day5;
import Day6;
import Day7;
import Day8;
import Day9;
import Day10;
import Day11;
import Day12;
import Day13;
import Day14;
import Day15;
import Day16;
import Day17;
import Day18;
import Day19;
import Day20;

// Include ImGui headers
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

void renderGUI();


int main(int argc, char *argv[]) {
  std::filesystem::path workingDir;
  if (argc < 2) {
    workingDir = std::filesystem::current_path() / ".." / "..";
  } else {
    workingDir = argv[1];
  }

   // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Setup OpenGL version (e.g., 3.3)
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "AdventOfCode2024", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize Glad
    /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize Glad\n";
        return -1;
    }*/

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render your GUI
        renderGUI();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup ImGui and GLFW
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

  //choose a day to solve
  while(true){
    std::cout << "Choose a day to solve (1-14), 0 to quit : ";
    int day;
    std::cin >> day;
    if(day == 1){
      Day1::solve(workingDir / "assets" / "1" / "input.txt");
      break;
    }else if(day == 2){
      Day2::solve(workingDir / "assets" / "2" / "input.txt");
      break;
    }else if (day == 0){
      break;
    }else if (day == 3){
      Day3::solve(workingDir / "assets" / "3" / "input.txt");
      break;
    }else if (day == 4){
      Day4::solve(workingDir / "assets" / "4" / "input.txt");
      break;
    }
    else if (day == 5){
      Day5::solve(workingDir / "assets" / "5" / "input.txt");
      break;    
    }else if (day == 6){
      Day6::solve(workingDir / "assets" / "6" / "input.txt");
      break;
    }else if (day == 7){
      Day7::solve(workingDir / "assets" / "7" / "input.txt");
      break;
    }else if (day == 8){
      Day8::solve(workingDir / "assets" / "8" / "input.txt");
      break;
    }else if (day == 9){
      Day9::solve(workingDir / "assets" / "9" / "input.txt");
      break;
    }else if (day == 10){
      Day10::solve(workingDir / "assets" / "10" / "input.txt");
      break;
    }else if (day == 11){
      Day11::solve(workingDir / "assets" / "11" / "input.txt");
      break;
    }else if (day == 12){
      Day12::solve(workingDir / "assets" / "12" / "input.txt");
      break;
    }else if  (day == 13){
      Day13::solve(workingDir / "assets" / "13" / "input.txt");
      break;
    }else if (day == 14){
      Day14::solve(workingDir / "assets" / "14" / "input.txt");
      break;
    }else if (day == 15){
      Day15::solve(workingDir / "assets" / "15" / "input.txt");
      break;
    }else if (day == 16){
      Day16::solve(workingDir / "assets" / "16" / "input.txt");
      break;
    }else if (day == 17){
      Day17::solve(workingDir / "assets" / "17" / "input.txt");
      break;
    }else if (day == 18){
      Day18::solve(workingDir / "assets" / "18" / "input.txt");
      break;
    }else if (day == 19){
      Day19::solve(workingDir / "assets" / "19" / "input.txt");
      break;
    }else if (day == 20){
      Day20::solve(workingDir / "assets" / "20" / "input.txt");
      break;
    }else{
      std::cout << "Invalid day, please choose a day between 1 and 14 or 0 to quit" << std::endl;
    }
  }
  return 0;
}


void renderGUI() {
    // Create a window called "Day Selector"
    ImGui::Begin("Day Selector");

    static int day = 0;
    ImGui::SliderInt("Choose a day to solve (1-20)", &day, 0, 20);

    if (ImGui::Button("Solve")) {
      
    }

    if (ImGui::Button("Quit")) {
        // Access the current GLFW window and set it to close
        GLFWwindow* window = glfwGetCurrentContext();
        if (window) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    ImGui::End();
}