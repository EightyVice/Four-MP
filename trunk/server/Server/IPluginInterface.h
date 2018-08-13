/// \file
/// \brief Header file that describes the IPluginInterface class.
/// \details See class description.
/// \author FaTony

#pragma once

/// \brief A plugin interface.
/// \details It declares all plugin functions that host can directly call. Each plugin
/// must implement all of them.
/// \author FaTony

class IPluginInterface
{
public:
	/// \brief Makes the plugin recieve the pointer to the plugin handler for future calls.
	/// \return True on success, false otherwise.
	virtual bool AttachToServer(void) = 0;

	/// \brief Called on plugin load.
	/// \return No return.
	virtual void OnPluginLoad(void) = 0;

	/// \brief Called on plugin unload.
	/// \return No return.
	virtual void OnPluginUnload(void) = 0;

	/// \brief Returns the name of the plugin.
	/// \return Name of the plugin.
	virtual wchar_t *GetName(void) = 0;

	/// \brief Returns the version of the plugin.
	/// \return Version of the plugin.
	virtual wchar_t *GetVersion(void) = 0;

	/// \brief Return the author of the plugin.
	/// \return Author of the plugin.
	virtual wchar_t *GetAuthor(void) = 0;
};
