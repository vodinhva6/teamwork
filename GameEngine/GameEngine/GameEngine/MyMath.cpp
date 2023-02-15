#include "MyMath.h"

VECTOR2 MyMath::Normalize(const VECTOR2& v)
{
    DirectX::XMVECTOR Vec = DirectX::XMLoadFloat2(&v);
    VECTOR2 vec;
    DirectX::XMStoreFloat2(&vec,DirectX::XMVector2Normalize(Vec));

    return vec;
}

VECTOR3 MyMath::Cross(const VECTOR3& v1, const VECTOR3& v2)
{
    VECTOR3 cross = {};
    VECTOR3 norV1 = Normalize(v1);
    VECTOR3 norV2 = Normalize(v2);
    DirectX::XMStoreFloat3(&cross,DirectX::XMVector3Cross(DirectX::XMVectorSet(norV1.x, norV1.y, norV1.z, 0), DirectX::XMVectorSet(norV2.x, norV2.y, norV2.z, 0)));
    return cross;
}

VECTOR3 MyMath::Normalize(const VECTOR3& v)
{
    VECTOR3 norm = {};
    DirectX::XMStoreFloat3(&norm,DirectX::XMVector3Normalize(DirectX::XMVectorSet(v.x, v.y, v.z, 0)));
    return norm;
}

VECTOR3 MyMath::Lerp(const VECTOR3& a, const VECTOR3& b, float t)
{
    DirectX::XMVECTOR A = DirectX::XMLoadFloat3(&a);
    DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&b);

    A = DirectX::XMVectorLerp(A, B, t);

    VECTOR3 newA;
    DirectX::XMStoreFloat3(&newA, A);

    return newA;
}

VECTOR3 MyMath::ScaleVector3(const VECTOR3& v, float scale)
{
    DirectX::XMVECTOR Vec = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&v));
    Vec = DirectX::XMVectorScale(Vec, scale);
    VECTOR3 vec;
    DirectX::XMStoreFloat3(&vec, Vec);
    return vec;
}

VECTOR3 MyMath::TransformCoordMaxtrix(const VECTOR3& v, const DirectX::XMFLOAT4X4& transform)
{
    DirectX::XMVECTOR V = DirectX::XMLoadFloat3(&v);
    DirectX::XMMATRIX M = DirectX::XMLoadFloat4x4(&transform);
    VECTOR3 c;
    DirectX::XMStoreFloat3(&c,DirectX::XMVector3TransformCoord(V, M));

    return c;
}

VECTOR3 MyMath::GetFowardVector(const float& x, const float& y, const float& z)
{
    DirectX::XMMATRIX M = DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(x), DirectX::XMConvertToRadians(y), DirectX::XMConvertToRadians(z));
    DirectX::XMFLOAT4X4 m;
    DirectX::XMStoreFloat4x4(&m, M);

    return VECTOR3(m._31,m._32,m._33);
}

VECTOR4 MyMath::Normalize(const VECTOR4& v)
{
    VECTOR4 norm = {};
    DirectX::XMStoreFloat4(&norm, DirectX::XMVector3Normalize(DirectX::XMLoadFloat4(&v)));
    return norm;
}

float MyMath::Dot(const VECTOR3& v1, const VECTOR3& v2)
{
    float dot = 0.0f;
    DirectX::XMStoreFloat(&dot,DirectX::XMVector3Dot(DirectX::XMVectorSet(v1.x, v1.y, v1.z, 0), DirectX::XMVectorSet(v2.x, v2.y, v2.z, 0)));
    dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return dot;
}

float MyMath::AngleBetweenVectorReturnDegrees(const VECTOR3& v1, const VECTOR3& v2)
{
    DirectX::XMVECTOR V1 = DirectX::XMLoadFloat3(&v1);
    DirectX::XMVECTOR V2 = DirectX::XMLoadFloat3(&v2);
    V1 = DirectX::XMVector3Normalize(V1);
    V2 = DirectX::XMVector3Normalize(V2);
    float angle = DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenNormals(V1, V2));
    angle = DirectX::XMConvertToDegrees(angle);
    if (DirectX::XMVectorGetY(DirectX::XMVector3Cross(V1,V2)) < 0)
    {
        angle *= -1;// 360 - angle;
    }
    return angle;
}

float MyMath::AngleBetweenVectorReturnRadian(const VECTOR3& v1, const VECTOR3& v2)
{
    DirectX::XMVECTOR V1 = DirectX::XMLoadFloat3(&v1);
    DirectX::XMVECTOR V2 = DirectX::XMLoadFloat3(&v2);
    V1 = DirectX::XMVector3Normalize(V1);
    V2 = DirectX::XMVector3Normalize(V2);
    return DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenNormals(V1, V2));
}

float MyMath::Length(const VECTOR3& v)
{
    float length = 0;
    DirectX::XMVECTOR Vec = DirectX::XMLoadFloat3(&v);
    DirectX::XMStoreFloat(&length, DirectX::XMVector3Length(Vec));
    return length;
}

float MyMath::Length(const VECTOR4& v)
{
    float length = 0;
    DirectX::XMVECTOR Vec = DirectX::XMLoadFloat4(&v);
    DirectX::XMStoreFloat(&length, DirectX::XMVector4Length(Vec));
    return length;
}

float MyMath::Length(const VECTOR2& v)
{
    float length = 0;
    DirectX::XMVECTOR Vec = DirectX::XMLoadFloat2(&v);
    DirectX::XMStoreFloat(&length, DirectX::XMVector3Length(Vec));
    return length;
}

float MyMath::floatEquallity(float x)
{
    return roundf(x);
}

int MyMath::toInt(float x)
{
    x = roundf(x);
    return int(x);
}

void MyMath::toZero(float& x, int dozen)
{
    
    if (x > (-1.0f / powf(10, (float)dozen)) && x < (1.0f / powf(10, (float)dozen)))
        x = 0.0f;
}

bool MyMath::Vector3AndVector3Equal(const VECTOR3& vec1, const VECTOR3& vec2, int dozen)
{
    VECTOR3 Vec = vec1 - vec2;
    toZero(Vec.x,dozen);
    toZero(Vec.y,dozen);
    toZero(Vec.z,dozen);
    return(Vec.x == 0 && Vec.y == 0 && Vec.z == 0);
    
}

bool MyMath::Vector4AndVector4Equal(const VECTOR4& vec1, const VECTOR4& vec2, int dozen)
{
    VECTOR4 Vec = vec1 - vec2;
    toZero(Vec.x,dozen);
    toZero(Vec.y,dozen);
    toZero(Vec.z,dozen);
    toZero(Vec.w,dozen);
    return(Vec.x == 0 && Vec.y == 0 && Vec.z == 0 && Vec.w == 0);
}

float MyMath::convertToRadian(float angle)
{
    return DirectX::XMConvertToRadians(angle);
}

float MyMath::convertToRadian(int angle)
{
    return convertToRadian((float)angle);
}

float MyMath::EqualTo10(const float& x)
{
    int tX = int(x);
    if ((tX % 10) != 0)
    {
        float t = tX / 10.0f;
        return roundf(t) * 10;
    }
    return x;
}

