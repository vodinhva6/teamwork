#include "SquarePrimitive.h"

#include "GraphicEngine.h"

SquarePrimitive::SquarePrimitive(ID3D11Device* device, const ShaderData& shaderData) :
    Sprite(device, L"", shaderData)
{
}

void SquarePrimitive::render(
     ID3D11DeviceContext* immediateContext,
     float drawPositionX, float drawPositionY, 
     float width, float height,
     float r, float g, float b, float a)
{
    D3D11_VIEWPORT viewport{};
    UINT num_viewports{ 1 };
    immediateContext->RSGetViewports(&num_viewports, &viewport);

    float x0{ drawPositionX - width };
    float y0{ drawPositionY - height };
    // right-top
    float x1{ drawPositionX + width };
    float y1{ drawPositionY - height };
    // left-bottom
    float x2{ drawPositionX - width };
    float y2{ drawPositionY + height };
    // right-bottom
    float x3{ drawPositionX + width };
    float y3{ drawPositionY + height };

    // float cx = dx + dw * 0.5f;
    // float cy = dy + dh * 0.5f;
    // rotate(x0, y0, cx, cy, 0);
    // rotate(x1, y1, cx, cy, 0);
    // rotate(x2, y2, cx, cy, 0);
    // rotate(x3, y3, cx, cy, 0);

    // Convert to ndc
    x0 = 2.0f * x0 / viewport.Width - 1.0f;
    y0 = 1.0f - 2.0f * y0 / viewport.Height;
    x1 = 2.0f * x1 / viewport.Width - 1.0f;
    y1 = 1.0f - 2.0f * y1 / viewport.Height;
    x2 = 2.0f * x2 / viewport.Width - 1.0f;
    y2 = 1.0f - 2.0f * y2 / viewport.Height;
    x3 = 2.0f * x3 / viewport.Width - 1.0f;
    y3 = 1.0f - 2.0f * y3 / viewport.Height;

    HRESULT hr{ S_OK };
    D3D11_MAPPED_SUBRESOURCE mapped_subresource{};
    hr = immediateContext->Map(vertex_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    vertex* vertices{ static_cast<vertex*>(mapped_subresource.pData) };
    if (vertices != nullptr)
    {
        vertices[0].position = { x0, y0 , 0 };
        vertices[1].position = { x1, y1 , 0 };
        vertices[2].position = { x2, y2 , 0 };
        vertices[3].position = { x3, y3 , 0 };
        vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = { r, g, b, a };
        vertices[0].texcoord = { 0, 0 };
        vertices[1].texcoord = { 1, 0 };
        vertices[2].texcoord = { 0, 1 };
        vertices[3].texcoord = { 1, 1 };
    }

    immediateContext->Unmap(vertex_buffer.Get(), 0);

    draw(immediateContext);

    drawPosition = { drawPositionX, drawPositionY };
    size = { width, height };
}

void SquarePrimitive::render(ID3D11DeviceContext* immediateContext,
        float topLeftPositionX, float topLeftPositionY,
        float bottomRightPositionX, float bottomRightPositionY, float angle,
        float r, float g, float b, float a)
{
    D3D11_VIEWPORT viewport{};
    UINT num_viewports{ 1 };
    immediateContext->RSGetViewports(&num_viewports, &viewport);

    float x0{ topLeftPositionX };
    float y0{ topLeftPositionY };
    // right-top
    float x1{ bottomRightPositionX };
    float y1{ topLeftPositionY };
    // left-bottom
    float x2{ topLeftPositionX };
    float y2{ bottomRightPositionY };
    // right-bottom
    float x3{ bottomRightPositionX };
    float y3{ bottomRightPositionY };

    // float cx = dx + dw * 0.5f;
    // float cy = dy + dh * 0.5f;
    // rotate(x0, y0, cx, cy, 0);
    // rotate(x1, y1, cx, cy, 0);
    // rotate(x2, y2, cx, cy, 0);
    // rotate(x3, y3, cx, cy, 0);

    // Convert to ndc
    x0 = 2.0f * x0 / viewport.Width - 1.0f;
    y0 = 1.0f - 2.0f * y0 / viewport.Height;
    x1 = 2.0f * x1 / viewport.Width - 1.0f;
    y1 = 1.0f - 2.0f * y1 / viewport.Height;
    x2 = 2.0f * x2 / viewport.Width - 1.0f;
    y2 = 1.0f - 2.0f * y2 / viewport.Height;
    x3 = 2.0f * x3 / viewport.Width - 1.0f;
    y3 = 1.0f - 2.0f * y3 / viewport.Height;

    HRESULT hr{ S_OK };
    D3D11_MAPPED_SUBRESOURCE mapped_subresource{};
    hr = immediateContext->Map(vertex_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    vertex* vertices{ static_cast<vertex*>(mapped_subresource.pData) };
    if (vertices != nullptr)
    {
        vertices[0].position = { x0, y0 , 0 };
        vertices[1].position = { x1, y1 , 0 };
        vertices[2].position = { x2, y2 , 0 };
        vertices[3].position = { x3, y3 , 0 };
        vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = { r, g, b, a };
        vertices[0].texcoord = { 0, 0 };
        vertices[1].texcoord = { 1, 0 };
        vertices[2].texcoord = { 0, 1 };
        vertices[3].texcoord = { 1, 1 };
    }

    immediateContext->Unmap(vertex_buffer.Get(), 0);

    draw(immediateContext);
}
