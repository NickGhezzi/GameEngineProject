#include "GamePCH.h"

#include "SheepTitleCard.h"

SheepTitleCard::SheepTitleCard(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
: GameObject( pScene, name, pos, rot, scale, pMesh, pShader, pTexture )
{
    m_TimeAlive = 0;
}

SheepTitleCard::~SheepTitleCard()
{
}

void SheepTitleCard::Reset()
{
    GameObject::Reset();

    m_TimeAlive = 0;
}

void SheepTitleCard::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    m_TimeAlive += deltaTime;

    if( m_TimeAlive > 0.5 )
        m_Position.y += deltaTime*4;
}

void SheepTitleCard::Display()
{
    m_Position.y = 3;
    m_TimeAlive = 0;
}
