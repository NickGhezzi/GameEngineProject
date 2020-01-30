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

    m_ViewProperties.at = vec3(0, 0, -15);
    m_ViewProperties.eye = vec3(0, 1, 0);
    m_ViewProperties.up = vec3(0, 0, 0);

    m_ProjectionProperties.aspect = 1;
    m_ProjectionProperties.farzy = 100;
    m_ProjectionProperties.fov = 45;
    m_ProjectionProperties.nearzy = 0.01;
    
}
    
Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
    m_ViewMatrix.CreateLookAtViewLeftHanded(m_ViewProperties.at, m_ViewProperties.eye, m_ViewProperties.up);
    m_ProjectionMatrix.CreatePerspectiveVFoV(m_ProjectionProperties.fov, m_ProjectionProperties.aspect, m_ProjectionProperties.nearzy, m_ProjectionProperties.farzy);

}

mat4 Camera::GetProjectionMatrix()
{
    return m_ProjectionMatrix;
}

mat4 Camera::GetViewMatrix()
{
    return m_ViewMatrix;
}

mat4 Camera::GetWorldMatrix()
{
    return m_WorldMatrix;
}

void Camera::Init(ViewProperties view, ProjectionProperties proj)
{
    m_ViewProperties.at = view.at;
    m_ViewProperties.eye = view.eye;
    m_ViewProperties.up = view.up;

    m_ProjectionProperties.aspect = proj.aspect;
    m_ProjectionProperties.farzy = proj.farzy;
    m_ProjectionProperties.fov = proj.fov;
    m_ProjectionProperties.nearzy = proj.nearzy;

   
}

