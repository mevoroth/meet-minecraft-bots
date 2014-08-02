#include "ZergActor.hpp"

#include <cmath>
#include "gl/glut.h"

#include "ActorsRepository.hpp"
#include "ai\AIFactory.hpp"

using namespace DatNS;

ZergActor::ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw)
	: Actor(pos, speed, fw)
	, _currentBehavior(0)
	, _sequenceState(0)
{
}

void ZergActor::multiply()
{
	ActorsRepository::get()->createParasite(*this);
}

void ZergActor::update(float elapsedTime)
{
	const BehaviorTree* bt = AIFactory::get()->createZergAI();
	bt->currentBehavior(*this);
}

void ZergActor::render()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1.f, 0.f, 0.f);

	glPushMatrix();
	//glMultMatrixf(m);
	glTranslatef(Position().X * 10 + 5, Position().Y * 10 + 5, Position().Z * 10 + 5);
	glutSolidCube(9);
	glPopMatrix();
}

void ZergActor::reset()
{

}

void ZergActor::storeSequenceState(const std::string& key, int state)
{
	_states[key] = state;
}
int ZergActor::retrieveState(const std::string& key)
{
	std::map<std::string, int>::const_iterator it = _states.find(key);
	if (it != _states.cend())
	{
		return it->second;
	}
	_states[key] = 0;
	return 0;
}

NYVert3Df ZergActor::getNewPosition() const
{
	NYVert3Df randVect = retrieve();
	return getPosition() + randVect * 0.001f;
}
