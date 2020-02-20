#include "GamePCH.h"

#include "ShakeCameraObject.h"
#include "GameObjects/Camera.h"

ShakeCameraObject::ShakeCameraObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
    : Camera(pScene, pos)
{
    m_InitialPosition = m_Position;
    m_ShakeTimer = 0.2;
    m_bisShaking = false;
}

ShakeCameraObject::~ShakeCameraObject()
{

}

void ShakeCameraObject::Shake()
{
    m_bisShaking = true;
}

void ShakeCameraObject::Update(float deltaTime)
{
    Camera::Update(deltaTime);

    // TODO_ICA1: Make the camera shake.
    //            Make sure the camera doesn't drift. i.e. Don't change the position, add offsets to it.

    if (m_bisShaking == true && m_ShakeTimer > 0)
    {
        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        m_ViewMat.CreateSRT(vec3(1), vec3(x, y, 0), m_Position);
        m_ViewMat.Inverse();
        m_ShakeTimer -= deltaTime;

    }
    else
    {
        m_ViewMat.CreateSRT(vec3(1), vec3(0), m_Position);
        m_ViewMat.Inverse();
        m_ShakeTimer = 0.2;
        m_bisShaking = false;
    }
    // Set up view matrix.
}
