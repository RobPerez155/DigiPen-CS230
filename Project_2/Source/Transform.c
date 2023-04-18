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
		}

		return ptrTransform;
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
		Vector2D* zilch = NULL;

		if (transform != NULL) {
			return &transform->translation;
		}
		else {
			// Could be a problem
			return zilch;
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
			// Could be a problem
			return zilch;
		}
	}

	// Set the translation of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	//	 translation = Pointer to the new translation.
	void TransformSetTranslation(Transform* transform, const Vector2D* translation)
	{
		// Could be a problem
		transform->translation = *translation;
	}

	// Set the rotation of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	//	 rotation = The rotation value (in radians).
	void TransformSetRotation(Transform* transform, float rotation)
	{
		transform->rotation = rotation;
	}

	// Set the scale of a Transform component.
	// Params:
	//	 transform = Pointer to the Transform component.
	//	 translation = Pointer to the new scale.
	void TransformSetScale(Transform* transform, const Vector2D* scale)
	{
		transform->scale = *scale;
	}

	//------------------------------------------------------------------------------

