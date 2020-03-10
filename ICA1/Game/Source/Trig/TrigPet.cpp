#include "GamePCH.h"
#include "TrigPet.h"

TrigPet::TrigPet(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
: GameObject( pScene, name, pos, rot, scale, pMesh, pShader, pTexture )
{
    m_pObjectWeAreFollowing = nullptr;
}

TrigPet::~TrigPet()
{
}

void TrigPet::Update(float deltatime)
{
    GameObject::Update( deltatime );

    if( m_pObjectWeAreFollowing == nullptr )
        return;
}

void TrigPet::SetObjectToFollow(GameObject* pObject)
{
    m_pObjectWeAreFollowing = pObject;
}
