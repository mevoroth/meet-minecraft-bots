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

void ActorsRepository::insert(ParasiteActor* actor)
{
	_parasites.push_back(actor);
}

Actor* ActorsRepository::createParasite(ParasiteActor& actor)
{
	ParasiteActor* parasite = new ParasiteActor();
	throw std::exception("NOT FULLY IMPLEMENTED!");
	insert(parasite);
	return parasite;
}

void ActorsRepository::removeParasite(ParasiteActor* actor)
{
	_parasites.remove(actor);
	delete actor;
}
