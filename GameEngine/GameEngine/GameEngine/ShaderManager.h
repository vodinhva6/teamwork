#pragma once
#include <d3d11.h>

enum VERTEXSHADER
{
    SPRITE_VEXTEXSHADER,
    SPRITE3D_VEXTEXSHADER,
    SKINNEDMESH_LARMBERT_VEXTEXSHADER,
    SKINNEDMESH_LARMBERTWITHSHADOW_VEXTEXSHADER,
    SKINNEDMESH_CREATESHADOW_VEXTEXSHADER,
    GEOMETRIC_DEBUG_VEXTEXSHADER

};

enum PIXELSHADER
{
    SPRITE_PIXELSHADER,
    SPRITE3D_PIXELSHADER,
    SKINNEDMESH_OFSOFTSHADOW_PIXELSHADER,
    SKINNEDMESH_LARMBERT_PIXELSHADER,
    SKINNEDMESH_LARMBERTWITHSHADOW_PIXELSHADER,
    GEOMETRIC_DEBUG_PIXELSHADER,
    SKINNEDMESH_SKYBOX
};

enum INPUTLAYOUT
{
    SPRITE,
    SPRITE3D,
    SKINNEDMESH,
    GEOMETRIC_DEBUG
};



class ShaderManager
{
public:
    ShaderManager() {}
    HRESULT createVSFromFile_cso(ID3D11Device* device, const char* cso_name, ID3D11VertexShader** vertex_shader,
         ID3D11InputLayout * *input_layout, D3D11_INPUT_ELEMENT_DESC* input_element_desc, UINT num_elements);
    HRESULT createPSFromFile_cso(ID3D11Device* device, const char* cso_name, ID3D11PixelShader** pixel_shader);

    void SetDrawStateDraw2D(ID3D11DeviceContext* dcContext);

    void BeginDraw2D(ID3D11DeviceContext* dcContext);
    void BeginDraw3DSprite(ID3D11DeviceContext* dcContext);
    void BeginDraw3D(ID3D11DeviceContext* dcContext);
    void BeginDraw3DWithShadow(ID3D11DeviceContext* dcContext, ID3D11DepthStencilState* depth,
        ID3D11BlendState* blend, ID3D11RasterizerState* rasze);
    void BeginDraw3DCreateDepthBufferOfShadow(ID3D11DeviceContext* dcContext);
    void BeginDraw3DCreateSoftShadow(ID3D11DeviceContext* dcContext, ID3D11DepthStencilState* depth,
        ID3D11BlendState* blend, ID3D11RasterizerState* rasze);
    void BeginDrawDebug(ID3D11DeviceContext* dcContext, ID3D11DepthStencilState* depth,
        ID3D11BlendState* blend, ID3D11RasterizerState* rasze);
    void BeginDrawSkyBox(ID3D11DeviceContext* dcContext, ID3D11DepthStencilState* depth,
        ID3D11BlendState* blend, ID3D11RasterizerState* rasze);
    void End(ID3D11DeviceContext* dcContext);
    void CreateShadowAllLayout(ID3D11Device* dcContext);
    ~ShaderManager() {}
private:
    

    Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader[8];
    Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader[8];
    Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout[8];
};

