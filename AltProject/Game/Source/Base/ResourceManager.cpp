#include "GamePCH.h"

#include "ResourceManager.h"
#include "Base/Mesh.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for( auto object: m_pMeshes )
        delete object.second;

    for( auto object: m_pShaders )
        delete object.second;

    for( auto object: m_pTextures )
        delete object.second;

    for( auto object: m_pMaterials )
        delete object.second;
}
