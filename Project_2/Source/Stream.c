//------------------------------------------------------------------------------
//
// File Name:	Stream.c
// Author(s):	Robert Perez (rob.perez)
// Project:		Project 1
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Stream.h"

#include "Trace.h"
#include <DGL.h>

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// TODO: Declare a private variable for storing a file handle.
static FILE* streamFile;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Open a file for reading.
// (NOTE: Use fopen_s() with the "rt" option.)
// (NOTE: You must generate the following trace message if the file was not opened successfully:
//	  TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);
//	  Where errorMsg is a char array containing the error message obtained using strerror_s().)
// 
// Params:
//	 filePath = The file to be opened for reading.
// Returns:
//	 NULL if filePath is NULL or the file could not be opened.
//	 Pointer to a FILE object if the file was opened successfully.
Stream StreamOpen(const char* filePath)
{
	fopen_s(&streamFile, filePath, "rt");
	char errorMsg[100];

	strerror_s(errorMsg, 100, errno);

	if (streamFile == NULL) {
		TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);
		return NULL;
	}	else {
		return streamFile;
	}
}

// Read a single integer from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for an integer.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 0 if the stream was not opened succesfully;
//	 otherwise, an integer value read from the file.
int StreamReadInt(Stream stream)
{
	if (stream == NULL)
	{
		return 0;
	}
	else {
		int streamScan;
		fscanf_s(stream, "%i", &streamScan);
		return streamScan;
	}
}

// Read a single float from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for a float.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream was opened succesfully,
//	   then return a float value read from the file,
//	   else return 0.
float StreamReadFloat(Stream stream) {
	if (stream == NULL)
	{
		return 0;
	}
	else {
		float streamScan;
		fscanf_s(stream, "%f", &streamScan);
		return streamScan;
	}
}

// Read the data for a Vector2D from a stream.
// (NOTE: Verify that the stream and vector pointer are valid first.)
// (HINT: Use StreamReadFloat() to read the x and y values, in sequence.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream and vector pointer are both valid,
//	   then fill the vector with two float values (x & y),
//	   else do nothing (optionally, write an error message to the trace log).
void StreamReadVector2D(Stream stream, DGL_Vec2* vector) {
	if (stream != NULL && vector != NULL) {
		vector->x = StreamReadFloat(stream);
		vector->y = StreamReadFloat(stream);
	}
	else if ( StreamReadFloat == NULL) {
		TraceMessage("Error: StreamOpen could not open file");
	}
	else {
		TraceMessage("Error: DGL_Vec returned NULL");
	}
}

// Read a token (a single word) from a file.
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 Pointer to tokenBuffer
const char* StreamReadToken(Stream stream)
{
	tokenBuffer[0] = 0;
	int tokenBuffCount = _countof(tokenBuffer);

	if (stream)
	{
		fscanf_s(stream, "%s", tokenBuffer, tokenBuffCount);
	}

	return tokenBuffer;
}

// Close an opened stream.
// (NOTE: Do not attempt to close the stream if the pointer is null.)
// (PRO TIP: Avoid dangling pointers by setting the FILE pointer to NULL.)
// Params:
//	 stream = The file stream to be closed.
void StreamClose(Stream* stream) {
	if (stream == NULL) {
		TraceMessage("Error: StreamClose could not close file");
	}
	else {
		fclose(*stream);
		*stream = NULL;
	}
}