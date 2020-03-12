#include "GamePCH.h"
#include "Bin.h"

Bin::Bin(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position, ColorType type):
GameObject(m_pScene, pMesh, pMat, scale, rotation, position),
m_Color(type)
{
    m_Name = "Bin";
}

Bin::~Bin()
{
}
