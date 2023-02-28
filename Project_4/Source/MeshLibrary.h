//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S22
//
// Copyright © 2022 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

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

typedef struct Mesh Mesh;

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

// Initialize the Mesh Manager.
// (NOTE: Make sure to initialize all memory to zero.)
void MeshLibraryInit();

// Create a mesh and add it to the mesh manager.
// 1: Use sprintf_s() to construct a path name using meshName
//	   (HINT: The correct path name should be constructed using "Data/&s.txt".)
// 2: Call StreamOpen(), passing the pathname
// 3: If the stream was opened successfully,
//	  a: Call MeshCreate() to create an empty Mesh object.
//    b: Call MeshRead() to construct a mesh using data read from the file
//	  c: Call MeshLibraryAdd(), passing the created mesh
//	  d: Close the stream
//	  e: Return the created mesh
// Params:
//	 meshName = The name of the mesh to be created.
// Returns:
//	 If the mesh was created successfully,
//	   then return a pointer to the created mesh,
//	   else return NULL.
const Mesh* MeshLibraryBuild(const char * meshName);

// Free all Mesh objects in the Mesh Manager.
// (NOTE: You must call MeshFree() to free each Mesh object.)
// (HINT: The list should contain nothing but NULL pointers once this function is done.)
void MeshLibraryFreeAll();

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

