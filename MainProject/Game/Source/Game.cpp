#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"

#include "Scenes/SceneCube.h"
#include "Scenes/SimpleScene.h"

#include "ResourceManager.h"
#include "Base/Material.h"

using namespace fw;

Game::Game(Framework* pFramework)
: GameCore( pFramework )
{
    m_pImGuiManager = nullptr;

    m_pPlayerMaterial = nullptr;
    m_pMeshBox = nullptr;
    m_pShaderTexture = nullptr;
    m_pTexture = 0;

    m_pPlayer = nullptr;
    m_pCamera = nullptr;

    m_pController = new PlayerController();

    m_pPhysicsWorld = nullptr;

    m_pScenes = nullptr;
    m_pResourceManager = nullptr;

}

Game::~Game()
{
    delete m_pController;

    delete m_pPlayer;
    delete m_pCamera;

    delete m_pTexture;

    delete m_pMeshBox;

    delete m_pShaderTexture;

    delete m_pImGuiManager;

    delete m_pScenes;

    delete m_pPlayerMaterial;

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

    // Create our shaders.
   m_pShaderTexture = new ShaderProgram( "Data/Shaders/texture.vert", "Data/Shaders/texture.frag" );

    // Create our meshes.
    m_pMeshBox = new Mesh();
    m_pMeshBox->CreateBox( vec2(1,1), vec2(0,0) );

    // Load our textures.
    m_pTexture = new Texture( "Data/Textures/Dice.png" );

    // Create and setup materials
    m_pPlayerMaterial = new Material(m_pShaderTexture, m_pTexture);

    // populate resource manager
    m_pResourceManager = new ResourceManager();
    m_pResourceManager->AddTexture("Dice", new Texture("Data/Textures/Dice.png"));
    m_pResourceManager->AddShader("TextureShader", new ShaderProgram("Data/Shaders/texture.vert", "Data/Shaders/texture.frag"));
    m_pResourceManager->AddMaterial("PlayerMaterial", new Material(m_pShaderTexture, m_pTexture));

    //meshes
    m_pResourceManager->AddMesh("PlayerMesh", new Mesh())->CreateBox(vec2(1, 1), vec2(0, 0));
    m_pResourceManager->AddMesh("CubeMesh", new Mesh())->CreateCube(vec3(1, 1, 1), vec3(0, 0, 0));
    m_pResourceManager->AddMesh("Plane", new Mesh())->CreatePlane(vec2(4, 4), ivec2(20, 20));

    //Create physics world
    m_pPhysicsWorld = new fw::PhysicsWorld2D;

    m_pScenes = new SimpleScene(this);
    
    m_pScenes->Init();

    m_pScenes->LoadFromFile("Data/Simple.box2dscene");
    // Create our GameObjects.
    //m_pPlayer = new Player( m_pScenes, m_pMeshBox, m_pResourceManager->GetShader("TextureShader"), m_pResourceManager->GetTexture("MegaMan"), vec2( 0, 0 ), 0, m_pController );
    m_pCamera = new Camera( m_pScenes, vec2( 0, 0 ), vec2( 1/5.0f, 1/5.0f ) );
}

void Game::OnEvent(Event* pEvent)
{
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
   // m_pPlayer->Update( deltaTime );
   // m_pCamera->Update( deltaTime );
    m_pScenes->Update(deltaTime);
   
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
    m_pScenes->Draw();

    m_pImGuiManager->EndFrame();
}

ResourceManager* Game::GetResourceManager()
{
    return m_pResourceManager;
}

fw::PhysicsWorld* Game::GetPhysicsWorld()
{
    return m_pPhysicsWorld;
}
