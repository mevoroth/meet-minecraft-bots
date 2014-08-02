#ifndef _SEQUENCE_STORE_HPP_
#define _SEQUENCE_STORE_HPP_

namespace DatNS
{
	class SequenceStore
	{
	public:
		virtual void storeSequenceState(const std::string& key, int state) = 0;
		virtual int retrieveState(const std::string& key) = 0;
	};
}

#endif
