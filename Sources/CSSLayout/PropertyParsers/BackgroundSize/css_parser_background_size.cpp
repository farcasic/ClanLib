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

#include "CSSLayout/precomp.h"
#include "css_parser_background_size.h"
#include "API/CSSLayout/PropertyValues/css_value_background_size.h"

namespace clan
{

std::vector<std::string> CSSParserBackgroundSize::get_names()
{
	std::vector<std::string> names;
	names.push_back("background-size");
	return names;
}

void CSSParserBackgroundSize::parse(const std::string &name, const std::vector<CSSToken> &tokens, std::vector<std::unique_ptr<CSSPropertyValue> > &inout_values)
{
	std::unique_ptr<CSSValueBackgroundSize> background_size(new CSSValueBackgroundSize());

	size_t pos = 0;
	CSSToken token = next_token(pos, tokens);

	if (token.type == CSSToken::type_ident && pos == tokens.size() && equals(token.value, "inherit"))
	{
		background_size->type = CSSValueBackgroundSize::type_inherit;
	}
	else
	{
		background_size->type = CSSValueBackgroundSize::type_value;
		background_size->values.clear();
		while (true)
		{
			CSSValueBackgroundSize::Size size;

			bool single_value = false;
			if (token.type == CSSToken::type_ident)
			{
				if (equals(token.value, "contain"))
				{
					size.type = CSSValueBackgroundSize::size_contain;
					single_value = true;
				}
				else if (equals(token.value, "cover"))
				{
					size.type = CSSValueBackgroundSize::size_cover;
					single_value = true;
				}
				else if (equals(token.value, "auto"))
				{
					size.type = CSSValueBackgroundSize::size_values;
					size.value_x = CSSValueBackgroundSize::value_type_auto;
				}
				else
				{
					return;
				}
			}
			else if (is_length(token))
			{
				CSSLength length;
				if (parse_length(token, length))
				{
					size.value_x = CSSValueBackgroundSize::value_type_length;
					size.length_x = length;
				}
				else
				{
					return;
				}
			}
			else if (token.type == CSSToken::type_percentage)
			{
				size.value_x = CSSValueBackgroundSize::value_type_percentage;
				size.percentage_x = StringHelp::text_to_float(token.value);
			}
			else
			{
				return;
			}

			if (pos == tokens.size())
			{
				background_size->values.push_back(size);
				break;
			}

			token = next_token(pos, tokens);
			if (token.type != CSSToken::type_delim || token.value != ",")
			{
				if (single_value)
				{
					return;
				}
				else if (token.type == CSSToken::type_ident && equals(token.value, "auto"))
				{
					size.value_y = CSSValueBackgroundSize::value_type_auto;
				}
				else if (is_length(token))
				{
					CSSLength length;
					if (parse_length(token, length))
					{
						size.value_y = CSSValueBackgroundSize::value_type_length;
						size.length_y = length;
					}
					else
					{
						return;
					}
				}
				else if (token.type == CSSToken::type_percentage)
				{
					size.value_y = CSSValueBackgroundSize::value_type_percentage;
					size.percentage_y = StringHelp::text_to_float(token.value);
				}
				else
				{
					return;
				}

				if (pos == tokens.size())
				{
					background_size->values.push_back(size);
					break;
				}

				token = next_token(pos, tokens);
			}

			background_size->values.push_back(size);

			if (token.type != CSSToken::type_delim || token.value != ",")
				return;

			token = next_token(pos, tokens);
		}
	}

	inout_values.push_back(std::move(background_size));
}

}
