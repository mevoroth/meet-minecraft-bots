#ifndef _ACTORS_REPOSITORY_HPP_
#define _ACTORS_REPOSITORY_HPP_

#include <list>
#include "Actor.hpp"
#include "ParasiteActor.hpp"

using namespace std;

namespace DatNS
{
	class ActorsRepository
	{
	private:
		static ActorsRepository* _inst;

		list<ParasiteActor*> _parasites;

		ActorsRepository();
	public:
		static ActorsRepository* get();
		void insert(Actor* actor);
		void insert(ParasiteActor* actor);

		Actor* createParasite(ParasiteActor& actor);
		void removeParasite(ParasiteActor* actor);
	};
}

#endif
