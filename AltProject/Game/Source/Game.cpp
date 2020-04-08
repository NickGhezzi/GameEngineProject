#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "Base/ResourceManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Scenes/BaseScene.h"
#include "SceneDonkeyKong/SceneDonkeyKong.h"
#include "SceneCactusFall/SceneCactusFall.h"

using namespace fw;

Game::Game(Framework* pFramework)
: GameCore( pFramework )
{
    m_pImGuiManager = nullptr;

    m_pResourceManager = nullptr;

    m_pActiveScene = nullptr;

    m_pController = new PlayerController();
}

Game::~Game()
{
    delete m_pController;

    delete m_pResourceManager;

    delete m_pImGuiManager;

    for( auto pScene : m_pLoadedScenes )
        delete pScene;
}

void Game::Init()
{
    m_pImGuiManager = new ImGuiManager();
    m_pImGuiManager->Init();

    glEnable( GL_CULL_FACE );
    glFrontFace( GL_CW );

    // Turn on v-sync.
    wglSwapInterval( 1 );

    m_pResourceManager = new ResourceManager();

    // Create our shaders.
    m_pResourceManager->AddShader( "Texture", new fw::ShaderProgram( "Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag" ) );

    // Create our meshes.
    Mesh* pMesh = new Mesh();
    pMesh->CreateBox( vec2(1,1), vec2(0,0) );
    m_pResourceManager->AddMesh( "Box", pMesh );

    // Load our textures.
    m_pResourceManager->AddTexture( "Megaman", new fw::Texture( "Data/Textures/Megaman.png" ) );

    //m_pPhysicsScene = new BoxStackingScene( this );
    BaseScene* pScene = new SceneDonkeyKong( this );
    pScene->Init();
    m_pLoadedScenes.push_back( pScene );

    pScene = new SceneCactusFall( this );
    pScene->Init();
    m_pLoadedScenes.push_back( pScene );
    
    m_pActiveScene = m_pLoadedScenes[1];
}

void Game::OnBeginFrame()
{
    m_pController->StoreOldFlags();
}

void Game::OnEvent(Event* pEvent)
{
    m_pImGuiManager->OnEvent( pEvent );

    m_pController->OnEvent( pEvent );

    m_pActiveScene->OnEvent( pEvent );

    if( pEvent->GetType() == "InputEvent" )
    {
        fw::InputEvent* pInputEvent = (fw::InputEvent*)pEvent;

        if( pInputEvent->GetState() == fw::InputState::Pressed )
        {
            if( pInputEvent->GetKeyCode() == 'R' )
            {
                m_pActiveScene->Reset();
            }
            if( pInputEvent->GetKeyCode() == '1' )
            {
                m_pActiveScene = m_pLoadedScenes[0];
            }
            if( pInputEvent->GetKeyCode() == '2' )
            {
                m_pActiveScene = m_pLoadedScenes[1];
            }
        }
    }
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( (float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltaTime );

    // Enable/disable V-Sync.
    if( m_pFramework->IsKeyDown( VK_F1 ) )
        wglSwapInterval( 0 );
    if( m_pFramework->IsKeyDown( VK_F2 ) )
        wglSwapInterval( 1 );

    m_pActiveScene->Update( deltaTime );

    ImGui::Begin( "Scene Selector" );
    if( ImGui::Button( "1) Donkey Kong" ) )
    {
        m_pActiveScene = m_pLoadedScenes[0];
    }
    if( ImGui::Button( "2) Cactus Fall" ) )
    {
        m_pActiveScene = m_pLoadedScenes[1];
    }
    ImGui::End();

    m_pController->StoreOldFlags();
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor( 0.0f, 0.0f, 0.4f, 0.0f ); // dark blue
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Enable alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_pActiveScene->Draw();

    m_pImGuiManager->EndFrame();
}
