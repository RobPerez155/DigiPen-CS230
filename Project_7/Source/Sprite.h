//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
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

class Sprite : public Component
{
public:
	explicit Sprite(Entity& parent);

	Component* Clone(Entity& newParent) const override;

	Sprite* Clone(const Sprite* other);

	void Read(Stream stream);

	void Render(const Transform* transform);

	float GetAlpha(const Sprite* sprite);

	void SetAlpha(float alpha);

	void SetFrame(unsigned int frameIndex);

	void SetMesh(const Mesh* mesh);

	void SetSpriteSource(const SpriteSource* spriteSource);

	void SetText(const char* text);
};
#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

/*typedef struct Mesh Mesh;
typedef struct SpriteSource SpriteSource;
typedef struct Sprite Sprite;
typedef struct Transform Transform;
typedef FILE* Stream;*/

//------------------------------------------------------------------------------
// Public Constants:
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

/*Sprite* SpriteClone(const Sprite* other);

void SpriteRead(Sprite* sprite, Stream stream);

void SpriteRender(const Sprite* sprite, Transform* transform);

float SpriteGetAlpha(const Sprite* sprite);

void SpriteSetAlpha(Sprite* sprite, float alpha);

void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex);

void SpriteSetMesh(Sprite* sprite, const Mesh* mesh);

void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource);

void SpriteSetText(Sprite* sprite, const char* text);*/

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

