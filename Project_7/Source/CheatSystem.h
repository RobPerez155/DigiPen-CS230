//------------------------------------------------------------------------------
//
// File Name:	CheatSystem.h
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

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {	// Assume C declarations for C++.
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct BaseSystem BaseSystem;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Typedefs:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub System.
BaseSystem* CheatSystemGetInstance(void);

/*----------------------------------------------------------------------------*/

//static bool CheatSystemInit(void)
//{
//	return true;
//}
//
//// Make an array of scenes
//static const CheatSystemKeyBinding keyBindings[] =
//{
//		{'1', Level1SceneGetInstance},
//		{'2', Level2SceneGetInstance},
//		{'3', AsteroidsSceneGetInstance},
//		{'4', SandboxSceneGetInstance},
//		{'5', DemoSceneGetInstance},
//		{'6', OmegaSceneGetInstance}
//};
//
//int arrLength = sizeof(keyBindings);
//
//// Update the System.
//// Params:
////	 dt = Change in time (in seconds) since the last game loop.
//static void CheatSystemUpdate(float dt)
//{
//	// Tell the compiler that the 'dt' variable is unused.
//	UNREFERENCED_PARAMETER(dt);
//	// Create for loop to check for key presses
//	for (int i = 0; i <= arrLength; i++)
//	{
//		if (DGL_Input_KeyTriggered(keyBindings[i].key))
//		{
//			const Scene* nextScene = keyBindings[i].getInstance();
//			SceneSystemSetNext(nextScene);
//		}
//	}
//}

#ifdef __cplusplus
}                       // End of extern "C" {
#endif

