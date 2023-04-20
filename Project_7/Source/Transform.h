//------------------------------------------------------------------------------
//
// File Name:	Transform.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "Component.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Stream.h"
#include "DGL.h"


//------------------------------------------------------------------------------
class Transform : public Component
{
public:
	__inline static Type type() { return Type::Transform; }
	//using explicit to specify that we want to see the "Transform" call on creations of transforms
	explicit Transform(Entity& parent);
	
	Component* Clone(Entity& newParent) const override;
	
	void Read(Stream stream) override;
	
	const Matrix2D& GetMatrix();
	
	const Vector2D& GetTranslation() const;
	//const Vector2D* GetTranslation(const Transform* transform);
	
	float GetRotation() const;
	
	const Vector2D& GetScale() const;

	void Update( float dt);
	
	void SetTranslation(const Vector2D& newTranslation);
	
	void SetRotation(float newRotation);
	
	void SetScale(const Vector2D& newScale);


private:
	// The translation (or world position) of an entity.
	Vector2D	translation;

	// The rotation (or orientation) of an entity (in radians).
	float	rotation;

	Vector2D	scale;

	Matrix2D matrix;

	bool isDirty;

};


#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

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
#if 0
// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
	typedef struct Transform
	{
		// The translation (or world position) of an entity.
		Vector2D	translation;

		// The rotation (or orientation) of an entity (in radians).
		float	rotation;

		// The scale (or size) of an entity.
		// (Hint: This should be initialized to (1, 1).)
		Vector2D	scale;

		// True if the transformation matrix needs to be recalculated.
		// (Hint: This should be initialized to true.)
		// (Hint: This should be set to true when the Transform data changes.)
		bool	isDirty;

		// The transformation matrix resulting from concatenating the matrices
		//   representing the translation, rotation, and scale transformations.
		//	 (e.g. matrix = Translation*Rotation*Scale matrices)
		Matrix2D	matrix;

	} Transform;
#endif

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	//// Dynamically allocate a new Transform component.
	//// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	//// (Hint: You must initialize the scale values to non-zero values.)
	//// Returns:
	////	 If the memory allocation was successful,
	////	   then return a pointer to the allocated memory,
	////	   else return nullptr.
	//Transform* TransformCreate(void);
	//
	//// Dynamically allocate a clone of an existing Transform.
	//// (Hint: Perform a shallow copy of the member variables.)
	//// Params:
	////	 other = Pointer to the component to be cloned.
	//// Returns:
	////	 If 'other' is valid and the memory allocation was successful,
	////	   then return a pointer to the cloned component,
	////	   else return nullptr.
	//Transform* TransformClone(const Transform* other);
	//
	//// Free the memory associated with a Transform component.
	//// (NOTE: The Transform pointer must be set to nullptr.)
	//// Params:
	////	 transform = Pointer to the Transform pointer.
	//void TransformFree(Transform** transform);
	//
	//// Read the properties of a Transform component from a file.
	//// [NOTE: Read the translation value using StreamReadVector2D.]
	//// [NOTE: Read the rotation value using StreamReadFloat.]
	//// [NOTE: Read the scale value using StreamReadVector2D.]
	//// Params:
	////	 transform = Pointer to the Transform component.
	////	 stream = The data stream used for reading.
	//void TransformRead(Transform* transform, Stream stream);
	//
	//// Get the transform matrix, based upon translation, rotation and scale settings.
	//// (HINT: If the isDirty flag is true, then recalculate the transform matrix.)
	//// Params:
	////	 transform = Pointer to the Transform component.
	//// Returns:
	////	 If the Transform pointer is valid,
	////		then return a pointer to the component's matrix structure,
	////		else return a nullptr pointer.
	//const Matrix2D* GetMatrix(Transform* transform);
	//
	//// Get the translation of a Transform component.
	//// Params:
	////	 transform = Pointer to the Transform component.
	//// Returns:
	////	 If the Transform pointer is valid,
	////		then return a pointer to the component's translation,
	////		else return a nullptr pointer.
	//const Vector2D* GetTranslation(const Transform* transform);
	//
	//// Get the rotation value of a Transform component.
	//// Params:
	////	 transform = Pointer to the Transform component.
	//// Returns:
	////	 If the Transform pointer is valid,
	////		then return the component's rotation value (in radians),
	////		else return 0.0f.
	//float GetRotation(const Transform* transform);
	//
	//// Get the scale of a Transform component.
	//// Params:
	////	 transform = Pointer to the Transform component.
	//// Returns:
	////	 If the Transform pointer is valid,
	////		then return a pointer to the component's scale,
	////		else return a nullptr pointer.
	//const Vector2D* GetScale(const Transform* transform);
	//
	//// Set the translation of a Transform component.
	//// Params:
	////	 transform = Pointer to the Transform component.
	////	 translation = Pointer to the new translation.
	//void SetTranslation(Transform* transform, const Vector2D* translation);
	//
	//// Set the rotation of a Transform component.
	//// Params:
	////	 transform = Pointer to the Transform component.
	////	 rotation = The rotation value (in radians).
	//void SetRotation(Transform* transform, float rotation);
	//
	//// Set the scale of a Transform component.
	//// Params:
	////	 transform = Pointer to the Transform component.
	////	 translation = Pointer to the new scale.
	//void SetScale(Transform* transform, const Vector2D* scale);

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

//#ifndef TRANSFORM_H
//#define TRANSFORM_H
//
//#include "Vector2D.h"
//#include "Matrix2D.h"
//#include "Stream.h"
//
//class Transform
//{
//public:
//	Transform();
//	~Transform();
//
//	Vector2D GetTranslation() const;
//	float GetRotation() const;
//	Vector2D GetScale() const;
//	Matrix2D GetMatrix();
//
//	void SetTranslation(const Vector2D& translation);
//	void SetRotation(float rotation);
//	void SetScale(const Vector2D& scale);
//
//	Transform* Clone() const;
//	void Free();
//
//private:
//	Vector2D translation;
//	float rotation;
//	Vector2D scale;
//	Matrix2D matrix;
//	bool isDirty;
//
//	void Read(Stream& stream);
//};
//
//Transform* TransformCreate();
//void TransformRead(Transform& transform, Stream& stream);
//void TransformWrite(const Transform& transform, Stream& stream);
//const Vector2D* GetTranslation(const Transform& transform);
//float GetRotation(const Transform& transform);
//const Vector2D* GetScale(const Transform& transform);
//void SetTranslation(Transform& transform, const Vector2D& translation);
//void SetRotation(Transform& transform, float rotation);
//void SetScale(Transform& transform, const Vector2D& scale);
//const Matrix2D* GetMatrix(Transform& transform);
