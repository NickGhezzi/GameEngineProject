#ifndef __Game_H__
#define __Game_H__

class Ball;
class Camera;
class GameObject;
class ImGuiManager;
class Mesh;
class Player;
class PlayerController;

class Game : public fw::GameCore
{
protected:
    ImGuiManager* m_pImGuiManager;

    fw::ShaderProgram* m_pShaderTexture;
    Mesh* m_pMeshBox;
    fw::Texture* m_pTexture;

    Player* m_pPlayer;
    Camera* m_pCamera;

    PlayerController* m_pController;

public:
    Game(fw::Framework* pFramework);
    virtual ~Game();

    virtual void Init() override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__Game_H__
