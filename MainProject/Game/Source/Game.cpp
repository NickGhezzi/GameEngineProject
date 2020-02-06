#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"

#include "Scenes/SceneCube.h"
#include "Scenes/SimpleScene.h"
#include "Scenes/SceneWater.h"

#include "ResourceManager.h"
#include "Base/Material.h"

using namespace fw;

Game::Game(Framework* pFramework)
: GameCore( pFramework )
{
    m_pImGuiManager = nullptr;

    m_pController = new PlayerController();

    m_pPhysicsWorld = nullptr;

    m_pResourceManager = nullptr;

}

Game::~Game()
{
    delete m_pController;

    delete m_pImGuiManager;

    delete m_pSceneCube;
    delete m_pSceneWater;
    delete m_pSimpleScene;

    delete m_pResourceManager;

    delete m_pPhysicsWorld;
}

void Game::Init()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);

    m_pImGuiManager = new ImGuiManager();
    m_pImGuiManager->Init();

    // Turn on v-sync.
    wglSwapInterval( 1 );


    // populate resource manager
    m_pResourceManager = new ResourceManager();

    m_pResourceManager->AddTexture("Dice", new Texture("Data/Textures/Dice.png"));
    m_pResourceManager->AddTexture("Megaman", new Texture("Data/Textures/Megaman.png"));
    m_pResourceManager->AddTexture("Ground", new Texture("Data/Textures/Ground.png"));

    m_pResourceManager->AddShader("Shader_Texture", new ShaderProgram("Data/Shaders/texture.vert", "Data/Shaders/texture.frag"));
    m_pResourceManager->AddShader("Shader_Water", new ShaderProgram("Data/Shaders/Water.vert", "Data/Shaders/Water.frag"));

    m_pResourceManager->AddMaterial("Megaman", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Megaman")));
    m_pResourceManager->AddMaterial("Ground", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Ground")));
    m_pResourceManager->AddMaterial("Dice", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Dice")));
    m_pResourceManager->AddMaterial("Water", new Material(m_pResourceManager->GetShader("Shader_Water"), m_pResourceManager->GetTexture("Dice")));

    //meshes
    m_pResourceManager->AddMesh("PlayerMesh", new Mesh())->CreateBox(vec2(1, 1), vec2(0, 0));
    m_pResourceManager->AddMesh("CubeMesh", new Mesh())->CreateCube(vec3(1, 1, 1), vec3(0, 0, 0));
    m_pResourceManager->AddMesh("Plane", new Mesh())->CreatePlane(vec2(6, 6), ivec2(20, 20));

    //Create physics world
    m_pPhysicsWorld = new fw::PhysicsWorld2D();

    //CUBE ASSIGNMENT:::: comment out simple scene and uncomment scenecube for the cube. sorry for the inconvenience

    m_pSceneCube = new SceneCube(this);
    m_pSceneWater = new SceneWater(this);
    m_pSimpleScene = new SimpleScene(this);

    m_pSceneCube->Init();
    m_pSceneWater->Init();
    m_pSimpleScene->Init();

    m_pSimpleScene->LoadFromFile("Data/Simple.box2dscene");

    m_pCurrentScene = m_pSimpleScene;


    // Create our GameObjects.
    
}

void Game::OnEvent(Event* pEvent)
{
    m_pImGuiManager->OnEvent( pEvent );
    m_pController->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( (float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltaTime );

    // Enable/disable V-Sync.
    if( m_pFramework->IsKeyDown( VK_F1 ) )
        wglSwapInterval( 0 );
    if( m_pFramework->IsKeyDown( VK_F2 ) )
        wglSwapInterval( 1 );

    //update physicsworld
    m_pPhysicsWorld->Update(deltaTime);

    // Update objects.
    ImGui::Begin("Scene Selector");
    if (ImGui::Button("Cube"))
    {
        m_pCurrentScene = m_pSceneCube;
        
    }
    if (ImGui::Button("Water"))
    {
        m_pCurrentScene = m_pSceneWater;
       
    }
    if (ImGui::Button("SimpleScene"))
    {
        m_pCurrentScene = m_pSimpleScene;

    }
    ImGui::End();

    m_pCurrentScene->Update(deltaTime);
   
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor( 0.0f, 0.0f, 0.4f, 0.0f ); // dark blue
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Enable alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // Draw our game objects.
    //m_pPlayer->Draw( m_pCamera );
    m_pCurrentScene->Draw();

    m_pImGuiManager->EndFrame();
}

ResourceManager* Game::GetResourceManager()
{
    return m_pResourceManager;
}

fw::PhysicsWorld2D* Game::GetPhysicsWorld()
{
    return (PhysicsWorld2D*)m_pPhysicsWorld;
}
