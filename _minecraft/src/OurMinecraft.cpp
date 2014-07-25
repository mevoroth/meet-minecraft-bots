#include "OurMinecraft.hpp"

#include "actors\ActorsRepository.hpp"

using namespace DatNS;

void DatNS::init()
{
	// Create Parasite
	for (int i = 0; i < ActorsRepository::START_PARASITES; ++i)
	{
		ActorsRepository::get()->createParasite();
	}

	for (int i = 0; i < ActorsRepository::START_ELVES; ++i)
	{
		ActorsRepository::get()->createElves();
	}

	for (int i = 0; i < ActorsRepository::START_BUSHES; ++i)
	{
		ActorsRepository::get()->createBushes();
	}

	for (int i = 0; i < ActorsRepository::START_ELVES; ++i)
	{
		ActorsRepository::get()->createElves();
	}
}

void DatNS::update()
{

}
