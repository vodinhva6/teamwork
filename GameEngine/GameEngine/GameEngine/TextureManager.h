#pragma once
#include <d3d11.h>



class TextureManager
{
public:
    TextureManager() {}
    HRESULT loadTextureFromFile(ID3D11Device* device, const wchar_t* filename,
        ID3D11ShaderResourceView** shader_resource_view, D3D11_TEXTURE2D_DESC* texture2d_desc);
    HRESULT make_dummy_texture(ID3D11Device* device, ID3D11ShaderResourceView** shader_resource_view, DWORD value/*0xAABBGGRR*/, UINT dimension);
    void releaseAllTextures();
    ~TextureManager();
};

