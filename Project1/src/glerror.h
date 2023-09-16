#pragma once
#ifndef GLERROR_H
#define GLERROR_H

#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCHECK(x) clearGlError();\
	x;\
	ASSERT(checkGlError(#x, __FILE__, __LINE__));

void clearGlError();

bool checkGlError(const char* expression, const char* file, int line);

#endif // !GLERROR_H
