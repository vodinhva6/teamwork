#pragma once
#include "Framework.h"
#include "SingletonPatternTemplate.h"
#include "SamplerStateManager.h"
#include "DepthStencilStateManager.h"
#include "BlendStateManager.h"
#include "RasterizerStateManager.h"
#include "ConstantBufferManager.h"
#include "FrameBufferManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"


#include "Sprite.h"
#include "Square.h"
#include "SkinnedMesh.h"
#include "Sprite3D.h"
#include "LightManager.h"
#include "GeometricPrimitive.h"
#include "EffectSeerManager.h"
#include "StaticMesh.h"
#include "BoundingCapsule.h"
#include "BoundingSphere.h"
#include "Ray.h"


enum class RunMode
{
    GameMode,
    DebugMode
};

class GraphicEngine: public SingletonPatternTemplate<GraphicEngine>
{
    friend class SingletonPatternTemplate<GraphicEngine>;
public:
    void Init();
    void CreateCOM(ID3D11Device* device, IDXGISwapChain1* swapChain,const SIZE& frameSize);
    void Update(float elapsedTime);
    void Render();


    void setExitGame(bool exit) { exitGame = exit; }
    bool getExitGame() { return exitGame; }

    ~GraphicEngine();
public:
    void drawSkinnedMesh(SkinnedMesh* obj, const DirectX::XMFLOAT4X4 world, const VECTOR4& color,
        SkinnedMesh::animation::keyframe* key, const int& drawTurn, DrawStates& drawStates, int slotFrameBuffer);
    void drawEffect(std::string effName, const VECTOR3& position, const int& drawTurn, int slotFrameBuffer, float size = 1, VECTOR3 rotation = { 0,0,0 }, float angle = 0, VECTOR4 color = { 1,1,1,1 }
    );
    void drawSprite3D(Sprite3D* sprite3D, const DirectX::XMFLOAT4X4 world, const VECTOR4& color, int drawTurn);
    void drawSpriteLate(Sprite* sprite,
        const VECTOR2& position, const VECTOR2& scale,
        const VECTOR4& color,
        const VECTOR2& texture_position, const VECTOR2& texture_size,
        const float& angle, const int& drawTurn,
        DrawStates& drawStates
    );
    void drawSpriteEarly(Sprite* sprite,
        const VECTOR2& position, const VECTOR2& scale,
        const VECTOR4& color,
        const VECTOR2& texture_position, const VECTOR2& texture_size,
        const float& angle, const int& drawTurn,
        DrawStates& drawStates
    );
    void drawSpriteLate(Sprite* sprite,
        const VECTOR2& position, const VECTOR2& scale,
        const VECTOR4& color,
        const VECTOR2& texture_position, const VECTOR2& texture_size,
        const float& angle, const int& drawTurn
    );
    void drawSpriteEarly(Sprite* sprite,
        const VECTOR2& position, const VECTOR2& scale,
        const VECTOR4& color,
        const VECTOR2& texture_position, const VECTOR2& texture_size,
        const float& angle, const int& drawTurn
    );
    void drawBackgroudSpriteLate(Sprite* sprite, const VECTOR2& position, const VECTOR2& size, const int& drawTurn);
    void drawBackgroudSpriteEarly(Sprite* sprite, const VECTOR2& position, const VECTOR2& size, const int& drawTurn);
    void textOut(int textNo, const std::string contents, const VECTOR2& position, const float& size, const VECTOR4& color, const int& drawTurn, bool late = true);
   
    void drawDebugBounding(GeometricPrimitive* geo, const DirectX::XMFLOAT4X4 world, const VECTOR4& color, const int& type);
public:
    Sprite* createSprite(const wchar_t* filename, ShaderData* shaderData = nullptr);
    Square* createSquare();
    Sprite3D* createSprite3D(const wchar_t* filename);
    SkinnedMesh* createSkinnedMesh(const char* fbx_name, bool triangulate, SkinnedMeshObjectAxis axis, ShaderData shaderData = {}, VECTOR3 offsetvertex = { 0,0,0 });
    void createEffect(const char* filename, std::string effName);
    BoundingCapsule* createCapsuleDebug(const float& height, const float& weight, const VECTOR3& offset);
    BoundingSphere* createSphereDebug(const float& radius, const VECTOR3& offset);
    Ray* createRay(const VECTOR3& begin, const VECTOR3& end, const VECTOR4& color, RayType Type);

public:


    float getAspectRatio();
    void getViewPort(D3D11_VIEWPORT* viewport);
    RunMode getGameMode() { return runMode; }
    float getElapsedTime() { return Framework::get()->getElapsedTime(); }

    void ResetFrameBufferManager() { framebufferManager.reset(); }

    ShaderManager* getShaderManager() { return shaderManager.get(); }
    TextureManager* getTextureManager() { return textureManager.get(); }
    LightManager* getLightManager() { return lightManager.get(); }
    FrameBufferManager* getFrameBufferManager() { return framebufferManager.get(); }
    CameraManager* getCameraManager() { return cameraManager.get(); }


    SamplerStateManager* getSamplerStateManager() { return samplerStateManager.get(); }
    DepthStencilStateManager* getDepthStencilStateManager() { return depthStencilStateManager.get(); }
    BlendStateManager* getBlendStateManager() { return blendStateManager.get(); }
    RasterizerStateManager* getRasterizerStateManager() { return rasterizerStateManager.get(); }

private:
    bool exitGame;
    RunMode runMode;

   
public:
    ID3D11DeviceContext* getDeviceContext() { return immediateContext.Get(); }
    ID3D11DeviceContext** getAddrDeviceContext() { return immediateContext.GetAddressOf(); }
public:
    void ResetRenderTagertAndDepthStencil();
    void RemoveQueneObject();

public:
    void Draw2D(bool late);
    void DrawAllUninvisibleObject(int frameBufferSlot);


private:
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext;


public:
    void CreateRenderTagert(ID3D11Device* device, IDXGISwapChain1* swapChain);
    void CreateDepthStencilView(ID3D11Device* device, IDXGISwapChain1* swapChain, const SIZE& frameSize);
    void CreateSamplerState(ID3D11Device* device);
    void CreateDepthStencilState(ID3D11Device* device);
    void CreateBlendState(ID3D11Device* device);
    void CreateRasterizerState(ID3D11Device* device);
    void CreateConstantBuffer(ID3D11Device* device);
    void CreateFramebuffer(ID3D11Device* device, IDXGISwapChain1* swapChain);
    void CreateShaderManager(ID3D11Device* device);
    void CreateTextureManager();
    void CreateLightManager();
    void CreateCameraManager();



    void CreateTextFont();


private:
    void CheckChangeRunGameMode();

   
private:
    void SetSlotPSConstantBuffer();
    void SetSlotVSConstantBuffer();
    void UpdateResources();
    void SetSlotSampler();


    void ClearRenderTagertAndDepthStencil(const VECTOR4& color = { 0,0,0,1 });

private:
    std::unique_ptr<SamplerStateManager>      samplerStateManager;
    std::unique_ptr<DepthStencilStateManager> depthStencilStateManager;
    std::unique_ptr<BlendStateManager       > blendStateManager;
    std::unique_ptr<RasterizerStateManager  > rasterizerStateManager;
    std::unique_ptr<ConstantBufferManager   > constantBufferManager;
    std::unique_ptr<FrameBufferManager      > framebufferManager;
    std::unique_ptr<ShaderManager           > shaderManager;
    std::unique_ptr<TextureManager          > textureManager;
    std::unique_ptr<LightManager            > lightManager;
    std::unique_ptr<CameraManager>            cameraManager;


   


private:
    const wchar_t* textFonts[8] =
    {
        L"./Data/Fonts/font0.png",
        L"./Data/Fonts/font1.png",
        L"./Data/Fonts/font2.png",
        L"./Data/Fonts/font3.png",
        L"./Data/Fonts/font4.png",
        L"./Data/Fonts/font5.png",
        L"./Data/Fonts/font6.png",
        L"./Data/Fonts/font7.png",
    };
    VECTOR2 text_fonts_size[8] =
    {
        {36,36},
        {36,36},
        {36,36},
        {36,36},
        {36,36},
        {36,36},
        {36,36},
        {100,100},
    };

    class SpritesData;
    class GeometricPrimitiveData;
    class StaticMeshData;
    class SkinnedMeshData;
    class EffectData;
    class Sprite3DData;
    class ObjectDrawData
    {
    public:
        virtual SpritesData* getSpritesData() { return nullptr; }
        virtual GeometricPrimitiveData* getGeometricPrimitiveData() { return nullptr; }
        virtual StaticMeshData* getStaticMeshData() { return nullptr; }
        virtual SkinnedMeshData* getSkinnedMeshData() { return nullptr; }
        virtual EffectData* getEffectData() { return nullptr; }
        virtual Sprite3DData* getSprite3D() { return nullptr; }
        virtual ~ObjectDrawData() {}
        DrawStates drawState_;
        int drawTurn_;
    };
    class SpritesData :public ObjectDrawData
    {
    public:
        SpritesData* getSpritesData() override { return this; }
        SpritesData(Sprite* sprite, const VECTOR2& position,
            const VECTOR2& size, const VECTOR4& color,
            const VECTOR2& texture_position, const VECTOR2& texture_size,
            const float& angle, int drawTurn,
            DrawStates drawState, std::string contents
        ) :
            sprite_(sprite), position_(position), size_(size), color_(color), texture_position_(texture_position),
            texture_size_(texture_size), angle_(angle), contents_(contents)
        {
            ObjectDrawData::drawTurn_ = drawTurn;
            ObjectDrawData::drawState_ = drawState;
        }

        SpritesData& operator=(const SpritesData& data)
        {
            this->sprite_ = data.sprite_;
            this->position_ = data.position_;
            this->size_ = data.size_;
            this->color_ = data.color_;
            this->texture_position_ = data.texture_position_;
            this->texture_size_ = data.texture_size_;
            this->angle_ = data.angle_;
            this->drawTurn_ = data.drawTurn_;
            this->drawState_ = data.drawState_;
            this->contents_ = data.contents_;
            return *this;
        }

        Sprite* sprite_;
        VECTOR2 position_;
        VECTOR2 size_;
        VECTOR4 color_;
        VECTOR2 texture_position_;
        VECTOR2 texture_size_;
        float angle_;


        std::string contents_;



        ~SpritesData() override {}
    };
    class GeometricPrimitiveData : public ObjectDrawData
    {
    public:
        GeometricPrimitiveData* getGeometricPrimitiveData() override { return this; }
        GeometricPrimitiveData() {}
        GeometricPrimitiveData(GeometricPrimitive* geometric, const DirectX::XMFLOAT4X4& world, const VECTOR4& color, const int& type)
            :geometric_(geometric), world_(world), color_(color), type_(type)
        {

        }

        GeometricPrimitiveData& operator=(const GeometricPrimitiveData& data)
        {
            this->geometric_ = data.geometric_;
            this->world_ = data.world_;
            this->color_ = data.color_;
            this->drawTurn_ = data.drawTurn_;
            this->drawState_ = data.drawState_;
            this->type_ = data.type_;
            return *this;
        }

        GeometricPrimitive* geometric_;
        DirectX::XMFLOAT4X4 world_;
        VECTOR4 color_;
        int type_;

        ~GeometricPrimitiveData() {}
    };
    class StaticMeshData :public ObjectDrawData
    {
    public:
        StaticMeshData* getStaticMeshData() override { return this; }
        StaticMeshData(StaticMesh* staticMesh, const VECTOR3& position,
            const VECTOR3& rotation,
            const VECTOR3& size, const VECTOR4& color, int drawTurn, DrawStates drawState,
            const bool& drawBoudingBox
        ) :staticMesh_(staticMesh), rotation_(rotation),
            position_(position), size_(size), color_(color),
            drawBoudingBox_(drawBoudingBox)
        {
            ObjectDrawData::drawTurn_ = drawTurn;
            ObjectDrawData::drawState_ = drawState;
        }

        StaticMeshData& operator=(const StaticMeshData& data)
        {
            this->staticMesh_ = data.staticMesh_;
            this->position_ = data.position_;
            this->size_ = data.size_;
            this->color_ = data.color_;
            this->drawTurn_ = data.drawTurn_;
            this->drawState_ = data.drawState_;
            this->drawBoudingBox_ = data.drawBoudingBox_;
            return *this;
        }

        StaticMesh* staticMesh_;
        VECTOR3 position_;
        VECTOR3 rotation_;
        VECTOR3 size_;
        VECTOR4 color_;
        bool drawBoudingBox_;


        ~StaticMeshData() override {}
    };
    class SkinnedMeshData :public ObjectDrawData
    {
    public:
        SkinnedMeshData* getSkinnedMeshData() override { return this; }
    
        SkinnedMeshData(SkinnedMesh* skinnedMesh, DirectX::XMFLOAT4X4 world, const VECTOR4& color, SkinnedMesh::animation::keyframe* keyframe, int drawTurn,
            DrawStates drawState) :
            skinnedMesh_(skinnedMesh), world_(world), color_(color), keyframe_(keyframe)
        {
            ObjectDrawData::drawTurn_ = drawTurn;
            ObjectDrawData::drawState_ = drawState;
        }
    
        SkinnedMeshData(SkinnedMesh* skinnedMesh, DirectX::XMFLOAT4X4 world, const VECTOR4& color, int drawTurn,
            DrawStates drawState) :
            skinnedMesh_(skinnedMesh), world_(world), color_(color), keyframe_(nullptr)
        {
            ObjectDrawData::drawTurn_ = drawTurn;
            ObjectDrawData::drawState_ = drawState;
        }
        SkinnedMeshData& operator=(const SkinnedMeshData& data)
        {
            this->skinnedMesh_ = data.skinnedMesh_;
            this->world_ = data.world_;
            this->color_ = data.color_;
            this->keyframe_ = data.keyframe_;
            this->drawTurn_ = data.drawTurn_;
            this->drawState_ = data.drawState_;
            return *this;
        }
    
        SkinnedMesh* skinnedMesh_;
        DirectX::XMFLOAT4X4 world_;
        VECTOR4 color_;
        SkinnedMesh::animation::keyframe* keyframe_;
    };
    class EffectData : public ObjectDrawData
    {
    public:

        EffectData* getEffectData() { return this; }

        EffectData(Effect* eff, const VECTOR3& position, const VECTOR3& rotation, const VECTOR4& color,
            const float& scale, const int& drawTurn, const float& angle, DrawStates drawState)
        {
            this->eff_ = eff;
            this->position_ = position;
            this->rotation_ = rotation;
            this->color_ = color;
            this->scale_ = scale;
            this->angle_ = angle;
            this->drawState_ = drawState;
            drawTurn_ = drawTurn;
        }
        EffectData& operator=(const EffectData& data)
        {
            this->eff_ = data.eff_;
            this->position_ = data.position_;
            this->rotation_ = data.rotation_;
            this->color_ = data.color_;
            this->scale_ = data.scale_;
            this->drawTurn_ = data.drawTurn_;
            this->angle_ = data.angle_;
            this->drawState_ = data.drawState_;
        }
        Effect* eff_;
        VECTOR3 position_;
        VECTOR3 rotation_;
        VECTOR4 color_;
        float angle_;
        float scale_;


    };
    class Sprite3DData : public ObjectDrawData
    {
    public:

        Sprite3DData(const Sprite3DData& data)
        {
            this->sprite3D = data.sprite3D;
            this->world = data.world;
            this->drawTurn_ = data.drawTurn_;
            this->color = data.color;
        }
        Sprite3DData(Sprite3D* sprite3D, DirectX::XMFLOAT4X4 world, const VECTOR4& color, int drawTurn) :
            sprite3D(sprite3D), world(world), color(color)
        {
            drawTurn_ = drawTurn;
        }
        Sprite3DData& operator=(const Sprite3DData& data)
        {
            this->sprite3D = data.sprite3D;
            this->world = data.world;
            this->drawTurn_ = data.drawTurn_;
            this->color = data.color;
            return *this;
        }
        Sprite3DData* getSprite3D() override { return this; }
        Sprite3D* sprite3D;
        DirectX::XMFLOAT4X4 world;
        VECTOR4 color;
    };


    std::map<std::string, Effect*> effects;
    std::vector<std::shared_ptr<SkinnedMesh>> skinnedMeshes;
    std::vector<std::shared_ptr<Sprite>> sprites;
    std::vector<std::shared_ptr<Square>> squares;
    std::vector<std::shared_ptr<GeometricPrimitive>> geometricPrimitive;
    std::vector<std::shared_ptr<Sprite3D>> sprites3D;


    std::vector<std::vector<ObjectDrawData*>> uninvisibleDataObjectsFrameBuffer;
    std::vector<ObjectDrawData*> invisibleDataObjects;
    std::vector<ObjectDrawData*> Object2DListEarly;
    std::vector<ObjectDrawData*> Object2DListLate;
    std::vector<ObjectDrawData*> sprites3DList;
    std::vector<ObjectDrawData*> drawDebugList;


private:
    void DeleteAllEffect();
};


