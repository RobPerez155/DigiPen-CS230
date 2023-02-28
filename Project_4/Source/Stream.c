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

// Read a single boolean value from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for an integer.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream was opened succesfully,
//	   then return a boolean value read from the file as an integer,
//	   else return 0.
bool StreamReadBoolean(Stream stream)
{
	if (stream == NULL)
	{
		return 0;
	}
	else {
		int streamScan;
		fscanf_s(stream, "%d", &streamScan);
		return streamScan;
	}
}

// Read the data for a Color from a stream.
// (NOTE: Verify that the stream and vector pointer are valid first.)
// (HINT: Use StreamReadFloat() to read the RGBA values, in sequence.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream and vector pointer are both valid,
//	   then read the RGBA components, in sequence,
//	   else fill the RGBA components with 0.
//		 (optionally, write an error message to the trace log).
void StreamReadColor(Stream stream, DGL_Color* color)
{
	//if color and stream are valid 
	if (stream != NULL && color != NULL)
	{
		float red = StreamReadFloat(stream);
		float green = StreamReadFloat(stream);
		float blue = StreamReadFloat(stream);
		float alpha = StreamReadFloat(stream);

	//read the color values in order, needed to look at DGL_Color struct to find the order
		color->r = red;
		color->g = green;
		color->b = blue;
		color->a = alpha;
	}
	else
	{
		if (color != NULL)
		{
			color->r = 0.0f;
			color->g = 0.0f;
			color->b = 0.0f;
			color->a = 0.0f;
		}
		TraceMessage("Error: Stream or color pointer is NULL in StreamReadColor.");
	}
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