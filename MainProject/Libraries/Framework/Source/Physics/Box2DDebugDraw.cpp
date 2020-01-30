#include "FrameworkPCH.h"
#include "Box2DDebugDraw.h"

namespace fw
{
    Box2DDebugDraw::Box2DDebugDraw(ShaderProgram* pShaderProgram, MyMatrix* pMatView, MyMatrix* pMatProj)
    {
        m_pShaderProgram = pShaderProgram;
        m_pMatView = pMatView;
        m_pMatProj = pMatProj;
    }

    Box2DDebugDraw::~Box2DDebugDraw()
    {
    }

    void Box2DDebugDraw::SetViewProjMatrices(MyMatrix* pMatView, MyMatrix* pMatProj)
    {
        m_pMatView = pMatView;
        m_pMatProj = pMatProj;
    }

    void SetupUniforms(ShaderProgram* pShaderProgram, MyMatrix* viewmat, MyMatrix* projmat, Vector4 color)
    {
        GLuint programHandle = pShaderProgram->GetProgram();

        // Enable our shader program.
        glUseProgram( programHandle );

        // Get the uniform locations.
        GLint uViewMatrix = glGetUniformLocation( programHandle, "u_ViewMatrix" );
        GLint uProjMatrix = glGetUniformLocation( programHandle, "u_ProjMatrix" );
        GLint uColor = glGetUniformLocation( programHandle, "u_Color" );

        if( uViewMatrix != -1 )
        {
            glUniformMatrix4fv( uViewMatrix, 1, false, &viewmat->m11 );
        }

        if( uProjMatrix != -1 )
        {
            glUniformMatrix4fv( uProjMatrix, 1, false, &projmat->m11 );
        }

        if( uColor != -1 )
        {
            glUniform4f( uColor, color.x, color.y, color.z, color.w );
        }
    }

    void Box2DDebugDraw::Draw(const b2Vec2* vertices, int32 vertexCount, const b2Color& color, unsigned char alpha, int primitiveType)
    {
        if( m_pMatView == nullptr || m_pMatProj == nullptr )
            return;

        // Bind our vertex and index buffers.
        glBindBuffer( GL_ARRAY_BUFFER, 0 );

        // Setup the position attribute.
        GLint aPos = glGetAttribLocation( m_pShaderProgram->GetProgram(), "a_Position" );
        assert( aPos != -1 );
        glVertexAttribPointer( aPos, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)vertices );
        glEnableVertexAttribArray( aPos );

        // Setup the uniforms.
        Vector4 color4( color.r, color.g, color.b, alpha/255.0f );
        SetupUniforms( m_pShaderProgram, m_pMatView, m_pMatProj, color4 );

        glDisable( GL_CULL_FACE );
        glDisable( GL_DEPTH_TEST );

        //glLineWidth( 1 );
        glDrawArrays( primitiveType, 0, vertexCount );

        glEnable( GL_CULL_FACE );
        glEnable( GL_DEPTH_TEST );
    }

    void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        Draw( vertices, vertexCount, color, 255, GL_LINE_LOOP );
    }

    void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        Draw( vertices, vertexCount, color, 128, GL_TRIANGLE_FAN );
        Draw( vertices, vertexCount, color, 255, GL_LINE_LOOP );
    }

    void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
    {
        // If you want debug circles, plot the points here and call draw.
    }

    void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
    {
        // If you want debug circles, plot the points here and call draw.
    }

    void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
    {
        b2Vec2 vertices[2] = { p1, p2 };

        Draw( vertices, 2, color, 255, GL_LINES );
    }

    void Box2DDebugDraw::DrawTransform(const b2Transform& xf)
    {
        b2Vec2 vertices[2] = { xf.p };

        vertices[1] = xf.p + 0.5f * xf.q.GetXAxis();
        Draw( vertices, 2, b2Color( 1, 0, 0 ), 255, GL_LINES );

        vertices[1] = xf.p + 0.5f * xf.q.GetYAxis();
        Draw( vertices, 2, b2Color( 0, 1, 0 ), 255, GL_LINES );
    }
    void Box2DDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
    {
    }
}
