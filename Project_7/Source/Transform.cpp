//------------------------------------------------------------------------------
//
// File Name:	Transform.c
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

#include "Transform.h"
#include "Matrix2D.h"
#include "Vector2D.h"
#include "DGL.h"
#include "Stream.h"
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

// An example of the structure to be defined in Transform.c.

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.

//struct Transform {
//	Vector2D translation;

//	float rotation;

//	Vector2D scale = { 1.0f, 1.0f };

//	Matrix2D matrix;

//	bool isDirty = true;
//};


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new Transform component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: You must initialize the scale values to non-zero values.)
// Returns:
// Pizza
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return nullptr.
//Allocate Memory, Initialize, Return what's allocated'

//Transform* TransformCreate()
//{
//	Transform* ptrTransform = new Transform();

//	if (ptrTransform != nullptr)
//	{
//		// Initialize value
//		DGL_Vec2 scale = { 10.0f, 10.0f };
//		ptrSetScale(scale);
//		ptrSetDirty(true);
//	}

//	return ptrTransform;
//}

Transform::Transform(Entity& parent) : Component(parent)
{
    scale = {1, 1};
    rotation = 0;
    translation = {0.0f, 0.0f};
    isDirty = false;
    Matrix2DIdentity(&matrix);
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





//void TransformFree(Transform** transform)
//{
//	if (*transform)
//		delete* transform;

//	*transform = nullptr;
//}

// Read the properties of a Transform component from a file.
// [NOTE: Read the translation value using StreamReadVector2D.]
// [NOTE: Read the rotation value using StreamReadFloat.]
// [NOTE: Read the scale value using StreamReadVector2D.]
// Params:
//	 transform = Pointer to the Transform component.
//	 stream = The data stream used for reading.
void Transform::Read(Stream stream)
{
    if (stream != nullptr)
    {
        StreamReadVector2D(stream, &translation);
        rotation = StreamReadFloat(stream);
        StreamReadVector2D(stream, &scale);
    }
}

//void Transform::Read(Stream stream)
//{
//	if (stream != nullptr)
//	{
//		StreamReadVector2D(stream, &translation);
//		rotation = StreamReadFloat(stream);
//		StreamReadVector2D(stream, &scale);
//	}
//}

// Get the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's translation,
//		else return a nullptr pointer.
const Vector2D& Transform::GetTranslation() const
{
    return translation;
}

//const Vector2D* Transform::GetTranslation() const
//{
//	if (this != nullptr) {
//		return &translation;
//	}
//	else {
//		return nullptr;
//	}
//}


// Get the rotation value of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return the component's rotation value (in radians),
//		else return 0.0f.
float Transform::GetRotation() const
{
        return rotation;
}

//float Transform::GetRotation(const Transform* transform)
//{
//	if (transform != nullptr) {
//		return rotation;
//	}
//	else {
//		return 0.0f;
//	}
//}


// Get the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's scale,
//		else return a nullptr pointer.
//const Vector2D* Transform::GetScale(const Transform* transform)
//{
//	Vector2D* zilch = nullptr;

//	if (transform != nullptr) {
//		return &scale;
//	}
//	else {
//		return zilch;
//	}
//}
const Vector2D& Transform::GetScale() const
{
    return scale;
}

// Set the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new translation.
void Transform::SetTranslation(const Vector2D& translation)
{
    this->translation = translation;
    isDirty = true;
}

//void Transform::SetTranslation(const Vector2D& translation)
//{
//	this->translation = translation;
//	this->isDirty = true;
//}


// Set the rotation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 rotation = The rotation value (in radians).
void Transform::SetRotation(float rotation)
{
    this->rotation = rotation;
    isDirty = true;
}

// Set the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new scale.
void Transform::SetScale(const Vector2D& scale)
{
    this->scale = scale;
    isDirty = true;
}

// Get the transform matrix, based upon translation, rotation and scale settings.
// (HINT: If the isDirty flag is true, then recalculate the transform matrix.)
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's matrix structure,
//		else return a nullptr pointer.
const Matrix2D& Transform::GetMatrix()
{
    if (isDirty)
    {
        //const Matrix2D*
        Matrix2D output;

        //o	Use the Matrix2DScale, Matrix2DRotRad, and Matrix2DTranslate functions to create separate matrices for the transform’s scale, rotation, and translation values.
        //Local variables
        Matrix2D scale, rotate, translate;

        Matrix2DScale(&scale, scale.x, scale.y);

        Matrix2DRotRad(&rotate, rotation);

        Matrix2DTranslate(&translate, translation.x, translation.y);

        Matrix2DConcat(&output, &rotate, &scale);

        Matrix2DConcat(&output, &translate, &output);

        isDirty = false;

        matrix = output;
    }

    return matrix;
}

//------------------------------------------------------------------------------


