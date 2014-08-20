#ifndef _A_STAR_HPP_
#define _A_STAR_HPP_

#include "engine\utils\types_3d.h"
#include <map>
#include <list>
#include <algorithm>
using namespace std;

namespace DatNS
{
	struct CompClosest
	{
		bool operator()(const pair<NYVert3Df, float>& a, const pair<NYVert3Df, float>& b);
	};
	class AStar
	{
	private:
		NYVert3Df _start;
		NYVert3Df _end;
		NYVert3Df _current;
		map<NYVert3Df, NYVert3Df> _parents;
		map<NYVert3Df, float> _costs;
		map<NYVert3Df, float> _costsHeuristic;
		list<NYVert3Df> _seens;
		bool _canFly;

		void _setCost(const NYVert3Df& neighbor, float cost);
		NYVert3Df _findClosest() {
			return min_element(_costsHeuristic.begin(), _costsHeuristic.end(), CompClosest())->first;
		}
		NYVert3Df _reconstruct(const NYVert3Df& to)
		{
			if (_parents.find(to) != _parents.end() && _parents[to] != _start)
			{
				return _reconstruct(_parents[to]);
			}
			return to;
		}
		list<NYVert3Df> _neighbors(const NYVert3Df& o);
		float _distance(const NYVert3Df& a, const NYVert3Df& b) { return (NYVert3Df(a) - b).getMagnitude(); };
		float _costBetween(const NYVert3Df& a, const NYVert3Df& b) { return (NYVert3Df(a) - b).getMagnitude(); };
		float _currentCost(const NYVert3Df& neighbor) {
			if (_costs.find(neighbor) == _costs.end())
			{
				return INFINITY;
			}
			return _costs[neighbor];
		}
		void _setParents(const NYVert3Df& a, const NYVert3Df& b);
	public:
		AStar(const NYVert3Df& begin, const NYVert3Df& end);
		NYVert3Df find();
		void canFly(bool canFly = false);
	};
}

#endif
