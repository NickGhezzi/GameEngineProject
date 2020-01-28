#ifndef __InputEvent_H__
#define __InputEvent_H__

#include "Event.h"

namespace fw
{
    enum class InputState
    {
        Pressed,
        Released,
    };

    class InputEvent : public Event
    {
    protected:
        InputState m_State;
        int m_KeyCode;

    public:
        InputEvent(InputState state, int keyCode)
        {
            m_State = state;
            m_KeyCode = keyCode;
        }

        virtual std::string GetType() { return "InputEvent"; }

        InputState GetState() { return m_State; }
        int GetKeyCode() { return m_KeyCode; };
    };

} // namespace fw

#endif //__InputEvent_H__
