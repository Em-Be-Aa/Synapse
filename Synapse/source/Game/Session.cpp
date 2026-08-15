#include "../Actor/Actor.h"
#include "../AI/StateMachine/StateMachine.h"
#include "../Camera/Camera.h"
#include "../Characters/Enemy.h"
#include "../Characters/Player.h"
#include "../Managers/CollisionManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/RenderManager.h"
#include "../Managers/TickManager.h"
#include "../Managers/UpdateManager.h"
#include "../Shader/RenderComponent.h"
#include "../Shader/Renderer2D.h"
#include "../Templates/Templates.h"
#include "../Tile/TileMap.h"
#include "../Window/Window.h"
#include "Session.h"
#include "WaveSpawner.h"
#include <cstdlib>
#include <ctime>
#include <glad/glad.h>

void Session::Init()
{

    Landscape = SpawnActor<TileMap>();
    SynapsePlayer = SpawnActor<Player>();

    // duplicates should not be added.
    SynapsePlayer->GetAbilityComponent().AddAbility("LIGHT ATTACK");
    SynapsePlayer->GetAbilityComponent().AddAbility("HEAVY ATTACK");

    // If the player dies...this behaves weird..fix this so it can act independent if there is no owner
    defaultCamera = SpawnActor<Camera>(SynapsePlayer);

    InputManager* IM = game->GetInputManager();
    Window* GW = game->GetGameWindow();

    // Setting Input Actor
    IM->EnableActorInput(SynapsePlayer);
    IM->onMouseMove = ([GW, this](double xpos, double ypos) { defaultCamera->CameraMove(GW->window, xpos, ypos); });


    //glEnable(GL_DEPTH_TEST);
    srand(time(0));

    waveSpawner = SpawnActor<WaveSpawner>(this);


    waveSpawner->StartWave(1);


}

void Session::Update(double deltaTime)
{

    InputManager* IM = game->GetInputManager();
    Window* GW = game->GetGameWindow();


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Process Inputs
    IM->ProcessInputs();

    // 3D Transformation, Camera and Projection
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 view;
    glm::vec3 CameraPosition = { defaultCamera->attachedActor->Position.x, defaultCamera->attachedActor->Position.y, 6.0f };
    view = glm::lookAt(CameraPosition, CameraPosition + defaultCamera->cameraFront, defaultCamera->cameraUp);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), ((float)GW->Width / (float)GW->Height), 0.1f, 100.0f);

    // Start renderer scene for Renderer2D (this will set view/projection uniforms)
    Renderer2D::BeginScene(view, projection);

    // Add pending actors spawned during the previous frame
    UpdateManager::GetUpdateManager().FlushPending();

    // Update World...this should work for things we need updated before we tick world
    for (auto& O : UpdateManager::GetUpdateManager().RegisteredObjects)
    {
        if (!O->isPendingDestroy)
        {
            O->Update(deltaTime);
        }
    }

    // Tick World
    for (Actor* O : TickManager::GetTickManager()->RegisteredActors)
    {
        if (!O->isPendingDestroy)
        {
            O->Tick(deltaTime);
        }
    }

    // Submit all registered RenderComponents to Renderer2D
    for (RenderComponent* rc : RenderManager::GetRenderManager().RenderComps)
    {
        if (rc)
            Renderer2D::Submit(*rc);
    }

    // End and flush renderer
    Renderer2D::EndScene();

    // Remove Pending Destroy Objects
    UpdateManager::GetUpdateManager().RemovePendingDestroyObjects();
    TickManager::GetTickManager()->RemovePendingDestroyActors();
    RenderManager::GetRenderManager().DestoryPendingRenders();
    CollisionManager::GetCollisionManager()->DestoryPendingCollidors();
    IM->DisableInputforPendingDestoryed();

    glfwSwapBuffers(GW->window);
    glfwPollEvents();
}
