#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <cstdint>
enum class FrameBufferName
{
    FRAMEBUFFER2DEARLY,
    SHADOWFRAMEBUFFER,
    MSAABUFFER1,
    MSAABUFFER2,
    MSAABUFFER3,
    BLURFRAMEBUFFER,
    DEBUGERFRAMEBUFFER,
    FRAMEBUFFER2DLATE,
    MAINBLITFRAMEBUFFER,


    SOFTSHADOWFRAMEBUFFER,
    TESTBUFER,


};
class FrameBuffer
{
public:
    FrameBuffer() {}
    FrameBuffer(IDXGISwapChain* swapChain ,ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    virtual ~FrameBuffer() {}
    ID3D11RenderTargetView* getRenderTargetView() { return renderTargetView.Get(); }
    ID3D11DepthStencilView* getDepthStencilView() { return depthStencilView.Get(); }
    ID3D11ShaderResourceView* getShaderResourceView(int slotNum) { return shaderResourceView[slotNum].Get(); }
    ID3D11ShaderResourceView** getAddrShaderResourceView(int slotNum) { return shaderResourceView[slotNum].GetAddressOf(); }

    virtual void DrawedOn(ID3D11DeviceContext* immediateContext) {}
protected:
    FrameBufferName name;

    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView[2];


    Microsoft::WRL::ComPtr<ID3D11VertexShader> embedded_vertex_shader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> embedded_pixel_shader;
};

class Framebuffer2DEarly : public FrameBuffer
{
public:
    Framebuffer2DEarly(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:
};

class ShadowFrameBuffer : public FrameBuffer
{
public:
    ShadowFrameBuffer(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:

};

class MSAABuffer1 : public FrameBuffer
{
public:
    MSAABuffer1(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:
};

class MSAABuffer2 : public FrameBuffer
{
public:
    MSAABuffer2(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:
};


class MSAABuffer3 : public FrameBuffer
{
public:
    MSAABuffer3(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:
};


class MainFrameBuffer : public FrameBuffer
{
public:
    MainFrameBuffer(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:
};

class BlurFrameBuffer : public FrameBuffer
{
public:
    BlurFrameBuffer(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:
};

class DebuggerFrameBuffer : public FrameBuffer
{
public:
    DebuggerFrameBuffer(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:
};

class Framebuffer2DLate : public FrameBuffer
{
public:
    Framebuffer2DLate(IDXGISwapChain* swapChain, ID3D11Device* device, FLOAT width, FLOAT height, bool msaa, FrameBufferName name, bool shadow = false);
    void DrawedOn(ID3D11DeviceContext* immediateContext) override;
private:
};