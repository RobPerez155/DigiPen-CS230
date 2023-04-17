//------------------------------------------------------------------------------
//
// File Name:	Teleporter.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "DGL.h"
#include "Entity.h"
#include "Physics.h"
#include "Transform.h"
#include "Vector2D.h"


#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	typedef struct Entity Entity;

	//------------------------------------------------------------------------------
	// Public Consts:
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

	// When an Entity goes off-screen, teleport it to the other side.
	// Params:
	//	 entity = Pointer to the Entity to be checked.
	void TeleporterUpdateEntity(Entity* entity)
	{
		Transform* transform = EntityGetTransform(entity);
		Physics* physics = EntityGetPhysics(entity);

		// Position of the screen edges
		
		//Call DGL_Window_GetSize() to get the X / Y dimensions of the window.
		DGL_Vec2 windowSize = DGL_Window_GetSize();

		//Call Vector2DScale to scale the dimensions by 0.5f to get the window half size.
		DGL_Vec2 halfWindowSize;
		Vector2DScale(&halfWindowSize, &windowSize, 0.5);

		//The bottom - left corner of the window is at –halfSize.
		DGL_Vec2 botLeft = { -halfWindowSize.x, -halfWindowSize.y };

		//The top - right corner of the window is at + halfSize.
		DGL_Vec2 topRight = halfWindowSize;

		if (entity == nullptr || transform == nullptr || physics == nullptr)
			return;

		// get velocity
		Vector2D const* position = TransformGetTranslation(transform);
		Vector2D const* velocity = PhysicsGetVelocity(physics);
		Vector2D point = { 0,0 };

		// Moving positive x direction
		if (velocity->x > 0)
		{
			if (position->x > topRight.x)
			{
				point.x = botLeft.x;
				point.y = position->y;
			}
		}
		//Moving in negative x direction
		else
		{
			if	(position->x < botLeft.x)
			{
				point.x = topRight.x;
				point.y = position->y;
			}
		}

		// Moving positive y direction
		if (velocity->y > 0)
		{
			if (position->y > topRight.x)
			{
				point.y = botLeft.y;
				point.x = position->x;
			}
		}
		//Moving in negative y direction
		else
		{
			if (position->y < botLeft.y)
			{
				point.y = topRight.y;
				point.x = position->x;
			}
		}

		if (point.x != 0 || point.y != 0)
		{
			TransformSetTranslation(transform, &point);
		}
	}

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

