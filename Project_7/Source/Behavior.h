//------------------------------------------------------------------------------
//
// File Name:	Behavior.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 7
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "stdafx.h"
#include "Stream.h"
#include "Entity.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class Behavior : public Component
{
public:
	__inline static Type type() { return Type::Behavior; }

	explicit Behavior(Entity& parent);

	virtual void Read(Stream stream) override;
	
	virtual void Init() {}
	virtual void Exit() {}

	__inline void SetState(int newState) { stateNext = newState; }
	
	virtual void Update(float dt) override;
private:

protected:
	int stateCurr;
	int stateNext;
	float	timer;
};
