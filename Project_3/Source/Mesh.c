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

	// Dynamically allocate a new Mesh object AND create a quadrilateral mesh.
	Mesh* MeshCreateQuad(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
	{
		//(Hint: Use calloc() to ensure that all member variables are initialized to 0.)
		Mesh* ptrMesh = calloc(1, sizeof(Mesh));
		
		DGL_Graphics_StartMesh(); // Like taking out pen

		if (ptrMesh != NULL) 
		{

			strcpy_s(ptrMesh->name, _countof(ptrMesh->name), name);

			DGL_Graphics_StartMesh();

			DGL_Graphics_AddTriangle(
        &(DGL_Vec2){ -xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, vSize },
        &(DGL_Vec2){  xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize, 0.0f },
        &(DGL_Vec2){  xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize, vSize });
      DGL_Graphics_AddTriangle(
        &(DGL_Vec2){ -xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, vSize },
        &(DGL_Vec2){ -xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, 0.0f },
        &(DGL_Vec2){  xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize, 0.0f });

			ptrMesh->meshResource = DGL_Graphics_EndMesh(); // Putting pen away

			return ptrMesh;
		}

		return NULL;
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
		Mesh* spaceship = calloc(1, sizeof(Mesh));
		
		if (spaceship != NULL) 
		{
			strcpy_s(spaceship->name, _countof(spaceship->name), "spaceship");

			DGL_Graphics_StartMesh();

			DGL_Graphics_AddTriangle(
			&(DGL_Vec2){  0.5f,  0.0f }, &(DGL_Color){ 1.0f, 1.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, 0.0f },
			&(DGL_Vec2){ -0.5f, -0.5f }, &(DGL_Color){ 1.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, 0.0f },
			&(DGL_Vec2){ -0.5f,  0.5f }, &(DGL_Color){ 1.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, 0.0f });
	
			spaceship->meshResource = DGL_Graphics_EndMesh();

			return spaceship;
		}
		else {
			return NULL;
		}

	}

	// Render a mesh.
	// (NOTE: This is done using DGL_Graphics_DrawMesh().)
	// Params:
	//   mesh = Pointer to a Mesh to be rendered.
	void MeshRender(const Mesh* mesh)
	{
		DGL_Graphics_DrawMesh(mesh->meshResource, mesh->drawMode);
	}

	// Free the memory associated with a mesh.
	// (NOTE: The DGL_Mesh object must be freed using DGL_Graphics_FreeMesh().)
	// (NOTE: The Mesh object must be freed using free().
	// (NOTE: The Mesh pointer must be set to NULL.)
	// Params:
	//   mesh = Pointer to the Mesh pointer.
	void MeshFree(Mesh** mesh) //this is a pointer to a pointer Mesh
	{
		Mesh* ptrMesh = *mesh; //dereference mesh pointer so we can get meshResource in the next statement
		DGL_Graphics_FreeMesh(&ptrMesh->meshResource); //get address of meshResource
		free(*mesh);
		*mesh = NULL;
	}
