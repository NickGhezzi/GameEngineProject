#ifndef __Camera_H__
#define __Camera_H__

#include "GameObject.h"

class Game;

class Camera : public GameObject
{
protected:
    mat4 m_ViewMat;
    mat4 m_ProjMat;

public:
    Camera(BaseScene* pScene, vec3 position);
    ~Camera();

    mat4* GetView() { return &m_ViewMat; }
    mat4* GetProj() { return &m_ProjMat; }

    void Update(float deltaTime);
};

#endif //__Camera_H__
