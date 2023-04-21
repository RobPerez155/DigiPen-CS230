//------------------------------------------------------------------------------
//
// File Name:	Animation.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 7
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
#include "Animation.h"
#include "Entity.h"
#include "Sprite.h"
#include "Stream.h"

//------------------------------------------------------------------------------

class Animation : public Component
{
public:
	__inline static Type type() { return Type::Animation; }
	
	explicit Animation(Entity& parent);
	
	Component* Clone(Entity& newParent) const override;
		
	void Read(Stream stream) override;
		
	//void SetParent(Animation* animation, Entity* parent);
		
	//void Play(Animation* animation, int frameCount, float frameDuration, bool isLooping);
	void Play(int animFrameCount, float animFrameDuration, bool animIsLooping);
	
	void Update(float dt) override;
		
	bool IsDone() const;

	
private:
	// Pointer to the parent Entity associated with the Animation component.
	Entity* parent;

	// The current frame being displayed.
	unsigned int frameIndex;

	// The maximum number of frames in the sequence.
	unsigned int frameCount;

	// The time remaining for the current frame.
	float frameDelay;

	// The amount of time to display each successive frame.
	float frameDuration;

	// True if the animation is running; false if the animation has stopped.
	bool isRunning;

	// True if the animation loops back to the beginning.
	bool isLooping;

	// True if the end of the animation sequence has been reached, false otherwise.
	// (Hint: This should be true for only one game loop.)
	bool isDone;

	void AdvanceFrame(float dt);
};