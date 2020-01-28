#include "GamePCH.h"
#include "Game.h"

using namespace fw;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Framework* pFramework = new Framework();
    GameCore* pGame = new Game( pFramework );
    
    pFramework->Init( 600, 600 );
    pFramework->Run( pGame );
    pFramework->Shutdown();

    delete pGame;
    delete pFramework;

    MyMemory_ValidateAllocations( true );
}
