#include "ZergActor.hpp"

#include "ActorsRepository.hpp"

using namespace DatNS;

void ZergActor::multiply()
{
	ActorsRepository::get()->createParasite(*this);
}
