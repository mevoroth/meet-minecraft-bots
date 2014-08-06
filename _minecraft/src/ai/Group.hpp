#ifndef _GROUP_HPP_
#define _GROUP_HPP_

namespace DatNS
{
	class Group : public Behavior
	{
	public:
		virtual ReturnCode update(Actor& actor) const;

		virtual void onFinished(Actor& actor) const {};
		virtual void onStarted(Actor& actor) const {};
		virtual void onDoing(Actor& actor) const {};
		virtual void onAbort(Actor& actor) const {};
		virtual void onInvalid(Actor& actor) const {};
	};
}

#endif
