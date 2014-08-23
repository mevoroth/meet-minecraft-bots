#ifndef _TYPES_EXTENDED_HPP_
#define _TYPES_EXTENDED_HPP_

#include "engine\utils\types_3d.h"
#include "engine\timer.h"

#include "world.h"

const NYVert3Df UP = NYVert3Df(0, 0, 1);
const NYVert3Df RIGHT = NYVert3Df(1, 0, 0);
const NYVert3Df FORWARD = NYVert3Df(0, 1, 0);

class UniqWorld
{
private:
	static UniqWorld* instance;
	NYWorld* world;
	NYTimer* timer;
	UniqWorld();
	~UniqWorld();
public:
	static UniqWorld* get();
	inline NYWorld* World() { return world; };
	void setTimer(NYTimer* timer) { this->timer = timer; }
	inline NYTimer* Timer() { return timer; }
};

template <typename T> T clamp(T a, T m, T M)
{
	if (a < m)
	{
		return m;
	}
	else if (a > M)
	{
		return M;
	}
	else
	{
		return a;
	}
}

//template <typename T> T lerp(const T& a, const T& b, float t)
//{
//	t = clamp<float>(t, 0, 1);
//	//return a * t + b * (1 - t);
//	return (a - b) * t + b;
//}

NYVert3Df lerp(const NYVert3Df& a, const NYVert3Df& b, float t);

#endif
