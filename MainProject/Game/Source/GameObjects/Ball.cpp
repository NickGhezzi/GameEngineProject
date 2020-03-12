#include "GamePCH.h"
#include "Ball.h"

Ball::Ball(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position, ColorType type)
    : GameObject(m_pScene, pMesh, pMat, scale, rotation, position),
    m_Color(type)
{
    m_Name = "Ball";
}

Ball::~Ball()
{
}

ColorType Ball::GetType()
{
    return m_Color;
}
