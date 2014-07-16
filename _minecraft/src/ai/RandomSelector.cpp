#include "RandomSelector.h"

#include <ctime>
#include <cstdlib>
#include <numeric>

using namespace DatNS;
using namespace std;

static int accBehavior(Behavior* a, Behavior* b)
{
	return 0;
}

RandomSelector::RandomSelector()
{
	srand(time(0));
}

const Behavior* RandomSelector::getBehavior() const
{
	vector<Behavior*> behaviors = getBehaviors();
	int max = accumulate(
		behaviors.cbegin(),
		behaviors.cend(),
		0,
		accBehavior
	);
	int randNum = rand() % max;
	for (vector<Behavior*>::const_iterator it = behaviors.cbegin(), end = behaviors.cend();
		it != end; ++it)
	{
		(*it)->
	}
}
