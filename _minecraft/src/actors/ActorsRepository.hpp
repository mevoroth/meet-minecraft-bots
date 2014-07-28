#ifndef _ACTORS_REPOSITORY_HPP_
#define _ACTORS_REPOSITORY_HPP_

#include <list>
#include "Actor.hpp"
#include "ZergActor.hpp"
#include "ElfActor.hpp"

using namespace std;

namespace DatNS
{
	class ActorsRepository
	{
	private:
		static ActorsRepository* _inst;

		list<ZergActor*> _parasites;

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

		void insert(Actor* actor);
		void insert(ZergActor* actor);

		Actor* createParasite();
		Actor* createBush();
		Actor* createElf();
		Actor* createHunter();
		Actor* createParasite(const Actor& actor);
		void removeParasite(ZergActor* actor);

		list<ElfActor*> getElves();
		list<ZergActor*> getParasites();
	};
}

#endif
