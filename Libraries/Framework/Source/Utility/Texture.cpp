#include "FrameworkPCH.h"

#include "Texture.h"

namespace fw
{
    Texture::Texture(const char* filename)
    {
        m_TextureID = LoadTexture( filename );
    }

    Texture::~Texture()
    {
        glDeleteTextures( 1, &m_TextureID );
    }
}
