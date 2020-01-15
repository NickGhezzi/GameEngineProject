#ifndef __Player_H__
#define __Player_H__

#include "GameObject.h"

class Mesh;
class PlayerController;

class Player : public GameObject
{
protected:
    PlayerController* m_pController;
    fw::PhysicsBody* m_pPhysicsBody;

    int m_PlayerNumber;

public:
    Player(BaseScene* m_pScene, Mesh* pMesh, Material* pMat, vec2 position, int playerNum, PlayerController* pController);
    ~Player();

    virtual void Update(float deltaTime);
};

#endif //__Player_H__
