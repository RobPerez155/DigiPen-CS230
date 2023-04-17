//------------------------------------------------------------------------------
//
// File Name:	SpriteSourceLibrary.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Sprite.h"
#include "SpriteSource.h"
#include "SpriteSourceLibrary.h"
#include "Stream.h"

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

	typedef struct SpriteSource SpriteSource;

	//------------------------------------------------------------------------------
	// Public Consts:
	//------------------------------------------------------------------------------
#define spriteSourceListSize 100
	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	// An example of the structure to be defined in SpriteSourceLibrary.c.

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
	typedef struct SpriteSourceLibrary
	{
		// The number of sprite sources currently in the list.
		unsigned int spriteSourceCount;

		// A list of all currently loaded sprite sources.
		// This list can be a fixed-length array (minimum size of 10 entries)
		// or a dynamically-sized array, such as a linked list.
		SpriteSource* spriteSourceList[spriteSourceListSize];

	} SpriteSourceLibrary;


	//------------------------------------------------------------------------------
	// Private Variables:
	static SpriteSourceLibrary sprites;
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Functions:
			static void SpriteSourceLibraryAdd(SpriteSource* spriteSource);
			static const SpriteSource* SpriteSourceLibraryFind(const char* spriteSource);
	//------------------------------------------------------------------------------

	// Initialize the SpriteSource Library.
	// (NOTE: Make sure to initialize all memory to zero.)
	void SpriteSourceLibraryInit()
	{
		//SpriteSourceLibrary* newLib = calloc(1, sizeof(SpriteSourceLibrary));
		SpriteSourceLibrary* newLib = new SpriteSourceLibrary();

	UNREFERENCED_PARAMETER(newLib);
	}

	// Create a SpriteSource and add it to the SpriteSource manager.
	// 1: Call SpriteSourceLibraryFind() to determine if the sprite source already exists
	// 2: If the named sprite source does not already exist,
	//	  a: Use sprintf_s() to construct a path name using spriteSourceName
	//	     (HINT: The correct path name should be constructed using "Data/%s.txt".)
	//	  b: Call StreamOpen(), passing the path name
	//    c: If the stream was opened successfully,
	//		 1: Call SpriteSourceCreate() to construct a new, empty SpriteSource.
	//       2: Call SpriteSourceRead() to read the SpriteSource data from the file.
	//		 3: Call SpriteSourceLibraryAdd(), passing the created SpriteSource.
	//       4: Close the stream.
	// 3: Return the SpriteSource (already existing or just created)
	// Params:
	//	 SpriteSourceName = The name of the SpriteSource to be created.
	// Returns:
	//	 If the SpriteSource already exists or was created successfully,
	//	   then return a pointer to the SpriteSource,
	//	   else return nullptr.
	const SpriteSource* SpriteSourceLibraryBuild(const char* spriteSourceName)
	{
		if (SpriteSourceLibraryFind(spriteSourceName) != nullptr)
		{
			return SpriteSourceLibraryFind(spriteSourceName);
		}

		// 1: Use sprintf_s() to construct a path name using meshName
		//	   (HINT: The correct path name should be constructed using "Data/&s.txt".)
		char pathName[FILENAME_MAX] = "";
		sprintf_s(pathName, _countof(pathName), "Data/%s.txt", spriteSourceName);

		// 2: Call StreamOpen(), passing the pathname
		Stream fileStream = StreamOpen(pathName);

		// 3: If the stream was opened successfully,
		if (fileStream != nullptr)
		{
			//a: Call MeshCreate() to create an empty Mesh object.
			SpriteSource* newSpriteSource = SpriteSourceCreate();

			// b: Call MeshRead() to construct a mesh using data read from the file
			SpriteSourceRead(newSpriteSource, fileStream);

			//c: Call MeshLibraryAdd(), passing the created mesh
			SpriteSourceLibraryAdd(newSpriteSource);

			//d: Close the stream
			StreamClose(&fileStream);

			//e: Return the created mesh
			return newSpriteSource;
		}
		else
		{
			return nullptr;
		}
	}

	void SpriteSourceLibraryAdd(SpriteSource* spriteSource)
	{
		for (int i = 0; i < spriteSourceListSize; i++)
		{
			if (sprites.spriteSourceList[i] == nullptr)
			{
				sprites.spriteSourceList[i] = spriteSource;
				sprites.spriteSourceCount++;
				return;
			}
		}
	}

	const SpriteSource* SpriteSourceLibraryFind(const char* spriteSource)
	{
		// for loop to iterate through meshList 
		for (int i = 0; i < spriteSourceListSize; i++)
		{
			const SpriteSource* tempSprite = SpriteSourceCreate();
			tempSprite = sprites.spriteSourceList[i];
			if (SpriteSourceIsNamed(tempSprite, spriteSource))
			{
				return tempSprite;
			}
		}
		return nullptr;
	}

	// Free all SpriteSource objects in the SpriteSource Library.
	// (NOTE: You must call SpriteSourceFree() to free each SpriteSource object.)
	// (HINT: The list should contain nothing but nullptr pointers once this function is done.)
	void SpriteSourceLibraryFreeAll()
	{
		// Iterate through list
		for (int i = 0; i < spriteSourceListSize; i++)
		{
			// for each item run entity render
			SpriteSourceFree(&sprites.spriteSourceList[i]);
			sprites.spriteSourceList[i] = nullptr;
		}
	}

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

