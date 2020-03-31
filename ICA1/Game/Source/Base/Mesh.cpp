#include "GamePCH.h"

#include "Base/Mesh.h"
#include "Base/VertexFormat.h"
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

void SetUniformMatrix(ShaderProgram* pShader, char* name, mat4* pMat)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    if( location != -1 )
    {
        glUniformMatrix4fv( location, 1, false, &pMat->m11 );
    }
}

void Mesh::Draw(Camera* pCamera, ShaderProgram* pShader, mat4* worldMat, fw::Texture* pTexture, vec3 lightcolor)
{
    assert( m_PrimitiveType != -1 );
    assert( m_NumVerts != 0 );

    // Setup attributes.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    GLint locPosition = glGetAttribLocation( pShader->GetProgram(), "a_Position" );
    if( locPosition != -1 )
    {
        glVertexAttribPointer( locPosition, 3, GL_FLOAT, GL_FALSE, 36, (void*)0 );
        glEnableVertexAttribArray( locPosition );
    }

    GLint locColor = glGetAttribLocation( pShader->GetProgram(), "a_Color" );
    if( locColor != -1 )
    {
        glVertexAttribPointer( locColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 36, (void*)12 );
        glEnableVertexAttribArray( locColor );
    }

    GLint locUV = glGetAttribLocation( pShader->GetProgram(), "a_UV" );
    if( locUV != -1 )
    {
        glVertexAttribPointer( locUV, 2, GL_FLOAT, GL_FALSE, 36, (void*)16 );
        glEnableVertexAttribArray( locUV );
    }

    GLint locNormal = glGetAttribLocation(pShader->GetProgram(), "a_Normal");
    if (locNormal != -1)
    {
        glVertexAttribPointer(locNormal, 3, GL_FLOAT, GL_FALSE, 36, (void*)24);
        glEnableVertexAttribArray(locNormal);
    }


    // Enable shader and setup uniforms.
    glUseProgram( pShader->GetProgram() );

    SetUniformMatrix( pShader, "u_WorldMat", worldMat );
    SetUniformMatrix( pShader, "u_ViewMat", pCamera->GetView() );
    SetUniformMatrix( pShader, "u_ProjMat", pCamera->GetProj() );
    //SetUniformTexture( "u_Texture", 0, pTexture->GetTextureID() );
    //SetUniform1f( "u_Time", fw::GetSystemTimeSinceGameStart() );

    GLint u_Time = glGetUniformLocation( pShader->GetProgram(), "u_Time" );
    if( u_Time != -1 )
    {
        glUniform1f( u_Time, (float)fw::GetSystemTimeSinceGameStart() );
    }

    // Setup the texture.
    int textureUnit = 0;
    glActiveTexture( GL_TEXTURE0 + textureUnit );
    glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );
    GLint uTexture = glGetUniformLocation( pShader->GetProgram(), "u_Texture" );
    if( uTexture != -1 )
    {
        glUniform1i( uTexture, textureUnit );
    }

    GLint locLight = glGetUniformLocation(pShader->GetProgram(), "u_LightColor");
    if (locLight != -1)
    {
        glUniform3f(locLight, lightcolor.x, lightcolor.y, lightcolor.x);
    }

    GLint locLightPos = glGetUniformLocation(pShader->GetProgram(), "u_LightPos");
    if (locLightPos != -1)
    {
        glUniform3f(locLightPos, 0.0f, 2.0f, 0.0f);
    }

    GLint locCamerapos = glGetUniformLocation(pShader->GetProgram(), "u_CameraPos");
    if (locCamerapos != -1)
    {
        glUniform3f(locCamerapos, pCamera->GetPosition().x, pCamera->GetPosition().y, pCamera->GetPosition().z);
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

    VertexFormat vertexAttributes[] =
    {
        VertexFormat( vec2( -size.x/2, -size.y/2 ) + offset, ColorByte( 255, 0, 0, 255 ), vec2( 0.0f, 0.0f ), vec3(0,0, -1) ),
        VertexFormat( vec2( -size.x/2,  size.y/2 ) + offset, ColorByte( 0, 255, 0, 255 ), vec2( 0.0f, 1.0f ), vec3(0,0, -1)),
        VertexFormat( vec2(  size.x/2,  size.y/2 ) + offset, ColorByte( 0, 0, 255, 255 ), vec2( 1.0f, 1.0f ) , vec3(0,0, -1)),
        VertexFormat( vec2(  size.x/2, -size.y/2 ) + offset, ColorByte( 255, 255, 255, 255 ), vec2( 1.0f, 0.0f ), vec3(0,0, -1)),
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
        //front face 0
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 1.0f / 2.0f)), //bottom left
        VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 1.0f)), //top left
        VertexFormat(vec3(size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f / 3.0f, 1.0f)), //top right
        VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f / 3.0f, 1.0f / 2.0f)), //bottom right 

        //right face 4
        VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f / 3.0f, 1.0f / 2.0f)), //bottom left 4
        VertexFormat(vec3(size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f / 3.0f, 1.0f)), //top left 5 
        VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(2.0f / 3.0f, 1.0f)), // top right 6 
        VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255),  vec2(2.0f / 3.0f,  1.0f / 2.0f)),//bottom right 7

        //back face 8
        VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(2.0f / 3.0f, 1.0f / 2.0f)), //bottom left
        VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(2.0f / 3.0f, 1.0f)), //top left
        VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255),vec2(1.0f, 1.0f)),  //top right
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f, 1.0f / 2.0f)), //bottom right

        //top face 12
        VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(0.0f, 0.0f)), //bottom left
        VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255),vec2(0.0f, 1.0f / 2.0f)), //top left
        VertexFormat(vec3(size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f / 3.0f, 1.0f / 2.0f)), // top right
        VertexFormat(vec3(size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f / 3.0f, 0.0f)),//bottom right

        //left face 16
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f / 3.0f, 0.0f)), //bottom left
        VertexFormat(vec3(-size.x / 2, size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f / 3.0f, 1.0f / 2.0f)), //top left
        VertexFormat(vec3(-size.x / 2, size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255),vec2(2.0f / 3.0f, 1.0f / 2.0f)),  //top right
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(2.0f / 3.0f, 0.0f)), //bottom right

        //bottom face 20
        VertexFormat(vec3(-size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(2.0f / 3.0f, 0.0f)), //bottom left
        VertexFormat(vec3(-size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(2.0f / 3.0f, 1.0f / 2.0f)), //top left
        VertexFormat(vec3(size.x / 2, -size.y / 2, size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f, 1.0f / 2.0f)), // top right
        VertexFormat(vec3(size.x / 2, -size.y / 2, -size.z / 2) + offset, ColorByte(255,255,255,255), vec2(1.0f, 0.0f)),//bottom right
    };

    unsigned int indices[36] =
    {
        0,1,2, 0,2,3,
        4,5,6, 4,6,7,
        8,9,10, 8,10,11,
        12,13,14, 12,14,15,
        16,17,18, 16,18,19,
        20,22,21, 20,23,22
    };

    for (int i = 0; i < 36; i += 3)
    {
        vec3 pos0 = vertexAttributes[indices[i]].pos;
        vec3 pos1 = vertexAttributes[indices[i + 1]].pos;
        vec3 pos2 = vertexAttributes[indices[i + 2]].pos;

        vec3 dir0 = pos1 - pos0;
        vec3 dir1 = pos2 - pos0;

        vec3 normal = dir0.Cross(dir1);
        normal.Normalize();
        vertexAttributes[indices[i]].normal = normal;
        vertexAttributes[indices[i + 1]].normal = normal;
        vertexAttributes[indices[i + 2]].normal = normal;

    }

    Init(vertexAttributes, 24, indices, 36, GL_TRIANGLES, GL_STATIC_DRAW);
}
