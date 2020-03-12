#include "GamePCH.h"
#include "Launcher.h"

Launcher::Launcher(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position):
    GameObject(m_pScene, pMesh, pMat, scale, rotation, position)
{
    m_IsTouching = false;
    m_Name = "Launcher";
}

Launcher::~Launcher()
{
}

void Launcher::SetIsTouching(bool istouching)
{
    m_IsTouching = istouching;
}

void Launcher::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    if (m_IsTouching == true)
    {
        m_pPhysicsBody->ApplyTorque(100000);
        m_IsTouching = false;
    }

}
