#include "OurMinecraft.hpp"

#include "actors\ActorsRepository.hpp"

using namespace DatNS;

void DatNS::init()
{
	// Create Parasite
	for (int i = 0; i < ActorsRepository::START_PARASITES; ++i)
	{
		ActorsRepository::get()->createParasite();
	}

	for (int i = 0; i < ActorsRepository::START_ELVES; ++i)
	{
		ActorsRepository::get()->createElf();
	}

	for (int i = 0; i < ActorsRepository::START_BUSHES; ++i)
	{
		ActorsRepository::get()->createBush();
	}

	for (int i = 0; i < ActorsRepository::START_HUNTERS; ++i)
	{
		ActorsRepository::get()->createHunter();
	}
}

void DatNS::update(float elapsed)
{
	list<ZergActor*> z = ActorsRepository::get()->getParasites();
	for (list<ZergActor*>::const_iterator it = z.begin();
		it != z.end();
		++it)
	{
		(*it)->update(elapsed);
	}
}

void DatNS::draw()
{
	ActorsRepository::reset();
	list<ZergActor*> z = ActorsRepository::get()->getParasites();
	for (list<ZergActor*>::const_iterator it = z.begin();
		it != z.end();
		++it)
	{
		(*it)->render();
	}
}
