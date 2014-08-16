#ifndef _EATER_HPP_
#define _EATER_HPP_

#include "actors\Actor.hpp"
#include "Eatable.hpp"

namespace DatNS
{
	class Eater
	{
	private:
		Eatable* eatable;
	public:
		void eat();
		void setEatable(Eatable* actor) { eatable = actor; };
	};
}

#endif
