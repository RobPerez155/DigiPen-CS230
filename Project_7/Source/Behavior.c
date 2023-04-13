//------------------------------------------------------------------------------
//
// File Name:	Behavior.h
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 4
// Course:		CS230S23
//
// Copyright � 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Stream.h"
//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	typedef struct Entity Entity;
	typedef struct Behavior Behavior;
	typedef FILE* Stream;

	//------------------------------------------------------------------------------
	// Public Consts:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	typedef void(*BehaviorFunctionPtr)(Behavior* behavior);
	typedef void(*BehaviorFunctionPtrDt)(Behavior* behavior, float dt);

	// This structure is being declared publicly, as it will be used to implement
	// pseudo-inheritance in Project 5.
	// NOTE: You are not allowed to change the contents of this structure, as it is
	// part of the public interface.
	typedef struct Behavior
	{
		// Pointer to the behavior's parent game object.
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
	//	   else return NULL.
	Behavior* BehaviorClone(Behavior* other)
	{
		if (other == NULL)
		{
			return NULL;
		}

		//Behavior* behaviorClone = calloc(1, other->memorySize);
		Behavior* behaviorClone = new Behavior;
		behaviorClone = static_cast<Behavior*>(::operator new(other->memorySize));

		if (behaviorClone == NULL)
		{
			return NULL;
		}

		//*behaviorClone = *other;
		memcpy(behaviorClone, other, other->memorySize);

		return behaviorClone;
	}

	// Free the memory associated with a Behavior component.
	// (Also, set the behavior pointer to NULL.)
	// Params:
	//	 behavior = Pointer to the Behavior component.
	void BehaviorFree(Behavior** behavior)
	{
		if (*behavior)
			free(*behavior);

		*behavior = NULL;
	};

	// Read the properties of a Behavior component from a file.
	// [NOTE: Read the stateCurr and stateNext values using StreamReadInt.]
	// [NOTE: Read the timer value using StreamReadFloat.]
	// Params:
	//	 behavior = Pointer to the Behavior component.
	//	 stream = Pointer to the data stream used for reading.
	void BehaviorRead(Behavior* behavior, Stream stream)
	{
		if (behavior != NULL)
		{

			behavior->stateCurr = StreamReadInt(stream);
			behavior->stateNext = StreamReadInt(stream);
			behavior->timer = StreamReadFloat(stream);
		}
	}

	// Set the parent game object for a Behavior component.
	// Params:
	//	 behavior = Pointer to the Behavior component.
	//	 parent = Pointer to the parent game object.
	void BehaviorSetParent(Behavior* behavior, Entity* parent)
	{
		if (behavior != NULL)
			behavior->parent = parent;
	}

	// Update the Behavior component.
	// (Hint: Refer to the Word document for detailed instructions regarding this function.)
	// Params:
	//	 behavior = Pointer to the Behavior component.
	//	 dt = Change in time (in seconds) since the last game loop.

	//�	The function, BehaviorUpdate, should implement a finite - state machine(FSM), as follows :
	//o	Validate the behavior pointer.
	//	If the behavior state is changing(stateCurr != stateNext),
	//		Call the onExit() function, iff(�if and only if�) it exists.
	//		Set stateCurr = stateNext
	//		Call the onInit() function, iff it exists.
	//	Call the onUpdate function, iff it exists.

	void BehaviorUpdate(Behavior* behavior, float dt)
	{
		if (behavior != NULL)
		{
			if (behavior->stateCurr != behavior->stateNext)
			{
				if (behavior->onExit)
				{
					behavior->onExit(behavior);
				}

				behavior->stateCurr = behavior->stateNext;

				if (behavior->onInit)
				{
					behavior->onInit(behavior);
				}
			}

			if (behavior->onUpdate)
			{
				behavior->onUpdate(behavior, dt);
			}
		}
	}

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif
