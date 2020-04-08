#ifndef __GameEvent_H__
#define __GameEvent_H__

#include "../../Libraries/Framework/Source/Events/Event.h"

class GameObject;

class RemoveFromSceneEvent : public fw::Event
{
protected:
    GameObject* m_pGameObject;

public:
    RemoveFromSceneEvent(GameObject* pGameObject)
    {
        m_pGameObject = pGameObject;
    }

    virtual std::string GetType() override { return "RemoveFromSceneEvent"; }

    GameObject* GetGameObject() { return m_pGameObject; }
};

#endif //__GameEvent_H__
