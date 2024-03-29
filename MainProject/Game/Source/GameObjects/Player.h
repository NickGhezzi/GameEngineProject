#ifndef __Player_H__
#define __Player_H__

#include "GameObject.h"

class Mesh;
class PlayerController;

class Player : public GameObject
{
protected:
    PlayerController* m_pController;
    
    int m_PlayerNumber;
    bool bPressed;
public:
    Player(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec3 scale, vec3 rotation, vec3 position, int playerNum, PlayerController* pController);
    ~Player();

    virtual void Update(float deltaTime) override;

    bool bLockToX;
    bool bLockControlls;
    bool bIsActionPressed;
};

#endif //__Player_H__
