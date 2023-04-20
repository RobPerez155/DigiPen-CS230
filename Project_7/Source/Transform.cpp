//------------------------------------------------------------------------------
//
// File Name:	Transform.cpp
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 2
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "DGL.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Stream.h"
#include "Transform.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
Transform::Transform(Entity& parent) : Component(parent)
{
  scale = {1, 1};
  rotation = 0;
  translation = {0.0f, 0.0f};
  isDirty = false;
  Matrix2DIdentity(&matrix);
  ;
}

Component* Transform::Clone(Entity& newParent) const
{
  
  Transform* transformClone = new Transform(newParent);

  if (transformClone == nullptr)
  {
    return nullptr;
  }

  transformClone->matrix = matrix;
  transformClone->translation = translation;
  transformClone->scale = scale;
  transformClone->rotation = rotation;
  transformClone->isDirty = isDirty;
  
  return transformClone;
}

void Transform::Read(Stream stream)
{
  if (stream != nullptr)
  {
    StreamReadVector2D(stream, &translation);
    rotation = StreamReadFloat(stream);
    StreamReadVector2D(stream, &scale);
  }
}

const Vector2D& Transform::GetTranslation() const
{
  return translation;
}

float Transform::GetRotation() const
{
  return rotation;
}

const Vector2D& Transform::GetScale() const
{
  return scale;
}

void Transform::SetTranslation(const Vector2D& newTranslation)
{
  this->translation = newTranslation;
  isDirty = true;
}

void Transform::SetRotation(float newRotation)
{
  this->rotation = newRotation;
  isDirty = true;
}

void Transform::SetScale(const Vector2D& newScale)
{
  this->scale = newScale;
  isDirty = true;
}

const Matrix2D& Transform::GetMatrix()
{
  if (isDirty)
  {
    Matrix2D output;
    
    Matrix2D newScale, rotate, translate;

    Matrix2DScale(&newScale, this->scale.x, this->scale.y);

    Matrix2DRotRad(&rotate, rotation);

    Matrix2DTranslate(&translate, translation.x, translation.y);

    Matrix2DConcat(&output, &rotate, &newScale);

    Matrix2DConcat(&output, &translate, &output);

    isDirty = false;

    matrix = output;
  }

  return matrix;
}

//------------------------------------------------------------------------------


