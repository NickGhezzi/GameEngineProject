#include "GamePCH.h"

#include "MeteorObject.h"
#include "Game.h"
#include "Base/ObjectPool.h"
#include "Events/GameEvents.h"
#include "Scenes/BaseScene.h"
#include "ICA1/ShakeCameraObject.h"

MeteorObject::MeteorObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
: GameObject( pScene, name, pos, rot, scale, pMesh, pShader, pTexture )
{
    m_Name = "Meteor";
}

MeteorObject::~MeteorObject()
{
}

void MeteorObject::Reset()
{
    GameObject::Reset();

    RemoveFromSceneEvent* pEvent = new RemoveFromSceneEvent( this );
    m_pScene->GetGame()->GetFramework()->GetEventManager()->AddEventToQueue( pEvent );
}

void MeteorObject::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    if( m_Position.y < -10 )
    {
        Reset();
    }
}

void MeteorObject::OnCollision(GameObject* pOtherGameObject, vec3 worldPosition, vec3 worldNormal)
{
    GameObject::OnCollision( pOtherGameObject, worldPosition, worldNormal );

    ((ShakeCameraObject*)m_pScene->GetCamera())->Shake();
    Reset();
}
