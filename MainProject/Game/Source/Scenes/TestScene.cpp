#include "GamePCH.h"
#include "TestScene.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "ResourceManager.h"

TestScene::TestScene(Game* game) :
    BaseScene(game)
{
    m_pCamera = nullptr;
    m_pPlayer = nullptr;
    m_pFloor = nullptr;
}

TestScene::~TestScene()
{
    delete m_pCamera;
    delete m_pPlayer;
    delete m_pFloor;
}

void TestScene::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_pPlayer = new Player(this, m_pResources->GetMesh("Cube"), m_pResources->GetMaterial("Dice"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0), 0, m_pGame->m_pController);
    m_pPlayer->CreateBody(true);
    m_pPlayer->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    m_pFloor = new GameObject(this, m_pResources->GetMesh("FloorMesh"), m_pResources->GetMaterial("Ground"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(5, 0, 0));
    m_pFloor->CreateBody(false);
    m_pFloor->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    m_pPlayer->AddJoint(m_pFloor, vec2(0, 0));
    m_pCamera = new Camera(this, vec3(0, 0, 0), vec2(1 / 5.0f, 1 / 5.0f));
}

void TestScene::Update(float deltaTime)
{
    m_pPhysicsWorld->Update(deltaTime);

    m_pPlayer->Update(deltaTime);
    m_pFloor->Update(deltaTime);
    m_pCamera->Update(deltaTime);
}

void TestScene::Draw()
{
    m_pPlayer->Draw(m_pCamera);
    m_pFloor->Draw(m_pCamera);
    m_pCamera->Draw(m_pCamera);
}

void TestScene::LoadFromFile(const char* filename)
{

}
