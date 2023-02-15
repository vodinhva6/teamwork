#pragma once
#include "FrameBuffer.h"
#include "FullscreenQuad.h"
#include <vector>
#include <memory>

class FrameBufferManager 
{
public:
    void Init(IDXGISwapChain* swapChain, ID3D11Device* device, D3D11_VIEWPORT* viewPort);
    void ClearAllBuffer(ID3D11DeviceContext* immediateContext);
    void DrawOnFrameBuffer(ID3D11DeviceContext* immediateContext);
    void ResolveMSAAFrameBufferToMainBuffer(ID3D11Device* device,ID3D11DeviceContext* immediateContext);
    void BlitMainFrameBufferToScreen(ID3D11DeviceContext* immediateContext);
    void BlitFrom(ID3D11DeviceContext* immediateContext, FrameBuffer* frameBuffer);

    FrameBuffer* getFrameBuffer(FrameBufferName name);
    size_t getSizeListFrameBuffer() { return listFrameBuffer.size(); }
    FullscreenQuad* getFullscreenQuad() { return blitTransfer.get(); }
    ~FrameBufferManager();
private:
    
    void Activate(ID3D11DeviceContext* immediateContext, FrameBuffer* framebuffer);
    void Deactivate(ID3D11DeviceContext* immediateContext, FrameBuffer* framebuffer);
    void Clear(ID3D11DeviceContext* immediateContext, FrameBuffer* framebuffer, float r = 0, float g = 0, float b = 0, float a = 0, float depth = 1);
    void Resolve(ID3D11Device* device,ID3D11DeviceContext* immediateContext, FrameBuffer* framebufferSource, FrameBuffer* framebufferReception);

    std::unique_ptr<FullscreenQuad>          blitTransfer;
    std::vector<std::unique_ptr<FrameBuffer>> listFrameBuffer;


    UINT viewportCount{ D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE };
    D3D11_VIEWPORT cachedViewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> cachedRenderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> cachedDepthStencilView;
    D3D11_VIEWPORT viewport;
};