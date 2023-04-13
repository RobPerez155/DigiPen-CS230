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
	typedef struct Transform
	{
		// The translation (or world position) of an entity.
		Vector2D	translation;

		// The rotation (or orientation) of an entity (in radians).
		float	rotation;

		// The scale (or size) of an entity.
		// (Hint: This should be initialized to (1, 1).)
		Vector2D	scale;

		Matrix2D matrix;

		bool isDirty;

	} Transform;


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
	//	   else return NULL.
	//Allocate Memory, Initialize, Return what's allocated'
	Transform* TransformCreate(void)
	{
		Transform* ptrTransform = calloc(1, sizeof(Transform));

		if (ptrTransform != NULL)
		{
			//Initialize value
			ptrTransform->scale = (DGL_Vec2){ 10.0f, 10.0f };
			ptrTransform->isDirty = true;
		}

		return ptrTransform;
	}

	// Dynamically allocate a clone of an existing Transform.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
	Transform* TransformClone(const Transform* other)
	{
		if (other == NULL)
		{
			return NULL;
		}

		Transform* transformClone = calloc(1, sizeof(Transform));

		if (transformClone == NULL)
		{
			return NULL;
		}

		*transformClone = *other;

		return transformClone;
	}

	// Free the memory associated with a Transform component.
	// (NOTE: The Transform pointer must be set to NULL.)
	// Params:
	//	 transform = Pointer to the Transform pointer.
	void TransformFree(Transform** transform)
	{
		if (*transform)
			free(*transform);

		*transform = NULL;
	}
	
	// Read the properties of a Transform component from a file.
	// [NOTE: Read the translation value using StreamReadVector2D.]
	// [NOTE: Read the rotation value using StreamReadFloat.]
	// [NOTE: Read the scale value using StreamReadVector2D.]
	// Params:
	//	 transform = Pointer to the Transform component.
	//	 stream = The data stream used for reading.
	void TransformRead(Transform* transform, Stream stream)
	{
		if (stream != NULL)
		{
			StreamReadVector2D(stream, &transform->translation);
			transform->rotation = StreamReadFloat(stream);
			StreamReadVector2D(stream, &transform->scale);
		}
	}

	// Get the translation of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	// Returns:
	//	 If the Transform pointer is valid,
	//		then return a pointer to the component's translation,
	//		else return a NULL pointer.
	const Vector2D* TransformGetTranslation(const Transform* transform)
	{
		if (transform != NULL) {
			return &transform->translation;
		}
		else {
			return NULL;
		}
	}

	// Get the rotation value of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	// Returns:
	//	 If the Transform pointer is valid,
	//		then return the component's rotation value (in radians),
	//		else return 0.0f.
	float TransformGetRotation(const Transform* transform)
	{
		if (transform != NULL) {
			return transform->rotation;
		}
		else {
			return 0.0f;
		}
	}

	// Get the scale of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	// Returns:
	//	 If the Transform pointer is valid,
	//		then return a pointer to the component's scale,
	//		else return a NULL pointer.
	const Vector2D* TransformGetScale(const Transform* transform)
	{
		Vector2D* zilch = NULL;

		if (transform != NULL) {
			return &transform->scale;
		}
		else {
			return zilch;
		}
	}

	// Set the translation of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	//	 translation = Pointer to the new translation.
	void TransformSetTranslation(Transform* transform, const Vector2D* translation)
	{
		transform->translation = *translation;
		transform->isDirty = true;
	}

	// Set the rotation of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	//	 rotation = The rotation value (in radians).
	void TransformSetRotation(Transform* transform, float rotation)
	{
		transform->rotation = rotation;
		transform->isDirty = true;
	}

	// Set the scale of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	//	 translation = Pointer to the new scale.
	void TransformSetScale(Transform* transform, const Vector2D* scale)
	{
		transform->scale = *scale;
		transform->isDirty = true;
	}

	// Get the transform matrix, based upon translation, rotation and scale settings.
// (HINT: If the isDirty flag is true, then recalculate the transform matrix.)
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's matrix structure,
//		else return a NULL pointer.
	const Matrix2D* TransformGetMatrix(Transform* transform)
	{
		if (transform->isDirty)
		{

		//const Matrix2D*
		Matrix2D output;

		//o	Use the Matrix2DScale, Matrix2DRotRad, and Matrix2DTranslate functions to create separate matrices for the transform’s scale, rotation, and translation values.
		//Local variables
		Matrix2D scale, rotate, translate;

		Matrix2DScale(&scale, transform->scale.x, transform->scale.y);

		Matrix2DRotRad(&rotate, transform->rotation);

		Matrix2DTranslate(&translate, transform->translation.x, transform->translation.y);

		Matrix2DConcat(&output, &rotate, &scale);

		Matrix2DConcat(&output, &translate, &output);

		transform->isDirty = false;

		transform->matrix = output;
		}
		
		return &transform->matrix;
	}

	//------------------------------------------------------------------------------

