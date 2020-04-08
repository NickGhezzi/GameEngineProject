#ifndef __GameObjectCactus_H__
#define __GameObjectCactus_H__

#include "GameObjects/GameObject.h"

class Material;

class GameObjectCactus : public GameObject
{
protected:
    float m_TargetRotation;
    float m_dis;
    float m_angle;
    float m_angle2;

public:
    GameObjectCactus(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~GameObjectCactus();

    virtual void Update(float deltaTime) override;
    virtual void Draw(Camera* pCamera) override;
};

#endif //__GameObjectCactus_H__
