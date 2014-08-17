#ifndef _ACTORS_REPOSITORY_HPP_
#define _ACTORS_REPOSITORY_HPP_

#include <list>
#include "Actor.hpp"
#include "ZergActor.hpp"
#include "ElfActor.hpp"
#include "BushActor.hpp"
#include "HunterActor.hpp"

#include "GroupActor.hpp"

using namespace std;

namespace DatNS
{
	class ZergActor;
	class HunterActor;

	class ActorsRepository
	{
	private:
		static ActorsRepository* _inst;

		list<Group*> _groups;
		list<ElfActor*> _elves;
		list<ZergActor*> _parasites;
		list<BushActor*> _bushes;
		list<HunterActor*> _hunters;

		ActorsRepository();
	public:
		enum {
			START_PARASITES	= 10,
			START_BUSHES	= 10,
			START_ELVES		= 10,
			START_HUNTERS	= 10
		};
		static ActorsRepository* get();
		static void reset();

		//void insert(Actor* actor);
		void insert(ZergActor* actor);
		void insert(BushActor* actor);
		void insert(ElfActor* actor);
		void insert(HunterActor* actor);
		void insert(Group* group);

		Actor* createParasite();
		Actor* createParasite(const Actor& actor);
		Actor* createBush();
		Actor* createElf();
		Actor* createElf(Actor& actor);
		Actor* createHunter();
		Actor* createHunter(const Actor& actor);
		Group* createGroup();
		void removeParasite(ZergActor* actor);
		void removeBush(BushActor* actor);
		void remove(Group* group);

		list<ElfActor*> getElves();
		list<ZergActor*> getParasites();
		list<BushActor*> getBushes();
		list<HunterActor*> getHunters();
		list<Group*> getGroups() { return _groups; };
	};
}

#endif
