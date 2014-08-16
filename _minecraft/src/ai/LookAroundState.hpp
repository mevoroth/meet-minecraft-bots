#ifndef _LOOK_AROUND_STATE_HPP_
#define _LOOK_AROUND_STATE_HPP_

namespace DatNS
{
	class LookAroundState
	{
	private:
		float elapsedTime;
	public:
		float getElapsedTime() const { return elapsedTime; };
		void setElapsedTime(float elapsedTime) { this->elapsedTime = elapsedTime; };
		virtual void updateLookAround() = 0;
	};
}

#endif
