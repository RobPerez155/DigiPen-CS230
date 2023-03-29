//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once

#include "stdafx.h"
#include <Windows.h>

#include "BaseSystem.h"
#include "ScoreSystem.h"
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

	typedef struct ScoreSystem
	{
		BaseSystem base;

		unsigned score;
		unsigned highScore;
		unsigned waveCount;

	}	ScoreSystem;
	
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------
		//------------------------------------------------------------------------------
	ScoreSystem score;
	ScoreSystem newScore;
	
	// Private Functions:
	//------------------------------------------------------------------------------
	
	static bool ScoreSystemInit(void);
	static void ScoreSystemUpdate(float dt);
	static void ScoreSystemRender(void);
	static void ScoreSystemExit(void);

		//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	static ScoreSystem instance =
	{
		{ "ScoreSystem", ScoreSystemInit, ScoreSystemUpdate, ScoreSystemRender, ScoreSystemExit},
	};

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Get the instance of the Score System.
	BaseSystem* ScoreSystemGetInstance(void)
	{
		// Initialize any system-specific variables here:

		// Return a reference to the instance of this system.
		return (BaseSystem*)&instance;
	}

	// Initialize the System.
	static bool ScoreSystemInit(void)
	{
		return true;
	}

	// Update the System.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	static void ScoreSystemUpdate(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		UNREFERENCED_PARAMETER(dt);
	}

	// Render the System.
	static void ScoreSystemRender(void)
	{
	}

	// Shutdown the System.
	//   (HINT: Free any allocated resources and/or opened files).
	static void ScoreSystemExit(void)
	{
	}

	// Clear the Score System
	// (Set the score, highScore, and waveCount variables to 0.)
	void ScoreSystemClear(void)
	{
		score.score = 0;
		score.highScore = 0;
		score.waveCount = 0;
		newScore.highScore = score.score;
	}

	// Reset the Score System.
	// (Step 1: The highScore variable should be updated if score is higher.)
	// (Step 2: The score and waveCount variables should be set to zero.)
	void ScoreSystemReset(void)
	{
		if (score.score >= score.highScore /* >= newScore.highScore*/)
		{
			score.highScore = score.score /*= score.highScore*/;
			score.score = 0;
			score.waveCount = 0;
		}
		else {
			score.highScore = score.highScore;
			score.score = 0;
			score.waveCount = 0;
		}
	}

	// Get the specified value from the Score System.
	// (HINT: There many different ways to handle this.  Two options include:
	//   - Store the Score System variables in an array and use this index
	//     to access into the array.
	//   - Use a switch-statement to access the correct variable.)
	// returns:
	//   The value stored in the specified variable.
	unsigned ScoreSystemGetValue(ScoreSystemId valueId)
	{
		unsigned returnVal = 0;

		switch (valueId)
		{
		case SsiScore:
			returnVal = score.score;
			break;

		case SsiHighScore:
			returnVal = score.highScore;
			break;

		case SsiWaveCount:
			returnVal = score.waveCount;
			break;

		default:
			break;
		}

		return returnVal;
	}

	// Increase the current score by a specified amount.
	// Params:
	//   amount = The amount to be added to the score.
	void ScoreSystemIncreaseScore(unsigned amount)
	{
		score.score += amount;
	}

	// Increase the current wave count by one.
	void ScoreSystemIncreaseWave(void)
	{
		score.waveCount++;
	}

	/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       // End of extern "C" {
#endif

