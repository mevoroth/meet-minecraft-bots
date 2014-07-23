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
		enum { START_PARASITE = 10 };
		static ActorsRepository* get();
		void insert(Actor* actor);
		void insert(ZergActor* actor);

		Actor* createParasite();
		Actor* createParasite(const Actor& actor);
		void removeParasite(ZergActor* actor);

		list<ElfActor*> getElves();
	};
}

#endif
