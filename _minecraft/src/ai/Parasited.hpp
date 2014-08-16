#ifndef _PARASITED_HPP_
#define _PARASITED_HPP_

namespace DatNS
{
	class Parasited
	{
	private:
		bool parasited;
	public:
		Parasited() { parasited = false; }
		bool isParasited() { return parasited; };
		void setParasited(bool parasited) { this->parasited = parasited; }
	};
}

#endif
