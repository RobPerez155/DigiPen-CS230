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
  Sprite* animSprite = this->parent->GetComponent<Sprite>();
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
    /*animation->frameIndex = StreamReadInt(stream);
    animation->frameCount = StreamReadInt(stream);
    animation->frameDelay = StreamReadFloat(stream);
    animation->frameDuration = StreamReadFloat(stream);
    animation->isRunning = StreamReadBoolean(stream);
    animation->isLooping = StreamReadBoolean(stream);*/
  }
}

/*void Animation::SetParent(Animation* animation, Entity* parent)
{
  if (animation != nullptr)
    animation->parent = parent;
}*/

void Animation::Play(int frameCount, float frameDuration, bool isLooping)
//void Animation::Play(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
    this->frameIndex = frameCount;
    /*this->frameCount = this->frameCount;*/
    this->frameDelay = frameDuration;
    /*this->frameDuration = this->frameDuration;*/
    this->isRunning = isLooping;
    /*this->isLooping = this->isLooping;*/

  //Fixed
    // Sprite* animSprite = Entity::GetSprite(this->parent);
  Sprite* animSprite = (this->GetParent().GetComponent<Sprite>());
  //Fixed
    animSprite->SetFrame(this->frameIndex);
    this->isDone = false;
}

void Animation::Update(float dt)
//void Animation::Update(Animation* animation, float dt)
{
  {
    for (auto it = components.begin(); it != components.end(); ++it)
    {
      it->second->Update(dt);
    }
  }
  /*if (animation != nullptr)
  {
    animation->isDone = false;
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
  return;*/
}

bool Animation::IsDone() const
//bool Animation::IsDone(const Animation* animation);
{
  return this->isDone;
}
