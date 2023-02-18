//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Rob Perez	(rob.perez)
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
#include "Sprite.h"
#include "SpriteSource.h"
#include "Stream.h"
#include "Mesh.h"
#include "Matrix2D.h"
#include "Trace.h"
#include "Transform.h"
#include "DGL.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	typedef struct Sprite
	{
		// The frame currently being displayed (for sprite sheets).
		unsigned int frameIndex;

		// The alpha transparency to use when drawing the sprite.
		float alpha;

		// The sprite source used when drawing (NULL = simple colored mesh).
		const SpriteSource* spriteSource;

		// The mesh used to draw the sprite.
		const Mesh* mesh;

		const char* text;

	} Sprite;


	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------
	Sprite* ptrSprite;
	
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Dynamically allocate a new Sprite component.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	// (NOTE: You must initialize the 'alpha' member variable to 1.0f.)
	// Returns:
	//	 If the memory allocation was successful,
	//	   then return a pointer to the allocated memory,
	//	   else return NULL.
	Sprite* SpriteCreate(void) {
		ptrSprite = calloc(1, sizeof(Sprite));

		if (ptrSprite != NULL)
		{
			ptrSprite->alpha = 1.0f;
			return ptrSprite;
		}
		else {
			return NULL;
		}
	}

	// Free the memory associated with a Sprite component.
	// (NOTE: The Sprite pointer must be set to NULL.)
	// Params:
	//	 sprite = Pointer to the Sprite pointer.
	void SpriteFree(Sprite** sprite) 
	{
		if (*sprite)
		free(*sprite);

		*sprite = NULL;
	};

	// Read the properties of a Sprite component from a file.
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//	 stream = The data stream used for reading.
	void SpriteRead(Sprite* sprite, Stream stream)
	{
		if (sprite != NULL)
		{
			sprite->frameIndex = StreamReadInt(stream);
			sprite->alpha = StreamReadFloat(stream);
		}
	}

	// Render a Sprite (Sprite can be textured or untextured).
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//   transform = Pointer to the Transform component.
	//To successfully draw a Sprite, you will need to perform the following steps :
	//-	If the Sprite has a sprite source :
	//			Set the shader mode to TEXTURE.
	//			Call SpriteSourceSetTexture.
	//			Call SpriteSourceSetTextureOffset, passing the Sprite’s frameIndex.
	//	- If the Sprite does not have a SpriteSource,
	//			Set the shader mode to COLOR.
	//			Call DGL_Graphics_SetTexture, passing NULL.
	
	//	-	Call DGL_Graphics_SetCB_TransformData, passing the translation, scale, and rotation values from the transform.
	//	-	Call DGL_Graphics_SetCB_Alpha, passing the “alpha” value from the sprite
	//	-	Call DGL_Graphics_SetCB_TintColor, passing all 0.0f values
	//	-	Call MeshRender, passing the Mesh from the sprite.
	//	-	Call DGL_Graphics_SetTexture, passing NULL.

	void SpriteRender(const Sprite* sprite, Transform* transform) 
	{		

		if (sprite->spriteSource != NULL)
		{
			DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
			SpriteSourceSetTexture(sprite->spriteSource);
			SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);
		}
		else if (sprite->spriteSource == NULL)
		{
			DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
			DGL_Graphics_SetTexture(NULL);
		}

		DGL_Graphics_SetCB_TransformMatrix(TransformGetMatrix(transform));

		DGL_Graphics_SetCB_Alpha(sprite->alpha);
		DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
		MeshRender(sprite->mesh);
		DGL_Graphics_SetTexture(NULL);
	}

	// Get a Sprite's alpha value.
	// Params:
	//	 sprite = Pointer to the Sprite component.
	float SpriteGetAlpha(const Sprite* sprite)
	{
		if (sprite != NULL) 
		{
			return sprite->alpha;
		}
		else {
			return 0.0;
		}	
	}

	// Set a Sprite's alpha value.
	// (NOTE: Make sure to clamp the resulting alpha value between 0.0f and 1.0f, as the
	//	input value might be outside of this range.)
	// (HINT: The min() and max() macros can be combined to create a clamp function.)
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//   alpha = The Sprite's new alpha value.
	void SpriteSetAlpha(Sprite* sprite, float alpha)
	{
		max(alpha, 1.0f);
		min(alpha, 0.0f);

		DGL_Graphics_SetCB_Alpha(sprite->alpha);
		sprite->alpha = alpha;
	}

	// Set a Sprite's current frame.
	// (NOTE: You must verify that the frameIndex parameter is within the
	//	range [0 to frame count] before changing the Sprite's frame index!)
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//   frameIndex = New frame index for the Sprite (0 .. frame count).
	// ADDITIONAL REQUIREMENTS:
	// - This function must make the following function call:
	//     TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
	void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex)
	{
		if (frameIndex >= 0 && frameIndex <= sprite->frameIndex)
		{
			sprite->frameIndex = frameIndex;
			TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
		}
	}

	// Set the Sprite's mesh.
	// (NOTE: This mesh may be textured or untextured.)
	// (NOTE: This mesh may contain any number of triangles.)
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//   mesh = Pointer to a Mesh object.
	void SpriteSetMesh(Sprite* sprite, const Mesh* mesh)
	{
		sprite->mesh = mesh;
	}

	// Set a new SpriteSource for the specified Sprite.
	// (NOTE: The spriteSource parameter may be NULL.  This will remove an existing
	//	texture from a Sprite and cause the Sprite to be displayed as a colored mesh.)
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//	 spriteSource = Pointer to a SpriteSource (this pointer may be NULL).
	void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource)
	{
		sprite->spriteSource = spriteSource;
	}

	// Assign a text string to a Sprite component.  This will allow a sequence of
//	 characters to be displayed as text.
// (NOTE: The text parameter may be NULL.  This will remove an existing text
//	 string from a sprite and cause the sprite to be displayed normally.)
// Params:
//	 sprite = Pointer to the Sprite component.
//	 text = Pointer to a zero-terminated array of characters.
	void SpriteSetText(Sprite* sprite, const char* text)
	{
		sprite->text = text;
	}

	// Draw a sprite, it can be textured or untextured
	void SpriteDraw(const Sprite* sprite, Transform* transform)
	{
		// Validate the Sprite and Sprite Mesh pointers.
		if (sprite != NULL && sprite->mesh != NULL)
		{
			//If the Sprite has a valid SpriteSource,
			if (sprite->spriteSource != NULL)
			{
			//	Set the shader mode to TEXTURE.
				DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);

			//	Set the SpriteSource texture.
				SpriteSourceSetTexture(sprite->spriteSource);

			//	Set the SpriteSource texture offset.
				SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);
			}
		}
		else {
			//	Set the shader mode to COLOR.
			DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
			//	Call DGL_Graphics_SetTexture(NULL).
			DGL_Graphics_SetTexture(NULL);
		}
		
		if (sprite != NULL)
		{
			//	Set the alpha transparency for the Sprite.
			DGL_Graphics_SetCB_Alpha(sprite->alpha);
		}
		
		//	Set the tint color for the Sprite to(0, 0, 0, 0).
		DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
		
		//	If the sprite’s text pointer is NULL,
		if (sprite != NULL && sprite->text == NULL)
		{
			//	Call TransformGetMatrix().
			//	Call DGL_Graphics_SetCB_TransformMatrix(), passing the Transform’s matrix.
			DGL_Graphics_SetCB_TransformMatrix(TransformGetMatrix(transform));

			//	Call MeshRender(), passing the Sprite’s mesh.
			MeshRender(sprite->mesh);
		}
		else {
			//Call TransformGetMatrix() to get a local copy of the Transform component’s transformation matrix(“matrix”).
			Matrix2D transformMatrix = *TransformGetMatrix(transform);

			//Call Matrix2DTranslate() to create an translation matrix(“offset”) with an X value equal to the Transform component’s X scale.
			Matrix2DTranslate(&transformMatrix, TransformGetScale(transform)->x, TransformGetScale(transform)->y);

			//Assign a local “const char* ” variable equal to the Sprite’s text pointer.This variable will be used to “walk” through the string without modifying the sprite’s text pointer.
			// 
			//While the local text pointer points at a non - zero character,
			//	Convert the current character into a zero - based frame index.
				//	Hint : The font sheet begins at the space character(‘ ‘).
			
			//	Set the SpriteSource texture offset using this calculated frame index.
			
			//	Call DGL_Graphics_SetCB_TransformMatrix(), passing the local copy of the Transform’s matrix.
			
			//	Call MeshRender(), passing the sprite’s mesh.
			
			//	Advance the local char pointer to the next character in the string.
			
			//	Call Matrix2DConcat() to concatenate the translation matrixand transformation matrix.
			//	matrix = offset * matrix

		}
	}

	/*----------------------------------------------------------------------------*/

