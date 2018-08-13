/*
www.sourceforge.net/projects/tinyxml
Original code (2.0 and earlier )copyright (c) 2000-2006 Lee Thomason (www.grinninglizard.com)

This software is provided _UI('as-is'), without any express or implied 
warranty. In no event will the authors be held liable for any 
damages arising from the use of this software.

Permission is granted to anyone to use this software for any 
purpose, including commercial applications, and to alter it and 
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "tinyxml.h"

// The goal of the seperate error file is to make the first
// step towards localization. tinyxml (currently) only supports
// english error messages, but the could now be translated.
//
// It also cleans up the code a bit.
//

const TIXML_CHAR* TiXmlBase::errorString[ TIXML_ERROR_STRING_COUNT ] =
{
	_TIXML_L("No error"),
	_TIXML_L("Error"),
	_TIXML_L("Failed to open file"),
	_TIXML_L("Memory allocation failed."),
	_TIXML_L("Error parsing Element."),
	_TIXML_L("Failed to read Element name"),
	_TIXML_L("Error reading Element value."),
	_TIXML_L("Error reading Attributes."),
	_TIXML_L("Error: empty tag."),
	_TIXML_L("Error reading end tag."),
	_TIXML_L("Error parsing Unknown."),
	_TIXML_L("Error parsing Comment."),
	_TIXML_L("Error parsing Declaration."),
	_TIXML_L("Error document empty."),
	_TIXML_L("Error null (0) or unexpected EOF found in input stream."),
	_TIXML_L("Error parsing CDATA."),
	_TIXML_L("Error when TiXmlDocument added to document, because TiXmlDocument can only be at the root."),
};
