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
#include "SpriteSourceLibrary.h"
#include "Stream.h"
#include "Mesh.h"
#include "MeshLibrary.h"
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

		// The sprite source used when drawing (nullptr = simple colored mesh).
		const SpriteSource* spriteSource;

		// The mesh used to draw the sprite.
		const Mesh* mesh;

		const char* text;

	} Sprite;
	//class Sprite {
	//public:
	//	// The frame currently being displayed (for sprite sheets).
	//	unsigned int frameIndex;

	//	// The alpha transparency to use when drawing the sprite.
	//	float alpha;

	//	// The sprite source used when drawing (nullptr = simple colored mesh).
	//	const SpriteSource* spriteSource;

	//	// The mesh used to draw the sprite.
	//	const Mesh* mesh;

	//	const char* text;

	//	// Constructor
	//	Sprite() : frameIndex(0), alpha(1.0f), spriteSource(nullptr), mesh(nullptr), text(nullptr) {}

	//	// Destructor
	//	~Sprite() {}
	//};

	void SpriteDraw(const Sprite* sprite, Transform* transform);

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------
	Sprite* ptrSprite;
	DGL_Color tintColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Dynamically allocate a new Sprite component.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	// (NOTE: You must initialize the 'alpha' member variable to 1.0f.)
	// Returns:
	//	 If the memory allocation was successful,
	//	   then return a pointer to the allocated memory,
	//	   else return nullptr.
	Sprite* SpriteCreate(void) {
		ptrSprite = new Sprite();

		if (ptrSprite != nullptr)
		{
			ptrSprite->alpha = 1.0f;
			return ptrSprite;
		}
		else {
			return nullptr;
		}
	}
	//static Sprite* Create() {
	//	Sprite* sprite = new Sprite();

	//	if (sprite != nullptr) {
	//		sprite->alpha = 1.0f;
	//		return sprite;
	//	}
	//	else {
	//		return nullptr;
	//	}
	//}

	// Free the memory associated with a Sprite component.
	// (NOTE: The Sprite pointer must be set to nullptr.)
	// Params:
	//	 sprite = Pointer to the Sprite pointer.
	void SpriteFree(Sprite** sprite) 
	{
		if (*sprite)
		delete(*sprite);

		*sprite = nullptr;
	};
	//void Sprite::Free(Sprite** sprite)
	//{
	//	if (*sprite)
	//		delete(*sprite);

	//	*sprite = nullptr;
	//};

	// Dynamically allocate a clone of an existing Sprite.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return nullptr.
	Sprite* SpriteClone(const Sprite* other)
	{
		if (other == nullptr)
		{
			return nullptr;
		}

		Sprite* spriteClone = new Sprite();

		if (spriteClone == nullptr)
		{
			return nullptr;
		}

		*spriteClone = *other;

		return spriteClone;
	}
	//Sprite* Sprite::Clone() const
	//{
	//	Sprite* spriteClone = new Sprite();

	//	if (spriteClone != nullptr)
	//	{
	//		*spriteClone = *this;
	//	}

	//	return spriteClone;
	//}


	// Read the properties of a Sprite component from a file.
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//	 stream = The data stream used for reading.
	void SpriteRead(Sprite* sprite, Stream stream)
	{
		if (sprite != nullptr)
		{
			sprite->frameIndex = StreamReadInt(stream);
			sprite->alpha = StreamReadFloat(stream);

			const char* meshName = StreamReadToken(stream);
			const Mesh* newMesh = MeshLibraryBuild(meshName);
			SpriteSetMesh(sprite, newMesh);

			const char* ss_name = StreamReadToken(stream);
			if (strcmp(ss_name, "None") != 0 || ss_name[0] != '\0')
			{
				
				sprite->spriteSource = SpriteSourceLibraryBuild(ss_name);
			}	
		}
	}
	//void Sprite::Read(Stream stream)
	//{
	//	if (this != nullptr)
	//	{
	//		frameIndex = stream.ReadInt();
	//		alpha = stream.ReadFloat();

	//		const char* meshName = stream.ReadToken();
	//		const Mesh* newMesh = MeshLibraryBuild(meshName);
	//		SetMesh(newMesh);

	//		const char* ss_name = stream.ReadToken();
	//		if (strcmp(ss_name, "None") != 0 || ss_name[0] != '\0')
	//		{
	//			spriteSource = SpriteSourceLibraryBuild(ss_name);
	//		}
	//	}
	//}


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
	//			Call DGL_Graphics_SetTexture, passing nullptr.
	
	//	-	Call DGL_Graphics_SetCB_TransformData, passing the translation, scale, and rotation values from the transform.
	//	-	Call DGL_Graphics_SetCB_Alpha, passing the “alpha” value from the sprite
	//	-	Call DGL_Graphics_SetCB_TintColor, passing all 0.0f values
	//	-	Call MeshRender, passing the Mesh from the sprite.
	//	-	Call DGL_Graphics_SetTexture, passing nullptr.

	void SpriteRender(const Sprite* sprite, Transform* transform) 
	{		

		if (sprite->spriteSource != nullptr)
		{
			DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
			SpriteSourceSetTexture(sprite->spriteSource);
			SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);
		}
		else if (sprite->spriteSource == nullptr)
		{
			DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
			DGL_Graphics_SetTexture(nullptr);
		}
	
		DGL_Graphics_SetCB_TransformMatrix(TransformGetMatrix(transform));
		DGL_Graphics_SetCB_Alpha(sprite->alpha);
		DGL_Graphics_SetCB_TintColor(&tintColor);
		MeshRender(sprite->mesh);
		DGL_Graphics_SetTexture(nullptr);
		SpriteDraw(sprite, transform);
	}
	//void Sprite::render(Transform* transform)
	//{
	//	if (spriteSource != nullptr)
	//	{
	//		DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
	//		SpriteSourceSetTexture(spriteSource);
	//		SpriteSourceSetTextureOffset(spriteSource, frameIndex);
	//	}
	//	else if (spriteSource == nullptr)
	//	{
	//		DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
	//		DGL_Graphics_SetTexture(nullptr);
	//	}

	//	DGL_Graphics_SetCB_TransformMatrix(transform->getMatrix());
	//	DGL_Graphics_SetCB_Alpha(alpha);
	//	DGL_Graphics_SetCB_TintColor(&tintColor);
	//	mesh->render();
	//	DGL_Graphics_SetTexture(nullptr);
	//	Sprite::draw(this, transform);
	//}


	// Get a Sprite's alpha value.
	// Params:
	//	 sprite = Pointer to the Sprite component.
	float SpriteGetAlpha(const Sprite* sprite)
	{
		if (sprite != nullptr) 
		{
			return sprite->alpha;
		}
		else {
			return 0.0;
		}	
	}
	//float Sprite::getAlpha() const
	//{
	//	return alpha;
	//}

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
	//void Sprite::setAlpha(float alpha)
	//{
	//	alpha = std::max(alpha, 1.0f);
	//	alpha = std::min(alpha, 0.0f);

	//	DGL_Graphics_SetCB_Alpha(alpha);
	//	this->alpha = alpha;
	//}


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
		if (frameIndex >= 0 )
		{
			sprite->frameIndex = frameIndex;
			TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
		}
	}
	//void Sprite::setFrame(unsigned int frameIndex)
	//{
	//	if (frameIndex >= 0)
	//	{
	//		this->frameIndex = frameIndex;
	//		TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
	//	}
	//}


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
	//void Sprite::setMesh(const Mesh* mesh)
	//{
	//	this->mesh = mesh;
	//}


	// Set a new SpriteSource for the specified Sprite.
	// (NOTE: The spriteSource parameter may be nullptr.  This will remove an existing
	//	texture from a Sprite and cause the Sprite to be displayed as a colored mesh.)
	// Params:
	//	 sprite = Pointer to the Sprite component.
	//	 spriteSource = Pointer to a SpriteSource (this pointer may be nullptr).
	void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource)
	{
		sprite->spriteSource = spriteSource;
	}
	//void Sprite::setSpriteSource(const SpriteSource* spriteSource)
	//{
	//	this->spriteSource = spriteSource;
	//}


	// Assign a text string to a Sprite component.  This will allow a sequence of
//	 characters to be displayed as text.
// (NOTE: The text parameter may be nullptr.  This will remove an existing text
//	 string from a sprite and cause the sprite to be displayed normally.)
// Params:
//	 sprite = Pointer to the Sprite component.
//	 text = Pointer to a zero-terminated array of characters.
	void SpriteSetText(Sprite* sprite, const char* text)
	{
		sprite->text = text;
	}
	//void Sprite::SetText(const char* text)
	//{
	//	this->text = text;
	//}

	// Draw a sprite, it can be textured or untextured
	void SpriteDraw(const Sprite* sprite, Transform* transform)
	{
		if (sprite == nullptr)
			return;

		// Validate the Sprite and Sprite Mesh pointers.
		if (sprite != nullptr && sprite->mesh != nullptr)
		{
			//If the Sprite has a valid SpriteSource,
			if (sprite->spriteSource != nullptr)
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
			//	Call DGL_Graphics_SetTexture(nullptr).
			DGL_Graphics_SetTexture(nullptr);
		}
		
		if (sprite != nullptr)
		{
			//	Set the alpha transparency for the Sprite.
			DGL_Graphics_SetCB_Alpha(sprite->alpha);
		}
		
		//	Set the tint color for the Sprite to(0, 0, 0, 0).
		DGL_Graphics_SetCB_TintColor(&tintColor);
		
		//	If the sprite’s text pointer is nullptr,
		if (sprite != nullptr && sprite->text == nullptr)
		{
			//	Call TransformGetMatrix().
			//	Call DGL_Graphics_SetCB_TransformMatrix(), passing the Transform’s matrix.
			DGL_Graphics_SetCB_TransformMatrix(TransformGetMatrix(transform));

			//	Call MeshRender(), passing the Sprite’s mesh.
			MeshRender(sprite->mesh);
		}
		else {
			//Call TransformGetMatrix() to get a local copy of the Transform component’s transformation matrix(“matrix”).
			//Call Matrix2DTranslate() to create an translation matrix(“offset”) with an X value equal to the Transform component’s X scale.
			Matrix2D matrix = *TransformGetMatrix(transform);
			Matrix2D translateMatrix;
			Matrix2DTranslate(&translateMatrix, TransformGetScale(transform)->x, 0);
			//Assign a local “const char* ” variable equal to the Sprite’s text pointer.This variable will be used to “walk” through the string without modifying the sprite’s text pointer.
			const char* buffer = sprite->text;



			//While the local text pointer points at a non - zero character,
			//	Convert the current character into a zero - based frame index.
			while (*buffer != '\0')
			{
				int tempChar = (*buffer) - ' ' ;
				SpriteSourceSetTextureOffset(sprite->spriteSource, tempChar);
				DGL_Graphics_SetCB_TransformMatrix(&matrix);
				MeshRender(sprite->mesh);

				buffer++;
				Matrix2DConcat(&matrix, &translateMatrix, &matrix);
			}

			DGL_Graphics_SetTexture(nullptr);
		}
	}


	/*----------------------------------------------------------------------------*/


	//void Sprite::Draw(const Sprite* sprite, Transform* transform)
	//{
	//	if (sprite == nullptr)
	//		return;

	//	// Validate the Sprite and Sprite Mesh pointers.
	//	if (sprite != nullptr && sprite->mesh != nullptr)
	//	{
	//		// If the Sprite has a valid SpriteSource,
	//		if (sprite->spriteSource != nullptr)
	//		{
	//			// Set the shader mode to TEXTURE.
	//			DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);

	//			// Set the SpriteSource texture.
	//			SpriteSourceSetTexture(sprite->spriteSource);

	//			// Set the SpriteSource texture offset.
	//			SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);
	//		}
	//	}
	//	else {
	//		// Set the shader mode to COLOR.
	//		DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
	//		// Call DGL_Graphics_SetTexture(nullptr).
	//		DGL_Graphics_SetTexture(nullptr);
	//	}

	//	if (sprite != nullptr)
	//	{
	//		// Set the alpha transparency for the Sprite.
	//		DGL_Graphics_SetCB_Alpha(sprite->alpha);
	//	}

	//	// Set the tint color for the Sprite to (0, 0, 0, 0).
	//	DGL_Graphics_SetCB_TintColor(&tintColor);

	//	// If the sprite’s text pointer is nullptr,
	//	if (sprite != nullptr && sprite->text == nullptr)
	//	{
	//		// Call TransformGetMatrix().
	//		// Call DGL_Graphics_SetCB_TransformMatrix(), passing the Transform’s matrix.
	//		DGL_Graphics_SetCB_TransformMatrix(TransformGetMatrix(transform));

	//		// Call MeshRender(), passing the Sprite’s mesh.
	//		MeshRender(sprite->mesh);
	//	}
	//	else {
	//		// Call TransformGetMatrix() to get a local copy of the Transform component’s transformation matrix(“matrix”).
	//		// Call Matrix2DTranslate() to create an translation matrix(“offset”) with an X value equal to the Transform component’s X scale.
	//		Matrix2D matrix = *TransformGetMatrix(transform);
	//		Matrix2D translateMatrix;
	//		Matrix2DTranslate(&translateMatrix, TransformGetScale(transform)->x, 0);
	//		// Assign a local “const char* ” variable equal to the Sprite’s text pointer. This variable will be used to “walk” through the string without modifying the sprite’s text pointer.
	//		const char* buffer = sprite->text;

	//		// While the local text pointer points at a non-zero character,
	//		// Convert the current character into a zero-based frame index.
	//		while (*buffer != '\0')
	//		{
	//			int tempChar = (*buffer) - ' ';
	//			SpriteSourceSetTextureOffset(sprite->spriteSource, tempChar);
	//			DGL_Graphics_SetCB_TransformMatrix(&matrix);
	//			MeshRender(sprite->mesh);

	//			buffer++;
	//			Matrix2DConcat(&matrix, &translateMatrix, &matrix);
	//		}

	//		DGL_Graphics_SetTexture(nullptr);
	//	}
	//}