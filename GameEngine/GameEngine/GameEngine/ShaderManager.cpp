#include <wrl.h>
#include <string>
#include <map>
#include <memory>
#include "GraphicEngine.h"
#include "ShaderManager.h"
#include "Misc.h"

HRESULT ShaderManager::createVSFromFile_cso(ID3D11Device* device , const char* cso_name, ID3D11VertexShader** vertex_shader, ID3D11InputLayout** input_layout, D3D11_INPUT_ELEMENT_DESC* input_element_desc, UINT num_elements)
{
    FILE* fp{ nullptr };
    fopen_s(&fp, cso_name, "rb");
    _ASSERT_EXPR_A(fp, "CSO File not found");

    fseek(fp, 0, SEEK_END);
    long cso_sz{ ftell(fp) };
    fseek(fp, 0, SEEK_SET);
    
    std::unique_ptr<unsigned char[]> cso_data{ std::make_unique<unsigned char[]>(cso_sz) };
    fread(cso_data.get(), cso_sz, 1, fp);
    fclose(fp);

    HRESULT hr{ S_OK };
    hr = device->CreateVertexShader(cso_data.get(), cso_sz, nullptr, vertex_shader);
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    if (input_layout)
    {
        hr = device->CreateInputLayout(input_element_desc, num_elements,
            cso_data.get(), cso_sz, input_layout);
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    } 

    return hr;
}

HRESULT ShaderManager::createPSFromFile_cso(ID3D11Device* device , const char* cso_name, ID3D11PixelShader** pixel_shader)
{
    FILE * fp{ nullptr };
    fopen_s(&fp, cso_name, "rb");
    _ASSERT_EXPR_A(fp, "CSO File not found");
    
     fseek(fp, 0, SEEK_END);
    long cso_sz{ ftell(fp) };
    fseek(fp, 0, SEEK_SET);
    
    std::unique_ptr<unsigned char[]> cso_data{ std::make_unique<unsigned char[]>(cso_sz) };
    fread(cso_data.get(), cso_sz, 1, fp);
    fclose(fp);
    
     HRESULT hr{ S_OK };
    hr = device->CreatePixelShader(cso_data.get(), cso_sz, nullptr, pixel_shader);
    _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    
     return hr;
}



void ShaderManager::CreateShadowAllLayout(ID3D11Device* device)
{
    HRESULT hr;

    {
        D3D11_INPUT_ELEMENT_DESC input_element_desc[]
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
           D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },/*
            { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
           D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },*/
        };
        hr = createVSFromFile_cso(device, "./Data/Shaders/GeometricPrimitiveDebugShader_vs.cso",
            VertexShader[VERTEXSHADER::GEOMETRIC_DEBUG_VEXTEXSHADER].ReleaseAndGetAddressOf(), 
            InputLayout[INPUTLAYOUT::GEOMETRIC_DEBUG].ReleaseAndGetAddressOf(), input_element_desc, _countof(input_element_desc));
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
        hr = createPSFromFile_cso(device, "./Data/Shaders/GeometricPrimitiveDebugShader_ps.cso",
            PixelShader[PIXELSHADER::GEOMETRIC_DEBUG_PIXELSHADER].ReleaseAndGetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

    }
    //Sprite
    {
        D3D11_INPUT_ELEMENT_DESC input_element_desc[]
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };

        hr = createVSFromFile_cso(device, "./Data/Shaders/sprite_vs.cso",
            VertexShader[VERTEXSHADER::SPRITE_VEXTEXSHADER].ReleaseAndGetAddressOf(), InputLayout[INPUTLAYOUT::SPRITE].ReleaseAndGetAddressOf(), input_element_desc, _countof(input_element_desc));
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
        hr = createPSFromFile_cso(device, "./Data/Shaders/sprite_ps.cso",
            PixelShader[PIXELSHADER::SPRITE_PIXELSHADER].ReleaseAndGetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    }

    //3DSprite
    {
        D3D11_INPUT_ELEMENT_DESC input_element_desc[]
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };

        hr = createVSFromFile_cso(device, "./Data/Shaders/Sprite3D_vs.cso",
            VertexShader[VERTEXSHADER::SPRITE3D_VEXTEXSHADER].ReleaseAndGetAddressOf(), InputLayout[INPUTLAYOUT::SPRITE3D].ReleaseAndGetAddressOf(), input_element_desc, _countof(input_element_desc));
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
        hr = createPSFromFile_cso(device, "./Data/Shaders/Sprite3D_ps.cso",
            PixelShader[PIXELSHADER::SPRITE3D_PIXELSHADER].ReleaseAndGetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
    }

    //SkinnedMesh
    {
        D3D11_INPUT_ELEMENT_DESC input_element_desc[]
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT },
            { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT },
            { "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT },
            { "WEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT },
            { "BONES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT },

        };

        //
        {
            hr = createVSFromFile_cso(device, "./Data/Shaders/skinned_mesh_vs.cso",
                VertexShader[VERTEXSHADER::SKINNEDMESH_LARMBERT_VEXTEXSHADER].ReleaseAndGetAddressOf(),
                InputLayout[INPUTLAYOUT::SKINNEDMESH].ReleaseAndGetAddressOf(), input_element_desc, ARRAYSIZE(input_element_desc));
            _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

            hr = createPSFromFile_cso(device, "./Data/Shaders/skinned_mesh_ps.cso",
                PixelShader[PIXELSHADER::SKINNEDMESH_LARMBERT_PIXELSHADER].ReleaseAndGetAddressOf());
            _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
        }

        //
        {
            hr = createVSFromFile_cso(device, "./Data/Shaders/SkinnedMeshWithShadow_VS.cso",
                VertexShader[VERTEXSHADER::SKINNEDMESH_LARMBERTWITHSHADOW_VEXTEXSHADER].ReleaseAndGetAddressOf(),
                InputLayout[INPUTLAYOUT::SKINNEDMESH].ReleaseAndGetAddressOf(), input_element_desc, ARRAYSIZE(input_element_desc));
            _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

            hr = createPSFromFile_cso(device, "./Data/Shaders/SkinnedMeshWithShadow_PS.cso",
                PixelShader[PIXELSHADER::SKINNEDMESH_LARMBERTWITHSHADOW_PIXELSHADER].ReleaseAndGetAddressOf());
            _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
        }


        //
        {
            hr = createVSFromFile_cso(device, "./Data/Shaders/SkinnedMeshOfShadow_VS.cso",
                VertexShader[VERTEXSHADER::SKINNEDMESH_CREATESHADOW_VEXTEXSHADER].ReleaseAndGetAddressOf(),
                InputLayout[INPUTLAYOUT::SKINNEDMESH].ReleaseAndGetAddressOf(), input_element_desc, ARRAYSIZE(input_element_desc));
            _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

            hr = createPSFromFile_cso(device, "./Data/Shaders/SkinnedMeshCreateSoftShadow_PS.cso",
                PixelShader[PIXELSHADER::SKINNEDMESH_OFSOFTSHADOW_PIXELSHADER].ReleaseAndGetAddressOf());
            _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

        }

        {
            hr = createPSFromFile_cso(device, "./Data/Shaders/SkyBoxSkinnedMesh_PS.cso",
                PixelShader[PIXELSHADER::SKINNEDMESH_SKYBOX].ReleaseAndGetAddressOf());
            _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

        }


    }


}

void ShaderManager::SetDrawStateDraw2D(ID3D11DeviceContext* dcContext)
{
    GraphicEngine* grap = GraphicEngine::get();

    ID3D11DepthStencilState* depth = grap->getDepthStencilStateManager()->getDepthStencill(DepthStencilStates::DepthTestOff_DepthWriteOff);
    ID3D11BlendState* blend = grap->getBlendStateManager()->getBlendState(BlendStates::AlphaBlendAlphaCoverage);
    ID3D11RasterizerState* rasze = grap->getRasterizerStateManager()->getRasterizerState(RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);

}


void ShaderManager::BeginDraw2D(ID3D11DeviceContext* dcContext)
{
    GraphicEngine* grap = GraphicEngine::get();

    ID3D11DepthStencilState* depth = grap->getDepthStencilStateManager()->getDepthStencill(DepthStencilStates::DepthTestOff_DepthWriteOff);
    ID3D11BlendState* blend = grap->getBlendStateManager()->getBlendState(BlendStates::AlphaBlendAlphaCoverage);
    ID3D11RasterizerState* rasze = grap->getRasterizerStateManager()->getRasterizerState(RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn);

    dcContext->IASetInputLayout(InputLayout[INPUTLAYOUT::SPRITE].Get());
    dcContext->VSSetShader(VertexShader[VERTEXSHADER::SPRITE_VEXTEXSHADER].Get(), nullptr, 0);
    dcContext->PSSetShader(PixelShader[PIXELSHADER::SPRITE_PIXELSHADER].Get(), nullptr, 0);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);


}

void ShaderManager::BeginDraw3DSprite(ID3D11DeviceContext* dcContext)
{
    GraphicEngine* grap = GraphicEngine::get();

    ID3D11DepthStencilState* depth = grap->getDepthStencilStateManager()->getDepthStencill(DepthStencilStates::DepthTestOn_DepthWriteOn);
    ID3D11BlendState* blend = grap->getBlendStateManager()->getBlendState(BlendStates::Alpha);
    ID3D11RasterizerState* rasze = grap->getRasterizerStateManager()->getRasterizerState(RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn);


    dcContext->IASetInputLayout(InputLayout[INPUTLAYOUT::SPRITE3D].Get());
    dcContext->VSSetShader(VertexShader[VERTEXSHADER::SPRITE3D_VEXTEXSHADER].Get(), nullptr, 0);
    dcContext->PSSetShader(PixelShader[PIXELSHADER::SPRITE3D_PIXELSHADER].Get(), nullptr, 0);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);
}

void ShaderManager::BeginDraw3D(ID3D11DeviceContext* dcContext)
{
    GraphicEngine* grap = GraphicEngine::get();

    ID3D11DepthStencilState* depth = grap->getDepthStencilStateManager()->getDepthStencill(DepthStencilStates::DepthTestOn_DepthWriteOn);
    ID3D11BlendState* blend = grap->getBlendStateManager()->getBlendState(BlendStates::Alpha);
    ID3D11RasterizerState* rasze = grap->getRasterizerStateManager()->getRasterizerState(RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn);

    dcContext->IASetInputLayout(InputLayout[INPUTLAYOUT::SKINNEDMESH].Get());
    dcContext->VSSetShader(VertexShader[VERTEXSHADER::SKINNEDMESH_LARMBERT_VEXTEXSHADER].Get(), nullptr, 0);
    dcContext->PSSetShader(PixelShader[PIXELSHADER::SKINNEDMESH_LARMBERT_PIXELSHADER].Get(), nullptr, 0);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);

}

void ShaderManager::BeginDraw3DWithShadow(ID3D11DeviceContext* dcContext, ID3D11DepthStencilState* depth,
    ID3D11BlendState* blend, ID3D11RasterizerState* rasze)
{
    dcContext->IASetInputLayout(InputLayout[INPUTLAYOUT::SKINNEDMESH].Get());
    dcContext->VSSetShader(VertexShader[VERTEXSHADER::SKINNEDMESH_LARMBERTWITHSHADOW_VEXTEXSHADER].Get(), nullptr, 0);
    dcContext->PSSetShader(PixelShader[PIXELSHADER::SKINNEDMESH_LARMBERTWITHSHADOW_PIXELSHADER].Get(), nullptr, 0);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);
}

void ShaderManager::BeginDraw3DCreateDepthBufferOfShadow(ID3D11DeviceContext* dcContext)
{
    GraphicEngine* grap = GraphicEngine::get();

    ID3D11DepthStencilState* depth = grap->getDepthStencilStateManager()->getDepthStencill(DepthStencilStates::DepthTestOn_DepthWriteOn);
    ID3D11BlendState* blend = grap->getBlendStateManager()->getBlendState(BlendStates::Alpha);
    ID3D11RasterizerState* rasze = grap->getRasterizerStateManager()->getRasterizerState(RasterizerStates::CullingOpposition);

    dcContext->VSSetShader(VertexShader[VERTEXSHADER::SKINNEDMESH_CREATESHADOW_VEXTEXSHADER].Get(), nullptr, 0);
    dcContext->IASetInputLayout(InputLayout[INPUTLAYOUT::SKINNEDMESH].Get());
    dcContext->PSSetShader(nullptr, nullptr, 0);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);
}

void ShaderManager::BeginDraw3DCreateSoftShadow(ID3D11DeviceContext* dcContext, ID3D11DepthStencilState* depth, ID3D11BlendState* blend, ID3D11RasterizerState* rasze)
{
    dcContext->VSSetShader(VertexShader[VERTEXSHADER::SKINNEDMESH_LARMBERTWITHSHADOW_VEXTEXSHADER].Get(), nullptr, 0);
    dcContext->IASetInputLayout(InputLayout[INPUTLAYOUT::SKINNEDMESH].Get());
    dcContext->PSSetShader(PixelShader[PIXELSHADER::SKINNEDMESH_OFSOFTSHADOW_PIXELSHADER].Get(), nullptr, 0);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);
}

void ShaderManager::BeginDrawDebug(ID3D11DeviceContext* dcContext, ID3D11DepthStencilState* depth, ID3D11BlendState* blend, ID3D11RasterizerState* rasze)
{
    dcContext->IASetInputLayout(InputLayout[INPUTLAYOUT::GEOMETRIC_DEBUG].Get());
    dcContext->VSSetShader(VertexShader[VERTEXSHADER::GEOMETRIC_DEBUG_VEXTEXSHADER].Get(), nullptr, 0);
    dcContext->PSSetShader(PixelShader[PIXELSHADER::GEOMETRIC_DEBUG_PIXELSHADER].Get(), nullptr, 0);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);
}

void ShaderManager::BeginDrawSkyBox(ID3D11DeviceContext* dcContext, ID3D11DepthStencilState* depth, ID3D11BlendState* blend, ID3D11RasterizerState* rasze)
{

    dcContext->IASetInputLayout(InputLayout[INPUTLAYOUT::SKINNEDMESH].Get());
    dcContext->VSSetShader(VertexShader[VERTEXSHADER::SKINNEDMESH_LARMBERT_VEXTEXSHADER ].Get(), nullptr, 0);
    dcContext->PSSetShader(PixelShader[PIXELSHADER::SKINNEDMESH_SKYBOX].Get(), nullptr, 0);

    dcContext->OMSetBlendState(blend, nullptr, 0xFFFFFFFF);
    dcContext->RSSetState(rasze);
    dcContext->OMSetDepthStencilState(depth, 1);
}



void ShaderManager::End(ID3D11DeviceContext* dcContext)
{
    dcContext->IASetInputLayout(nullptr);
    dcContext->VSSetShader(nullptr, nullptr, 0);
    dcContext->PSSetShader(nullptr, nullptr, 0);
}


