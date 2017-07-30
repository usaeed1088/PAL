#include "Instantiator.h"

namespace PAL
{
	Instantiator::Instantiator()
	{

	}

	API::FactoryPtr Instantiator::APIFactory()
	{
		return API::Factory::Instance();
	}

	Object::FactoryPtr Instantiator::ObjectFactory()
	{
		return Object::Factory::Instance();
	}
}