#ifndef __GameObjectTarget_H__
#define __GameObjectTarget_H__

#include "GameObjects/GameObject.h"

class GameObjectTarget : public GameObject
{
protected:
    vec3 m_Color;
public:
    GameObjectTarget(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~GameObjectTarget();

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera) override;
    virtual void Reset() override;


    void SetColor(vec3 color);
};

#endif //__GameObjectTarget_H__
