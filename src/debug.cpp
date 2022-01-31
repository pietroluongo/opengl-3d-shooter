#include <GL/gl.h>
#include <iostream>
#include <sstream>
#include <string>

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
    glfvec2 colliderPos =
        context->getGameRef()->getPlayer()->getCollider()->getCenter();
    glm::ivec2 mousePos = context->getScreenSpaceMousePos();
    glm::fvec2 mousePosN = context->getNormalizedMousePos();
    glm::fvec2 mousePosW = context->getWorldSpaceMousePos();
    glm::fvec4 cameraBounds =
        context->getGameRef()->getMainCamera()->getBounds();
    glm::fvec2 cameraPosition =
        context->getGameRef()->getMainCamera()->getPosition();
    glm::bvec4 playerCollisionData =
        context->getGameRef()->getPlayer()->getCollisionArr();

    std::vector<Enemy*> enemies = context->getGameRef()->getEnemies();

    int minutes = (int)context->getTotalPlaytime() / 60;
    int seconds = (int)context->getTotalPlaytime() % 60;
    int millis = (int)(context->getTotalPlaytime() * 1000) % 1000;

    if (context->shouldDrawDebugInfo) {
        ImGui::Begin("Debug [F1]", &context->shouldDrawDebugInfo);
        ImGui::Text("Application average %.3f ms/frame (%.3f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::Text("DeltaTime from GLUT: %.6f", context->getDeltaTime());
        ImGui::Text("Total playtime: %02d:%02d:%03d", minutes, seconds, millis);

        ImGui::Text("Mouse coords: %d, %d", mousePos.x, mousePos.y);
        ImGui::Text("Mouse normalized: %f, %f", mousePosN.x, mousePosN.y);
        ImGui::Text("Mouse world space: %f, %f", mousePosW.x, mousePosW.y);
        ImGui::Text("World bounds: %f, %f, %f, %f",
                    context->getGameRef()->getMap()->getWorldBounds()[0],
                    context->getGameRef()->getMap()->getWorldBounds()[1],
                    context->getGameRef()->getMap()->getWorldBounds()[2],
                    context->getGameRef()->getMap()->getWorldBounds()[3]);
        ImGui::Text("Game State: %s", context->getGameRef()->getState());
        ImGui::End();
    }
    if (context->shouldDrawCameraInfo) {
        ImGui::Begin("Camera [F2]", &context->shouldDrawCameraInfo);
        ImGui::Text("Camera bounds: %.2f, %.2f, %.2f, %.2f", cameraBounds.x,
                    cameraBounds.y, cameraBounds.z, cameraBounds.w);
        ImGui::Text("Camera position: %.2f, %.2f", cameraPosition.x,
                    cameraPosition.y);
        ImGui::SliderFloat("Zoom level",
                           &context->getGameRef()->getMainCamera()->zoomLevel,
                           0.1f, 10.0f);
        ImGui::Checkbox(
            "Toggle Free Camera (control w/ IJKL)",
            &context->getGameRef()->getMainCamera()->freeCamEnabled);
        ImGui::Checkbox(
            "Toggle Chase Camera",
            &context->getGameRef()->getMainCamera()->shouldFollowTarget);
        ImGui::End();
    }
    if (context->shouldDrawPhysicsInfo) {
        ImGui::Begin("Physics [F3]", &context->shouldDrawPhysicsInfo);
        ImGui::Checkbox("Toggle Coordinate Systems",
                        &context->shouldObjectsDrawCoordinateSystem);
        ImGui::Checkbox("Toggle object colliders",
                        &context->shouldObjectsDrawColliders);
        ImGui::Checkbox("Should platform draw collision",
                        &context->shouldPlatformsShowCollisions);
        ImGui::End();
    }
    if (context->shouldDrawEnemyInfo) {
        ImGui::Begin("Enemy [F4]", &context->shouldDrawEnemyInfo);
        ImGui::Checkbox("Toggle Enemy Debug Info",
                        &context->shouldEnemiesDrawInfo);
        ImGui::Checkbox("Toggle shooting", &context->enemiesCanShoot);
        ImGui::Checkbox("Toggle movement", &context->enemiesCanMove);
        int i = 0;
        std::ostringstream os;
        for (auto enemy : enemies) {
            glm::bvec4 enemyCollisionData = enemy->getCollisionArr();
            os.str("");
            os.clear();
            os << "Enemy " << i++;
            if (ImGui::CollapsingHeader(os.str().c_str())) {
                ImGui::Text("Pos: [%.2f, %.2f]", enemy->getPosition().x,
                            enemy->getPosition().y);
                ImGui::Text(
                    "Collision direction:\n\t         %d\n\t      %d     %d\n\t"
                    "         %d",
                    enemyCollisionData[2], enemyCollisionData[0],
                    enemyCollisionData[1], enemyCollisionData[3]);
            }
        }
        ImGui::End();
    }
    if (context->shouldDrawPlayerInfo) {
        ImGui::Begin("Player [F12]", &context->shouldDrawPlayerInfo);
        ImGui::Text("Player pos: %.2f, %.2f", playerPos.x, playerPos.y);
        ImGui::Text("Player collider pos: %.2f, %.2f", colliderPos.x,
                    colliderPos.y);
        ImGui::SliderFloat("Arm angle",
                           &context->getGameRef()->getPlayer()->armAngle, 45.0f,
                           135.0f);
        ImGui::Text("Player AnimState: %s",
                    context->getGameRef()->getPlayer()->getCurrentAnimState());
        ImGui::Text("Collision direction:\n\t         %d\n\t      %d     %d\n\t"
                    "         %d",
                    playerCollisionData[2], playerCollisionData[0],
                    playerCollisionData[1], playerCollisionData[3]);
        ImGui::Text("Player Bounds:\n\t%12.2f\n\t%.2f\t%.2f\n\t"
                    "%12.2f",
                    context->getGameRef()
                        ->getPlayer()
                        ->getCollider()
                        ->getBoundingBox()[2],
                    context->getGameRef()
                        ->getPlayer()
                        ->getCollider()
                        ->getBoundingBox()[0],
                    context->getGameRef()
                        ->getPlayer()
                        ->getCollider()
                        ->getBoundingBox()[1],
                    context->getGameRef()
                        ->getPlayer()
                        ->getCollider()
                        ->getBoundingBox()[3]);
        if (ImGui::SliderFloat(
                "Player Size",
                context->getGameRef()->getPlayer()->tmp_getSize(), 0.0f,
                100.0f)) {
            context->getGameRef()->getPlayer()->handleResize();
        }
        ImGui::SliderFloat4(
            "Player leg rotation",
            context->getGameRef()->getPlayer()->getLegRotation(), -90, 90);
        ImGui::Text("Player heading: %s",
                    context->getGameRef()->getPlayer()->getHeading());
        ImGui::Text("Player jump time: %.2f",
                    context->getGameRef()->getPlayer()->getJumpTime());
        ImGui::Text("Player fall timer: %.2f",
                    context->getGameRef()->getPlayer()->getFallTimer());
        ImGui::Text("Player anim timer: %.2f",
                    context->getGameRef()->getPlayer()->animTimer);
        ImGui::Checkbox("Player invincible",
                        &context->getGameRef()->getPlayer()->isInvincible);
        ImGui::End();
    }
}

} // namespace debug
