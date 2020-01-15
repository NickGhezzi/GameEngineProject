#include "GamePCH.h"
#include "Material.h"

Material::Material(fw::ShaderProgram* pshader, fw::Texture* ptexture)
{
    m_pShader = pshader;
    m_pTexture = ptexture;
}


