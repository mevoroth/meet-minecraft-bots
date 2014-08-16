#include "Eater.hpp"

#include "actors\ActorsRepository.hpp"

using namespace DatNS;

void Eater::eat()
{
	eatable->consume();
}
