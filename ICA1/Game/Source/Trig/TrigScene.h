#ifndef __TrigScene_H__
#define __TrigScene_H__

#include "Scenes/BaseScene.h"

class TrigPickup;

class TrigScene : public BaseScene
{
protected:
    std::vector<TrigPickup*> m_Pickups;

    GameObject* m_pHUDObject;
    Camera* m_pHUDCamera;
public:
    TrigScene(Game* pGame);
    virtual ~TrigScene();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    std::vector<TrigPickup*>& GetPickups() { return m_Pickups; }
};

#endif //__TrigScene_H__
