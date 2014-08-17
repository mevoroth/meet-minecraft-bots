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
	static int i = 0;
	list<ZergActor*> z = ActorsRepository::get()->getParasites();
	for (list<ZergActor*>::const_iterator it = z.begin();
		it != z.end();
		++it)
	{
		(*it)->update(elapsed);
	}
	list<BushActor*> b = ActorsRepository::get()->getBushes();
	for (list<BushActor*>::const_iterator it = b.begin();
		it != b.end();
		++it)
	{
		(*it)->update(elapsed);
	}
	list<HunterActor*> h = ActorsRepository::get()->getHunters();
	for (list<HunterActor*>::const_iterator it = h.begin();
		it != h.end();
		++it)
	{
		(*it)->update(elapsed);
	}
	list<ElfActor*> e = ActorsRepository::get()->getElves();
	for (list<ElfActor*>::const_iterator  it = e.begin();
		it != e.end();
		++it)
	{
		(*it)->update(elapsed);
	}
	++i;
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
	list<BushActor*> b = ActorsRepository::get()->getBushes();
	for (list<BushActor*>::const_iterator it = b.begin();
		it != b.end();
		++it)
	{
		(*it)->render();
	}
	list<HunterActor*> h = ActorsRepository::get()->getHunters();
	for (list<HunterActor*>::const_iterator it = h.begin();
		it != h.end();
		++it)
	{
		(*it)->render();
	}
	list<ElfActor*> e = ActorsRepository::get()->getElves();
	for (list<ElfActor*>::const_iterator  it = e.begin();
		it != e.end();
		++it)
	{
		(*it)->render();
	}
}
