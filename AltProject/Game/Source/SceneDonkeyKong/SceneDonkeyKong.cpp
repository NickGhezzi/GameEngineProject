#include "GamePCH.h"

#include "SceneDonkeyKong.h"

#include "BarrelObject.h"
#include "ElevatorObject.h"
#include "FollowCameraObject.h"
#include "MarioObject.h"

#include "Game.h"
#include "Base/ResourceManager.h"
#include "Scenes/BaseScene.h"
#include "Base/ObjectPool.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "Base/Mesh.h"

const float SceneDonkeyKong::TIME_BEFORE_INITIAL_BARREL_SPAWN = 0.5f;
const float SceneDonkeyKong::TIME_BETWEEN_BARREL_SPAWNS = 5.5f;
const int SceneDonkeyKong::NUM_BARRELS_IN_POOL = 100;

SceneDonkeyKong::SceneDonkeyKong(Game* pGame)
: BaseScene( pGame )
, m_BarrelPool()
{
    m_BarrelSpawnTimer = TIME_BEFORE_INITIAL_BARREL_SPAWN;
    m_Score = 0;
}

SceneDonkeyKong::~SceneDonkeyKong()
{
}

void SceneDonkeyKong::Init()
{
    BaseScene::Init();

    m_pPhysicsWorld = new fw::PhysicsWorld2D( m_pGame->GetFramework() );
    
    ResourceManager* pResources = m_pGame->GetResourceManager();

    // Create meshes specific to this game.  Will assert if name is already in use.
    {
        pResources->AddMesh( "Sprite", new Mesh() )->CreateBox( vec2(1,1), vec2(0,0) );
        pResources->AddMesh("NumberQuadMario", new Mesh())->CreateBox(vec2(1, 1), vec2(0, 0));
        //pResources->AddMesh( "SpriteReversed", new Mesh() )->CreateBoxWithFlippedHorizontalUVs( vec2(1,1), vec2(0,0) );
    }

    // Load textures specific to this game.  Will assert if name is already in use.
    {
        pResources->AddTexture( "DKBG1",          new fw::Texture( "Data/SceneDonkeyKong/DKBG1.png" ) );
        pResources->AddTexture( "DonkeyKong",     new fw::Texture( "Data/SceneDonkeyKong/DonkeyKong.png" ) );
        pResources->AddTexture( "MarioStanding",  new fw::Texture( "Data/SceneDonkeyKong/MarioStanding.png" ) );
        pResources->AddTexture( "MarioRunning1",  new fw::Texture( "Data/SceneDonkeyKong/MarioRunning1.png" ) );
        pResources->AddTexture( "MarioRunning2",  new fw::Texture( "Data/SceneDonkeyKong/MarioRunning2.png" ) );
        pResources->AddTexture( "MarioDead",      new fw::Texture( "Data/SceneDonkeyKong/MarioDead.png" ) );
        pResources->AddTexture( "Barrel",         new fw::Texture( "Data/SceneDonkeyKong/Barrel.png" ) );
        pResources->AddTexture( "Hammer",         new fw::Texture( "Data/SceneDonkeyKong/Hammer.png" ) );
        pResources->AddTexture( "Elevator",       new fw::Texture( "Data/SceneDonkeyKong/Elevator.png" ) );
        pResources->AddTexture( "NumbersMario",   new fw::Texture( "Data/SceneCactusFall/numbers.png"));

    }

    // Create materials specific to this game.  Will assert if name is already in use.
    {
        pResources->AddMaterial( "DKBG1",         new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "DKBG1"         ) ) );
        pResources->AddMaterial( "DonkeyKong",    new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "DonkeyKong"    ) ) );
        pResources->AddMaterial( "MarioStanding", new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "MarioStanding" ) ) );
        pResources->AddMaterial( "MarioRunning1", new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "MarioRunning1" ) ) );
        pResources->AddMaterial( "MarioRunning2", new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "MarioRunning2" ) ) );
        pResources->AddMaterial( "MarioDead",     new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "MarioDead"     ) ) );
        pResources->AddMaterial( "Barrel",        new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "Barrel"        ) ) );
        pResources->AddMaterial( "Hammer",        new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "Hammer"        ) ) );
        pResources->AddMaterial( "Elevator",      new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "Elevator"      ) ) );
        pResources->AddMaterial( "NumbersMario",  new Material( pResources->GetShader( "Texture" ), pResources->GetTexture( "NumbersMario"  ) ) );
    }

    // Create some game objects.
    {

       

        // Camera.
        FollowCameraObject* pCamera = new FollowCameraObject( this, "Camera", vec3(0,0,-20), vec3(0,0,0), vec3(1,1,1) );
        m_pCamera = pCamera;

        // BG.
        AddObjectToScene( new GameObject( this, "DKBG1", vec3(0,0,0.01f), vec3(0,0,0), vec3(15*256/256.0f,15,1), pResources->GetMesh( "Sprite" ), pResources->GetMaterial( "DKBG1" ) ) );

        // Player.
        vec3 pos = vec3( -3.8f, 1.2f, 0 );
        pos = vec3( 2.0f, 3.2f, 0 ); // Uncomment to move player near the elevator.
        MarioObject* pPlayer = new MarioObject( this, "Player", pos, vec3(0, 0,0), vec3(0.75f,0.75f,1), pResources->GetMesh( "Sprite" ), pResources->GetMaterial( "MarioStanding" ), pResources);
        AddObjectToScene( pPlayer );
        pPlayer->SetController( m_pGame->GetController() );
        pPlayer->CreateBody( true );
        uint16* maskplayer[] = { new uint16(PhysicsCategory_Hammer), new uint16(PhysicsCategory_Barrel),  new uint16(PhysicsCategory_Environment) };
        pPlayer->GetBody()->AddBox( vec2(0.75f,0.75f), 1.0f, false, 3, PhysicsCategory_Player, maskplayer);
        for (int i = 0; i < 3; i++)
        {
            delete maskplayer[i];
        }
        // TODO_DonkeyKong: Set the player so he doesn't rotate.
        pPlayer->GetBody()->SetFixedRotation(true);
        // Donkey Kong.
        AddObjectToScene( new GameObject( this, "DonkeyKong", vec3(-4.8f,4.1f,0), vec3(0,0,0), vec3(3,3,1), pResources->GetMesh( "Sprite" ), pResources->GetMaterial( "DonkeyKong" ) ) );

        // TODO_DonkeyKong: Set hammers to be sensors.
        // Hammers.
        GameObject* pHammer = new GameObject( this, "Hammer1", vec3(-4.8f,1.7f,0), vec3(0,0,0), vec3(0.7f,0.7f,1), pResources->GetMesh( "Sprite" ), pResources->GetMaterial( "Hammer" ) );
        AddObjectToScene( pHammer );
        pHammer->CreateBody(false);
        uint16* maskhammer[] = { new uint16(PhysicsCategory_Player) };
        pHammer->GetBody()->AddBox( vec2(0.75f,0.75f), 1.0f, true, 1, PhysicsCategory_Hammer, maskhammer);
        delete maskhammer[0];
        // TODO_DonkeyKong: Add 20 Barrels to pool.
        for( int i=0; i<20; i++ )
        {
            // TODO_DonkeyKong: Add a physics body with a circle shape to each barrel object.
            //        Make sure the barrel isn't active since it's going into a pool.
            //        Give each barrel a random density between 1 and 2 so they roll at different speeds.
            //        Set the barrels to not collide with each other.
            float density = 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - 1.0f)));
            BarrelObject* pBarrel = new BarrelObject(this, "Barrel", vec3(-1000, -1000, 0), vec3(0, 0, 0), vec3(0.5, 0.5, 0.5), pResources->GetMesh("Sprite"), pResources->GetMaterial("Barrel"));
            pBarrel->CreateBody(true);
            uint16* maskbarrel[] = { new uint16(PhysicsCategory_Player),  new uint16(PhysicsCategory_Environment) };
            pBarrel->GetBody()->AddCircle(0.3, density, 2, PhysicsCategory_Barrel, maskbarrel);
            pBarrel->GetBody()->SetActive(false);
            pBarrel->SetPool(&m_BarrelPool);
            m_BarrelPool.AddObjectToPool(pBarrel);
            delete maskbarrel[0];
            delete maskbarrel[1];
        }

        // Create the board.
        {
            vec2 points[10];

            GameObject* pBorder = new GameObject( this, "Border", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), nullptr, nullptr );
            AddObjectToScene( pBorder );
            points[0].Set( -7.0, -8.0 );
            points[1].Set( -7.0,  8.0 );
            points[2].Set(  7.0,  8.0 );
            points[3].Set(  7.0, -8.0 );
            points[4].Set( -7.0, -8.0 );
            pBorder->CreateBody(false);
            pBorder->GetBody()->AddChain( points, 5, 1.0f );

            GameObject* pLevel0 = new GameObject( this, "Level0", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), nullptr, nullptr );
            AddObjectToScene( pLevel0 );
            points[0].Set( -7.0f, -7.0f );
            points[1].Set(  0.0f, -7.0f );
            points[2].Set(  7.0f, -6.6f );
            pLevel0->CreateBody(false);
            pLevel0->GetBody()->AddChain( points, 3, 1.0f );

            GameObject* pLevel1 = new GameObject( this, "Level1", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), nullptr, nullptr );
            AddObjectToScene( pLevel1 );
            points[0].Set( -7.0f, -4.65f );
            points[1].Set(  5.6f, -5.4f );
            pLevel1->CreateBody(false);
            pLevel1->GetBody()->AddChain( points, 2, 1.0f );

            GameObject* pLevel2 = new GameObject( this, "Level2", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), nullptr, nullptr );
            AddObjectToScene( pLevel2 );
            points[0].Set( -5.6f, -3.45f );
            points[1].Set(  7.0f, -2.7f );
            pLevel2->CreateBody(false);
            pLevel2->GetBody()->AddChain( points, 2, 1.0f );

            GameObject* pLevel3 = new GameObject( this, "Level3", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), nullptr, nullptr );
            AddObjectToScene( pLevel3 );
            points[0].Set( -7.0f, -0.75f );
            points[1].Set(  5.6f, -1.55f );
            pLevel3->CreateBody(false);
            pLevel3->GetBody()->AddChain( points, 2, 1.0f );

            GameObject* pLevel4 = new GameObject( this, "Level4", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), nullptr, nullptr );
            AddObjectToScene( pLevel4 );
            points[0].Set( -5.6f,  0.40f );
            points[1].Set(  7.0f,  1.15f );
            pLevel4->CreateBody( false );
            pLevel4->GetBody()->AddChain( points, 2, 1.0f );

            GameObject* pLevel5 = new GameObject( this, "Level5", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), nullptr, nullptr );
            AddObjectToScene( pLevel5 );
            points[0].Set( -7.0f,  2.55f );
            points[1].Set(  2.2f,  2.55f );
            points[2].Set(  5.6f,  2.35f );
            pLevel5->CreateBody(false);
            pLevel5->GetBody()->AddChain( points, 3, 1.0f );

            ElevatorObject* pElevator = new ElevatorObject( this, "Elevator",
                vec3(0,3.75f,0), vec3(0,0,0), vec3(48/17.0f,32/17.0f,1),
                pResources->GetMesh( "Sprite" ), pResources->GetMaterial( "Elevator" ) );
            AddObjectToScene( pElevator );
            points[0].Set( -1.45f,  -0.5f );
            points[1].Set(  1.45f,  -0.5f );
            pElevator->CreateBody( true );
            pElevator->GetBody()->AddChain( points, 2, 1.0f );
            pElevator->CreateJointAndSensor();
        }
    }

    AddObjectToScene(new GameObject(this, "Number1000s", vec3(-1, 6.55, 0), vec3(0, 0, 0), vec3(1, 1, 1), pResources->GetMesh("NumberQuadMario"), pResources->GetMaterial("NumbersMario")));
    AddObjectToScene(new GameObject(this, "Number100s", vec3(0, 6.55, 0), vec3(0, 0, 0), vec3(1, 1, 1), pResources->GetMesh("NumberQuadMario"), pResources->GetMaterial("NumbersMario")));
    AddObjectToScene(new GameObject(this, "Number10s", vec3(1, 6.55, 0), vec3(0, 0, 0), vec3(1, 1, 1), pResources->GetMesh("NumberQuadMario"), pResources->GetMaterial("NumbersMario")));
    AddObjectToScene(new GameObject(this, "Number1s", vec3(2, 6.55, 0), vec3(0, 0, 0), vec3(1, 1, 1), pResources->GetMesh("NumberQuadMario"), pResources->GetMaterial("NumbersMario")));

}

void SceneDonkeyKong::Reset()
{
    BaseScene::Reset();

    m_BarrelSpawnTimer = TIME_BEFORE_INITIAL_BARREL_SPAWN;
}

void SceneDonkeyKong::Update(float deltaTime)
{
    BaseScene::Update( deltaTime );

    m_Score = static_cast<MarioObject*>(GetGameObjectByName("Player"))->GetScore();

    if (static_cast<MarioObject*>(GetGameObjectByName("Player"))->GetHasWon())
    {
        static_cast<ElevatorObject*>(GetGameObjectByName("Elevator"))->EnableMotor();
    }

    if( m_pGame->GetFramework()->IsKeyDown( 'B' ) == true )
    {
        m_BarrelSpawnTimer = 0;
    }

    m_BarrelSpawnTimer -= deltaTime;
    if( m_BarrelSpawnTimer < 0 )
    {
        m_BarrelSpawnTimer = TIME_BETWEEN_BARREL_SPAWNS;

        vec3 barrelSpawnPoint = vec3( -4.0f, 3.5f, 0.0f );
        vec2 barrelForce = vec2( 2.0f, 0.0f );

        // TODO_DonkeyKong: Spawn a barrel from the pool, place it at barrelSpawnPoint and give it a push to the right.
        GameObject* obj = m_BarrelPool.GetObjectFromPool();
        obj->GetBody()->SetTransform(barrelSpawnPoint, 0);
        obj->GetBody()->SetActive(true);
        obj->GetBody()->ApplyLinearImpulseToCenter(barrelForce);
        AddObjectToScene(obj);

    }

    {

        int frame1000s = 0;
        int frame100s = 0;
        int frame10s = 0;
        int frame1s = 0;

        if (m_Score > 9 && m_Score < 100)
        {
            frame1s = (int)m_Score % 10;
            frame10s = (int)m_Score / 10;
        }
        else if (m_Score > 99 && m_Score < 1000)
        {
            frame1s = (int)m_Score % 10;
            frame100s = (int)m_Score / 100;

            frame10s = ((int)m_Score - (frame100s * 100)) / 10;
        }
        else if (m_Score > 999)
        {
            frame1s = (int)m_Score % 10;
            frame1000s = (int)m_Score / 1000;

            frame100s = ((int)m_Score - (frame1000s * 1000)) / 100;
            frame10s = ((int)m_Score - (frame100s * 100) - (frame1000s * 1000)) / 10;
        }
        else
        {
            frame1s = m_Score;
        }

        GetGameObjectByName("Number1000s")->SetUVScaleAndOffset(vec2(64.0f / 1024.0f, 1.0f), vec2(frame1000s / 16.0f, 0.0f));
        GetGameObjectByName("Number100s")->SetUVScaleAndOffset(vec2(64.0f / 1024.0f, 1.0f), vec2(frame100s / 16.0f, 0.0f));
        GetGameObjectByName("Number10s")->SetUVScaleAndOffset(vec2(64.0f / 1024.0f, 1.0f), vec2(frame10s / 16.0f, 0.0f));
        GetGameObjectByName("Number1s")->SetUVScaleAndOffset(vec2(64.0f / 1024.0f, 1.0f), vec2(frame1s / 16.0f, 0.0f));
    }

}

void SceneDonkeyKong::Draw()
{
    BaseScene::Draw();
}
