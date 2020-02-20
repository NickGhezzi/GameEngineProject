#include "GamePCH.h"

#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "Game.h"

using namespace fw;

Camera::Camera(BaseScene* pScene, vec3 position)
: GameObject( pScene, "Camera", position, 0, 0, nullptr, nullptr, nullptr )
{
}
    
Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
    //ImGui::Begin("Camera Controls");

    //ImGui::Text("Testing output");
    ////ImGui::Text("Position: %f, %f", m_Position.x, m_Position.y);
    //ImGui::DragFloat3("Position", &m_Position.x, 0.1f);

    //ImGui::End();

    m_ViewMat.CreateLookAtViewLeftHanded( m_Position, vec3(0,1,0), vec3(0) );
    m_ProjMat.CreatePerspectiveVFoV( 45.0f, 1.0f, 0.01f, 100.0f );
}
