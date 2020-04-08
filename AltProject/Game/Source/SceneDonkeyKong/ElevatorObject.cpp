#include "GamePCH.h"

#include "ElevatorObject.h"

#include "Scenes/BaseScene.h"

ElevatorObject::ElevatorObject(BaseScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_Sensor = nullptr;
}

ElevatorObject::~ElevatorObject()
{
    delete m_Sensor;
}

void ElevatorObject::Reset()
{
    // TODO_DonkeyKong: Turn off the motor on the joint.
    m_pBody->EnableMotor(false);
}

void ElevatorObject::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    if( m_pBody == nullptr )
        return;
    
}

void ElevatorObject::CreateJointAndSensor()
{
    // TODO_DonkeyKong: Create a prismatic joint that extends from (0 to 1 on the y axis).
    //        Also create a sensor for the elevator.
    //        When the player enters the sensor, enable a motor on the joint to move the elevator up.
    m_Sensor = new GameObject(m_pScene, "ElevatorSensor", m_Position, vec3(0, 0, 0), vec3(1, 1, 1), nullptr, nullptr);
    m_Sensor->CreateBody(false);
    uint16* mask[] = { new uint16(PhysicsCategory_Player) };
    m_Sensor->GetBody()->AddBox(vec2(2, 1.2), 1, true, 1, PhysicsCategory_Environment, mask);
    delete mask[0];

    m_pBody->AddPrismaticJoint(m_Sensor->GetBody(), 1, 0, 1000, 20);
    m_pBody->EnableMotor(false);
}

void ElevatorObject::EnableMotor()
{
    // TODO_DonkeyKong: Turn on the motor on the joint.
    m_pBody->EnableMotor(true);
}

