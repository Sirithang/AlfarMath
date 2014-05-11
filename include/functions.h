#pragma once

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
}