#ifndef _BEHAVIOR_TREE_HPP_
#define _BEHAVIOR_TREE_HPP_

#include "Selector.hpp"
#include "Behavior.hpp"
#include "actors\Actor.hpp"

namespace DatNS
{
	class BehaviorTree
	{
	private:
		Selector* _selector;
	public:
		/**
		 * Set selector to list
		 * @param[in] Selector
		 */
		void setSelector(Selector* sel);
		/**
		 * @param[in] Actor
		 * @eturn const Behavior* Find current behavior
		 */
		const Behavior* currentBehavior(const Actor& actor) const;
	};
};

#endif
