function OnGameModeInit()
{
	SetScriptName("Building mode");
	SetScriptVersion("0.0.0.1");
	SetScriptAuthor("009");

	CreateCar(0x506434F6, -57.856403, 857.939880, 14.718335, 0.0, 0, 0);
	CreateCar(0x18F25AC7, -58.236626, 841.208984, 14.706969, 0.0, 0, 0);
	CreateCar(0x1D06D681, -58.281269, 820.258911, 14.704250, 0.0, 0, 0);
	CreateCar(0x79FBB0C5, -58.267639, 799.859314, 14.659676, 0.0, 0, 0);
	CreateCar(0xEE6024BC, -58.164066, 772.126892, 14.707888, 0.0, 0, 0);

	CreateCar(0x1D06D681, -43.250000,-10.875000,14.818866, 0.0, 0, 0);
	CreateCar(0x79FBB0C5, -43.250000,-20.875000,14.818866, 0.0, 0, 0);
	CreateCar(0xEE6024BC, -43.250000,-30.875000,14.818866, 0.0, 0, 0);
	
	SetGameTime([12, 0]);
	
	SendMessageToAll("Hello + 12345 + привет");

	addPlayerClass(0x98E29920, 0, 0, 0, 0, 16, 100, 0, 0, 0, 0); // Not using
}

function OnGameModeExit()
{
	print("Builing mode by 009 unloaded. "+time()+"\n");
}

function OnPlayerConnect(playerid, name)
{
	SetPlayerSpawnPosition(playerid, -106.500755, 764.368164, 15.337303, 180.0);
}

function OnPlayerDisconnect(playerid)
{
	SendMessageToAll(GetPlayerName(playerid) + " [ " + playerid + " ]" + " disconnect from server");
}

function OnPlayerSpawn(playerid)
{
	print("hello spawn");
	
	if(playerid == 0) SetPlayerModel(playerid, 0x6AF081E8); // Playboy X
	else if(playerid == 1) SetPlayerModel(playerid, 0x58A1E271); // Liljacob
	else if(playerid == 2) SetPlayerModel(playerid, 0x89395FC9); // Roman
	else SetPlayerModel(playerid, 0x98E29920);
	
	GivePlayerWeapon(playerid, 15, 150);
}

function OnPlayerDeath(playerid, killerid, reason)
{
	SetPlayerSpawnPosition(playerid, -106.500755, 764.368164, 15.337303, 180.0);
	if(killerid != -1)
		SendMessageToAll(GetPlayerName(killerid) + " [ " + killerid + " ]" + " kill " + GetPlayerName(playerid) + " [ " + playerid + " ]" + " reason: " + reason);
	else
		SendMessageToAll(GetPlayerName(playerid) + " [ " + playerid + " ]" + " dead with reason: " + reason
}	

function OnPlayerText(playerid, text)
{
	return 1;
}

function OnPlayerCommandText(playerid, cmd, params)
{
	print("COMMAND '"+cmd+"' & '"+params+"' from "+playerid+"\n");
	if(cmd == "createcar")
	{
		local carid = params;
		local position = GetPlayerPos(playerid);
		CreateVehicle(carid.tointeger(),position[0],position[1],position[2],0.0,1,1);
		SendMessageToAll(GetPlayerName(playerid) + " [" + playerid + "]" + " create vehicle: " + carid.tointeger());
		return 1;
	}
	else if(cmd == "gun")
	{		
		local gunid = params;
		GivePlayerWeapon(playerid, gunid.tointeger(),9999);
		SendMessageToPlayer(playerid, "you got weapon");
		SendMessageToAll(GetPlayerName(playerid)+" got weapon");
		return 1;
	}
	else if(cmd == "setmyspawnhere")
	{		
		//local pos = GetPlayerPos(playerid);
		//SetPlayerSpawn(playerid,pos[0],pos[1],pos[2]);
		SetPlayerPos(playerid,-106.500755, 764.368164, 15.337303);
		return 1;
	}
	else if(cmd == "setmyskin")
	{		
		local skinid = params;
		SetPlayerSkin(playerid,skinid.tointeger());
		return 1;
	}
	return 0;
}