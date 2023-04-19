//------------------------------------------------------------------------------
//
// File Name:	Behavior.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "stdafx.h"
#include "Stream.h"
#include "Entity.h"
#include "Behavior.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class Behavior : public Component
{
public:
	typedef void(*BehaviorFunctionPtr)(Behavior* behavior);
	typedef void(*BehaviorFunctionPtrDt)(Behavior* behavior, float dt);
	
	Entity* parent;

	unsigned int memorySize;

	int stateCurr;
	int stateNext;
	
	BehaviorFunctionPtr		onInit;
	BehaviorFunctionPtrDt	onUpdate;
	BehaviorFunctionPtr		onExit;
	
	float	timer;

	Component* Clone(Entity& newParent) const override;

	void Read(Stream stream);
	
	void SetParent(Entity* newParent);

	void Update(float dt);
}


#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

/*
typedef struct Entity Entity;
typedef struct Behavior Behavior;
typedef FILE* Stream;
*/

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

/*typedef void(*BehaviorFunctionPtr)(Behavior* behavior);
typedef void(*BehaviorFunctionPtrDt)(Behavior* behavior, float dt);

// This structure is being declared publicly, as it will be used to implement
// pseudo-inheritance in Project 5.
// NOTE: You are not allowed to change the contents of this structure, as it is
// part of the public interface.
typedef struct Behavior
{
	// Pointer to the behavior's parent Entity.
	Entity* parent;

	// The following variable is used to allocate the correct amount of memory
	//   when cloning a behavior component.  Cloning of "derived" behaviors will
	//   fail if insufficient memory is allocated.
	unsigned int memorySize;

	// Behavior Finite-State Machine (FSM) state variables.
	int stateCurr;
	int stateNext;

		// Behavior Finite-State Machine (FSM) function pointers.
	BehaviorFunctionPtr		onInit;
	BehaviorFunctionPtrDt	onUpdate;
	BehaviorFunctionPtr		onExit;

	// Additional variables shared by all behaviors.
	// NOTE: Variables that are unique to a specific behavior should not be placed here.

	// Generic timer - may be used as a life timer or a weapon cooldown timer.
	// (Default = 0, means infinite amount of time remaining or weapon can be fired.)
	float	timer;

} Behavior;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a clone of an existing behavior.
// (Hint: Perform a shallow copy of the member variables.)
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return nullptr.
Behavior* BehaviorClone(Behavior* other);

// Free the memory associated with a Behavior component.
// (Also, set the behavior pointer to nullptr.)
// Params:
//	 behavior = Pointer to the Behavior component.
void BehaviorFree(Behavior* * behavior);

// Read the properties of a Behavior component from a file.
// [NOTE: Read the stateCurr and stateNext values using StreamReadInt.]
// [NOTE: Read the timer value using StreamReadFloat.]
// Params:
//	 behavior = Pointer to the Behavior component.
//	 stream = Pointer to the data stream used for reading.
void BehaviorRead(Behavior* behavior, Stream stream);

// Set the parent Entity for a Behavior component.
// Params:
//	 behavior = Pointer to the Behavior component.
//	 parent = Pointer to the parent Entity.
void BehaviorSetParent(Behavior* behavior, Entity* parent);

// Update the Behavior component.
// (Hint: Refer to the Word document for detailed instructions regarding this function.)
// Params:
//	 behavior = Pointer to the Behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorUpdate(Behavior* behavior, float dt);*/

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

