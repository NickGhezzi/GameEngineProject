#pragma once
#include "GameObject.h"

class Mesh;

class Ball : public GameObject
{
protected:

    ColorType m_Color;
public:
    Ball(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position, ColorType type);
    ~Ball();

};