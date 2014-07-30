#ifndef _SEQUENCE_STORE_HPP_
#define _SEQUENCE_STORE_HPP_

namespace DatNS
{
	class SequenceStore
	{
	public:
		virtual void storeSequenceState(int state) = 0;
		virtual int retrieveState() const = 0;
	};
}

#endif
