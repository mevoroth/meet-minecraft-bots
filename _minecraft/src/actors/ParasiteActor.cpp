#include "ParasiteActor.hpp"

#include "ActorsRepository.hpp"

using namespace DatNS;

void ParasiteActor::multiply()
{
	ActorsRepository::get()->createParasite(*this);
}

void ParasiteActor::multiply()
{

}
