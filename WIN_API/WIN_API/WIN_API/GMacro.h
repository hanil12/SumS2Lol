#pragma once
#include "Math/Vector.h"

// WINDOW
#define WIN_WIDTH	1366
#define WIN_HEIGHT	768
#define CENTER		Vector(WIN_WIDTH, WIN_HEIGHT) * 0.5f

// MATH
#define PI 3.141592
#define LERP(s,e,t)		s + (e - s) * t

// RGB
#define RED			RGB(255,0,0)
#define GREEN		RGB(0,255,0)
#define BLUE		RGB(0,0,255)
#define WHITE		RGB(255,255,255)
#define BLACK		RGB(0,0,0)