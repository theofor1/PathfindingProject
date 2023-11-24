#pragma once

#include "Vector3D.h"

template <typename ScalarType>
Vector3D<ScalarType>::Vector3D(ScalarType _X, ScalarType _Y, ScalarType _Z)
    : X(_X), Y(_Y), Z(_Z)
{
}

template <typename ScalarType>
inline Vector3D<ScalarType> Vector3D<ScalarType>::operator+(const Vector3D<ScalarType> &OtherVector) const
{
    Vector3D<ScalarType> NewVector;
    NewVector.X = this->X + OtherVector.X;
    NewVector.Y = this->Y + OtherVector.Y;
    NewVector.Z = this->Z + OtherVector.Z;
    return NewVector;
}

template <typename ScalarType>
inline Vector3D<ScalarType> Vector3D<ScalarType>::operator-(const Vector3D<ScalarType> OtherVector) const 
{
    Vector3D<ScalarType> NewVector;
    NewVector.X = this->X - OtherVector.X;
    NewVector.Y = this->Y - OtherVector.Y;
    NewVector.Z = this->Z - OtherVector.Z;
    return NewVector;
}

template <typename ScalarType>
inline Vector3D<ScalarType> Vector3D<ScalarType>::operator*(const Vector3D<ScalarType> OtherVector) const 
{
    Vector3D<ScalarType> NewVector;
    NewVector.X = this->X * OtherVector.X;
    NewVector.Y = this->Y * OtherVector.Y;
    NewVector.Z = this->Z * OtherVector.Z;
    return NewVector;
}

template <typename ScalarType>
inline float Vector3D<ScalarType>::GetSquareLength() const
{
    return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
}

template <typename ScalarType>
inline float Vector3D<ScalarType>::GetLength() const
{
    return sqrt(GetLength());
}

template <typename ScalarType>
inline Vector3D<ScalarType> GetNormalized()
{
    // à coder
    return Vector3D<ScalarType>;
}


