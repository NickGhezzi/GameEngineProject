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

public:
    Player(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 position, int playerNum, PlayerController* pController);
    ~Player();

    virtual void Update(float deltaTime);
};

#endif //__Player_H__
