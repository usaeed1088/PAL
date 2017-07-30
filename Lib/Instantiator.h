#pragma once

#include "API/Factory/Factory.h"
#include "Object/Factory/Factory.h"

namespace PAL
{
	class Instantiator
	{
	private:
		Instantiator();

	public:
		static API::FactoryPtr APIFactory();
		static Object::FactoryPtr ObjectFactory();
	};
}