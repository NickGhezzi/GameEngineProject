#ifndef __ShakeCameraObject_H__
#define __ShakeCameraObject_H__

#include "GameObjects/Camera.h"

class ShakeCameraObject : public Camera
{
protected:

public:
    ShakeCameraObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    virtual ~ShakeCameraObject();

    virtual void Update(float deltaTime);

    void Shake();

    float m_ShakeTimer;

    bool m_bisShaking;
};

#endif //__ShakeCameraObject_H__
