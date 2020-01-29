#include "GamePCH.h"

#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "../Scenes/BaseScene.h"

using namespace fw;

Camera::Camera(BaseScene* m_pScene, vec3 position, vec2 projectionScale)
: GameObject(m_pScene, nullptr, 0, vec3(1,1,1), vec3(0,0,0), position )
, m_ProjectionScale( projectionScale )
{
    //delete m_pPhysicsBody;
    m_pPhysicsBody = nullptr;
}
    
Camera::~Camera()
{
}

