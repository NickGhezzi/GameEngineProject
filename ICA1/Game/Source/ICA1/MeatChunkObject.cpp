#include "GamePCH.h"

#include "MeatChunkObject.h"
#include "Game.h"
#include "Base/ObjectPool.h"
#include "Events/GameEvents.h"
#include "Scenes/BaseScene.h"

MeatChunkObject::MeatChunkObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
: GameObject( pScene, name, pos, rot, scale, pMesh, pShader, pTexture )
{
}

MeatChunkObject::~MeatChunkObject()
{
}

void MeatChunkObject::Reset()
{
    GameObject::Reset();

    RemoveFromSceneEvent* pEvent = new RemoveFromSceneEvent( this );
    m_pScene->GetGame()->GetFramework()->GetEventManager()->AddEventToQueue( pEvent );
}
