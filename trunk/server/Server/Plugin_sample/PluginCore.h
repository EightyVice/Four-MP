/// \file
/// \brief Header file that describes the PluginCore class.
/// \details See class description.

#pragma once

#include "..\IPluginHandlerInterface.h"

/// \brief A plugin core. Implements all interface functions.
/// \details Plugin core contains implementation of all interface functions that are
/// required for the correct work. It is separated from the plugin itself so the user can
/// have all their code in their class and system utilities in this so they don't collide.
/// Do NOT edit this class.

class PluginCore :
	public IPluginInterface
{
public:
	/// \brief Constructor.
	PluginCore(void);

	/// \brief Destructor.
	~PluginCore(void);

	/// \brief Makes the plugin recieve the pointer to the plugin handler for future calls.
	/// \return True on success, false otherwise.
	virtual bool AttachToServer(void);

	/// \brief Called on plugin load.
	/// \return No return.
	virtual void OnPluginLoad(void);

	/// \brief Called on plugin unload.
	/// \return No return.
	virtual void OnPluginUnload(void);

	/// \brief Returns the name of the plugin.
	/// \return Name of the plugin.
	virtual wchar_t *GetName(void);

	/// \brief Returns the version of the plugin.
	/// \return Version of the plugin.
	virtual wchar_t *GetVersion(void);

	/// \brief Return the author of the plugin.
	/// \return Author of the plugin.
	virtual wchar_t *GetAuthor(void);
protected:
	IPluginHandlerInterface *server; ///< Holds the pointer to the host.
};
