#include "GamePCH.h"

#include "Game.h"
#include "Base/ResourceManager.h"
#include "Base/Mesh.h"
#include "ICA1/ICA1Scene.h"
#include "ICA1/ShakeCameraObject.h"
#include "ICA1/SheepObject.h"
#include "ICA1/MeteorObject.h"
#include "ICA1/MeatChunkObject.h"
#include "ICA1/SheepTitleCard.h"

const float ICA1Scene::INITIAL_PROJECTILE_SPAWN_DELAY = 1.0f;
const float ICA1Scene::TIME_BETWEEN_PROJECTILE_SPAWNS = 0.3f;
const int ICA1Scene::NUM_PROJECTILES_IN_POOL = 100;
const int ICA1Scene::NUM_MEAT_CHUNKS_IN_POOL = 20;

ICA1Scene::ICA1Scene(Game* pGame)
: BaseScene( pGame )
, m_ProjectilePool()
, m_MeatChunkPool()
{
    m_ProjectileSpawnTimer = INITIAL_PROJECTILE_SPAWN_DELAY;

    m_pSheep = nullptr;
    m_pTitle = nullptr;
    m_pWin = nullptr;
    m_pLose = nullptr;
}

ICA1Scene::~ICA1Scene()
{
}

void ICA1Scene::Reset()
{
    BaseScene::Reset();

    m_ProjectileSpawnTimer = INITIAL_PROJECTILE_SPAWN_DELAY;
}

void ICA1Scene::Init()
{
    BaseScene::Init();
    
    // Create physics world.
    m_pPhysicsWorld = new fw::PhysicsWorld2D( m_pGame->GetFramework() );

    ResourceManager* pResources = m_pGame->GetResourceManager();

    // Create our shaders.
    {
        // Already loaded in Game.
        //pResources->AddShader( "Texture", new fw::ShaderProgram( "Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag" ) );
    }

    // Create meshes.
    {
        // Already loaded in Game.
        //Mesh* pMesh = new Mesh();
        //pMesh->CreateBox( vec2(1,1), false );
        //pResources->AddMesh( "Box", pMesh );
    }
    
    // Load our textures.
    {
        pResources->AddTexture( "Ground", new fw::Texture( "Data/ICA1/Ground.png" ) );
        pResources->AddTexture( "Meteor", new fw::Texture( "Data/ICA1/Meteor.png" ) );
        pResources->AddTexture( "Sheep", new fw::Texture( "Data/ICA1/Sheep.png" ) );
        pResources->AddTexture( "Bone", new fw::Texture( "Data/ICA1/Bone.png" ) );
        pResources->AddTexture( "Meat", new fw::Texture( "Data/ICA1/ItemFood.png" ) );
        pResources->AddTexture( "Title", new fw::Texture( "Data/ICA1/Title.png" ) );
        pResources->AddTexture( "BG", new fw::Texture( "Data/ICA1/BG.png" ) );
        pResources->AddTexture( "Win", new fw::Texture( "Data/ICA1/Win.png" ) );
        pResources->AddTexture( "Lose", new fw::Texture( "Data/ICA1/Lose.png" ) );
    }

    // Create some game objects.
    {
        // Camera.
        m_pCamera = new ShakeCameraObject( this, "Camera", vec3(0,0,-15), vec3(0,0,0), vec3(1,1,1), 0, 0, 0 );

        // BG.
        AddObjectToScene( new GameObject( this, "BG", vec3(0,0,0), vec3(0,0,0), vec3(15,15,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "BG" ) ) );

        // Player.
        m_pSheep = new SheepObject( this, "Player", vec3(0,-4,0), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Sheep" ) );
        m_pSheep->SetController( m_pGame->GetController() );
        m_pSheep->CreateBody( true );
        m_pSheep->GetBody()->AddBox( vec3(1, 1, 1), 1 );
        AddObjectToScene( m_pSheep );

        // Ground.
        GameObject* pObj = new GameObject( this, "Ground", vec3(0,-5,0), vec3(0,0,0), vec3(10,1,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Ground" ) );
        pObj->CreateBody( false );
        pObj->GetBody()->AddBox( vec3(10, 1, 1), 0 );
        AddObjectToScene( pObj );

        // Titles.
        m_pTitle = new SheepTitleCard( this, "Title", vec3(0,3,0), vec3(0,0,0), vec3(10,1,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Title" ) );
        m_pWin = new SheepTitleCard( this, "Win", vec3(0,20,0), vec3(0,0,0), vec3(10,1,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Win" ) );
        m_pLose = new SheepTitleCard( this, "Lose", vec3(0,20,0), vec3(0,0,0), vec3(10,1,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Lose" ) );

        AddObjectToScene( m_pTitle );
        AddObjectToScene( m_pWin );
        AddObjectToScene( m_pLose );
    }

    // Fill the pool with 100 projectiles.
    {
        for( int i=0; i<NUM_PROJECTILES_IN_POOL; i++ )
        {
            float meteorsize = 0.5f;

            char tempstr[50];
            sprintf_s( tempstr, 50, "Meteor%d", i );
            MeteorObject* pMeteor = new MeteorObject( this, tempstr, vec3(-10000,-10000,0), vec3(0,0,0), vec3(meteorsize,meteorsize,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), pResources->GetTexture( "Meteor" ) );
            pMeteor->CreateBody( true );
            pMeteor->GetBody()->AddCircle( meteorsize/2, 50 );
            pMeteor->GetBody()->SetActive( false );

            m_ProjectilePool.AddObjectToPool( pMeteor );
            pMeteor->SetPool( &m_ProjectilePool );
        }
    }

    // Fill the pool with 100 random bits of meat and bone.
    {
        for( int i=0; i<NUM_MEAT_CHUNKS_IN_POOL; i++ )
        {
            float meatchunksize = 0.5f;

            char tempstr[50];
            sprintf_s( tempstr, 50, "MeatChunk%d", i );

            fw::Texture* chunkTexture = pResources->GetTexture( "Meat" );
            if( rand()%2 == 0 )
                chunkTexture = pResources->GetTexture( "Bone" );

            MeatChunkObject* pMeatChunk = new MeatChunkObject( this, tempstr, vec3(-10000,-10000,0), vec3(0,0,0), vec3(meatchunksize,meatchunksize,1), pResources->GetMesh( "Box" ), pResources->GetShader( "Texture" ), chunkTexture );
            pMeatChunk->CreateBody( true );
            pMeatChunk->GetBody()->AddCircle( meatchunksize/6, 0.5f );
            pMeatChunk->GetBody()->SetActive( false );

            m_MeatChunkPool.AddObjectToPool( pMeatChunk );
            pMeatChunk->SetPool( &m_MeatChunkPool );
        }        
    }
}

void ICA1Scene::OnEvent(fw::Event* pEvent)
{
    BaseScene::OnEvent( pEvent );

    if( pEvent->GetType() == "InputEvent" )
    {
        fw::InputEvent* pInputEvent = (fw::InputEvent*)pEvent;

        if( pInputEvent->GetState() == fw::InputState::Pressed )
        {
            if( pInputEvent->GetKeyCode() == 'R' )
            {
                Reset();
            }

            if( pInputEvent->GetKeyCode() == 'F' )
            {
                m_pSheep->Die();
            }
        }
    }
}

void ICA1Scene::Update(float deltaTime)
{
    BaseScene::Update( deltaTime );

    ImGui::Begin( "TODO" );
    ImGui::Text( "Search the project for TODO_ICA1" );
    ImGui::Text( "There's a demo exe in the folder" );
    ImGui::Text( "(R) to reset, (F) to die" );
    ImGui::End();

    m_ProjectileSpawnTimer -= deltaTime;
    if( m_ProjectileSpawnTimer < 0 )
    {
        // TODO_ICA1: Spawn a meteor from the pool.
        //            Set the meteors initial position and give them a push towards the ground.
        GameObject* obj = m_ProjectilePool.GetObjectFromPool();
        float x = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 - -5)));
        float x1 = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - -1)));
        //obj->Reset();
        obj->GetBody()->SetActive(true);
        obj->GetBody()->SetTransform(vec3(x,10,0), 0);
        obj->GetBody()->ApplyLinearImpulseToCenter(vec3(x1, -1, 0));
        m_ProjectileSpawnTimer = TIME_BETWEEN_PROJECTILE_SPAWNS;
        AddObjectToScene(obj);
    }
}

void ICA1Scene::Draw()
{
    BaseScene::Draw();
}

void ICA1Scene::SpawnMeatChunks(vec3 spawnPos, unsigned int numChunks)
{
    // TODO_ICA1: Spawn a bunch of meat chunks and add forces to them, make sure they spin as they fly off.
    //            Make sure the chunks fly into the air, don't just have them flop onto the ground.
    for (int i = 0; i < numChunks; i++)
    {

        float x = -0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 - -0.5)));
        float y = -0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 - -0.5)));
        int rot = rand() % 30;

        GameObject* obj = m_MeatChunkPool.GetObjectFromPool();
        obj->GetBody()->SetActive(true);
        obj->GetBody()->SetTransform(spawnPos, 0);
        obj->GetBody()->ApplyLinearImpulseToCenter(vec3(x, y, 0));
        obj->GetBody()->ApplyTorque(vec3(0, 0, rot));
        AddObjectToScene(obj);
    }


}
