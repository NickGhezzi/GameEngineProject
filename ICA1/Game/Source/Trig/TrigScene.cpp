#include "GamePCH.h"

#include "TrigScene.h"
#include "Game.h"
#include "Base/ResourceManager.h"

#include "ChaseCameraObject.h"
#include "TrigPet.h"
#include "TrigPlayer.h"
#include "TrigPickup.h"

TrigScene::TrigScene(Game* pGame)
: BaseScene( pGame )
{
}

TrigScene::~TrigScene()
{
    delete m_pHUDObject;
    delete m_pHUDCamera;
}

void TrigScene::Init()
{
    BaseScene::Init();

    glEnable( GL_DEPTH_TEST );
    
    ResourceManager* pResources = m_pGame->GetResourceManager();

    // Load some textures.
    {
        pResources->AddTexture( "Trig_Ground", new fw::Texture( "Data/ICA1/Ground.png" ) );
        pResources->AddTexture( "Trig_Pickup", new fw::Texture( "Data/ICA1/Meteor.png" ) );
        pResources->AddTexture( "Trig_Player", new fw::Texture( "Data/ICA1/Sheep.png" ) );
        pResources->AddTexture( "Trig_Pet", new fw::Texture( "Data/ICA1/Sheep.png" ) );
    }

    // Create some game objects.
    {
        // Ground
        AddObjectToScene( new GameObject( this, "Ground", vec3(0,-0.5f,0), vec3(-90,0,0), vec3(15,15,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Trig_Ground" ) ) );

        // Player
        TrigPlayer* pPlayer = new TrigPlayer( this, "Player", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Cube" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Trig_Player" ) );
        pPlayer->SetController( m_pGame->GetController() );
        AddObjectToScene( pPlayer );

        // Camera
        ChaseCameraObject* pChaseCam = new ChaseCameraObject( this, vec3(0,0,0) );
        pChaseCam->SetObjectToFollow( pPlayer, 10 );
        m_pCamera = pChaseCam;

        // Pet
        AddObjectToScene( new GameObject( this, "Pet", vec3(-2,0,0), vec3(0,0,0), vec3(0.5f,0.5f,0.5f), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Trig_Pet" ) ) );

        // Pickups
        for( int i=0; i<7; i++ )
        {
            TrigPickup* pPickup = new TrigPickup( this, "Pickup", vec3(-6.0f+i*2.0f,0,5), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Trig_Pickup" ) );
            AddObjectToScene( pPickup );
            m_Pickups.push_back( pPickup );
        }

    }
    m_pHUDObject = new GameObject(this, "HealthBar", vec3(20, 90, 0), 0, vec3(30, 10, 0), pResources->GetMesh("Box"), pResources->GetShader("Texture"), pResources->GetTexture("Trig_Player"));
    m_pHUDCamera = new Camera(this, vec3(0, 0, 0));
}

void TrigScene::Update(float deltaTime)
{
    BaseScene::Update( deltaTime );
}

void TrigScene::Draw()
{
    BaseScene::Draw();
    glClear(GL_DEPTH_BUFFER_BIT);
    //dont do this make hudcamera class
    m_pHUDCamera->GetView()->SetIdentity();
    m_pHUDCamera->GetProj()->CreateOrtho(0, 100, 0, 100, -1, 1);
    m_pHUDObject->Draw(m_pHUDCamera);
}
