//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 2
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "SpriteSource.h"
#include "DGL.h"
#include "Stream.h"
#include "Trace.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	typedef struct DGL_Texture DGL_Texture;
	typedef struct SpriteSource SpriteSource;

	//------------------------------------------------------------------------------
	// Public Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	// An example of the structure to be defined in SpriteSource.c.

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
	typedef struct SpriteSource
	{
		// The name of the sprite source.
		// A buffer is used to allow each sprite source to have a unique name.
		// The buffer is hardcoded to an arbitrary length that will be sufficient
		//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
		//	 arrays for this purpose but the additional complexity is unnecessary
		//	 and it is your responsibility to ensure that the memory is successfully
		//	 allocated and deallocated in all possible situations.
		char name[32];

		// The dimensions of the sprite sheet.
		// (Hint: These should be initialized to (1, 1).)
		int	numRows;
		int	numCols;

		// Pointer to a texture resource created using the DigiPen Graphics Library (DGL).
		const DGL_Texture* texture;

	} SpriteSource;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Dynamically allocate a new SpriteSource object.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	// (Hint: numRows and numCols should be initialized to 1.)
	// Returns:
	//	 If the memory allocation was successful,
	//	   then return a pointer to the allocated memory,
	//	   else return NULL.
	SpriteSource* SpriteSourceCreate()
	{
		SpriteSource* ptrSpriteSource = calloc(1, sizeof(SpriteSource));
	
		if (ptrSpriteSource != NULL)
		{
			ptrSpriteSource->numRows = 1;
			ptrSpriteSource->numCols = 1;

			return ptrSpriteSource;
		}
		else {
			return NULL;
		}
	}

	// Free the memory associated with a SpriteSource object.
	// (NOTE: The SpriteSource pointer must be set to NULL.)
	// Params:
	//	 spriteSource = Pointer to the SpriteSource pointer.
	void SpriteSourceFree(SpriteSource** spriteSource)
	{
		if (*spriteSource) 
		{
			free(*spriteSource);
		}

		*spriteSource = NULL;
	}

	// Load a texture from a file (may be an Col x Row sprite sheet).
	// Params:
	//	 numCols = The number of columns in the sprite sheet.
	//	 numRows = The number of rows in the sprite sheet.
	//	 textureName = The name of the texture to be loaded.
	void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName)
	{
		if (spriteSource != NULL)
		{
			spriteSource->texture = DGL_Graphics_LoadTexture(textureName);
			spriteSource->numCols = numCols;
			spriteSource->numRows = numRows;
		}
		else {
			TraceMessage(" Error Function %s\n File: %s\n Line: %d.", __FUNCTION__, __FILE__, __LINE__);
		}
	}

	// Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
	// (Hint: Frame count = numCols * numRows.)
	// Params:
	//	 spriteSource = Pointer to the SpriteSource object.
	// Returns:
	//	 If the SpriteSource pointer is valid,
	//		then return the calculated frame count (numCols * numRows),
	//		else return 0.
	unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource)
	{
		if (spriteSource != NULL)
		{
			int frameCount = spriteSource->numCols * spriteSource->numRows;
			return frameCount;
		}
		else {
			return 0;
		}
	}

	// Returns the UV coordinates of the specified frame in a sprite sheet.
	// (Hint: Refer to the Week 2 lecture slides for the correct calculations.)
	// Params:
	//	 spriteSource = Pointer to the SpriteSource object.
	//	 frameIndex = A frame index within a sprite sheet.
	//   u = Pointer to a float to contain the U coordinate. 
	//   v = Pointer to a float to contain the V coordinate. 
	void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, float* u, float* v)
	{
		*u = (1.f / spriteSource->numCols) * (frameIndex % spriteSource->numCols);
		*v = (1.f / spriteSource->numRows) * (frameIndex / spriteSource->numCols);
	}

	// Sets a SpriteSource texture for rendering.
	// Params:
	//	 spriteSource = Pointer to the SpriteSource object.
	void SpriteSourceSetTexture(const SpriteSource* spriteSource)
	{
		DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
		DGL_Graphics_SetTexture(spriteSource->texture);
	}

	// Sets the texture UV offsets for rendering.
	// Params:
	//	 spriteSource = Pointer to the SpriteSource object.
	void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex)
	{
		DGL_Vec2 texOffset = { 0,0 };
		SpriteSourceGetUV(spriteSource, frameIndex, &texOffset.x, &texOffset.y);
		DGL_Graphics_SetCB_TextureOffset(&texOffset);
	}

// 1: Read a token from the stream.
// 2: If the token read was "SpriteSource",
//	  a: Read a token from the stream and store it in the name variable.
//       (Hint: use strcpy_s for this purpose.)
//    b: Read the numCols and numRows values from the stream.
//	  c: Read a token from the stream. This is the path name of a texture.
//	  d: Call DGL_Graphics_LoadTexture and store the texture resource.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
//	 stream = Pointer to the data stream used for reading.
	void SpriteSourceRead(SpriteSource* spriteSource, Stream stream)
	{
		if (stream != NULL)
		{
			const char* tokenName = StreamReadToken(stream);
			if (strncmp(tokenName, "SpriteSource", _countof("SpriteSource")) != 0)
			{
				TraceMessage("Expected token 'SpriteSource' not found");
				return;
			}

			const char* spriteName = StreamReadToken(stream);

			strcpy_s(spriteSource->name, _countof(spriteSource->name), spriteName);
			spriteSource->numRows = StreamReadInt(stream);
			spriteSource->numCols = StreamReadInt(stream);
			spriteSource->texture = DGL_Graphics_LoadTexture(StreamReadToken(stream));
		}
	}

// Determines if a SpriteSource has the specified name.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
//	 name = Pointer to the name to be compared.
// Returns:
//	 If the SpriteSource and name pointers are valid,
//		then perform a string comparison and return the result (match = true),
//		else return false.
	bool SpriteSourceIsNamed(const SpriteSource* spriteSource, const char* name)
	{
		if (spriteSource != NULL && strcmp(spriteSource->name, name) == 0)
		{
			printf("It Matches!!! %s\n", spriteSource->name);
			return true;
		}
		else {
			return false;
		}
	}
	/*----------------------------------------------------------------------------*/

