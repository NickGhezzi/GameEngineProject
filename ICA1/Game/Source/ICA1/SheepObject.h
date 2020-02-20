#ifndef __SheepObject_H__
#define __SheepObject_H__

#include "GameObjects/GameObject.h"

class PlayerController;

class SheepObject : public GameObject
{
protected:
    bool m_CanJump;
    bool m_IsDead;

    PlayerController* m_pController;

public:
    SheepObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
    virtual ~SheepObject();

    virtual void Reset();
    void SetController(PlayerController* pController);

    virtual void Update(float deltaTime);

    void Die();
    virtual void OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal) override;
};

#endif //__SheepObject_H__
