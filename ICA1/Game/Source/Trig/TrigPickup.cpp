#include "GamePCH.h"
#include "TrigPickup.h"

TrigPickup::TrigPickup(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
: GameObject( pScene, name, pos, rot, scale, pMesh, pShader, pTexture )
{
}

TrigPickup::~TrigPickup()
{
}

void TrigPickup::Update(float deltaTime)
{
    GameObject::Update( deltaTime );
}
