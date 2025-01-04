module;


export module MainGUI;


export void renderHelloWorld() {
    ImGui::Begin("Hello World Window");
    ImGui::Text("Hello, World!");
    ImGui::End();
}