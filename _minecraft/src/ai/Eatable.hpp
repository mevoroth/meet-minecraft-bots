#ifndef _EATABLE_HPP_
#define _EATABLE_HPP_

namespace DatNS
{
	class Eatable
	{
	private:
		int consumable;
	public:
		Eatable(int consumable) { assert(consumable > 0); this->consumable = consumable; }
		void consume() { --consumable; if (!consumable) { destroy(); } };
		virtual void destroy() = 0;
	};
}

#endif
