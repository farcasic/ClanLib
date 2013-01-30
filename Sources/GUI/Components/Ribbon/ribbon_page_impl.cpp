/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
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
**    Harry Storbacka
**    Mark Page
*/

#include "GUI/precomp.h"
#include "API/GUI/Components/ribbon_page.h"
#include "API/GUI/Components/ribbon_section.h"
#include "API/GUI/Components/ribbon.h"
#include "ribbon_page_impl.h"
#include "ribbon_section_impl.h"

namespace clan
{

//////////////////////////////////////////////////////////////////////////
// Construction

RibbonPage_Impl::RibbonPage_Impl(const std::string &text) : text(text), show_tab(true)
{

}

//////////////////////////////////////////////////////////////////////////
// Attributes


//////////////////////////////////////////////////////////////////////////
// Operations

void RibbonPage_Impl::add_section(RibbonSection *section)
{
	sections.push_back(section);
	on_resized();
}

//////////////////////////////////////////////////////////////////////////
// Implementation

void RibbonPage_Impl::on_resized()
{
	Rect page_box = component->get_size();
	int section_x = 5;
	for (size_t i = 0; i < sections.size(); i++)
	{
		Rect section_box(section_x, 5, section_x + sections[i]->impl->size, page_box.bottom);
		sections[i]->set_geometry(section_box);
		section_x = section_box.right + 5;
	}
}

}