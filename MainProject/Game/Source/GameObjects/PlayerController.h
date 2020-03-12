#ifndef __PlayerController_H__
#define __PlayerController_H__

class PlayerController
{
    friend class Player;
    friend class Peg;

protected:
    bool m_Up;
    bool m_Down;
    bool m_Left;
    bool m_Right;
    bool m_Action;

public:
    PlayerController();
    ~PlayerController();

    void OnEvent(fw::Event* pEvent);
};

#endif //__PlayerController_H__
