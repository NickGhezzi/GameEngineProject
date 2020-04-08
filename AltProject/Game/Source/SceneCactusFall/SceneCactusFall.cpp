#include "GamePCH.h"

#include "SceneCactusFall.h"
#include "CactusCam.h"
#include "GameObjectCactus.h"
#include "GameObjectTarget.h"
#include "GameObjectTargetBonus.h"
#include "Game.h"
#include "Base/ResourceManager.h"
#include "Scenes/BaseScene.h"
#include "GameObjects/GameObject.h"
#include "Base/Mesh.h"

inline float randFromNegativeOneToOne()
{
    return rand()/(RAND_MAX/2) - 1.0f;
}

SceneCactusFall::SceneCactusFall(Game* pGame)
: BaseScene( pGame )
{
    m_Score = 2975;
    m_TestMode = false;
}

SceneCactusFall::~SceneCactusFall()
{
}

void SceneCactusFall::Init()
{
    BaseScene::Init();

    ResourceManager* pResources = m_pGame->GetResourceManager();

    // Create shaders.
    //pResources->AddShader( "Texture",      new fw::ShaderProgram( "Data/SceneCactusFall/texture.vert", "Data/SceneCactusFall/texture.frag" ) );
    pResources->AddShader( "VertColor",    new fw::ShaderProgram( "Data/SceneCactusFall/vertcolor.vert", "Data/SceneCactusFall/vertcolor.frag" ) );
    pResources->AddShader( "Font",         new fw::ShaderProgram( "Data/SceneCactusFall/font.vert", "Data/SceneCactusFall/font.frag" ) );

    // Create meshes.
    pResources->AddMesh( "Sphere",     new Mesh() )->CreateOBJ( "Data/SceneCactusFall/sphere.obj", 1.0f );
    pResources->AddMesh( "Cactus",     new Mesh() )->CreateOBJ( "Data/SceneCactusFall/sphere.obj", 0.4f );

    pResources->AddMesh( "Ground",     new Mesh() )->CreatePlane( vec2(800,800), ivec2(2,2), vec2(400,400), 5 );
    pResources->AddMesh( "NumberQuad", new Mesh() )->CreatePlane( vec2(1,1), ivec2(2,2), vec2(0,0), 1 );
    pResources->AddMesh( "Title",      new Mesh() )->CreatePlane( vec2(10,5), ivec2(2,2), vec2(5.0f,2.5f), 1 );

    pResources->AddMesh( "Ring1",      new Mesh() )->CreateRing( 0.0f,  2.0f, 64, ColorByte(255,0,0,255) );
    pResources->AddMesh( "Ring2",      new Mesh() )->CreateRing( 2.0f,  4.0f, 64, ColorByte(0,255,0,255) );
    pResources->AddMesh( "Ring3",      new Mesh() )->CreateRing( 4.0f,  6.0f, 64, ColorByte(0,0,255,255) );
    pResources->AddMesh( "Ring4",      new Mesh() )->CreateRing( 6.0f,  8.0f, 64, ColorByte(255,0,255,255) );
    pResources->AddMesh( "Ring5",      new Mesh() )->CreateRing( 8.0f, 10.0f, 64, ColorByte(255,255,0,255) );
    pResources->AddMesh( "BonusArc",   new Mesh() )->CreateArc( 10.0f,  60, 64, ColorByte(255,100,100,200) );
    
    // Load textures.
    pResources->AddTexture( "Cactus",  new fw::Texture( "Data/SceneCactusFall/cactus.png" ) );
    pResources->AddTexture( "Numbers", new fw::Texture( "Data/SceneCactusFall/numbers.png" ) );
    pResources->AddTexture( "Ground",  new fw::Texture( "Data/SceneCactusFall/stones.png" ) );
    pResources->AddTexture( "Sun",     new fw::Texture( "Data/SceneCactusFall/sun.png" ) );
    pResources->AddTexture( "Title",   new fw::Texture( "Data/SceneCactusFall/title.png" ) );

    // Create materials.
    pResources->AddMaterial( "Cactus",       new Material( pResources->GetShader( "Texture" ),      pResources->GetTexture( "Cactus"  ) ) );
    pResources->AddMaterial( "Numbers",      new Material( pResources->GetShader( "Texture" ),      pResources->GetTexture( "Numbers" ) ) );
    pResources->AddMaterial( "Ground",       new Material( pResources->GetShader( "Texture" ),      pResources->GetTexture( "Ground"  ) ) );
    pResources->AddMaterial( "Sun",          new Material( pResources->GetShader( "Texture" ),      pResources->GetTexture( "Sun"     ) ) );
    pResources->AddMaterial( "Title",        new Material( pResources->GetShader( "Texture" ),      pResources->GetTexture( "Title"   ) ) );
    pResources->AddMaterial( "VertColor",    new Material( pResources->GetShader( "VertColor" ),    nullptr ) );

    // Create some game objects.
    {
        // Ground.
        AddObjectToScene( new GameObject( this, "Ground", vec3(0,-0.5f,5), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Ground" ), pResources->GetMaterial( "Ground" ) ) );

        // Target rings.
        AddObjectToScene( new GameObjectTarget( this, "Ring1", vec3(0,0,5), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Ring1" ), pResources->GetMaterial( "VertColor" ) ) );
        AddObjectToScene( new GameObjectTarget( this, "Ring2", vec3(0,0,5), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Ring2" ), pResources->GetMaterial( "VertColor" ) ) );
        AddObjectToScene( new GameObjectTarget( this, "Ring3", vec3(0,0,5), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Ring3" ), pResources->GetMaterial( "VertColor" ) ) );
        AddObjectToScene( new GameObjectTarget( this, "Ring4", vec3(0,0,5), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Ring4" ), pResources->GetMaterial( "VertColor" ) ) );
        AddObjectToScene( new GameObjectTarget( this, "Ring5", vec3(0,0,5), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Ring5" ), pResources->GetMaterial( "VertColor" ) ) );
        AddObjectToScene( new GameObjectTargetBonus( this, "BonusArc", vec3(0,0.5f,5), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "BonusArc" ), pResources->GetMaterial( "VertColor" ) ) );

        // Junk floating in the air.
        for( int i=0; i<600; i++ )
        {
            std::string objectname = "Stuff" + std::to_string( i );
            vec3 pos = vec3( rand()%300-150.0f, rand()%450+20.0f, rand()%300-150.0f );
            float size = (randFromNegativeOneToOne() + 1.0f) / 2.0f;
            AddObjectToScene( new GameObject( this, objectname, pos, vec3(0,0,0), size, pResources->GetMesh( "Sphere" ), pResources->GetMaterial( "Sun" ) ) );
        }

        // Player.
        AddObjectToScene( new GameObjectCactus( this, "Player", vec3(0,0,0), vec3(-180,0,0), vec3(1,1,1), pResources->GetMesh( "Cactus" ), pResources->GetMaterial( "Cactus" ) ) );

        // Score numbers.
        AddObjectToScene( new GameObject( this, "Number1000s", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "NumberQuad" ), pResources->GetMaterial( "Numbers" ) ) );
        AddObjectToScene( new GameObject( this, "Number100s",  vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "NumberQuad" ), pResources->GetMaterial( "Numbers" ) ) );
        AddObjectToScene( new GameObject( this, "Number10s",   vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "NumberQuad" ), pResources->GetMaterial( "Numbers" ) ) );
        AddObjectToScene( new GameObject( this, "Number1s",    vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "NumberQuad" ), pResources->GetMaterial( "Numbers" ) ) );

        // Title.
        AddObjectToScene( new GameObject( this, "Title", vec3(0,3,0), vec3(0,0,0), vec3(1,1,1), pResources->GetMesh( "Title" ), pResources->GetMaterial( "Title" ) ) );

        // Camera.
        CactusCam* pCamera = new CactusCam( this, "Camera", vec3(0,15,0), vec3(0,0,0), vec3(1,1,1) );
        pCamera->SetObjectToFollow( GetGameObjectByName( "Player" ) );
        m_pCamera = pCamera;
    }
}

void SceneCactusFall::Update(float deltaTime)
{
    BaseScene::Update( deltaTime );

    {
        // TODO_CactusFall: Replace the 1234 hardcoded below with some math to display m_Score.
        //                  Must be done with math, no conversions to strings or 10000 if statements.
       

        int frame1000s = 0;
        int frame100s  = 0;
        int frame10s   = 0;
        int frame1s    = 0;

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

        GetGameObjectByName( "Number1000s" )->SetUVScaleAndOffset( vec2( 64.0f/1024.0f, 1.0f ), vec2( frame1000s/16.0f, 0.0f ) );
        GetGameObjectByName( "Number100s"  )->SetUVScaleAndOffset( vec2( 64.0f/1024.0f, 1.0f ), vec2( frame100s/16.0f, 0.0f ) );
        GetGameObjectByName( "Number10s"   )->SetUVScaleAndOffset( vec2( 64.0f/1024.0f, 1.0f ), vec2( frame10s/16.0f, 0.0f ) );
        GetGameObjectByName( "Number1s"    )->SetUVScaleAndOffset( vec2( 64.0f/1024.0f, 1.0f ), vec2( frame1s/16.0f, 0.0f ) );
    }

    bool reset = false;

    if( m_pGame->GetFramework()->WasKeyPressed( 'T' ) )
    {
        m_TestMode = !m_TestMode;
        if( m_TestMode == false )
        {
            reset = true;
        }
        else
        {
            GetGameObjectByName( "Title" )->SetPosition( vec3( 0, 1000000, 0 ) );
            GetGameObjectByName( "Player" )->SetPosition( vec3( 0, 0, 0 ) );
        }
    }

    if( m_pGame->GetFramework()->IsKeyDown( ' ' ) && GetGameObjectByName( "Title" )->GetPosition().y < 10000 )
        reset = true;

    if( reset )
    {
        GetGameObjectByName( "Title" )->SetPosition( vec3( 0, 1000000, 0 ) );
        GetGameObjectByName( "Player" )->SetPosition( vec3( 0, 600, 0 ) );
        m_pCamera->Reset();
        m_Score = 0;
    }

    ImGui::Begin( "Cactus Fall" );
    ImGui::Text( "%0.0f", m_Score );
    ImGui::End();

    ImGui::Begin( "Readme###CactusFall" );
    ImGui::Text( "T: Test mode" );
    ImGui::Text( "Q/E: Rotate the bonus arc" );
    ImGui::Text( "Z/C: Rotate the bonus arc faster" );
    ImGui::End();
}

void SceneCactusFall::Draw()
{
    BaseScene::Draw();
}
