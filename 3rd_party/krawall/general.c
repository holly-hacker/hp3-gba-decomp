/*
 * Krawall, XM/S3M Modplayer Library
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License in COPYING for more details.
 *
 * Modified to match the code in Harry Potter and the Prisoner of Azkaban
 * (Game Boy Advance); changes are marked HP3-GBA.
 */

#include "directsound.h"
#include "mixer.h"
#include "player.h"
#include "general.h"

void kragInit( int stereo )
{
	kramSetMasterVol( 128 );
	dsInit( stereo );
	// HP3-GBA: no kramResetChannels( 1 )
	kradActivate();
	krapInit();
}

// HP3-GBA: no kragReset(), and the version string is a CVS keyword
const static char __id[] = "$Id: Krawall $Date: 2003/09/01 06:51:01 $";

