#ifndef _ELF_ACTOR_HPP_
#define _ELF_ACTOR_HPP_

#include "Actor.hpp"
#include "Group.hpp"
#include "BushActor.hpp"

namespace DatNS
{
	class ElfActor
		: public Actor
	{
	public:
		enum ElfState
		{
			GROUP,
			LOOK_FOR_BUSH,
			STARE,
			EAT,
			MOVE,
			MULTIPLY,
			NONE
		};
	private:
		ElfState currentState;
		ElfState nextState;
		BushActor* bush;
		Group* group;
		int eaten;
		bool parasited;
		bool foundDestination;
		NYVert3Df destination;
		NYVert3Df currentPos;
		NYVert3Df next;
		float elapsedTime;
	public:
		ElfActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rotation);
		virtual void update(float elapsedTime);
		virtual void render();
		void setState(ElfState state) { currentState = state; }
		bool isParasited() const { return parasited; }
		void setParasited(bool parasited) { this->parasited = parasited; }
		void setGroup(Group* group) { this->group = group; this->group->add(this); }
		Group* getGroup() { return group; }
		BushActor* getTargetedBush() const { return bush; }
		void removeBush() { bush = 0; }

	};
}

#endif
