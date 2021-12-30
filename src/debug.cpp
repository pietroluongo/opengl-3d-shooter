#include <GL/gl.h>

#include "../include/debug.h"
#include "../include/game.h"

namespace debug {
void imgui_init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();
}

void drawUI() {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    imgui_display();

    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void imgui_display() {
    glfvec2 playerPos = context->getGameRef()->getPlayerPosition();
    glm::ivec2 mousePos = context->getMousePos();
    glm::fvec4 cameraBounds =
        context->getGameRef()->getMainCamera()->getBounds();
    glm::fvec2 cameraPosition =
        context->getGameRef()->getMainCamera()->getPosition();
    if (context->shouldDrawDebugInfo) {
        ImGui::Begin("Debug [F1]", &context->shouldDrawDebugInfo);
        ImGui::Text("Application average %.3f ms/frame (%.3f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::Text("DeltaTime from GLUT: %.6f", context->getDeltaTime());
        ImGui::Text("Player pos: %.2f, %.2f", playerPos.x, playerPos.y);
        ImGui::Text("Mouse coords: %d, %d", mousePos.x, mousePos.y);

        ImGui::End();
    }
    if (context->shouldDrawCameraInfo) {
        ImGui::Begin("Camera [F2]", &context->shouldDrawCameraInfo);
        ImGui::Text("Camera bounds: %.2f, %.2f, %.2f, %.2f", cameraBounds.x,
                    cameraBounds.y, cameraBounds.z, cameraBounds.w);
        ImGui::Text("Camera position: %.2f, %.2f", cameraPosition.x,
                    cameraPosition.y);
        ImGui::SliderFloat("Zoom level", &context->getGameRef()
                                                ->getMainCamera()
                                                ->zoomLevel,
                           0.1f, 10.0f);
        ImGui::Checkbox(
            "Toggle Free Camera (control w/ IJKL)",
            &context->getGameRef()->getMainCamera()->freeCamEnabled);
        ImGui::Checkbox(
            "Toggle Chase Camera",
            &context->getGameRef()->getMainCamera()->shouldFollowTarget);
        ImGui::End();
    }
    if(context->shouldDrawPhysicsInfo){
        ImGui::Begin("Physics [F3]", &context->shouldDrawPhysicsInfo);
        ImGui::Checkbox("Toggle Coordinate Systems", &context->shouldObjectsDrawCoordinateSystem);
        ImGui::End();
    }
}

} // namespace debug
