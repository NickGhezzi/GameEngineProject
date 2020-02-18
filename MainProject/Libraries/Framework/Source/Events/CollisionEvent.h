#pragma once

#include "Event.h"

namespace fw
{
    enum class CollisionEventType
    {
        OnHit,
    };

    class CollisionEvent : public Event
    {
    protected:
        CollisionEventType m_CollisionEventType;

        void* BodyA;
        void* BodyB;
        Vector2 Normal;
    public:
        CollisionEvent(CollisionEventType type, void* a, void* b, Vector2 normal )
        {
            m_CollisionEventType = type;
            BodyA = a;
            BodyB = b;
            Normal = normal;
        }

        virtual std::string GetType() { return "CollisionEvent"; }

        CollisionEventType GetGameEventType() { return m_CollisionEventType; }

        void* GetBodyA()
        {
            return BodyA;
        }

        void* GetBodyB()
        {
            return BodyB;
        }

        Vector2 GetHitNormal()
        {
            return Normal;
        }

    };
}