//------------------------------------------------------------------------------
//
// File Name:	Mesh.c
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

#include <stdlib.h> /* calloc, free */
#include "Mesh.h"
#include "DGL.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	typedef struct Mesh Mesh;

	//------------------------------------------------------------------------------
	// Public Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
	typedef struct Mesh
	{
		// The name of the Mesh.  This will be used later in the semester.
		char name[32];

		// Pointer to the DGL_Mesh resource.
		const DGL_Mesh* meshResource;

		// The draw mode to use when rendering the mesh (Usually "DGL_DM_TRIANGLELIST").
		DGL_DrawMode drawMode;
	} Mesh;


	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------
	Mesh* MeshQuad;
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Dynamically allocate a new Mesh object and create a quadrilateral mesh.
	// Params:
	//	 xHalfSize = The X half-size of the mesh.
	//	 yHalfSize = The Y half-size of the mesh.
	//   uSize = The U size of the mesh, relative to texture coordinates (0.0 .. 1.0).
	//   vSize = The V size of the mesh, relative to texture coordinates (0.0 .. 1.0).
	//	 name = A name for the mesh.
	// Returns:
	//	 If the mesh was created successfully,
	//	   then return a pointer to the created Mesh,
	//	   else return NULL.

	// Dynamically allocate a new Mesh object AND create a quadrilateral mesh.
	Mesh* MeshCreateQuad(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
	{
		//(Hint: Use calloc() to ensure that all member variables are initialized to 0.)
		Mesh* ptrMesh = calloc(1, sizeof(Mesh));
		
		if (ptrMesh 

		UNREFERENCED_PARAMETER(xHalfSize);
		UNREFERENCED_PARAMETER(yHalfSize);
		UNREFERENCED_PARAMETER(uSize);
		UNREFERENCED_PARAMETER(vSize);
		//UNREFERENCED_PARAMETER(name);

		return NULL;

		//Mesh* ptrMesh = calloc(1, sizeof(Mesh));

		//strcpy_s(name, _countof(name), name)
	// (Hint: The Mesh name can be stored using strcpy_s(). For example:
	//    strcpy_s(mesh->name, _countof(mesh->name), name); )

	// (Hint: The DGL_Mesh object must be created using 
	//	DGL_Graphics_StartMesh,
	//  DGL_Graphics_AddTriangle
	//	DGL_Graphics_EndMesh()
	}

	// Create a "spaceship" mesh.
	// (NOTE: This must be a "unit"-sized triangular mesh as described in the Project 2 instructions.)
	// (NOTE: The Mesh object must first be made using calloc().)
	// (NOTE: The Mesh name can be stored using strcpy_s().)
	// (NOTE: The DGL_Mesh object must be created using DGL_Graphics_StartMesh,
	//    DGL_Graphics_AddTriangle, and DGL_Graphics_EndMesh.)
	// Returns:
	//	 If the mesh was created successfully,
	//	   then return a pointer to the created Mesh,
	//	   else return NULL.
	Mesh* MeshCreateSpaceship(void)
	{
		return NULL;
	}

	// Render a mesh.
	// (NOTE: This is done using DGL_Graphics_DrawMesh().)
	// Params:
	//   mesh = Pointer to a Mesh to be rendered.
	void MeshRender(const Mesh* mesh)
	{
		UNREFERENCED_PARAMETER(mesh);
	}

	// Free the memory associated with a mesh.
	// (NOTE: The DGL_Mesh object must be freed using DGL_Graphics_FreeMesh().)
	// (NOTE: The Mesh object must be freed using free().
	// (NOTE: The Mesh pointer must be set to NULL.)
	// Params:
	//   mesh = Pointer to the Mesh pointer.
	void MeshFree(Mesh** mesh)
	{
		UNREFERENCED_PARAMETER(mesh);
		//DGL_Graphics_FreeMesh(*mesh);
	}

