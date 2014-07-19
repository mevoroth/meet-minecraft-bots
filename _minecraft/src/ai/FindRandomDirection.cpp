#include "FindRandomDirection.hpp"

#include <cstdlib>
#include "utils\types_extended.hpp"
#include "RandomDirectionStore.hpp"

using namespace DatNS;

Behavior::ReturnCode FindRandomDirection::update(Actor& actor)
{
	reinterpret_cast<RandomDirectionStore&>(actor).store(
		eulerToDirection(
			NYVert3Df(
				static_cast<float>(rand()) * 2.0f * M_PI / static_cast<float>(RAND_MAX),
				static_cast<float>(rand()) * 2.0f * M_PI / static_cast<float>(RAND_MAX),
				static_cast<float>(rand()) * 2.0f * M_PI / static_cast<float>(RAND_MAX)
			)
		)
	);
	onFinished(actor);
	return ReturnCode::FINISHED;
}
