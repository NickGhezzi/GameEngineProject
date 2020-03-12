#pragma once

#include "GameObject.h"

class Mesh;
class PlayerController;

class Peg : public GameObject
{
protected:
    PlayerController* m_pController;

    float m_AngleMin;
    float m_AngleMax;
    bool m_bIsActionPressed;
    bool m_bHasbeenpressed;
public:
    Peg(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position, PlayerController* pController);
    ~Peg();

    virtual void Update(float deltaTime) override;

};