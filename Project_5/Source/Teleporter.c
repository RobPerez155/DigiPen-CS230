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

		UNREFERENCED_PARAMETER(entity);
		UNREFERENCED_PARAMETER(botLeft);
		UNREFERENCED_PARAMETER(topRight);
	}

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

