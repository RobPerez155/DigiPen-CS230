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
#include "Component.h"
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

void Animation::AdvanceFrame(float dt)
{
  UNREFERENCED_PARAMETER(dt);

  //Sprite* animSprite = EntityGetSprite(this->parent);
  //auto* animSprite = this->parent;
  Sprite* animSprite = GetParent().GetComponent<Sprite>();
  this->frameIndex++;

  if (this->frameIndex >= this->frameCount)
  {
    if (this->isLooping)
    {
      this->frameIndex = 0;
      this->isDone = true;
    }
    else
    {
      this->frameIndex--;
      //this->frameIndex = -1;
      this->isRunning = false;
      this->isDone = true;
    }
  }

  if (this->isRunning)
  {
    // Sprite::SetFrame(animSprite, this->frameIndex);
    animSprite->SetFrame(this->frameIndex);
    this->frameDelay += this->frameDuration;
  }
  else
  {
    this->frameDelay = 0;
  }
}


Animation::Animation(Entity& parent): Component(parent), frameCount(0), frameDelay(.0f), frameDuration(0), frameIndex (0)
{

}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
Component* Animation::Clone(Entity& newParent) const
//Animation* Animation::Clone(const Animation* other)
{
  Animation* animationClone = new Animation(newParent);

  if (animationClone == nullptr)
  {
    return nullptr;
  }

  animationClone->frameIndex = frameIndex;
  animationClone->frameCount = frameCount;
  animationClone->frameDelay = frameDelay;
  animationClone->frameDuration = frameDuration;
  animationClone->isRunning = isRunning;
  animationClone->isLooping = isLooping;
  animationClone->isDone = isDone;

  return animationClone;
}

void Animation::Read(Stream stream)
//void Animation::Read(Animation* animation, Stream stream)
{
  if (stream != nullptr)
  {
    StreamReadInt(stream);
    StreamReadInt(stream);
    StreamReadFloat(stream);
    StreamReadFloat(stream);
    StreamReadBoolean(stream);
    StreamReadBoolean(stream);
    /*frameIndex = StreamReadInt(stream);
    frameCount = StreamReadInt(stream);
    frameDelay = StreamReadFloat(stream);
    frameDuration = StreamReadFloat(stream);
    isRunning = StreamReadBoolean(stream);
    isLooping = StreamReadBoolean(stream);*/
  }
}

/*void Animation::SetParent(Animation* animation, Entity* parent)
{
  if (animation != nullptr)
    parent = parent;
}*/

void Animation::Play(int animFrameCount, float animFrameDuration, bool animIsLooping)
//void Animation::Play(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
  this->frameIndex = 0;
  this->frameCount = animFrameCount;
  this->frameDelay = 0.0f;
  this->frameDuration = animFrameDuration;
  this->isRunning = true;
  this->isLooping = animIsLooping;

  //Fixed
  // Sprite* animSprite = Entity::GetSprite(this->parent);
  Sprite* animSprite = this->GetParent().GetComponent<Sprite>();
  if(animSprite)
  {
    //Fixed
    animSprite->SetFrame(this->frameIndex);
  }
  this->isDone = false;
}

void Animation::Update(float dt)
//void Animation::Update(Animation* animation, float dt)
{
  isDone = false;
  if (isRunning)
  {
    frameDelay -= dt;

    if (frameDelay <= 0)
    {
      AdvanceFrame(dt);
    }
  }
}

bool Animation::IsDone() const
//bool Animation::IsDone(const Animation* animation);
{
  return this->isDone;
}
