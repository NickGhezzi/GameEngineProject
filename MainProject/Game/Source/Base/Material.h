#pragma once


class Material
{
public:
    Material(fw::ShaderProgram* pshader, fw::Texture* ptexture);

    fw::ShaderProgram* m_pShader;
    fw::Texture* m_pTexture;
};