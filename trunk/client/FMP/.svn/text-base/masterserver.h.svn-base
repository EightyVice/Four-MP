#include <vector>

class TCPInterface;
class HTTPConnection;
namespace RakNet
{
	class RakString;
}

#define MASTER_HOST "master.four-mp.com"
#define MASTER_PATH "/"

struct ServerInfo
{
	wchar_t name[128];			// Server's name
	char ip[64];			// Server's IP
	unsigned short port;				// Server's port
	wchar_t loc[64];			// Server's location
	wchar_t mode[64];			// Server's game mode
	short players;			// Count players on server
	short maxplayers;			// Count slots on server
	bool password;			// Server have a password?
	wchar_t clan[64];			// Clan's server
	bool ban;				// Server in black list?
	bool vip;				// Server is VIP?
	unsigned int ping;	// Ping
};

// Information of player
struct MasterUserInfo
{
	int fmpid;				// FOUR-MP ID
	wchar_t name[32];			// Player nick
	wchar_t login[32];			// Player login
	wchar_t status[128];		// Player status
	char seskey[32];		// Session key hash
	std::wstring friends;			// Player's friends
};

// Query states
enum MasterServerStates
{
	MSS_NONE,
	MSS_ERROR,
	MSS_WAIT_SERVER_LIST,
	MSS_WAIT_USER_LOGIN,
	MSS_WAIT_USER_UPDATE,
	MSS_WAIT_USER_REGISTER,
	MSS_WAIT_USER_LOGOUT,
	MSS_WAIT_CHECK,
	MSS_WAIT_CLAN
};

// Class for four-mp master server
class MasterServer
{
	TCPInterface *tcp;
	HTTPConnection *http;

	std::vector<ServerInfo*> slist;
	MasterUserInfo *user;
	wchar_t error[128];

	MasterServerStates state;
protected:
	void Process();
	void ReadPacket(RakNet::RakString data);

	void ReadServerList(RakNet::RakString data);
	void ReadUserInfo(RakNet::RakString data);
	void ReadClanInfo(RakNet::RakString data);

	char *URLEncode(const wchar_t *string);
public:
	MasterServer();
	~MasterServer();
	void Load();

	void ClearServerList();
	wchar_t * GetError();

	bool QueryServerList(bool ban = 0, bool vip = 0, bool empty = 0, bool full = 0, bool password = 1, const wchar_t *clan = 0, const wchar_t *name = 0, const wchar_t *mode = 0, const wchar_t *loc = 0);
	bool QueryUserLogin(const wchar_t *login, const wchar_t *password);
	bool QueryUserUpdate(const wchar_t *status);
	bool QueryUserRegister(const wchar_t *login, const wchar_t *nick, const wchar_t *password, const wchar_t *email);
	bool QueryUserLogout();
	bool QueryClan();

	std::vector<ServerInfo*> *GetServerList();
	ServerInfo *GetServerInfo(int Index);
	ServerInfo *GetServerInfo(char *ip, unsigned short port, int *index);
	int GetNumServers();
	bool IsServerVIP(char *ip, unsigned short port);
	bool IsServerBanned(char *ip, unsigned short port);

	bool IsUserInfo();
	MasterUserInfo *GetUserInfo();
	int GetUserId();
	wchar_t *GetUserName();
	unsigned int GetUserSession();
};