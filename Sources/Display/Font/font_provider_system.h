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
**    Mark Page
*/

#pragma once

#include "API/Display/TargetProviders/font_provider.h"
#include "API/Display/Font/font_system.h"
#include "API/Display/Font/font_metrics.h"
#include "API/Display/Render/texture.h"
#include "API/Display/2D/texture_group.h"
#include <list>
#include <map>
#include "glyph_cache.h"

namespace clan
{

class FontEngine_Freetype;
class FontEngine_Win32;
class Colorf;
class TextureGroup;

class FontProvider_System : public FontProvider
{
/// \name Construction
/// \{
public:
	FontProvider_System();
	virtual ~FontProvider_System();

/// \}
/// \name Attributes
/// \{
public:
	/// \brief Returns information about the current font.
	FontMetrics get_font_metrics();

	/// \brief Get a glyph. Returns NULL if the glyph was not found
	Font_TextureGlyph *get_glyph(GraphicContext &gc, unsigned int glyph);

/// \}
/// \name Operations
/// \{
public:
	void insert_glyph(GraphicContext &gc, unsigned int glyph, Subtexture &sub_texture, const Point &offset, const Point &increment);
	void insert_glyph(GraphicContext &gc, const std::string &text);

	/// \brief Print text on gc.
	void draw_text(Canvas &canvas, float xpos, float ypos, const std::string &text, const Colorf &color);

	/// \brief Calculate size of text string.
	Size get_text_size(GraphicContext &gc, const std::string &text);

	/// \brief Set the font metrics for the bitmap font. This is done automatically if the font is loaded from the system font
	void set_font_metrics(const FontMetrics &metrics);

	void set_texture_group(TextureGroup &new_texture_group);

	int get_character_index(GraphicContext &gc, const std::string &text, const Point &point);

	/// \brief Load a system font (for use by insert_glyph to load text from a system font)
	void load_font( GraphicContext &context, const FontDescription &desc, const std::string &filename);

	/// \brief Free the system font when it is no longer required
	void free_font();

/// \}
/// \name Implementation
/// \{
private:

	FontEngine *font_engine;

	GlyphCache glyph_cache;
/// \}
};

}
