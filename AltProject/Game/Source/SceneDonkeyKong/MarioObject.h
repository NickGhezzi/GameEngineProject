#ifndef __MarioObject_H__
#define __MarioObject_H__

#include "GameObjects/Player.h"

class ResourceManager;

class MarioObject : public Player
{
protected:
    bool m_Dead;
    bool m_IsWalking;
    bool m_CanJump;
    bool m_IsRight;
    bool m_Switched;
    bool m_IsInvincible;
    bool m_HasWon;
    
    float m_InvincibleTimeLeft;
    float m_WalkTimer;

    int m_Score;
    
    ResourceManager* m_pResourceManager;
public:
    MarioObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, ResourceManager* pResourceManager);
    virtual ~MarioObject();

    virtual void Reset();

    virtual void Update(float deltaTime);

    virtual void OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal);

    void SetDead(bool dead);

    int GetScore();

    bool GetHasWon();
};

#endif //__MarioObject_H__
