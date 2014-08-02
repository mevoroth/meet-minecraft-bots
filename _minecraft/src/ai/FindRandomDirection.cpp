#include "FindRandomDirection.hpp"

#include <cstdlib>
#include "utils\types_extended.hpp"
#include "RandomDirectionStore.hpp"

using namespace DatNS;

Behavior::ReturnCode FindRandomDirection::update(Actor& actor) const
{
	NYVert3Df fw(FORWARD);
	NYVert3Df up(UP);
	NYVert3Df right(RIGHT);
	
	fw.rotate(up, static_cast<float>(rand()) * 2.0f * M_PI / static_cast<float>(RAND_MAX));
	fw.rotate(right, static_cast<float>(rand()) * 2.0f * M_PI / static_cast<float>(RAND_MAX));
	
	dynamic_cast<RandomDirectionStore&>(actor).store(fw);

	onFinished(actor);
	return ReturnCode::FINISHED;
}
