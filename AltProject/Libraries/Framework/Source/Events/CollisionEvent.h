#ifndef __CollisionEvent_H__
#define __CollisionEvent_H__

#include "Event.h"

namespace fw
{
    class CollisionEvent : public Event
    {
    protected:
        void* m_pObjectA;
        void* m_pObjectB;
        Vector3 m_Position;
        Vector3 m_Normal;

    public:
        CollisionEvent(void* pObjectA, void* pObjectB, Vector3 position, Vector3 normal)
        {
            m_pObjectA = pObjectA;
            m_pObjectB = pObjectB;
            m_Position = position;
            m_Normal = normal;
        }

        virtual std::string GetType() override { return "CollisionEvent"; }

        void* GetObjectA()    { return m_pObjectA; }
        void* GetObjectB()    { return m_pObjectB; }
        Vector3 GetPosition() { return m_Position; }
        Vector3 GetNormal()   { return m_Normal; }
    };

} // namespace fw

#endif //__CollisionEvent_H__
