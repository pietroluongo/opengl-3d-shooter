#include <GL/gl.h>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/debug.h"
#include "../include/game.h"
#include "../include/lightSrc.h"

namespace debug {
void imgui_init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
    io.ConfigViewportsNoTaskBarIcon = true;
#ifdef USE_GLUT
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
#endif

#ifdef USE_GLFW
    ImGui_ImplGlfw_InitForOpenGL(context->getWindow(), true);
#endif
    ImGui_ImplOpenGL2_Init();
}

void drawUI() {
    ImGui_ImplOpenGL2_NewFrame();
#ifdef USE_GLUT
    ImGui_ImplGLUT_NewFrame();
#else
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif

    imgui_display();

    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
#ifdef USE_GLFW
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
#endif
}

void drawDebugInfo() {
    int minutes = (int)context->getTotalPlaytime() / 60;
    int seconds = (int)context->getTotalPlaytime() % 60;
    int millis = (int)(context->getTotalPlaytime() * 1000) % 1000;

    glm::ivec2 mousePos = context->getScreenSpaceMousePos();
    glm::fvec2 mousePosN = context->getNormalizedMousePos();
    glm::fvec2 mousePosW = context->getWorldSpaceMousePos();

    ImGui::Begin("Debug [F1]", &context->shouldDrawDebugInfo);
    {
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
        if (ImGui::Button("Toggle Dimensionality")) {
            context->getGameRef()->toggleDimensions();
        }
        ImGui::BeginDisabled();
        for (int i = 0; i < context->nAxes; i++) {
            ImGui::SliderFloat("Axis %d", (float*)&context->axes[i], -1.0f,
                               1.0f);
        }
        ImGui::EndDisabled();
    }
    ImGui::End();
}

void drawCameraInfo() {
    glm::fvec4 cameraBounds =
        context->getGameRef()->getMainCamera()->getBounds();

    GLfloat model[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, model);

    glm::fvec2 cameraCenter =
        context->getGameRef()->getMainCamera()->getCenter();

    glm::mat4 cameraProjectionMatrix =
        context->getGameRef()->getMainCamera()->getProjectionMatrix();

    glm::fvec3 cameraPosition =
        context->getGameRef()->getMainCamera()->getPosition();

    ImGui::Begin("Camera [F2]", &context->shouldDrawCameraInfo);
    {
        ImGui::Text("Camera Mode: %s",
                    context->getGameRef()->getMainCamera()->getCameraMode());
        ImGui::Text("[2D] Camera bounds: %.2f, %.2f, %.2f, %.2f",
                    cameraBounds.x, cameraBounds.y, cameraBounds.z,
                    cameraBounds.w);
        ImGui::Text("[2D] Camera center: %.2f, %.2f", cameraCenter.x,
                    cameraCenter.y);
        ImGui::Text("[3D] Camera Position: %.2f, %.2f, %.2f", cameraPosition.x,
                    cameraPosition.y, cameraPosition.z);
        ImGui::SliderFloat("[?D] Zoom level",
                           &context->getGameRef()->getMainCamera()->zoomLevel,
                           0.1f, 10.0f);
        ImGui::SliderFloat("[3D] camera xz angle",
                           &context->getGameRef()->getMainCamera()->xzAngle,
                           -180.0f, 180.0f);
        ImGui::SliderFloat("[3D] camera xy angle",
                           &context->getGameRef()->getMainCamera()->xyAngle,
                           -180.0f, 180.0f);
        ImGui::Text(
            "Camera Behaviour: %s",
            context->getGameRef()->getMainCamera()->getCameraBehaviourName());
        if (ImGui::Button("Orbital camera")) {
            context->getGameRef()->getMainCamera()->setCameraBehaviour(
                CAMERA_ORBIT);
        }
        if (ImGui::Button("Free camera")) {
            context->getGameRef()->getMainCamera()->setCameraBehaviour(
                CAMERA_FREE);
        }
        if (ImGui::Button("Third person camera")) {
            context->getGameRef()->getMainCamera()->setCameraBehaviour(
                CAMERA_TPS);
        }
        if (ImGui::Button("First person camera")) {
            context->getGameRef()->getMainCamera()->setCameraBehaviour(
                CAMERA_FPS);
        }
        if (ImGui::Button("Camera Aim")) {
            context->getGameRef()->getMainCamera()->setCameraBehaviour(
                CAMERA_AIM);
        }
        if (ImGui::Button("Camera 2D")) {
            context->getGameRef()->getMainCamera()->setCameraBehaviour(
                CAMERA_2D_PERSPECTIVE);
        }

        ImGui::Checkbox(
            "Toggle Free Camera (control w/ IJKLUO)",
            &context->getGameRef()->getMainCamera()->freeCamEnabled);
        ImGui::Checkbox(
            "Toggle Chase Camera",
            &context->getGameRef()->getMainCamera()->shouldFollowTarget);
        ImGui::Text("[3D] Camera Projection Matrix:");
        ImGui::Text("%.2f, %.2f, %.2f, %.2f", cameraProjectionMatrix[0][0],
                    cameraProjectionMatrix[0][1], cameraProjectionMatrix[0][2],
                    cameraProjectionMatrix[0][3]);
        ImGui::Text("%.2f, %.2f, %.2f, %.2f", cameraProjectionMatrix[1][0],
                    cameraProjectionMatrix[1][1], cameraProjectionMatrix[1][2],
                    cameraProjectionMatrix[1][3]);
        ImGui::Text("%.2f, %.2f, %.2f, %.2f", cameraProjectionMatrix[2][0],
                    cameraProjectionMatrix[2][1], cameraProjectionMatrix[2][2],
                    cameraProjectionMatrix[2][3]);
        ImGui::Text("%.2f, %.2f, %.2f, %.2f", cameraProjectionMatrix[3][0],
                    cameraProjectionMatrix[3][1], cameraProjectionMatrix[3][2],
                    cameraProjectionMatrix[3][3]);
        ImGui::Text(
            "Global Model Matrix:\n\t%.2f, %.2f, %.2f, %.2f\n\t%.2f, %.2f, "
            "%.2f, %.2f\n\t%.2f, "
            "%.2f, %.2f, %.2f\n\t%.2f, %.2f, %.2f, %.2f",
            model[0], model[1], model[2], model[3], model[4], model[5],
            model[6], model[7], model[8], model[9], model[10], model[11],
            model[12], model[13], model[14], model[15]);
    }
    ImGui::End();
}

void drawPhysicsInfo() {
    ImGui::Begin("Physics [F3]", &context->shouldDrawPhysicsInfo);
    {
        ImGui::Checkbox("Toggle Coordinate Systems",
                        &context->shouldObjectsDrawCoordinateSystem);
        ImGui::Checkbox("Toggle object colliders",
                        &context->shouldObjectsDrawColliders);
        ImGui::Checkbox("Should platform draw collision",
                        &context->shouldPlatformsShowCollisions);
    }
    ImGui::End();
}

void drawEnemyInfo() {
    std::vector<Enemy*> enemies = context->getGameRef()->getEnemies();

    ImGui::Begin("Enemy [F4]", &context->shouldDrawEnemyInfo);
    {
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
    }
    ImGui::End();
}

void drawMemoryInfo() {
    ImGui::Begin("Memory [F5]");
    {
        float values[100];
        for (unsigned long long int i = 0; i < 100; i++) {
            if (i >= context->enemyIdleTimerQueue.size())
                break;
            values[i] = context->enemyIdleTimerQueue.at(i);
        }
        ImGui::Text("Projectiles: %lu",
                    context->getGameRef()->getProjectileCount());
        // ImGui::Text("Player process time: %02.2f", context->playerIdleTime);
        ImGui::Text("Enemy process time: %02.2f",
                    context->getAveragedEnemyIdleTimer());
        ImGui::PlotLines("Enemy process time", values, 100, 0, "", 0, 16,
                         ImVec2(800, 100));
        // ImGui::Text("Projectile process time: %02.2f",
        //             context->projectileIdleTime);}
        ImGui::End();
    }
}

void drawLightingInfo() {
    // GLfloat val[10];
    // glGetLightfv(GL_LIGHT0, GL_POSITION, val);
    std::vector<LightSource*> lights = context->getGameRef()->getLights();
    std::ostringstream os;
    ImGui::Begin("Lighting [F6]", &context->shouldDrawLightingInfo);
    {
        if (ImGui::Button("Toggle Night Mode")) {
            context->getGameRef()->toggleDarkMode();
        }

        for (auto light : lights) {
            os.str("");
            os << "Light " << light->getId();
            if (ImGui::CollapsingHeader(os.str().c_str())) {
                ImGui::Text("Light Position: [%.2f, %.2f, %.2f]",
                            light->getPosition().x, light->getPosition().y,
                            light->getPosition().z);
                ImGui::Text("%s", light->getMode());
                if (light->isEnabled()) {
                    ImGui::Text("Enabled");
                    os.str("");
                    os << "Disable light " << light->getId();
                    if (ImGui::Button(os.str().c_str())) {
                        light->disable();
                    }
                } else {
                    os.str("");
                    os << "Enable light " << light->getId();
                    ImGui::Text("Disabled");
                    if (ImGui::Button(os.str().c_str())) {
                        light->enable();
                    }
                }
            }
        }
        // ImGui::Text("Light position: [%.2f, %.2f, %.2f]", val[0], val[1],
        //             val[2]);
        // ImGui::Checkbox("Toggle Lighting",
        // &context->shouldLightingBeEnabled);
        ImGui::End();
    }
}

void drawPlayerInfo() {
    glfvec3 playerPos = context->getGameRef()->getPlayerPosition();
    glfvec3 colliderPos =
        context->getGameRef()->getPlayer()->getCollider()->getCenter();

    glm::bvec4 playerCollisionData =
        context->getGameRef()->getPlayer()->getCollisionArr();

    ImGui::Begin("Player [F12]", &context->shouldDrawPlayerInfo);
    {
        ImGui::Text("Player pos: %.2f, %.2f, %.2f", playerPos.x, playerPos.y,
                    playerPos.z);
        ImGui::Text("Player collider pos: %.2f, %.2f, %.2f", colliderPos.x,
                    colliderPos.y, colliderPos.z);
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
                        ->getBoundingBox()
                        .min.y,
                    context->getGameRef()
                        ->getPlayer()
                        ->getCollider()
                        ->getBoundingBox()
                        .min.x,
                    context->getGameRef()
                        ->getPlayer()
                        ->getCollider()
                        ->getBoundingBox()
                        .max.x,
                    context->getGameRef()
                        ->getPlayer()
                        ->getCollider()
                        ->getBoundingBox()
                        .max.y);
        if (ImGui::SliderFloat(
                "Player Size",
                context->getGameRef()->getPlayer()->tmp_getSize(), 0.0f,
                100.0f)) {
            context->getGameRef()->getPlayer()->handleResize();
        }
        ImGui::SliderFloat4(
            "Player leg rotation",
            context->getGameRef()->getPlayer()->getLegRotation(), -90, 90);
        const glm::fvec3 playerRotation =
            context->getGameRef()->getPlayer()->getRotation();
        ImGui::Text("Player heading: %s",
                    context->getGameRef()->getPlayer()->getHeading());
        ImGui::Text("Player angle: %.2f, %.2f, %.2f", playerRotation.x,
                    playerRotation.y, playerRotation.z);
        ImGui::Text("Player visual rotation: %.2f, %.2f, %.2f",
                    context->getGameRef()->getPlayer()->getVisualRotation().x,
                    context->getGameRef()->getPlayer()->getVisualRotation().y,
                    context->getGameRef()->getPlayer()->getVisualRotation().z);
        ImGui::Text("Player jump time: %.2f",
                    context->getGameRef()->getPlayer()->getJumpTime());
        ImGui::Text("Player fall timer: %.2f",
                    context->getGameRef()->getPlayer()->getFallTimer());
        ImGui::Text("Player anim timer: %.2f",
                    context->getGameRef()->getPlayer()->animTimer);
        ImGui::Checkbox("Player invincible",
                        &context->getGameRef()->getPlayer()->isInvincible);
    }
    ImGui::End();
}

void imgui_display() {

    if (context->shouldDrawDebugInfo) {
        drawDebugInfo();
    }

    if (context->shouldDrawCameraInfo) {
        drawCameraInfo();
    }
    if (context->shouldDrawPhysicsInfo) {
        drawPhysicsInfo();
    }
    if (context->shouldDrawEnemyInfo) {
        drawEnemyInfo();
    }

    if (context->shouldDrawMemoryInfo) {
        drawMemoryInfo();
    }

    if (context->shouldDrawLightingInfo) {
        drawLightingInfo();
    }

    if (context->shouldDrawPlayerInfo) {
        drawPlayerInfo();
    }
}

} // namespace debug
