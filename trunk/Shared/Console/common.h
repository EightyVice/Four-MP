/// \file
/// \brief Header file that describes common functions shared by many of the console classes.
/// \details See individual description.
/// \author FaTony

#pragma once

#include <malloc.h>

/// \brief Wrapper for realloc.
/// \tparam BUFFERTYPE Type of the buffer.
/// \param[in,out] buffer Buffer to resize.
/// \param[in] size Size to which resize.
/// \return True on success, false otherwise.
template <typename BUFFERTYPE>
bool ResizeBuffer(BUFFERTYPE &buffer, const size_t size)
{
	BUFFERTYPE tempbuffer = (BUFFERTYPE)realloc(buffer, size * sizeof(*tempbuffer));
	if ((tempbuffer == NULL) && (size != 0))
	{
		return false;
	}
	buffer = tempbuffer;
	return true;
}