//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 2
// Course:		CS230S23
//
// Copyright � 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "EntityFactory.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------


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

	// Build a single instance of the specified game object.
	// Params:
	//	 filename = The name of the file to be deserialized.
	// Returns:
	//	 If the filename is valid
	//	   then return a pointer to a new instance of the specified game object,
	//	   else NULL.
	Entity* EntityFactoryBuild(const char* filename);

	//------------------------------------------------------------------------------

