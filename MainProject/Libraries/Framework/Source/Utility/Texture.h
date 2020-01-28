#ifndef __Texture_H__
#define __Texture_H__

namespace fw
{
    class Texture
    {
    protected:
        GLuint m_TextureID;

    public:
        Texture(const char* filename);
        virtual ~Texture();

        GLuint GetTextureID() { return m_TextureID; }
    };
};

#endif //__Texture_H__
