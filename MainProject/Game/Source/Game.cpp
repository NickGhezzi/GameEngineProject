#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"

#include "Scenes/SceneCube.h"
#include "Scenes/SceneWater.h"
#include "Scenes/ScenePhysics.h"
#include "Scenes/BoxStackingScene.h"
#include "Scenes/TestScene.h"
#include "Scenes/SortingGameScene.h"

#include "ResourceManager.h"
#include "Base/Material.h"

using namespace fw;

Game::Game(Framework* pFramework)
: GameCore( pFramework )
{
    m_pImGuiManager = nullptr;

    m_pController = new PlayerController();

    m_pResourceManager = nullptr;

}

Game::~Game()
{
    delete m_pController;

    delete m_pImGuiManager;

    delete m_pSceneCube;
    delete m_pSceneWater;
    delete m_pScenePhysics;
    delete m_pBoxStackingScene;
    delete m_pTestScene;
    delete m_pSortingGameScene;

    delete m_pResourceManager;
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
    m_pResourceManager->AddTexture("Water", new Texture("Data/Textures/Water.png"));
    m_pResourceManager->AddTexture("Box", new Texture("Data/Textures/Box.png"));
    m_pResourceManager->AddTexture("Wood", new Texture("Data/Textures/Wood.png"));
    m_pResourceManager->AddTexture("Peg", new Texture("Data/Textures/Peg.png"));
    m_pResourceManager->AddTexture("Circle", new Texture("Data/Textures/Circle.png"));

    m_pResourceManager->AddTexture("BallRed", new Texture("Data/Textures/BallRed.png"));
    m_pResourceManager->AddTexture("BallGreen", new Texture("Data/Textures/BallGreen.png"));
    m_pResourceManager->AddTexture("BallBlue", new Texture("Data/Textures/BallBlue.png"));
    m_pResourceManager->AddTexture("BinRed", new Texture("Data/Textures/BinRed.png"));
    m_pResourceManager->AddTexture("BinGreen", new Texture("Data/Textures/BinGreen.png"));
    m_pResourceManager->AddTexture("BinBlue", new Texture("Data/Textures/BinBlue.png"));

    m_pResourceManager->AddTexture("ScoreFont", new Texture("Data/Textures/Font12.png"));


    m_pResourceManager->AddShader("Shader_Texture", new ShaderProgram("Data/Shaders/texture.vert", "Data/Shaders/texture.frag"));
    m_pResourceManager->AddShader("Shader_Water", new ShaderProgram("Data/Shaders/Water.vert", "Data/Shaders/Water.frag"));

    m_pResourceManager->AddMaterial("Megaman", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Megaman")));
    m_pResourceManager->AddMaterial("Ground", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Ground")));
    m_pResourceManager->AddMaterial("Dice", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Dice")));
    m_pResourceManager->AddMaterial("Water", new Material(m_pResourceManager->GetShader("Shader_Water"), m_pResourceManager->GetTexture("Water")));
    m_pResourceManager->AddMaterial("Box", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Box")));
    m_pResourceManager->AddMaterial("BallRed", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("BallRed")));
    m_pResourceManager->AddMaterial("BallGreen", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("BallGreen")));
    m_pResourceManager->AddMaterial("BallBlue", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("BallBlue")));
    m_pResourceManager->AddMaterial("BinRed", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("BinRed")));
    m_pResourceManager->AddMaterial("BinGreen", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("BinGreen")));
    m_pResourceManager->AddMaterial("BinBlue", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("BinBlue")));

    m_pResourceManager->AddMaterial("Score", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("ScoreFont")));
    m_pResourceManager->AddMaterial("Wood", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Wood")));
    m_pResourceManager->AddMaterial("Peg", new Material(m_pResourceManager->GetShader("Shader_Texture"), m_pResourceManager->GetTexture("Peg")));



    //meshes
    m_pResourceManager->AddMesh("PlayerMesh", new Mesh())->CreateBox(vec2(1, 1), vec2(0, 0));
    m_pResourceManager->AddMesh("CubeMesh", new Mesh())->CreateCube(vec3(1, 1, 1), vec3(0, 0, 0));
    m_pResourceManager->AddMesh("Plane", new Mesh())->CreatePlane(vec2(50, 50), ivec2(100, 100));
    m_pResourceManager->AddMesh("FloorMesh", new Mesh())->CreateCube(vec3(5, 1, 1), vec3(0, 0, 0));
    m_pResourceManager->AddMesh("Cube", new Mesh())->LoadObjFromFile("Data/OBJ Files/cube.obj");
    m_pResourceManager->AddMesh("Sphere", new Mesh())->LoadObjFromFile("Data/OBJ Files/sphere.obj");
    m_pResourceManager->AddMesh("BinMesh", new Mesh())->CreateBox(vec2(2, 1), vec2(0, 0));

    for (int i = 0; i < 10; i++)
    {
        m_pResourceManager->AddMesh("Score" + std::to_string(i), new Mesh())->GenerateScore(i);
    }
    //Create physics world

    m_pSceneCube = new SceneCube(this);
    m_pSceneWater = new SceneWater(this);
    m_pScenePhysics = new ScenePhysics(this);
    m_pBoxStackingScene = new BoxStackingScene(this);
    m_pTestScene = new TestScene(this);
    m_pSortingGameScene = new SortingGameScene(this);

    m_pSceneCube->Init();
    m_pSceneWater->Init();
    m_pScenePhysics->Init();
    m_pBoxStackingScene->Init();
    m_pTestScene->Init();
    m_pSortingGameScene->Init();

    m_pSortingGameScene->LoadFromFile("Data/SortingGame.box2dscene");
    m_pScenePhysics->LoadFromFile("Data/Simple.box2dscene");

    m_pCurrentScene = m_pSortingGameScene;


    // Create our GameObjects.
    
}

void Game::OnEvent(Event* pEvent)
{
    m_pImGuiManager->OnEvent( pEvent );
    m_pController->OnEvent( pEvent );
    m_pCurrentScene->OnEvent(pEvent);
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( (float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltaTime );

    // Enable/disable V-Sync.
    if( m_pFramework->IsKeyDown( VK_F1 ) )
        wglSwapInterval( 0 );
    if( m_pFramework->IsKeyDown( VK_F2 ) )
        wglSwapInterval( 1 );

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
        m_pCurrentScene = m_pScenePhysics;

    }
    if (ImGui::Button("BoxStackingScene"))
    {
        m_pCurrentScene = m_pBoxStackingScene;

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


fw::Framework* Game::GetFramework()
{
    return m_pFramework;
}
