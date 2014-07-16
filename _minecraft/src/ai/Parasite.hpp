#ifndef _PARASITE_HPP_
#define _PARASITE_HPP_

#include "types.hpp"

namespace DatNS
{
	class Parasite
	{
	private:
		uint64_t _elapsed;
	public:
		Parasite();
		/**
		 * @return uint64_t Elapsed time
		 */
		uint64_t parasiting();
	};
};

#endif
