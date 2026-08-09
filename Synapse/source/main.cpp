#include "Actor/Object.h"
#include "Camera/Camera.h"
#include "Characters/Enemy.h"
#include "Characters/Player.h"
#include "GameConfig/GameConfigs.h"
#include "Managers/InputManager.h"
#include "Managers/RenderManager.h"
#include "Managers/TickManager.h"
#include "Managers/UpdateManager.h"
#include "Shader/Renderer2D.h"
#include "Templates/Templates.h"
#include "Tile/TileMap.h"
#include "Window/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

                                            
/*                                      
 
TODO:

3. Make Animation System include a single play of animation for attacks and stuff.
5. Make a grid system, all actors should be aware of their grid(or grid should have all actors in it). Through this make the collision system decoupled and moving actors should check for collision in their grid.
6. Movement along diagonal is faster, balance it.
7. Collidors of top and right stop player further from the other actors collision box.
8. Make Event System in game. Listener and things like that.
9. Make click, press, and release things for keyboard buttons....

*/


int main()
{
    Window DefaultWindow;

    // Managers
    InputManager DefaultInputManager(DefaultWindow.window);

    //make some system to manage all shaders and rendering.....adding it in actors logic is too hectic
    TileMap* Landscape = SpawnActor<TileMap>();

    // you dont even understand it...make it your self..the namespace thing remove it
    Renderer2D::Init("Shaders/shader.vs", "Shaders/shader.fs");

    //find a better way...right now im doing this so it is before ability is initialized
    GameConfigs::GetGameConfig();

    // Actors
    Player* SynapsePlayer = SpawnActor<Player>();
    Enemy* SlimeEnemy = SpawnActor<Enemy>();

    // duplicates should not be added.
    SynapsePlayer->GetAbilityComponent().AddAbility("LIGHT ATTACK", SynapsePlayer);
    SynapsePlayer->GetAbilityComponent().AddAbility("HEAVY ATTACK", SynapsePlayer);

    Camera DefaultCamera(SynapsePlayer);

    // Setting Input Actor
    DefaultInputManager.observers.push_back(SynapsePlayer);
    DefaultInputManager.onMouseMove = ([&DefaultWindow, &DefaultCamera](double xpos, double ypos) { DefaultCamera.CameraMove(DefaultWindow.window, xpos, ypos); });

    
    //glEnable(GL_DEPTH_TEST);
    srand(time(0));

    double currentTime;
    double initialTime = glfwGetTime();
    double deltaTime = 0.0f;

    // Render Loop
    while (!glfwWindowShouldClose(DefaultWindow.window))
    {

        currentTime = glfwGetTime();
        deltaTime = currentTime - initialTime;
        initialTime = currentTime;


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Process Inputs
        DefaultInputManager.ProcessInputs();

        // 3D Transformation, Camera and Projection
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 view;
        glm::vec3 CameraPosition = {DefaultCamera.attachedActor->Position.x, DefaultCamera.attachedActor->Position.y, 3.0f};
        view = glm::lookAt(CameraPosition, CameraPosition + DefaultCamera.cameraFront, DefaultCamera.cameraUp);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), ((float)DefaultWindow.Width / (float)DefaultWindow.Height), 0.1f, 100.0f);

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

        glfwSwapBuffers(DefaultWindow.window);
        glfwPollEvents();
    }


	// Cleanup and Exit
    // Shutdown renderer resources
    Renderer2D::Shutdown();
    glfwTerminate();
    return 0;
}


