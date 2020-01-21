#include "GamePCH.h"

#include "Base/Mesh.h"
#include "Base/VertexFormat.h"
#include "Base/Material.h"

#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"

using namespace fw;

Mesh::Mesh()
{
    m_VBO = 0;

    m_PrimitiveType = -1;
    m_NumVerts = 0;
}
    
Mesh::~Mesh()
{
    glDeleteBuffers( 1, &m_VBO );
}

void Mesh::Init(VertexFormat* pVerts, int numVerts, unsigned int* pIndices, int numIndices, GLenum primitiveType, GLenum usage)
{
    m_NumVerts = numVerts;
    m_NumIndices = numIndices;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*numVerts, pVerts, usage );

    // Generate and fill buffer with our indices.
    if( pIndices )
    {
        glGenBuffers( 1, &m_IBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numIndices, pIndices, usage );
    }
}

void Mesh::Init(VertexFormat* pVerts, unsigned int numVerts, GLenum primitiveType)
{
    Init( pVerts, numVerts, nullptr, 0, primitiveType, GL_STATIC_DRAW );
}

void Mesh::Draw(Camera* pCamera, Material* pMat, vec2 pos)
{
    assert( m_PrimitiveType != -1 );
    assert( m_NumVerts != 0 );

    // Setup attributes.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    GLint locPosition = glGetAttribLocation( pMat->m_pShader->GetProgram(), "a_Position" );
    if( locPosition != -1 )
    {
        glVertexAttribPointer( locPosition, 3, GL_FLOAT, GL_FALSE, 24, (void*)offsetof(VertexFormat, pos));
        glEnableVertexAttribArray( locPosition );
    }

    GLint locColor = glGetAttribLocation(pMat->m_pShader->GetProgram(), "a_Color" );
    if( locColor != -1 )
    {
        glVertexAttribPointer( locColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 24, (void*)offsetof(VertexFormat, color));
        glEnableVertexAttribArray( locColor );
    }

    GLint locUV = glGetAttribLocation(pMat->m_pShader->GetProgram(), "a_UV" );
    if( locUV != -1 )
    {
        glVertexAttribPointer( locUV, 2, GL_FLOAT, GL_FALSE, 24, (void*)offsetof(VertexFormat, uv));
        glEnableVertexAttribArray( locUV );
    }

    // Enable shader and setup uniforms.
    glUseProgram(pMat->m_pShader->GetProgram());

    GLint uWorldMatrix = glGetUniformLocation(pMat->m_pShader->GetProgram(), "u_WorldMatrix" );
    if (uWorldMatrix != -1)
    {
   /*     float mat[16] =
        {
            cos(pos.x), sin(pos.y), 0, 0,
            -sin(pos.y), cos(pos.x), 0, 0,
            0, 0, 1, 0,
            pos.x, pos.y, 0, 1
        };*/

        mat4 mat;
        mat.CreateSRT(vec3(1, 1, 1), vec3(0, 0, 0), vec3(pos.x, pos.y, 0));

        glUniformMatrix4fv(uWorldMatrix, 1, false, &mat.m11);

        //glUniform2f(uWorldMatrix, pos.x, pos.y );
    }



    GLint uViewMatrix = glGetUniformLocation(pMat->m_pShader->GetProgram(), "u_ViewMatrix" );
    if(uViewMatrix != -1 )
    {
        mat4 mat;
        mat.CreateLookAtViewLeftHanded(vec3(0, 0, -15), vec3(0, 1, 0), vec3(0, 0, 0));
       // mat.CreateSRT(vec3(1, 1, 1), vec3(0, 0, 0), vec3(-pCamera->GetPosition().x, -pCamera->GetPosition().y, 0));

        glUniformMatrix4fv(uViewMatrix, 1, false, &mat.m11);
        //glUniform2f( uCameraTranslation, -pCamera->GetPosition().x, -pCamera->GetPosition().y );
    }

    GLint uProjectionMat = glGetUniformLocation(pMat->m_pShader->GetProgram(), "u_ProjectionMatrix" );
    if(uProjectionMat != -1 )
    {
        mat4 projMatrix;
        //projMatrix.CreateOrtho(-5, -5, -5, 5, 0, 100);
        projMatrix.CreatePerspectiveVFoV(45, 1, 0.01, 100);

        glUniformMatrix4fv(uProjectionMat, 1, false, &projMatrix.m11);
        //glUniform2f( uProjectionScale, pCamera->GetProjectionScale().x, pCamera->GetProjectionScale().y );
    }

    // Setup the texture.
    int textureUnit = 0;
    glActiveTexture( GL_TEXTURE0 + textureUnit );
    glBindTexture( GL_TEXTURE_2D, pMat->m_pTexture->GetTextureID() );
    GLint uTexture = glGetUniformLocation(pMat->m_pShader->GetProgram(), "u_Texture" );
    if( uTexture != -1 )
    {
        glUniform1i( uTexture, textureUnit );
    }

    // Draw.
    if( m_NumIndices == 0 )
    {
        glDrawArrays( m_PrimitiveType, 0, m_NumVerts );   
    }
    else
    {
        glDrawElements( m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, nullptr );
    }
}

void Mesh::CreateBox(vec2 size, vec2 offset)
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
    assert( m_VBO == 0 );

    //-z towards camera

    VertexFormat vertexAttributes[] =
    {
        VertexFormat( vec2( -size.x/2, -size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 0.0f, 0.0f ) ),
        VertexFormat( vec2( -size.x/2,  size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 0.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2,  size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 1.0f, 1.0f ) ),
        VertexFormat( vec2(  size.x/2, -size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 1.0f, 0.0f ) ),
    };

    unsigned int indices[6] = { 0,2,1, 0,3,2 };

    Init( vertexAttributes, 4, indices, 6, GL_TRIANGLES, GL_STATIC_DRAW );
}
void Mesh::CreateCube(vec3 size, vec3 offset)
{
    assert(m_VBO == 0);

    
             //         _.-+.
             //    _.-""     '.
             //+:""            '.
             //J \               '.
             // L \             _.-+
             // |  '.       _.-"   |
             // J    \  _.-"       L
             //  L    +"          J
             //  +    |           |
             //   \   |          .+
             //    \  |       .-'
             //     \ |    .-'
             //      \| .-'
             //       +'   

    VertexFormat vertexAttributes[] =
    {
        //front face
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)), //bottom left
        VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)), //top left
        VertexFormat(vec3( size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)), //top right
        VertexFormat(vec3( size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)), //bottom right 

        //right face
        VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),

        //back face
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),

        //top face
        VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),

        //left face
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),

        //bottom face
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
        VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)),
    };
}
;
