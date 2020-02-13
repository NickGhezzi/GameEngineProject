#include "GamePCH.h"
#include "SceneWater.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "ResourceManager.h"

SceneWater::SceneWater(Game* game):
    BaseScene(game)
{
    m_pCamera = nullptr;
    m_pWater = nullptr;
}

SceneWater::~SceneWater()
{
    delete m_pCamera;
    delete m_pWater;
    delete m_pPhysicsWorld;
}

void SceneWater::Init()
{
    m_pResources = m_pGame->GetResourceManager();

    m_pWater = new Player(this, m_pResources->GetMesh("Plane"), m_pResources->GetMaterial("Water"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(-25, -25, 0), 0, m_pGame->m_pController);
    m_pWater->CreateBody(true);
    m_pWater->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);

    ViewProperties view = ViewProperties(vec3(0, 15, -15), vec3(0, 1, 0), vec3(0, 0, 22.0));
    ProjectionProperties proj = ProjectionProperties(45, 1, 0.01, 100);

    m_pCamera = new Camera(this, vec3(0, 0, 0), vec2(1 / 5.0f, 1 / 5.0f));
    m_pCamera->Init(view, proj);
}

void SceneWater::Update(float deltaTime)
{
    m_pPhysicsWorld->Update(deltaTime);
    m_pWater->Update(deltaTime);
    m_pCamera->Update(deltaTime);
}

void SceneWater::Draw()
{
    m_pWater->Draw(m_pCamera);
}

void SceneWater::LoadFromFile(const char* filename)
{
}
