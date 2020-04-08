#include "GamePCH.h"

#include "GameObjectTarget.h"

GameObjectTarget::GameObjectTarget(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
}

GameObjectTarget::~GameObjectTarget()
{
}

void GameObjectTarget::Update(float deltaTime)
{
    GameObject::Update( deltaTime );
}

void GameObjectTarget::Draw(Camera* pCamera)
{
    GameObject::Draw( pCamera );
}
