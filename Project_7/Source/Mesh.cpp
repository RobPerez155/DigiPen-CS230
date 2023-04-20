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
#include "Stream.h"
#include "DGL.h"
#include "Trace.h"
#include "Vector2D.h"

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
		DGL_Mesh* meshResource;
		//const DGL_Mesh* meshResource;

		// The draw mode to use when rendering the mesh (Usually "DGL_DM_TRIANGLELIST").
		DGL_DrawMode drawMode;
	} Mesh;


	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------
	Mesh* MeshQuad;
	//------------------------------------------------------------------------------
	// Private Functions:

	static void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name);
	//------------------------------------------------------------------------------
	
	void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
	{
		DGL_Graphics_StartMesh(); // Like taking out pen

		strcpy_s(mesh->name, _countof(mesh->name), name);

		//DGL_Graphics_AddTriangle(
		//	&(DGL_Vec2){ -xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, vSize },
		//	&(DGL_Vec2){  xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize, 0.0f },
		//	&(DGL_Vec2){  xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize, vSize });
		//DGL_Graphics_AddTriangle(
		//	&(DGL_Vec2){ -xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, vSize },
		//	&(DGL_Vec2){ -xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, 0.0f },
		//	&(DGL_Vec2){  xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize, 0.0f });

		DGL_Vec2 v1 = { -xHalfSize, -yHalfSize };
		DGL_Color c1 = { 0.0f, 0.0f, 0.0f, 1.0f };
		DGL_Vec2 uv1 = { 0.0f, vSize };

		DGL_Vec2 v2 = { xHalfSize, yHalfSize };
		DGL_Color c2 = { 0.0f, 0.0f, 0.0f, 1.0f };
		DGL_Vec2 uv2 = { uSize, 0.0f };

		DGL_Vec2 v3 = { xHalfSize, -yHalfSize };
		DGL_Color c3 = { 0.0f, 0.0f, 0.0f, 1.0f };
		DGL_Vec2 uv3 = { uSize, vSize };

		DGL_Graphics_AddTriangle(&v1, &c1, &uv1, &v2, &c2, &uv2, &v3, &c3, &uv3);

		v2 = { -xHalfSize, yHalfSize };
		c2 = { 0.0f, 0.0f, 0.0f, 1.0f };
		uv2 = { 0.0f, 0.0f };

		v3 = { xHalfSize, yHalfSize };
		c3 = { 0.0f, 0.0f, 0.0f, 1.0f };
		uv3 = { uSize, 0.0f };

		DGL_Graphics_AddTriangle(&v1, &c1, &uv1, &v2, &c2, &uv2, &v3, &c3, &uv3);


		mesh->meshResource = DGL_Graphics_EndMesh(); // Putting pen away
	}

// Dynamically allocate a new Mesh object but leave it empty.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the mesh was created successfully,
//	   then return a pointer to the created Mesh,
//	   else return nullptr.
	Mesh* MeshCreate()
	{
		//Mesh* newMesh = calloc(1, sizeof(Mesh));
		Mesh* newMesh = new Mesh();

		if (newMesh)
		{
			return newMesh;
		}
		else {
			return nullptr;
		}
	}

	// Read the properties of a Mesh object from a file.
// (NOTE: First, read a token from the file and verify that it is "Mesh".)
// (NOTE: Second, read a token and store it in the Mesh's name variable.)
// (NOTE: Third, read an integer indicating the number of vertices to be read.)
// (NOTE: For each vertex, read a Vector2D (position), a DGL_Color (color), and a Vector2D (UV).)
// (HINT: Call DGL_Graphics_AddVertex() to add a single vertex to the mesh.)
// Params:
//   mesh = Pointer to the Mesh.
//	 stream = The data stream used for reading.
	void MeshRead(Mesh* mesh, Stream stream)
	{
		// (NOTE: First, read a token from the file and verify that it is "Mesh".)
		if (stream != nullptr) 
		{
			std::string token = StreamReadToken(stream);

			// (NOTE: Second, read a token and store it in the Mesh's name variable.)
			if (token == "Quad")
			// (strncmp(token, "Quad", _countof("Quad")) == 0)
			{
				//Vector2D* position = calloc(1, sizeof(Vector2D));
				Vector2D* position = new Vector2D();


				StreamReadVector2D(stream, position);
				
				if (position == nullptr)
					return;

				Vector2D halfSized = { position->x, position->y };
				
				int cols = StreamReadInt(stream);
				int rows = StreamReadInt(stream);
				std::string meshName = StreamReadToken(stream);

				float invCols = 1.0f / static_cast<float>(cols);
				float invRows = 1.0f / static_cast<float>(rows);
				
				// MeshBuildQuad(mesh,halfSized.x, halfSized.y, (float)1/cols, (float)1/rows, meshName.c_str());
				MeshBuildQuad(mesh,halfSized.x, halfSized.y, invCols, invRows, meshName.c_str());
			}

			if (token == "Mesh")
			// (strncmp(token, "Mesh", _countof("Mesh")) != 0)
			{
				TraceMessage("Expected token 'Mesh' not found");
				return;
			}

			token = StreamReadToken(stream);
			strcpy_s(mesh->name, _countof(mesh->name), token.c_str());
		
			DGL_Graphics_StartMesh();
			// (NOTE: Third, read an integer indicating the number of vertices to be read.)
			int numVertices = StreamReadInt(stream);
			// (NOTE: For each vertex, read a Vector2D (position), a DGL_Color (color), and a Vector2D (UV).)
			for (int i = 0; i < numVertices; i++)
			{
				//Vector2D* position = calloc(1, sizeof(Vector2D));
				Vector2D* position = new Vector2D();

				//DGL_Color* color = calloc(1, sizeof(DGL_Color));
				DGL_Color* color = new DGL_Color();

				//Vector2D* textureOffset = calloc(1, sizeof(Vector2D));
				Vector2D* textureOffset = new Vector2D();


				StreamReadVector2D(stream, position);
				StreamReadColor(stream, color);
				StreamReadVector2D(stream, textureOffset);

				// (HINT: Call DGL_Graphics_AddVertex() to add a single vertex to the mesh.)

				DGL_Graphics_AddVertex(position, color, textureOffset);

			}
			mesh->meshResource = DGL_Graphics_EndMesh();
		}
	}

	// Dynamically allocate a new Mesh object AND create a quadrilateral mesh.
	Mesh* MeshCreateQuad(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
	{
		//Mesh* ptrMesh = calloc(1, sizeof(Mesh));
		Mesh* ptrMesh = new Mesh();


		MeshBuildQuad(ptrMesh, xHalfSize, yHalfSize, uSize, vSize, name);

		return ptrMesh;
	}

	// Create a "spaceship" mesh.
	// (NOTE: This mxust be a "unit"-sized triangular mesh as described in the Project 2 instructions.)
	// (NOTE: The Mesh object must first be made using calloc().)
	// (NOTE: The Mesh name can be stored using strcpy_s().)
	// (NOTE: The DGL_Mesh object must be created using DGL_Graphics_StartMesh,
	//    DGL_Graphics_AddTriangle, and DGL_Graphics_EndMesh.)
	// Returns:
	//	 If the mesh was created successfully,
	//	   then return a pointer to the created Mesh,
	//	   else return nullptr.
	Mesh* MeshCreateSpaceship(void)
	{
		//Mesh* spaceship = calloc(1, sizeof(Mesh));
		Mesh* spaceship = new Mesh();

		
		if (spaceship != nullptr) 
		{
			strcpy_s(spaceship->name, _countof(spaceship->name), "spaceship");

			DGL_Graphics_StartMesh();

			DGL_Vec2 v1 = { 0.5f,  0.0f };
			DGL_Color c1 = { 1.0f, 1.0f, 0.0f, 1.0f };
			DGL_Vec2 uv1 = { 0.0f, 0.0f };

			DGL_Vec2 v2 = { -0.5f, -0.5f };
			DGL_Color c2 = { 1.0f, 0.0f, 0.0f, 1.0f };
			DGL_Vec2 uv2 = { 0.0f, 0.0f };

			DGL_Vec2 v3 = { -0.5f,  0.5f };
			DGL_Color c3 = { 1.0f, 0.0f, 0.0f, 1.0f };
			DGL_Vec2 uv3 = { 0.0f, 0.0f };

			DGL_Graphics_AddTriangle(&v1, &c1, &uv1, &v2, &c2, &uv2, &v3, &c3, &uv3);

			//DGL_Graphics_AddTriangle(
			//&(DGL_Vec2){  0.5f,  0.0f }, &(DGL_Color){ 1.0f, 1.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, 0.0f },
			//&(DGL_Vec2){ -0.5f, -0.5f }, &(DGL_Color){ 1.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, 0.0f },
			//&(DGL_Vec2){ -0.5f,  0.5f }, &(DGL_Color){ 1.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ 0.0f, 0.0f });
	
			spaceship->meshResource = DGL_Graphics_EndMesh();

			return spaceship;
		}
		else {
			return nullptr;
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

	// Determines if a Mesh has the specified name.
// Params:
//	 mesh = Pointer to the Mesh object.
//	 name = Pointer to the name to be compared.
// Returns:
//	 If the mesh and name pointers are valid,
//		then perform a string comparison and return the result (match = true),
//		else return false.
	bool MeshIsNamed(const Mesh* mesh, const char* name)
	{ 
		if (mesh != nullptr && strcmp(mesh->name, name) == 0)
		{
			return true;
		}
		else {
			//printf("It DON'T Matches!!! %s\n", mesh->name);
			return false;
		}
	}

	// Free the memory associated with a mesh.
	// (NOTE: The DGL_Mesh object must be freed using DGL_Graphics_FreeMesh().)
	// (NOTE: The Mesh object must be freed using free().
	// (NOTE: The Mesh pointer must be set to nullptr.)
	// Params:
	//   mesh = Pointer to the Mesh pointer.
	void MeshFree(Mesh** mesh) //this is a pointer to a pointer Mesh
	{
		if (*mesh != nullptr)
		{
			Mesh* ptrMesh = *mesh; //dereference mesh pointer so we can get meshResource in the next statement
			DGL_Graphics_FreeMesh(&ptrMesh->meshResource); //get address of meshResource
			//free(*mesh); PROBLEM
			*mesh = nullptr;
		}
		else {
			return;
		}

	}



//-0.5 -0.1.0 0.51 0.0 1.0 0.0 1.0 
//0.5 0.5 1.0 0.51 0.0 1.0 1.0 0.0 
//0.5 -0.5 1.0 0.51 0.0 1.0 1.0 1.0
//-0.5 -0.5 1.0 0.51 0.0 1.0 0.0 1.0 
//-0.5 0.5 1.0 0.51 0.0 1.0 0.0 0.0 
//0.5 0.5 1.0 0.51 0.0 1.0 1.0 0.0 

//-0.5 -0.5 1.0 0.5 0.0 1.0 0.0 0.0
//-0.5 0.5 1.0 0.5 0.0 1.0 0.0 1.0
//0.5 - 0.5 1.0 0.5 0.0 1.0 1.0 0.0
//0.5 - 0.5 1.0 0.5 0.0 1.0 1.0 0.0
//- 0.5 0.5 1.0 0.5 0.0 1.0 0.0 1.0
//0.5 0.5 1.0 0.5 0.0 1.0 1.0 1.0
//
//Entity
//AsteroidsHighScore
//Transform
//- 425 320
// 	 -325 280
//			250	320
//0
//20 30