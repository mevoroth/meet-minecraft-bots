#include "ActorsRepository.hpp"

#include <exception>

using namespace DatNS;

ActorsRepository* ActorsRepository::_inst = 0;

ActorsRepository::ActorsRepository() {}
ActorsRepository* ActorsRepository::get()
{
	if (!_inst)
	{
		_inst = new ActorsRepository();
	}
	return _inst;
}

void ActorsRepository::insert(Actor* actor)
{
	
}

void ActorsRepository::insert(ZergActor* actor)
{
	_parasites.push_back(actor);
}

Actor* ActorsRepository::createParasite()
{
	ZergActor* parasite = new ZergActor(NYVert3Df(0, 0, 0), NYVert3Df(0, 0, 0), NYVert3Df(0, 0, 0));
	insert(parasite);
	return parasite;
}

Actor* ActorsRepository::createParasite(const Actor& src)
{
	ZergActor* parasite = new ZergActor(NYVert3Df(0, 0, 0), NYVert3Df(0, 0, 0), NYVert3Df(0, 0, 0));
	insert(parasite);
	return parasite;
}

void ActorsRepository::removeParasite(ZergActor* actor)
{
	_parasites.remove(actor);
	delete actor;
}

list<ElfActor*> ActorsRepository::getElves()
{
	return list<ElfActor*>();
}
