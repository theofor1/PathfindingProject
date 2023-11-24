#pragma once

template <typename ScalarType>
class Vector3D
{
public:
    explicit Vector3D(ScalarType _X = ScalarType{}, ScalarType _Y = ScalarType{}, ScalarType _Z = ScalarType{});

    friend std::ostream &operator<<(std::ostream &o, const Vector3D<ScalarType> &p)
    {
        o << "pt(" << p.X << ", " << p.Y << ", " << p.Z << ")";
        return o;
    }

    Vector3D<ScalarType> operator+(const Vector3D<ScalarType> &OtherVector) const;
    Vector3D<ScalarType> operator-(const Vector3D<ScalarType> OtherVector) const;
    Vector3D<ScalarType> operator*(const Vector3D<ScalarType> OtherVector) const;

    float GetSquareLength() const;
    float GetLength() const;
    Vector3D<ScalarType> GetNormalized();

    ScalarType X;
    ScalarType Y;
    ScalarType Z;
};

#include "Vector3D.hxx"
