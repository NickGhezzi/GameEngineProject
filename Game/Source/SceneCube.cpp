#include "GamePCH.h"
#include "SceneCube.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "ResourceManager.h"


SceneCube::SceneCube(Game* game):
    BaseScene(game)
{
    m_pCamera = nullptr;
    m_pPlayer = nullptr;
}

SceneCube::~SceneCube()
{
    delete m_pCamera;
    delete m_pPlayer;
}

void SceneCube::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_pPlayer = new Player(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("PlayerMaterial"), vec2(0, 0), 0, m_pGame->m_pController);
    m_pCamera = new Camera(this, vec2(0, 0), vec2(1 / 5.0f, 1 / 5.0f));
}

void SceneCube::Update(float deltaTime)
{
    m_pPlayer->Update(deltaTime);
    m_pCamera->Update(deltaTime);
}

void SceneCube::Draw()
{
    m_pPlayer->Draw(m_pCamera);
}