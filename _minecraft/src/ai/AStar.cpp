#include "AStar.hpp"

#include <algorithm>
#include "utils/types_extended.hpp"

using namespace DatNS;

extern bool operator< (const NYVert3Df& a, const NYVert3Df& b);

AStar::AStar(const NYVert3Df& begin, const NYVert3Df& end)
{
	_start = begin;
	_end = end;
	_setCost(begin, 0);
}

NYVert3Df AStar::find()
{
	UniqWorld::get()->Timer()->getElapsedSeconds();
	float elapsed = 0.f;
	while (_costs.size() != 0)
	{
		_current = _findClosest();
		if (_current == _end || elapsed > 0.5f)
		{
			return _reconstruct(_current);
		}

		_seens.push_back(_current);
		_costs.erase(_current);
		_costsHeuristic.erase(_current);

		list<NYVert3Df> neighbors = _neighbors(_current);

		for (list<NYVert3Df>::iterator it = neighbors.begin();
			it != neighbors.end();
			++it)
		{
			if (std::find(_seens.begin(), _seens.end(), *it) == _seens.end())
			{
				float cost = _costBetween(_current, *it);
				if (cost < _currentCost(*it))
				{
					_setParents(*it, _current);
					_setCost(*it, cost);
				}
			}
		}

		elapsed += UniqWorld::get()->Timer()->getElapsedSeconds();
	}
}

void AStar::_setCost(const NYVert3Df& neighbor, float cost)
{
	bool notFound = _costs.find(neighbor) == _costs.end();

	if (notFound
		|| !notFound && _costs[neighbor] < cost)
	{
		_costs[neighbor] = cost;
		_costsHeuristic[neighbor] = cost + _distance(neighbor, _end);
	}

}

void AStar::_setParents(const NYVert3Df& a, const NYVert3Df& b)
{
	if (_costs.find(a) == _costs.end())
	{
		_parents.insert(pair<NYVert3Df, NYVert3Df>(a, b));
		return;
	}
	_parents[a] = b;
}

list<NYVert3Df> AStar::_neighbors(const NYVert3Df& o)
{
	list<NYVert3Df> neighbors;
	if (!UniqWorld::get()->World()->getCube(o.X - 1, o.Y, o.Z)->isSolid())
	{
		neighbors.push_back(NYVert3Df(o.X - 1, o.Y, o.Z));
	}
	if (!UniqWorld::get()->World()->getCube(o.X + 1, o.Y, o.Z)->isSolid())
	{
		neighbors.push_back(NYVert3Df(o.X + 1, o.Y, o.Z));
	}
	if (!UniqWorld::get()->World()->getCube(o.X, o.Y - 1, o.Z)->isSolid())
	{
		neighbors.push_back(NYVert3Df(o.X, o.Y - 1, o.Z));
	}
	if (!UniqWorld::get()->World()->getCube(o.X, o.Y + 1, o.Z)->isSolid())
	{
		neighbors.push_back(NYVert3Df(o.X, o.Y + 1, o.Z));
	}
	if (!UniqWorld::get()->World()->getCube(o.X, o.Y, o.Z - 1)->isSolid())
	{
		neighbors.push_back(NYVert3Df(o.X, o.Y, o.Z - 1));
	}
	if (!UniqWorld::get()->World()->getCube(o.X, o.Y, o.Z + 1)->isSolid())
	{
		neighbors.push_back(NYVert3Df(o.X, o.Y, o.Z + 1));
	}
	return neighbors;
}

bool CompClosest::operator()(const pair<NYVert3Df, float>& a, const pair<NYVert3Df, float>& b)
{
	return a.second < b.second;
}
