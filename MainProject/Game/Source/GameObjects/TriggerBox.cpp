#include "GamePCH.h"
#include "TriggerBox.h"

TriggerBox::TriggerBox(BaseScene* m_pScene, vec3 scale, vec3 rotation, vec3 position)
    : GameObject(m_pScene, nullptr, nullptr, scale, rotation, position)
{
    m_Name = "TriggerBox";
}

TriggerBox::~TriggerBox()
{
}
