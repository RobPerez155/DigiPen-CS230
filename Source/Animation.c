//------------------------------------------------------------------------------
//
// File Name:	Animation.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 0
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Animation.h"
#include "Entity.h"
#include "Sprite.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct Animation
{
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

} Animation;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void AnimationAdvanceFrame(Animation* animation, float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (animation != NULL)
	{
		Sprite* animSprite = EntityGetSprite(animation->parent);
		animation->frameIndex++;

		if (animation->frameIndex < animation->frameCount)
		{
			if (animation->isRunning)
			{
				SpriteSetFrame(animSprite, animation->frameIndex);
				animation->frameDelay += animation->frameDuration;
				return;
			}
			else {
				return;
			}
		}
		else if (animation->isLooping)
		{
			animation->frameIndex = 0;
			animation->isDone = true;
		}
		else
		{
			animation->frameIndex--;
			//animation->frameIndex = -1;
			animation->isRunning = false;
		}
	}

}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new Animation component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
Animation* AnimationCreate(void)
{
	Animation* ptrAnimation = calloc(1, sizeof(Animation));

	if (ptrAnimation != NULL)
		return ptrAnimation;
	else
		return NULL;
}

// Free the memory associated with an Animation component.
// (NOTE: The Animation pointer must be set to NULL.)
// Params:
//	 animation = Pointer to the Animation pointer.
void AnimationFree(Animation** animation)
{
	if (*animation) 
		free(*animation);

	*animation = NULL;
}

// Read the properties of an Animation component from a file.
// [NOTE: Read the integer values for frameIndex and frameCount.]
// [NOTE: Read the float values for frameDelay and frameDuration.]
// [NOTE: Read the boolean values for isRunning and isLooping.]
// Params:
//	 animation = Pointer to the Animation component.
//	 stream = The data stream used for reading.
void AnimationRead(Animation* animation, Stream stream)
{
	//Could be a problem here
	if (animation != NULL && stream != NULL)
	{
		animation->frameIndex = StreamReadInt(stream);
		animation->frameCount = StreamReadInt(stream);
		animation->frameDelay = StreamReadFloat(stream);
		animation->frameDuration = StreamReadFloat(stream);
		animation->isRunning = StreamReadBoolean(stream);
		animation->isLooping = StreamReadBoolean(stream);
	}
}

// Set the parent Entity for an Animation component.
// Params:
//	 animation = Pointer to the Animation component.
//	 parent = Pointer to the parent Entity.
void AnimationSetParent(Animation* animation, Entity* parent)
{
	if (animation != NULL)
		animation->parent = parent;
}

// Play a simple animation sequence [0 .. frameCount - 1].
// (Hint: This function must initialize all variables, except for "parent".)
// Params:
//	 animation = Pointer to the Animation component.
//	 frameCount = The number of frames in the sequence.
//	 frameDuration = The amount of time to display each frame (in seconds).
//	 isLooping = True if the animation loops, false otherwise.
//Don't forget to check if isDone is set at the end of a loop
void AnimationPlay(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
	if (animation != NULL)
	{
		animation->frameIndex = 0;
		animation->frameCount = frameCount;
		animation->frameDelay = 0.0;
		animation->frameDuration = frameDuration;
		animation->isRunning = true;
		animation->isLooping = isLooping;
	
		Sprite* animSprite = EntityGetSprite(animation->parent);

		SpriteSetFrame(animSprite, animation->frameIndex);
	}

	return;
}

// Update the animation.
// Params:
//	 animation = Pointer to the Animation component.
//	 dt = Change in time (in seconds) since the last game loop.
void AnimationUpdate(Animation* animation, float dt)
{
	if (animation != NULL)
	{


		if (animation->isRunning)
		{
			animation->frameDelay -= dt;

			if (animation->frameDelay <= 0)
			{
				AnimationAdvanceFrame(animation, dt);
			}
		}
		return;
	}
	return;
}

// Determine if the animation has reached the end of its sequence.
// Params:
//	 animation = Pointer to the Animation component.
// Returns:
//	 If the Animation pointer is valid,
//		then return the value in isDone,
//		else return false.
bool AnimationIsDone(const Animation* animation)
{
	if (animation != NULL)
		return animation->isDone;
	else
		return false;
}
