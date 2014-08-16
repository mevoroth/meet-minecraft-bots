#ifndef _PARASITE_HPP_
#define _PARASITE_HPP_

#include <cstdint>

namespace DatNS
{
	class Parasite
	{
	private:
		float _elapsed;
	public:
		Parasite();
		/**
		 * @return float Elapsed time
		 */
		float parasiting();
	};
};

#endif
