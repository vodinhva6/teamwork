#pragma once

#include "MyMath.h"

#include <d3d11.h>
#include <wrl.h>

#include "Sprite.h"

class Square : public Sprite
{
public:
    Square(ID3D11Device* device, const VECTOR2& drawPosition, const VECTOR2& size, const VECTOR4& color);
    ~Square() override = default;

    void render(ID3D11DeviceContext* immediateContext, float dx, float dy, float dw, float dh) override;
private:
    std::vector<vertex> vertices;

    VECTOR2 drawPosition;
    VECTOR2 size;
};
