#include "ZergActor.hpp"

#include "ActorsRepository.hpp"

using namespace DatNS;

ZergActor::ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw)
	: Actor(pos, speed, fw)
{
}

void ZergActor::multiply()
{
	ActorsRepository::get()->createParasite(*this);
}

void ZergActor::update()
{

}
