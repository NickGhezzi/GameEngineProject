#pragma once

#include "GameObject.h"

class Mesh;

class Bin : public GameObject
{
protected:

    ColorType m_Color;
public:
    Bin(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position, ColorType type);
    ~Bin();

    ColorType GetType();

};