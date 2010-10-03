/* libLDR: Portable and easy-to-use LDraw format abstraction & I/O reference library *
 * To obtain more information about LDraw, visit http://www.ldraw.org.               *
 * Distributed in terms of the GNU Lesser General Public License v3                  *
 *                                                                                   *
 * Author: (c)2006-2008 Park "segfault" J. K. <mastermind_at_planetmono_dot_org>     */

#include <iostream>
#include <sstream>
#include <map>

#include "color.h"

namespace ldraw {

typedef std::map<int, const color_entity *> color_map_type;

const color_map_type color::color_map = color_map_type();
bool color::m_initialized = false;

// Predefined color table
const color_entity color::color_chart[] = {
	{material_normal,      { 33,  33,  33, 255},   0,  -1, "Black"},
	{material_normal,      {  0,  51, 178, 255},   1,  -1, "Blue"},
	{material_normal,      {107, 238, 144, 255},  10, 418, "Bright Green"},
	{material_normal,      { 92,  32,   0, 255},   6,  -1, "Brown"},
	{material_metallic,    {225, 110,  19, 255}, 334,  -1, "Chrome Gold"},
	{material_metallic,    {224, 224, 224, 255}, 383,  -1, "Chrome Silver"},
	{material_transparent, {255, 255, 255, 230},  47,  -1, "Clear (Trans White)"},
	{material_normal,      {  0,  29, 104, 255}, 272,  -1, "Dark Blue"},
	{material_normal,      { 99,  95,  82, 255},   8,  -1, "Dark Gray"},
	{material_normal,      { 39,  70,  44, 255}, 288,  -1, "Dark Green"},
	{material_normal,      {179,  62,   0, 255}, 484,  -1, "Dark Orange"},
	{material_normal,      {223, 102, 149, 255},   5,  -1, "Dark Pink"},
	{material_normal,      {120,   0,  28, 255}, 320,  -1, "Dark Red"},
	{material_normal,      { 99,  95,  97, 255},  72,  -1, "Dark Stone Gray"},
	{material_normal,      {197, 151,  80, 255},  28,  -1, "Dark Tan"},
	{material_normal,      {209, 131,   4, 255}, 366,  -1, "Earth Orange"},
	{material_metallic,    {208, 208, 208, 255}, 494,  -1, "Electric Contact"},
	{material_normal,      {193, 194, 193, 255},   7,  -1, "Gray"},
	{material_normal,      {  0, 140,  20, 255},   2,  -1, "Green"},
	{material_normal,      {107, 171, 220, 255},   9,  -1, "Light Blue"},
	{material_normal,      {230, 227, 218, 255}, 503,  -1, "Light Gray"},
	{material_normal,      {186, 255, 206, 255},  17, 431, "Light Green"},
	{material_normal,      {254, 159,   6, 255}, 462,  -1, "Light Orange"},
	{material_normal,      {255, 133, 122, 255},  12, 463, "Light Red"},
	{material_normal,      {215, 196, 230, 255},  20,  -1, "Light Violet"},
	{material_normal,      {253, 232, 150, 255},  18, 495, "Light Yellow"},
	{material_normal,      {215, 240,   0, 255},  27,  -1, "Lime"},
	{material_normal,      {216,  27, 109, 255},  26,  -1, "Magenta"},
	{material_normal,      {249,  96,   0, 255},  25,  -1, "Orange"},
	{material_normal,      {147, 130, 103, 255}, 134,  -1, "Pearl Copper"},
	{material_normal,      {215, 169,  75, 255}, 142,  -1, "Pearl Gold"},
	{material_normal,      {171, 173, 172, 255}, 135,  -1, "Pearl Gray"},
	{material_normal,      {106, 122, 150, 255}, 137,  -1, "Pearl Sand Blue"},
	{material_phosphorus,  {224, 255, 176, 255},  21,  -1, "Phosphor White (Glow in the Dark)"},
	{material_normal,      {249, 164, 198, 255},  13,  -1, "Pink"},
	{material_normal,      {196,   0,  38, 255},   4,  -1, "Red"},
	{material_normal,      {105,  64,  39, 255},  70,  -1, "Reddish Brown"},
	{material_rubber,      { 33,  33,  33, 255}, 256,  -1, "Rubber Black"},
	{material_rubber,      {  0,  51, 178, 255}, 273,  -1, "Rubber Blue"},
	{material_rubber,      {193, 194, 193, 255}, 375,  -1, "Rubber Gray"},
	{material_rubber,      {196,   0,  38, 255}, 324,  -1, "Rubber Red"},
	{material_rubber,      {255, 255, 255, 255}, 511,  -1, "Rubber White"},
	{material_normal,      {106, 122, 150, 255}, 379,  -1, "Sand Blue"},
	{material_normal,      {160, 188, 172, 255}, 378,  -1, "Sand Green"},
	{material_normal,      {191, 135, 130, 255}, 335,  -1, "Sand Red"},
	{material_normal,      {132,  94, 132, 255}, 373,  -1, "Sand Violet"},
	{material_normal,      {163, 162, 164, 255},  71,  -1, "Stone Gray (New Gray)"},
	{material_normal,      {232, 207, 161, 255},  19, 382, "Tan"},
	{material_normal,      {  0, 153, 159, 255},   3,  -1, "Teal"},
	{material_transparent, {  0,  32, 160, 230},  33,  -1, "Trans Blue (Trans Dark Blue)"},
	{material_transparent, {192, 255,   0, 230},  42,  -1, "Trans Flu Lime (Trans Neon Green, Trans Yellow-Green)"},
	{material_transparent, {249,  96,   0, 204},  57,  -1, "Trans Flu Orange"},
	{material_transparent, { 99,  95,  82, 230},  40,  32, "Trans Gray (Smoke)"},
	{material_transparent, {  6, 100,  50, 230},  34,  -1, "Trans Green"},
	{material_transparent, {174, 239, 236, 242},  41,  -1, "Trans Light Cyan (Trans Light Blue)"},
	{material_transparent, {223, 102, 149, 242},  45,  -1, "Trans Pink"},
	{material_transparent, {196,   0,  38, 230},  36,  -1, "Trans Red"},
	{material_transparent, {100,   0,  97, 242},  37,  -1, "Trans Violet"},
	{material_transparent, {202, 176,   0, 230},  46,  -1, "Trans Yellow"},
	{material_normal,      { 51, 166, 167, 255},  11,  -1, "Turquiose (Cyan)"},
	{material_normal,      {129,   0, 123, 255},  22,  -1, "Violet (Purple)"},
	{material_normal,      { 71,  50, 176, 255},  23,  -1, "Violet Blue"},
	{material_normal,      {255, 255, 255, 255},  15,  -1, "White"},
	{material_normal,      {255, 220,   0, 255},  14,  -1, "Yellow"},
	{material_normal,      { 33,  33,  33, 255},  -1,  -1, "Unknown"}, // Invalid color. same to 0
	{material_transparent, {193, 202, 222, 230},  39,  -1, "Light Bluish Violet"}
};

void color::init()
{
	color_map_type &m = *const_cast<color_map_type *>(&color_map);
	
	int count = sizeof(color_chart) / sizeof(color_entity);
	for (int i = 0; i < count; ++i) {
		if (color_chart[i].id1 != -1)
			m[color_chart[i].id1] = &color_chart[i];
		if (color_chart[i].id2 != -1)
			m[color_chart[i].id2] = &color_chart[i];
	}
	
	m_initialized = true;
}

color::~color()
{
	if (m_custom_color)
		delete m_entity;
}

// Map color-id to appropriate color value
void color::link()
{
	if (!m_initialized)
		throw exception(__func__, exception::user_error, "Color table is not initialized! run color::init() first.");
	
	m_custom_color = false;
	m_valid = true;

	const color_map_type::const_iterator it = color_map.find(m_id);
	if (it != color_map.end()) {
		m_entity = (*it).second;
		return;
	}

	if (m_id >= 256 && m_id <= 512) {
		// Dithered color (256 <= n <= 512)
		m_custom_color = true;
		const color_entity *c1 = color((m_id - 256) / 16).get_entity();
		const color_entity *c2 = color((m_id - 256) % 16).get_entity();
		
		color_entity *nc = new color_entity;
		nc->material = material_normal;
		nc->id1 = m_id;
		nc->id2 = -1;
		nc->name = "Dithered color";
		nc->rgba[0] = (unsigned char)(((int)c1->rgba[0] + (int)c2->rgba[0])/2);
		nc->rgba[1] = (unsigned char)(((int)c1->rgba[1] + (int)c2->rgba[1])/2);
		nc->rgba[2] = (unsigned char)(((int)c1->rgba[2] + (int)c2->rgba[2])/2);
		nc->rgba[3] = (unsigned char)(((int)c1->rgba[3] + (int)c2->rgba[3])/2);
		
		m_entity = nc;

		return;
	}
	
	// No color
	m_valid = false;
	m_entity = &color_chart[64];

	/*std::ostringstream s;
	  s << "Invalid color value '" << m_id << "'.";
	  throw exception(__func__, exception::warning, s.str());*/
}

// Get complement value of given color id
const color_entity* color::get_complement(int id)
{
	if (id < 0 || id > 15)
		return &color_chart[64];
	
	switch (id) {
		case 0:
		case 7:
		case 14:
		case 15:
			return &color_chart[8];
		case 1:
			return &color_chart[19];
		case 2:
			return &color_chart[2];
		case 3:
			return &color_chart[59];
		case 4:
			return &color_chart[23];
		case 5:
			return &color_chart[34];
		case 6:
		case 8:
			return &color_chart[0];
		case 9:
			return &color_chart[1];
		case 10:
		case 418:
			return &color_chart[18];
		case 11:
			return &color_chart[48];
		case 12:
		case 463:
			return &color_chart[35];
		case 13:
			return &color_chart[11];
	}
	
	return &color_chart[64];
}

}