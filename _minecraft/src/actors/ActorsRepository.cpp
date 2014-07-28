#include "ActorsRepository.hpp"

#include "utils\types_extended.hpp"

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

void ActorsRepository::reset()
{
	ZergActor::reset();
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
	NYWorld* w = UniqWorld::get()->World();
	static const int worldsize = MAT_SIZE * NYChunk::CHUNK_SIZE;

	int x = rand() % worldsize;
	int y = rand() % worldsize;

	ZergActor* parasite = new ZergActor(
		NYVert3Df(x, y, w->_MatriceHeightsTmp[x][y]),
		NYVert3Df(0, 0, 0),
		FORWARD
	);
	insert(parasite);
	return parasite;
}

Actor* ActorsRepository::createParasite(const Actor& src)
{
	ZergActor* parasite = new ZergActor(
		src.getPosition(),
		NYVert3Df(0, 0, 0),
		src.getForward()
	);
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

list<ZergActor*> ActorsRepository::getParasites()
{
	return _parasites;
}

Actor* ActorsRepository::createBush()
{
	return 0;
}
Actor* ActorsRepository::createElf()
{
	return 0;
}
Actor* ActorsRepository::createHunter()
{
	return 0;
}
