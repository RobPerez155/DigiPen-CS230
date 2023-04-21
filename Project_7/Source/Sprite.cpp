//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Rob Perez	(rob.perez)
// Project:		Project 7
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
#include "Entity.h"

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

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
Sprite* ptrSprite;
DGL_Color tintColor = {0.0f, 0.0f, 0.0f, 0.0f};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
Sprite::Sprite(Entity& parent) : Component(parent)
{
  frameIndex = 0;

  alpha = 0.0f;

  // should these be set to what they are? in other words spriteSource = SpriteSource
  spriteSource = nullptr;

  mesh = nullptr;
  
}

Component* Sprite::Clone(Entity& newParent) const
{
  auto spriteClone = new Sprite(newParent);

  if (spriteClone == nullptr)
  {
    return nullptr;
  }

  spriteClone->frameIndex = frameIndex;
  spriteClone->alpha = alpha;
  spriteClone->spriteSource = spriteSource;
  spriteClone->mesh = mesh;
  spriteClone->text = text;

  return spriteClone;
}

void Sprite::Read(Stream stream)
{
  if (stream != nullptr)
  {
    this->frameIndex = StreamReadInt(stream);
    this->alpha = StreamReadFloat(stream);

    std::string meshName = StreamReadToken(stream);
    const char* meshName_cstr = meshName.c_str();
    const Mesh* newMesh = MeshLibraryBuild(meshName_cstr);
    //SetMesh(this->mesh, newMesh);
    SetMesh(newMesh);

    //Issues
    std::string ss_name = StreamReadToken(stream);
    const char* ss_name_cstr = ss_name.c_str();
    if (strcmp(ss_name_cstr, "None") != 0 || ss_name_cstr[0] != '\0')
    {
      this->spriteSource = SpriteSourceLibraryBuild(ss_name_cstr);
    }
  }
}

void Sprite::Render()
{
  Transform* transform = GetParent().GetComponent<Transform>();
  if (this->spriteSource != nullptr)
  {
    DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
    SpriteSourceSetTexture(this->spriteSource);
    SpriteSourceSetTextureOffset(this->spriteSource, this->frameIndex);
  }
  else if (this->spriteSource == nullptr)
  {
    DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
    DGL_Graphics_SetTexture(nullptr);
  }
  //issue
  //  DGL_Graphics_SetCB_TransformMatrix(Transform::GetMatrix(transform));
  DGL_Graphics_SetCB_TransformMatrix(&transform->GetMatrix());
  DGL_Graphics_SetCB_Alpha(this->alpha);
  DGL_Graphics_SetCB_TintColor(&tintColor);
  MeshRender(this->mesh);
  DGL_Graphics_SetTexture(nullptr);
  //Sprite::Draw(this, transform);
  this->Draw(transform);
}



float Sprite::GetAlpha() const
{
    return this->alpha;
}

void Sprite::SetAlpha(float newAlpha)
{
  max(newAlpha, 1.0f);
  min(newAlpha, 0.0f);

  DGL_Graphics_SetCB_Alpha(this->alpha);
  this->alpha = newAlpha;
}

void Sprite::SetFrame(unsigned int newFrameIndex)
{
    this->frameIndex = newFrameIndex;
    TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
}

void Sprite::SetMesh(const Mesh* newMesh)
{
  this->mesh = newMesh;
}

void Sprite::SetSpriteSource(const SpriteSource* newSpriteSource)
{
  this->spriteSource = newSpriteSource;
}

void Sprite::SetText(const char* newText)
{
  this->text = newText;
}

void Sprite::Draw(Transform* transform) const
{
  // Validate the Sprite and Sprite Mesh pointers.
  if (this != nullptr && this->mesh != nullptr)
  {
    //If the Sprite has a valid SpriteSource,
    if (this->spriteSource != nullptr)
    {
      //	Set the shader mode to TEXTURE.
      DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);

      //	Set the SpriteSource texture.
      SpriteSourceSetTexture(this->spriteSource);

      //	Set the SpriteSource texture offset.
      SpriteSourceSetTextureOffset(this->spriteSource, this->frameIndex);
    }
  }
  else
  {
    //	Set the shader mode to COLOR.
    DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
    //	Call DGL_Graphics_SetTexture(nullptr).
    DGL_Graphics_SetTexture(nullptr);
  }

  if (this != nullptr)
  {
    //	Set the alpha transparency for the Sprite.
    DGL_Graphics_SetCB_Alpha(this->alpha);
  }

  //	Set the tint color for the Sprite to(0, 0, 0, 0).
  DGL_Graphics_SetCB_TintColor(&tintColor);

  //	If the sprite’s text pointer is nullptr,
  if (this->text.empty())
  {
    //	Call TransformGetMatrix().
    //	Call DGL_Graphics_SetCB_TransformMatrix(), passing the Transform’s matrix.
    DGL_Graphics_SetCB_TransformMatrix(&transform->GetMatrix());

    //	Call MeshRender(), passing the Sprite’s mesh.
    MeshRender(this->mesh);
  }
  else
  {
    //Call TransformGetMatrix() to get a local copy of the Transform component’s transformation matrix(“matrix”)
    //Call Matrix2DTranslate() to create an translation matrix(“offset”) with an X value equal to the Transform component’s X scale
    Matrix2D matrix = transform->GetMatrix();
    Matrix2D translateMatrix;
    Matrix2DTranslate(&translateMatrix, transform->GetScale().x, 0);
//    Matrix2DTranslate(&translateMatrix, Transform::GetScale(transform).x, 0);
    //Assign a local “const char* ” variable equal to the Sprite’s text pointer.This variable will be used to “walk” through the string without modifying the sprite’s text pointer
    const char* buffer = this->text.c_str();


    //While the local text pointer points at a non - zero character,
    //	Convert the current character into a zero - based frame index.
    while (*buffer != '\0')
    {
      int tempChar = (*buffer) - ' ';
      SpriteSourceSetTextureOffset(this->spriteSource, tempChar);
      DGL_Graphics_SetCB_TransformMatrix(&matrix);
      MeshRender(this->mesh);

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
