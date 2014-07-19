#ifndef _AI_FACTORY_HPP_
#define _AI_FACTORY_HPP_

#include "BehaviorTree.hpp"

namespace DatNS
{
	class AIFactory
	{
	private:
		static AIFactory* _inst;
		BehaviorTree* _zergAI;
		~AIFactory();
		AIFactory();
	public:
		static AIFactory* get();
		const BehaviorTree* createZergAI();
	};
}

#endif
