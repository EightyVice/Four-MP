/// \file
/// \brief Header file that describes the HandleManager class.
/// \details See class description.
/// \author FaTony

#pragma once

#define INVALID_HANDLE -1 ///< Used to indicate an error. Equivalent of NULL pointer.

/// \brief A handle manager. Handles are indirect pointers.
/// \details Since scripting languages can't directly work with pointers and they may
/// change (during realloc for example), there is a need in the system that will keep
/// strong references to pointers and provide an easy way to interact with any other
/// language. Handle system is designed for the exactly this purpose. It keeps track of
/// pointers, their type and owners. Pointers are stored as void * and since it is unknown
/// what data is under that pointer, there is a type stored as unsigned short along with
/// it. There are several built-in types, CoreHandleTypesManager is designed to work with
/// them. Plugins can register new types. Since handles are accessed by their index
/// (integer value) malicious addons could theoretically access them to change their
/// value. Therefore, each handle keeps an array of it's owners - application modules that
/// created or legally gained access to it. There are 3 types of owners: the core,
/// filterscripts and plugins. The second main function of the handle manager is garbage
/// collection. Plugin and filterscript developers don't need to care about unloading
/// all their created handles (but it will improve unloading if they'll do so). Handle
/// manager automatically deletes the owner on unloading and if owner count has become
/// zero, destroys the handle.
/// \author FaTony

class HandleManager
{
public:
	/// \brief Constructor. Should be called after VirtualMachineManager and PluginManager.
	HandleManager(void);

	/// \brief Destructor.
	~HandleManager(void);

	/// \brief Releases all handle types reserved by a plugin.
	/// \param[in] pluginindex Index of the plugin.
	/// \return No return.
	void ReleaseAllHandleTypes(const unsigned char pluginindex);

	/// \brief Reserves an empty handle type and retieves it to a plugin.
	/// \param[in] pluginindex Index of the plugin.
	/// \param[out] typeindex Index of the handle type.
	/// \return True on success, false otherwise.
	bool RequestNewHandleType(const unsigned char pluginindex, unsigned short &typeindex);

	/// \brief Releases handle type that was reserved by a plugin.
	/// \param[in] pluginindex Index of the plugin.
	/// \param[in] typeindex Index of the handle type.
	/// \return True on success, false otherwise.
	bool ReleaseHandleType(const unsigned char pluginindex, const unsigned short typeindex);

	/// \brief Closes all handles that was created or reserved by plugin or filterscript.
	/// \param[in] owner Owner index.
	/// \return No return.
	void CloseAllHandles(const short owner);

	/// \brief Adds new handle to the handle buffer and returns it's index.
	/// \param[in] owner Owner of the handle.
	/// \param[in] type Type of the handle.
	/// \param[in] ptr Pointer to the data the handle will represent.
	/// \return Handle index on success, INVALID_HANDLE otherwise.
	int AddNewHandle(const short owner, const unsigned short type, void *ptr);

	/// \brief Retrieves handle type of the given handle index.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Index of the handle.
	/// \param[out] type Type of the handle.
	/// \return True on success, false otherwise.
	bool GetHandleType(const short owner, const int handle, unsigned short &type);

	/// \brief Returns the pointer to the data which given handle points to.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Index of the handle.
	/// \return Void pointer on success, NULL otherwise.
	void *GetHandlePointer(const short owner, const int handle);

	/// \brief Sets the pointer to the data which given handle points to.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Index of the handle.
	/// \param[in] ptr Pointer to which set the handle.
	/// \return True on success, false otherwise.
	bool SetHandlePointer(const short owner, const int handle, void *ptr);

	/// \brief Closes the handle which was created or reserved by a plugin or filterscript.
	/// \param[in] owner Owner that requests access to the handle.
	/// \param[in] handle Index of the handle.
	/// \return True on success, false otherwise.
	bool CloseHandle(const short owner, const int handle);
	friend class CoreHandleTypesManager; ///< See CoreHandleTypesManager.h.
private:
	/// \brief Describes the type of the handle.
	struct HandleType
	{
		unsigned char owner; ///< Since only plugins can reserve handle types, this is equal to the plugin index or 255 for the core.
		int handlecount; ///< Number of handles with this type.
	};
	unsigned short maxtypebuffersize; ///< Holds the maximum size of the handle \b *types* buffer.
	unsigned short typebuffersize; ///< Holds the current size of the handle \b *types* buffer.
	HandleType **typebuffer; ///< Holds all handle types.
	short pluginowneroffset; ///< Holds the offset of the plugins in the handle owner index.

	/// \brief Describes a handle.
	struct Handle
	{
		short numowners; ///< Holds the number of owners of a handle.
		short *owner; ///< Holds all handle owners. 0 - core, 1 - game mode, 2..pluginowneroffset - 1 - filterscripts, pluginowneroffset..maxcountbuffersize - 1 - plugins
		unsigned short type; ///< Holds the type of a handle.
		void *ptr; //Holds a pointer to the data this handle points to.
	};
	int maxhandlebuffersize; ///< Holds the maximum size of the handle buffer.
	int handlebuffersize; ///< Holds the current size of the handle buffer.
	Handle **handlebuffer; ///< Holds all handles.
	short maxhandlesperowner; ///< Holds the maximum number of handles each owner can have.
	short maxcountbuffersize; ///< Holds the maximum size of handle \b *count* buffer.
	short countbuffersize; ///< Holds the current size of handle \b *count* buffer.
	short **countbuffer; ///< Holds the number of handles each owner has reserved.

	/// \brief Retrieves a free slot in the handle \b *types* buffer.
	/// \param[out] type Index of the handle type.
	/// \return True on success, false otherwise.
	bool GetHandleTypeFreeSlot(unsigned short &type);

	/// \brief Returns the free slot in the handle buffer.
	/// \return Handle index on success, INVALID_HANDLE otherwise.
	int GetHandleFreeSlot(void);

	/// \brief Returns the handle index by the given pointer.
	/// \param[in] ptr Pointer to search.
	/// \return Handle index on success, INVALID_HANDLE otherwise.
	int FindHandle(const void *ptr);

	/// \brief Checks if the given handle is owned by the given owner.
	/// \param[in] handle Index of the handle.
	/// \param[in] owner Index of the owner.
	/// \return True if the handle is owned, false otherwise.
	bool IsHandleOwned(const int handle, const short owner);

	/// \brief Adds the new owner to the given handle.
	/// \param[in] handle Index of the handle.
	/// \param[in] owner Index of the owner.
	/// \return True on success, false otherwise.
	bool AddHandleOwner(const int handle, const short owner);

	/// \brief Deletes the given owner from the given handle.
	/// \param[in] handle Index of the handle.
	/// \param[in] owner Index of the owner.
	/// \return True on success, false otherwise.
	bool DeleteHandleOwner(const int handle, const short owner);

	/// \brief Increases the number of handles reserved by the given owner by one.
	/// \param[in] owner Index of the owner.
	/// \return True on success, false otherwise.
	bool IncreaseHandleCount(const short owner);

	/// \brief Decreases the number of handles reserved by the given owner by one.
	/// \param[in] owner Index of the owner.
	/// \return True on success, false otherwise.
	bool DecreaseHandleCount(const short owner);
};
