#pragma once
#include "GameObject.h"
class Mesh;

class MovingPlatform : public GameObject
{
protected:

    bool m_IsTouching;
    vec3 m_StartingPos;
public:
    MovingPlatform(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position);
    ~MovingPlatform();

    void SetIsTouching(bool istouching);

    void Update(float deltaTime) override;
};