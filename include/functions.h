#pragma once

#include <math.h>

namespace alfar
{
	inline int iround(const float f)
	{
		return (int)(f+0.5f);
	}

	template<typename T>
	T min3(const T a, const T b, const T c)
	{
		T t = (a > b ? b : a);

		return t > c ? c : t;
	}

	template<typename T>
	T max3(const T a, const T b, const T c)
	{
		T t = (a < b ? b : a);

		return t < c ? c : t;
	}

	template<typename T>
	T clamp(const T v, const T min, const T max)
	{
		T t = v > min ? v : min;

		return t < max ? t : max;
	}

	inline bool approximatly(float a, float b)
	{
#define TOLERANCE 0.00001f;

		return fabs(a-b) < TOLERANCE;
	}
}