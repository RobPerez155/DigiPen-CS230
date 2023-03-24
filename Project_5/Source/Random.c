//------------------------------------------------------------------------------
//
// File Name:	Random.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include <stdlib.h>

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
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

// Initialize the pseudorandom number generator (PRNG).
// You may use the example code from
//	 https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rand.
// However, if you do so, then you must cite this source within the .c file.
	void RandomInit()
	{
		srand(1776);
	}

	// Generate a random number in the interval [rangeMin, rangeMax] (inclusive).
	// You may use the example code from
	//	 https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rand.
	// However, if you do so, then you must cite this source within the .c file.
	// Params:
	//	 rangeMin = The lowest possible number generated.
	//	 rangeMax = The highest possible number generated.
	// Returns:
	//   A random number in the interval [rangeMin, rangeMax].
	int RandomRange(int rangeMin, int rangeMax)
	{
		int random = (rand() % (rangeMax + 1 - rangeMin) + rangeMin);
		return random;
	}

	// Generate a random floating-point number in the interval [rangeMin, rangeMax] (inclusive).
	// Params:
	//	 rangeMin = The lowest possible number generated.
	//	 rangeMax = The highest possible number generated.
	float RandomRangeFloat(float rangeMin, float rangeMax)
	{
		//float random = (rand() / (rangeMax - rangeMin + 1) + rangeMin);
		float random = ((rangeMax - rangeMin) * ((float)rand() / RAND_MAX) + rangeMin);
		return random;

	}

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

