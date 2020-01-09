#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"

using namespace fw;

Game::Game(Framework* pFramework)
: GameCore( pFramework )
{
    m_pImGuiManager = nullptr;

    m_pShaderTexture = nullptr;
    m_pMeshBox = nullptr;
    m_pTexture = 0;

    m_pPlayer = nullptr;
    m_pCamera = nullptr;

    m_pController = new PlayerController();

    m_pPhysicsWorld = nullptr;
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

    delete m_pPhysicsWorld;
}

void Game::Init()
{
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
    m_pTexture = new Texture( "Data/Textures/Megaman.png" );

    //Create physics world
    m_pPhysicsWorld = new fw::PhysicsWorld2D;

    // Create our GameObjects.
    m_pPlayer = new Player( this, m_pMeshBox, m_pShaderTexture, m_pTexture, vec2( 0, 0 ), 0, m_pController );
    m_pCamera = new Camera( this, vec2( 0, 0 ), vec2( 1/5.0f, 1/5.0f ) );
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
    m_pPlayer->Update( deltaTime );
    m_pCamera->Update( deltaTime );

   
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
    m_pPlayer->Draw( m_pCamera );

    m_pImGuiManager->EndFrame();
}

fw::PhysicsWorld* Game::GetPhysicsWorld()
{
    return m_pPhysicsWorld;
}
