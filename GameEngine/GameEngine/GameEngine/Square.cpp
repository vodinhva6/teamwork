#include "Square.h"

#include "GraphicEngine.h"

Square::Square(ID3D11Device* device, const VECTOR2& drawPosition, const VECTOR2& size, const VECTOR4& color)
{
    HRESULT hr = S_OK;
    ShaderManager* shaderManager = GraphicEngine::get()->getShaderManager();

    // Create vertices.
    {
        Vertex& topLeftVertex = vertices.emplace_back();
        topLeftVertex.position = drawPosition;
        topLeftVertex.position.x -= size.x;
        topLeftVertex.position.y -= size.y;
        topLeftVertex.position.w = 1.0f;
        topLeftVertex.color = color;

        Vertex& topRightVertex = vertices.emplace_back();
        topRightVertex.position = drawPosition;
        topRightVertex.position.x += size.x;
        topRightVertex.position.y += size.y;
        topRightVertex.position.w = 1.0f;
        topRightVertex.color = color;

        Vertex& bottomLeftVertex = vertices.emplace_back();
        bottomLeftVertex.position = drawPosition;
        bottomLeftVertex.position.x -= size.x;
        bottomLeftVertex.position.y -= size.y;
        bottomLeftVertex.position.w = 1.0f;
        bottomLeftVertex.color = color;

        Vertex& bottomRightVertex = vertices.emplace_back();
        bottomRightVertex.position = drawPosition;
        bottomRightVertex.position.x += size.x;
        bottomRightVertex.position.y += size.y;
        bottomRightVertex.position.w = 1.0f;
        bottomRightVertex.color = color;
    }

    // Create vertex buffer.
    {
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA subresourceData = {};
        subresourceData.pSysMem = vertices.data();
        subresourceData.SysMemPitch = 0;
        subresourceData.SysMemSlicePitch = 0;

        hr = device->CreateBuffer(
            &bufferDesc, &subresourceData, vertexBuffer.ReleaseAndGetAddressOf()
        );
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    }

    // Create vertex shader and input layout.
    {
        D3D11_INPUT_ELEMENT_DESC elementDesc[] =
        {
            { "POSITION", 0,
                DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
                D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0
            },

            { "COLOR", 0,
                DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
                D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0
            },
        };

        hr = shaderManager->createVSFromFile_cso(
            device, "Data/Shaders/SquareVS.cso", 
            vertexShader.ReleaseAndGetAddressOf(),
            inputLayout.ReleaseAndGetAddressOf(),
            elementDesc, _countof(elementDesc)
        );
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    }

    // Create pixel shader.
    {
        hr = shaderManager->createPSFromFile_cso(
            device, "Data/Shaders/SquarePS.cso", pixelShader.ReleaseAndGetAddressOf()
        );
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    }

    this->drawPosition = drawPosition;
    this->size = size;
}

void Square::render(ID3D11DeviceContext* immediateContext, float dx, float dy, float dw, float dh)
{
}

void Square::Render(ID3D11DeviceContext* immediateContext)
{
    constexpr UINT stride = sizeof(Vertex);
    constexpr UINT offset = 0;

    immediateContext->IASetInputLayout(inputLayout.Get());
    immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    immediateContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

    immediateContext->VSSetShader(vertexShader.Get(), nullptr, 0);
    immediateContext->PSSetShader(pixelShader.Get(), nullptr, 0);

    immediateContext->Draw(4, 0);
}
