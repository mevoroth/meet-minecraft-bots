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
}

void ActorsRepository::insert(ElfActor* actor)
{
	_elves.push_back(actor);
}

void ActorsRepository::insert(BushActor* actor)
{
	_bushes.push_back(actor);
}

void ActorsRepository::insert(ZergActor* actor)
{
	_parasites.push_back(actor);
}

void ActorsRepository::insert(HunterActor* actor)
{
	_hunters.push_back(actor);
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

Actor* ActorsRepository::createElf(Actor& src)
{
	ElfActor* elf = new ElfActor(
		src.getPosition(),
		NYVert3Df(0, 0, 0),
		src.getForward()
	);
	Group* currGroup = dynamic_cast<ElfActor&>(src).getGroup();

	if (currGroup->full())
	{
		currGroup = createGroup();
	}

	elf->setGroup(currGroup);

	insert(elf);
	return elf;
}

Actor* ActorsRepository::createHunter(const Actor& src)
{
	HunterActor* hunter = new HunterActor(
		src.getPosition(),
		NYVert3Df(0, 0, 0),
		src.getForward()
		);
	insert(hunter);
	return hunter;
}

void ActorsRepository::removeParasite(ZergActor* actor)
{
	_parasites.remove(actor);
	for (list<HunterActor*>::iterator it = _hunters.begin();
		it != _hunters.end();
		++it)
	{
		if ((*it)->getTargetParasite() == actor)
		{
			(*it)->removeParasite();
		}
	}
	delete actor;
}
void ActorsRepository::removeBush(BushActor* actor)
{
	_bushes.remove(actor);
	for (list<ElfActor*>::iterator it = _elves.begin();
		it != _elves.end();
		++it)
	{
		if ((*it)->getTargetedBush() == actor)
		{
			(*it)->removeBush();
		}
	}
	delete actor;
}

void ActorsRepository::remove(Group* group)
{
	_groups.remove(group);
	delete group;
}

list<ElfActor*> ActorsRepository::getElves()
{
	return _elves;
}

list<ZergActor*> ActorsRepository::getParasites()
{
	return _parasites;
}

list<BushActor*> ActorsRepository::getBushes()
{
	return _bushes;
}

list<HunterActor*> ActorsRepository::getHunters()
{
	return _hunters;
}

Actor* ActorsRepository::createBush()
{
	NYWorld* w = UniqWorld::get()->World();
	static const int worldsize = MAT_SIZE * NYChunk::CHUNK_SIZE;

	int x = rand() % worldsize;
	int y = rand() % worldsize;

	BushActor* bush = new BushActor(
		NYVert3Df(x, y, w->_MatriceHeightsTmp[x][y]),
		NYVert3Df(0, 0, 0),
		FORWARD
	);
	insert(bush);
	return bush;
}
Actor* ActorsRepository::createElf()
{
	NYWorld* w = UniqWorld::get()->World();
	static const int worldsize = MAT_SIZE * NYChunk::CHUNK_SIZE;

	int x = rand() % worldsize;
	int y = rand() % worldsize;

	ElfActor* elf = new ElfActor(
		NYVert3Df(x, y, w->_MatriceHeightsTmp[x][y]),
		NYVert3Df(0, 0, 0),
		FORWARD
	);
	Group* g = createGroup();
	elf->setGroup(g);
	insert(g);
	insert(elf);
	return elf;
}
void ActorsRepository::insert(Group* group)
{
	_groups.push_back(group);
}
Group* ActorsRepository::createGroup()
{
	return new Group();
}
Actor* ActorsRepository::createHunter()
{
	NYWorld* w = UniqWorld::get()->World();
	static const int worldsize = MAT_SIZE * NYChunk::CHUNK_SIZE;

	int x = rand() % worldsize;
	int y = rand() % worldsize;

	HunterActor* hunter = new HunterActor(
		NYVert3Df(x, y, w->_MatriceHeightsTmp[x][y]),
		NYVert3Df(0, 0, 0),
		FORWARD
		);
	insert(hunter);
	return hunter;
}

