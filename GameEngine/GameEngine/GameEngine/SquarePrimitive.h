#pragma once

#include "MyMath.h"

#include <d3d11.h>
#include <wrl.h>

#include "Sprite.h"

class SquarePrimitive : public Sprite
{
public:
    SquarePrimitive(ID3D11Device* device, const ShaderData& shaderData);
    //SquarePrimitive(ID3D11Device* device, const VECTOR2& drawPosition, const VECTOR2& size, const VECTOR4& color);
    ~SquarePrimitive() override = default;

    void render(
        ID3D11DeviceContext* immediateContext,
        float drawPositionX, float drawPositionY, 
        float width, float height,
        float r, float g, float b, float a
    );
    void render(ID3D11DeviceContext* immediateContext,
        float topLeftPositionX, float topLeftPositionY,
        float bottomRightPositionX, float bottomRightPositionY, float angle,
        float r, float g, float b, float a
    ) override;

    const VECTOR2& GetDrawPosition() const { return drawPosition; }
    const VECTOR2& GetSize() const { return size; }
private:
    std::vector<vertex> vertices;

    VECTOR2 drawPosition;
    VECTOR2 size;
};
