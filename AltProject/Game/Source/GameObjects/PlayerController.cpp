#include "GamePCH.h"

#include "PlayerController.h"

using namespace fw;

PlayerController::PlayerController()
{
    m_OldFlags = 0;
    m_Flags = 0;
}

PlayerController::~PlayerController()
{
}

void PlayerController::OnEvent(fw::Event* pEvent)
{
    //unsigned char keys[2][4] = { { 'W', 'S', 'A', 'D' }, { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT } };

    if( pEvent->GetType() == "InputEvent" )
    {
        InputEvent* pIE = (InputEvent*)pEvent;

        if( pIE->GetState() == InputState::Pressed )
        {
            if( pIE->GetKeyCode() == 'W' ) m_Flags |= Up;
            if( pIE->GetKeyCode() == 'S' ) m_Flags |= Down;
            if( pIE->GetKeyCode() == 'A' ) m_Flags |= Left;
            if( pIE->GetKeyCode() == 'D' ) m_Flags |= Right;
            if( pIE->GetKeyCode() == ' ' ) m_Flags |= Action;
        }

        if( pIE->GetState() == InputState::Released )
        {
            if( pIE->GetKeyCode() == 'W' ) m_Flags &= ~Up;
            if( pIE->GetKeyCode() == 'S' ) m_Flags &= ~Down;
            if( pIE->GetKeyCode() == 'A' ) m_Flags &= ~Left;
            if( pIE->GetKeyCode() == 'D' ) m_Flags &= ~Right;
            if( pIE->GetKeyCode() == ' ' ) m_Flags &= ~Action;
        }
    }
}
