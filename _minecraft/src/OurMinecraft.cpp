#include "OurMinecraft.hpp"

#include "actors\ActorsRepository.hpp"

using namespace DatNS;

void DatNS::init()
{
	// Create Parasite
	for (int i = 0; i < ActorsRepository::START_PARASITE; ++i)
	{
		ActorsRepository::get()->createParasite();
	}
}

void DatNS::update()
{

}
