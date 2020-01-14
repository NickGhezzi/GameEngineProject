#include "GamePCH.h"

#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "BaseScene.h"

using namespace fw;

Camera::Camera(BaseScene* m_pScene, vec2 position, vec2 projectionScale)
: GameObject(m_pScene, nullptr, nullptr, 0, position )
, m_ProjectionScale( projectionScale )
{
}
    
Camera::~Camera()
{
}
