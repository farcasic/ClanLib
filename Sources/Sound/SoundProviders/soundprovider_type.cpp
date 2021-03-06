/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#include "Sound/precomp.h"

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include "API/Sound/SoundProviders/soundprovider_type.h"
#include "API/Sound/SoundProviders/soundprovider_factory.h"

namespace clan
{

/////////////////////////////////////////////////////////////////////////////
// SoundProviderType construction:

SoundProviderType::SoundProviderType(const std::string &type)
{
	SoundProviderFactory::types[type] = this;
}

SoundProviderType::~SoundProviderType()
{
	std::map<std::string, SoundProviderType *>::iterator it;
	
	for (it = SoundProviderFactory::types.begin(); it != SoundProviderFactory::types.end(); it++)
	{
		if (it->second == this)
		{
			SoundProviderFactory::types.erase(it);
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// SoundProviderType operations:


/////////////////////////////////////////////////////////////////////////////
// SoundProviderType implementation:

}
