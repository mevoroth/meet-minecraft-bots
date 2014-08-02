#include "CurrentBehavior.hpp"

#include <cstdio>

using namespace DatNS;

CurrentBehavior::CurrentBehavior() : _currentBehavior(0) {
	printf("test\n");
};
void CurrentBehavior::setBehavior(int state) { _currentBehavior = state; };
int CurrentBehavior::getBehavior() const {
	printf("test2\n");
	return _currentBehavior;
};
