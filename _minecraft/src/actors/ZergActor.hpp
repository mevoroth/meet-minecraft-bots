#ifndef _ZERG_ACTOR_HPP_
#define _ZERG_ACTOR_HPP_

#include "Actor.hpp"

// ai
#include "ai\Multiplyable.hpp"
#include "ai\Parasite.hpp"
#include "ai\SequenceStore.hpp"
#include "ai\CurrentBehavior.hpp"
#include "ai\RandomDirectionStore.hpp"
#include "ai\NewPosition.hpp"

#include "gl/glew.h"

//#include <vector>
#include <map>

using namespace std;

namespace DatNS
{
	class ZergActor
		: public Actor,
		public Multiplyable,
		public Parasite,
		public SequenceStore,
		public CurrentBehavior<int>,
		public RandomDirectionStore,
		public NewPosition
	{
	private:
		int _sequenceState;
		int _currentBehavior;
		NYVert3Df _randomDir;
		std::map<std::string, int> _states;

	public:
		ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw);

		static void reset();

		void multiply();
		virtual void storeSequenceState(const std::string& key, int state);
		virtual int retrieveState(const std::string& key);
		virtual void setBehavior(const int& state) { _currentBehavior = state; };
		virtual int getBehavior() const { return _currentBehavior; };
		virtual void store(const NYVert3Df& dir) { _randomDir = dir; };
		virtual NYVert3Df retrieve() const { return _randomDir; };
		virtual NYVert3Df getNewPosition() const;

		void update(float elapsedTime);
		void render();
	};
};

#endif
