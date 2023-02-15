#include "BoundingSphere.h"
#include <vector>
BoundingSphere::BoundingSphere(ID3D11Device* device, const float& radius, const VECTOR3& offset):
    radius_(radius),offset_(offset)
{
    std::vector<vertex> Vertexies;
    float angleX = 0.0f;
    vertex Vertex = {};
    while (angleX <= 360.0f)
    {
        Vertex.position.y = offset.x + radius*cosf(DirectX::XMConvertToRadians(angleX));
        Vertex.position.x = offset.y + radius*sinf(DirectX::XMConvertToRadians(angleX));
        Vertex.position.z = offset.z + 0;
        Vertexies.push_back(Vertex);
        angleX += 15.0f;
    }
    angleX = 0;
    while (angleX != 360.0f)
    {
        for (int i = + 1; i < 24; i++)
        {
            DirectX::XMVECTOR position = {
                Vertexies[i].position.x,Vertexies[i].position.y,Vertexies[i].position.z
            };
            position = DirectX::XMVector3TransformCoord(position, DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angleX)));
            vertex Vertex = {};
            DirectX::XMStoreFloat3(&Vertex.position, position);
            Vertexies.push_back(Vertex);
        }
        angleX += 15.0f;
    }
    //
   
    


    std::vector<uint32_t> indicess;
    for (int i = 0; i < Vertexies.size(); i++)
    {
        indicess.push_back(i);
        if (i + 23 < Vertexies.size())
        {
            indicess.push_back(i);
            indicess.push_back(i+23);
        }
    }

    create_com_buffers(device, &Vertexies.at(0), Vertexies.size(), &indicess.at(0), indicess.size());


}
