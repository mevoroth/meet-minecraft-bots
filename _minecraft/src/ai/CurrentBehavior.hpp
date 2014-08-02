#ifndef _CURRENT_BEHAVIOR_HPP_
#define _CURRENT_BEHAVIOR_HPP_

namespace DatNS
{
	template <typename State>
	class CurrentBehavior
	{
	public:
		virtual void setBehavior(const State& state) = 0;
		virtual State getBehavior() const = 0;
	};
}

#endif
