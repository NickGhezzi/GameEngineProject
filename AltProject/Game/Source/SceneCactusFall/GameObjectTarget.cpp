#include "GamePCH.h"

#include "GameObjectTarget.h"
#include "Base/Mesh.h"

GameObjectTarget::GameObjectTarget(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_Color = vec3(0, 0, 0);
}

GameObjectTarget::~GameObjectTarget()
{
}

void GameObjectTarget::Update(float deltaTime)
{
    m_Color = vec3(0, 0, 0);
    GameObject::Update( deltaTime );
}

void GameObjectTarget::Draw(Camera* pCamera)
{
    if (m_pMesh != nullptr)
    {
        mat4 worldMatrix;
        worldMatrix.CreateSRT(m_Scale, m_Rotation, m_Position);

        m_pMesh->SetupAttributes(m_pMaterial);
        m_pMesh->SetupUniforms(m_pMaterial, &worldMatrix, pCamera, m_UVScale, m_UVOffset, m_Color);
        m_pMesh->Draw(m_pMaterial);
    }
}

void GameObjectTarget::Reset()
{
    GameObject::Reset();

    m_Color = vec3(0, 0, 0);
}

void GameObjectTarget::SetColor(vec3 color)
{
    m_Color = color;
}
