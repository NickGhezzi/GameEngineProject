//
// Copyright (c) 2016-2019 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef __ImGuiManager_H__
#define __ImGuiManager_H__

#include "../../Libraries/imgui/imgui.h"

namespace fw
{

    class Event;

    class ImGuiManager
    {
    protected:
        void ClearInput();

        GLuint m_FontTexture;
        int m_ShaderHandle;
        int m_VertHandle;
        int m_FragHandle;
        int m_AttribLocationTex;
        int m_AttribLocationProjMtx;
        int m_AttribLocationPosition;
        int m_AttribLocationUV;
        int m_AttribLocationColor;
        unsigned int m_VboHandle;
        unsigned int m_VaoHandle;
        unsigned int m_ElementsHandle;

    public:
        ImGuiManager();
        virtual ~ImGuiManager();

        void Init();
        void Shutdown();

        void OnFocusLost();

        void OnEvent(fw::Event* pEvent);

        void StartFrame(float width, float height, float deltaTime);
        void EndFrame();

        void RenderDrawLists(ImDrawData* draw_data);

        bool CreateFontsTexture();
        bool CreateDeviceObjects();
        void InvalidateDeviceObjects();
    };

}

#endif //__ImGuiManager_H__
