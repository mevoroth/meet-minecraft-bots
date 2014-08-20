#ifndef _GROUP_HPP_
#define _GROUP_HPP_

#include "engine/log/log_file.h"
#include <typeinfo.h>
#include <cassert>
#include <list>
#include "Settings.hpp"

using namespace std;

namespace DatNS
{
	class ElfActor;
	class Group
	{
	private:
		list<ElfActor*> elements;
	public:
		list<ElfActor*> getElements() { return elements; };
		void add(ElfActor* actor);
		void remove(ElfActor* actor);
		int size() const { return elements.size(); }
		NYVert3Df getPosition();
		bool full() const { return size() == GROUP_SIZE; }
	};
}

#endif
