#ifndef __PlayerController_H__
#define __PlayerController_H__

class PlayerController
{
    friend class Player;

protected:
    int m_OldFlags;
    int m_Flags;

public:
    enum InputFlags
    {
        Up      = 0x01,
        Down    = 0x02,
        Right   = 0x04,
        Left    = 0x08,
        Action  = 0x10,
    };

    PlayerController();
    ~PlayerController();

    void OnEvent(fw::Event* pEvent);

    void StoreOldFlags() { m_OldFlags = m_Flags; }

    bool IsUpHeld()     { return m_Flags & InputFlags::Up; }
    bool IsDownHeld()   { return m_Flags & InputFlags::Down; }
    bool IsLeftHeld()   { return m_Flags & InputFlags::Left; }
    bool IsRightHeld()  { return m_Flags & InputFlags::Right; }
    bool IsActionHeld() { return m_Flags & InputFlags::Action; }

    bool WasActionPressed() { return (m_OldFlags & InputFlags::Action) == 0 &&
                                     (m_Flags & InputFlags::Action) != 0; }
    bool WasActionReleased() { return m_Flags & InputFlags::Action; }
};

#endif //__PlayerController_H__
