#pragma once

#include "RendererAPI.h"

namespace NR
{
    class RenderCommand
    {
    public:
        inline static void Init()
        {
            sRendererAPI->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            sRendererAPI->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const glm::vec4& color)
        {
            sRendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            sRendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
        {
            sRendererAPI->DrawIndexed(vertexArray, count);
        }
        
        inline static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
        {
            sRendererAPI->DrawLines(vertexArray, vertexCount);
        }

        inline static void SetLineWidth(float width)
        {
            sRendererAPI->SetLineWidth(width);
        }

    private:
        static Ref<RendererAPI> sRendererAPI;
    };
}