#ifndef __VideoSystem__
#define __VideoSystem__

#pragma once
#include "Core.h"

namespace VideoSystem
{
	irr::video::E_DRIVER_TYPE GetDriver();
	irr::IrrlichtDevice* GetDevice();
};

#endif