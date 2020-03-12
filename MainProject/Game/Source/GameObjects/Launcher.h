#pragma once
#include "GameObject.h"
class Mesh;

class Launcher : public GameObject
{
protected:

    bool m_IsTouching;
  
public:
    Launcher(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position);
    ~Launcher();

    void SetIsTouching(bool istouching);

    void Update(float deltaTime) override;
};