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
    public:
        CollisionEvent(CollisionEventType type, void* a, void* b )
        {
            m_CollisionEventType = type;
        }

        virtual std::string GetType() { return "CollisionEvent"; }

        CollisionEventType GetGameEventType() { return m_CollisionEventType; }

    };
}