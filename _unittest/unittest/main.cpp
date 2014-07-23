#include "actors\Actor.hpp"
#include "engine\utils\types_3d.h"
#include "utils\types_extended.hpp"

namespace Test
{
	class TestActor : public DatNS::Actor
	{
	public:
		TestActor() : Actor(NYVert3Df(0, 0, 0), NYVert3Df(0, 0, 0), NYVert3Df(0, 0, 0)) {};
		void update() {};
	};
}

int main()
{
	Test::TestActor* act = new Test::TestActor();

	NYVert3Df before, after, fw;

	before = act->Rotation();

	fw = eulerToDirection(act->Rotation());
	act->setForward(act->getForward());

	after = act->Rotation();

	printf("Before : (%f, %f, %f)\n", before.X, before.Y, before.Z);
	printf("After  : (%f, %f, %f)\n", after.X, after.Y, after.Z);
	printf("Fw     : (%f, %f, %f)\n", fw.X, fw.Y, fw.Z);

	system("pause");

	return 0;
}
