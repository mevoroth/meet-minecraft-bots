#include "ZergActor.hpp"

#include "ActorsRepository.hpp"

using namespace DatNS;

ZergActor::ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rot)
	: Actor(pos, speed, rot)
{
}

void ZergActor::multiply()
{
	ActorsRepository::get()->createParasite(*this);
}

void ZergActor::update()
{

}
