//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.h
// Author(s):	Rob Perez (rob.perez)
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
#include "stdafx.h"
#include "DGL.h"
#include "MeshLibrary.h"
#include "Mesh.h"
#include "Stream.h"

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
	// Private Consts:
	//------------------------------------------------------------------------------
#define meshListSize 100

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	typedef struct MeshLibrary
	{
		// This variable is not required but could be used for tracking the number
		//   of Mesh objects currently in the list.
		unsigned int meshCount;

		// A list of all currently loaded meshes.
		// This list can be a fixed-length array (minimum size of 10 entries)
		// or a dynamically-sized array, such as a linked list.
		const Mesh* meshList[meshListSize];

	} MeshLibrary;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------
		static MeshLibrary meshes;

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------
		static void MeshLibraryAdd(Mesh* mesh);
		static const Mesh* MeshLibraryFind(const char* meshName);
		

	// Initialize the Mesh Manager.
	// (NOTE: Make sure to initialize all memory to zero.)
	void MeshLibraryInit()
	{
		//init all to 0 -> MeshLibrary
		meshes = (MeshLibrary) { 0 };
	}

	const Mesh* MeshLibraryFind(const char* meshName)
	{
		// for loop to iterate through meshList 
		for (int i = 0; i < meshListSize; i++)
		{
			const Mesh* tempMesh = MeshCreate();
			tempMesh = meshes.meshList[i];
			if (MeshIsNamed(tempMesh, meshName))
			{
				return tempMesh;
			}
		}
		return NULL;
	}

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
	const Mesh* MeshLibraryBuild(const char* meshName)
	{
		if (MeshLibraryFind(meshName) != NULL)
		{
			return MeshLibraryFind(meshName);
		}

	// 1: Use sprintf_s() to construct a path name using meshName
	//	   (HINT: The correct path name should be constructed using "Data/&s.txt".)
		char pathName[FILENAME_MAX] = "";
		sprintf_s(pathName, _countof(pathName), "Data/%s.txt", meshName);

	// 2: Call StreamOpen(), passing the pathname
		Stream fileStream = StreamOpen(pathName);
		
	// 3: If the stream was opened successfully,
		if (fileStream != NULL)
		{
			//a: Call MeshCreate() to create an empty Mesh object.

			Mesh* newMesh = MeshCreate();

			// b: Call MeshRead() to construct a mesh using data read from the file
			MeshRead(newMesh, fileStream);

			//c: Call MeshLibraryAdd(), passing the created mesh
			MeshLibraryAdd(newMesh);
	
			//d: Close the stream
			StreamClose(&fileStream);

			//e: Return the created mesh
			return newMesh;
		}
		else
		{
			return NULL;
		}
	}

	void MeshLibraryAdd(Mesh* mesh)
	{
		for (int i = 0; i < meshListSize; i++)
		{
			if (meshes.meshList[i] == NULL)
			{
				meshes.meshList[i] = mesh;
				meshes.meshCount++;
				return;
			}
		}
	}

	// Free all Mesh objects in the Mesh Manager.
	// (NOTE: You must call MeshFree() to free each Mesh object.)
	// (HINT: The list should contain nothing but NULL pointers once this function is done.)
	void MeshLibraryFreeAll()
	{
		// Iterate through list
		for (int i = 0; i < meshListSize; i++)
		{
			// for each item run entity render
			MeshFree(&meshes.meshList[i]);
			meshes.meshList[i] = NULL;
		}
	}

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

