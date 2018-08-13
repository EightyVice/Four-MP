/*
*	Created:			28.10.09
*	Created by:			009 & VoLT & WNeZRoS
*	Last Modifed:		29.10.09
*/
#pragma once

#include <windows.h>
#include "Hook\types.h"
#include "natives.h"

extern DWORD dwLoadOffset;


namespace Natives
{
	// rebuild
	static void GivePedFakeNetworkName(Ped ped, char * name, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha) { NativeInvoke::Invoke<NATIVE_GIVE_PED_FAKE_NETWORK_NAME , ScriptVoid>(ped, name, red, green, blue, alpha); }
	static bool IsControlPressed(unsigned int unk_0, unsigned int key) { return NativeInvoke::Invoke<NATIVE_IS_CONTROL_PRESSED, bool>(unk_0, key); }
	static void SetPedDensityMultiplier(unsigned int den) { NativeInvoke::Invoke<NATIVE_SET_PED_DENSITY_MULTIPLIER, ScriptVoid>(den); }
	static void SetCarDensityMultiplier(unsigned int den) { NativeInvoke::Invoke<NATIVE_SET_CAR_DENSITY_MULTIPLIER, ScriptVoid>(den); }
	static void DisableCarGenerators(ScriptAny p0) { NativeInvoke::Invoke<NATIVE_DISABLE_CAR_GENERATORS, ScriptVoid>(p0); }
	//static void DisableCarGeneratorsWithHeli(ScriptAny p0) { NativeInvoke::Invoke<NATIVE_DISABLE_CAR_GENERATORS_WITH_HELI, ScriptVoid>(p0); }
	static void SetNoResprays(bool no) { NativeInvoke::Invoke<NATIVE_SET_NO_RESPRAYS,ScriptVoid>(no); }
	static void TerminateAllScriptsWithThisName(char * name) { NativeInvoke::Invoke<NATIVE_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME,ScriptVoid>(name); }
	static void SetMaxWantedLevel(unsigned int max) { NativeInvoke::Invoke<NATIVE_SET_MAX_WANTED_LEVEL,ScriptVoid>(max); }
	static void GetCharCoordinates(Ped ped, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_CHAR_COORDINATES, ScriptVoid>(ped, pX, pY, pZ); }
	static void GetCharHeading(Ped ped, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CHAR_HEADING, ScriptVoid>(ped, pValue); }
	static bool IsCharInAnyCar(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANY_CAR, bool>(ped); }
	static bool HasModelLoaded(eModel model) { return NativeInvoke::Invoke<NATIVE_HAS_MODEL_LOADED, bool>(model); }
	static void RequestModel(eModel model) { NativeInvoke::Invoke<NATIVE_REQUEST_MODEL, ScriptVoid>(model); }
	static void MarkModelAsNoLongerNeeded(eModel model) { NativeInvoke::Invoke<NATIVE_MARK_MODEL_AS_NO_LONGER_NEEDED, ScriptVoid>(model); }
	static void ChangePlayerModel(Player playerIndex, eModel model) { NativeInvoke::Invoke<NATIVE_CHANGE_PLAYER_MODEL, ScriptVoid>(playerIndex, model); }
	static Player ConvertIntToPlayerIndex(unsigned int playerId) { return NativeInvoke::Invoke<NATIVE_CONVERT_INT_TO_PLAYERINDEX, Player>(playerId); }
	static unsigned int GetPlayerId() { return NativeInvoke::Invoke<NATIVE_GET_PLAYER_ID, unsigned int>(); }
	static void GetPlayerChar(Player playerIndex, Ped *pPed) { NativeInvoke::Invoke<NATIVE_GET_PLAYER_CHAR, ScriptVoid>(playerIndex, pPed); }
	static void SetCharDefaultComponentVariation(Ped ped) { NativeInvoke::Invoke<NATIVE_SET_CHAR_DEFAULT_COMPONENT_VARIATION, ScriptVoid>(ped); }
	static void CreateChar(unsigned int type, eModel model, float x, float y, float z, Ped *pPed, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_CREATE_CHAR, ScriptVoid>(type, model, x, y, z, pPed, unknownTrue); }
	static bool DoesCharExist(Ped ped) { return NativeInvoke::Invoke<NATIVE_DOES_CHAR_EXIST, bool>(ped); }
	static void AddArmourToChar(Ped ped, unsigned int amount) { NativeInvoke::Invoke<NATIVE_ADD_ARMOUR_TO_CHAR, ScriptVoid>(ped, amount); }
	static void TaskEnterCarAsDriver(Ped ped, Vehicle vehicle, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_ENTER_CAR_AS_DRIVER, ScriptVoid>(ped, vehicle, duration); }
	static void TaskEnterCarAsPassenger(Ped ped, Vehicle vehicle, unsigned int duration, unsigned int seatIndex) { NativeInvoke::Invoke<NATIVE_TASK_ENTER_CAR_AS_PASSENGER, ScriptVoid>(ped, vehicle, duration, seatIndex); }
	static void SetFloatStat(eFloatStatistic stat, float value) { NativeInvoke::Invoke<NATIVE_SET_FLOAT_STAT, ScriptVoid>(stat, value); }
	static void SetIntStat(eIntStatistic stat, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_INT_STAT, ScriptVoid>(stat, value); }
	static void SetCharCoordinates(Ped ped, float x, float y, float z) { NativeInvoke::Invoke<NATIVE_SET_CHAR_COORDINATES, ScriptVoid>(ped, x, y, z); }
	static void GiveWeaponToChar(Ped ped, eWeapon weapon, unsigned int ammo, bool unknown0) { NativeInvoke::Invoke<NATIVE_GIVE_WEAPON_TO_CHAR, ScriptVoid>(ped, weapon, ammo, unknown0); }
	static void TaskJump(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_TASK_JUMP, ScriptVoid>(ped, value); }
	static void TaskToggleDuck(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_TASK_TOGGLE_DUCK, ScriptVoid>(ped, value); }
	static void TaskAimGunAtCoord(Ped ped, float tX, float tY, float tZ, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_CAR_DRIVE_TO_COORD, ScriptVoid>(ped, tX, tY, tZ, duration); }
	static void TaskCarDriveToCoord(Ped ped, Vehicle car, float x, float y, float z, float speed, unsigned int p1f_2b, unsigned int p2, unsigned int p3, unsigned int px2, unsigned int p45000) { NativeInvoke::Invoke<NATIVE_TASK_CAR_DRIVE_TO_COORD, ScriptVoid>(ped, car, x, y, z, speed, p1f_2b, p2, p3, px2, p45000); }
	static void TaskShootAtCoord(Ped ped, float x, float y, float z, unsigned int time_ms, unsigned int type_5) { NativeInvoke::Invoke<NATIVE_TASK_SHOOT_AT_COORD, ScriptVoid>(ped, x, y, z, time_ms, type_5); }
	static void SetCharHeading(Ped ped, float heading) { NativeInvoke::Invoke<NATIVE_SET_CHAR_HEADING, ScriptVoid>(ped, heading); }
	static void TaskGoStraightToCoord(Ped ped, float x, float y, float z, unsigned int unknown2, unsigned int unknown45000) { NativeInvoke::Invoke<NATIVE_TASK_GO_STRAIGHT_TO_COORD, ScriptVoid>(ped, x, y, z, unknown2, unknown45000); }
	static void DeleteChar(Ped *pPed) { NativeInvoke::Invoke<NATIVE_DELETE_CHAR, ScriptVoid>(pPed); }
	static void ClearCharTasks(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_TASKS, ScriptVoid>(ped); }
	static void TaskLeaveAnyCar(Ped ped) { NativeInvoke::Invoke<NATIVE_TASK_LEAVE_ANY_CAR, ScriptVoid>(ped); }
	static void SetCurrentCharWeapon(Ped ped, eWeapon w, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_SET_CURRENT_CHAR_WEAPON, ScriptVoid>(ped, w, unknownTrue); }
	static void TaskSwapWeapon(Ped ped, eWeapon weapon) { NativeInvoke::Invoke<NATIVE_TASK_SWAP_WEAPON, ScriptVoid>(ped, weapon); }
	static void SetCharComponentVariation(Ped ped, ePedComponent component, unsigned int modelVariation, unsigned int textureVariation) { NativeInvoke::Invoke<NATIVE_SET_CHAR_COMPONENT_VARIATION, ScriptVoid>(ped, component, modelVariation, textureVariation); }
	static void GetCharModel(Ped ped, eModel *pModel) { NativeInvoke::Invoke<NATIVE_GET_CHAR_MODEL, ScriptVoid>(ped, pModel); }
	static void SetCharHealth(Ped ped, unsigned int health) { NativeInvoke::Invoke<NATIVE_SET_CHAR_HEALTH, ScriptVoid>(ped, health); }
	static void SetRoomForCharByKey(Ped ped, eInteriorRoomKey key) { NativeInvoke::Invoke<NATIVE_SET_ROOM_FOR_CHAR_BY_KEY, ScriptVoid>(ped, key); }
	static void GetCarSpeed(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_SPEED, ScriptVoid>(vehicle, pValue); }
	static bool DoesVehicleExist(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_DOES_VEHICLE_EXIST, bool>(vehicle); }
	static bool IsCarStopped(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_STOPPED, bool>(vehicle); }
	static void GetCarSpeedVector(Vehicle vehicle, Vector3 *pVector, bool unknownFalse) { NativeInvoke::Invoke<NATIVE_GET_CAR_SPEED_VECTOR, ScriptVoid>(vehicle, pVector, unknownFalse); }
	static void GetCarHeading(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_HEADING, ScriptVoid>(vehicle, pValue); }
	static bool IsCharInAir(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_AIR, bool>(ped); } 
	static bool IsCharDucking(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_DUCKING, bool>(ped); }
	static void GetMaximumNumberOfPassengers(Vehicle vehicle, unsigned int *pMax) { NativeInvoke::Invoke<NATIVE_GET_MAXIMUM_NUMBER_OF_PASSENGERS, ScriptVoid>(vehicle, pMax); }
	static void GetCarCoordinates(Vehicle vehicle, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_CAR_COORDINATES, ScriptVoid>(vehicle, pX, pY, pZ); }
	static bool IsCharSittingInAnyCar(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_SITTING_IN_ANY_CAR, bool>(ped); }
	static bool IsCharOnFoot(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_ON_FOOT, bool>(ped); }
	static ScriptAny GetCurrentCharWeapon(Ped ped, eWeapon *pWeapon) { return NativeInvoke::Invoke<NATIVE_GET_CURRENT_CHAR_WEAPON, ScriptAny>(ped, pWeapon); }
	static void FreezeCharPosition(Ped ped, bool frozen) { NativeInvoke::Invoke<NATIVE_FREEZE_CHAR_POSITION, ScriptVoid>(ped, frozen); }
	static void GetGameCam(Camera *camera) { NativeInvoke::Invoke<NATIVE_GET_GAME_CAM, ScriptVoid>(camera); }
	static void GetCamPos(Camera camera,  float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_CAM_POS, ScriptVoid>(camera, pX, pY, pZ); }
	static void GetCamRot(Camera camera, float *angleX, float *angleY, float *angleZ) { NativeInvoke::Invoke<NATIVE_GET_CAM_ROT, ScriptVoid>(camera, angleX, angleY, angleZ); }
	static void GetCharHealth(Ped ped, unsigned int *pHealth) { NativeInvoke::Invoke<NATIVE_GET_CHAR_HEALTH, ScriptVoid>(ped, pHealth); }
	static void GetCharArmour(Ped ped, unsigned int *pArmour) { NativeInvoke::Invoke<NATIVE_GET_CHAR_ARMOUR, ScriptVoid>(ped, pArmour); }
	static void CreateCar(unsigned int nameHash, float x, float y, float z, Vehicle *pVehicle, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_CREATE_CAR, ScriptVoid>(nameHash, x, y, z, pVehicle, unknownTrue); }
	static void SetCarHeading(Vehicle vehicle, float dir) { NativeInvoke::Invoke<NATIVE_SET_CAR_HEADING, ScriptVoid>(vehicle, dir); }
	static void GetCarCharIsUsing(Ped ped, Vehicle *pVehicle) { NativeInvoke::Invoke<NATIVE_GET_CAR_CHAR_IS_USING, ScriptVoid>(ped, pVehicle); }
	static void AllowEmergencyServices(bool allow) { NativeInvoke::Invoke<NATIVE_ALLOW_EMERGENCY_SERVICES, ScriptVoid>(allow); }
	static void SwitchAmbientPlanes(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_AMBIENT_PLANES, ScriptVoid>(on); }  
	static void SwitchArrowAboveBlippedPickups(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_ARROW_ABOVE_BLIPPED_PICKUPS, ScriptVoid>(on); }
	static void SwitchRandomBoats(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_RANDOM_BOATS, ScriptVoid>(on); }
	static void SwitchRandomTrains(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_RANDOM_TRAINS, ScriptVoid>(on); }
	static void SwitchGarbageTrucks(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_GARBAGE_TRUCKS, ScriptVoid>(on); }
	static void ClearAreaOfChars(float x, float y, float z, float radius) { NativeInvoke::Invoke<NATIVE_CLEAR_AREA_OF_CHARS, ScriptVoid>(x, y, z, radius); }
	static void ClearAreaOfCops(float x, float y, float z, float radius) { NativeInvoke::Invoke<NATIVE_CLEAR_AREA_OF_COPS, ScriptVoid>(x, y, z, radius); }
	static void RemoveAllCharWeapons(Ped ped) { NativeInvoke::Invoke<NATIVE_REMOVE_ALL_CHAR_WEAPONS, ScriptVoid>(ped); }
	static void SetCharMoney(Ped ped, unsigned int amount) { NativeInvoke::Invoke<NATIVE_SET_CHAR_MONEY, ScriptVoid>(ped, amount); }
	static void SetTimeOfDay(unsigned int hour, unsigned int minute) { NativeInvoke::Invoke<NATIVE_SET_TIME_OF_DAY, ScriptVoid>(hour, minute); }
	static unsigned int GetCharDrawableVariation(Ped ped, ePedComponent component) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_DRAWABLE_VARIATION, ScriptAny>(ped, component); }
	static unsigned int GetCharTextureVariation(Ped ped, ePedComponent component) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_TEXTURE_VARIATION, unsigned int>(ped, component); }
	static void PrintStringWithLiteralStringNow(const char *gxtName, const char *text, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_STRING_WITH_LITERAL_STRING_NOW, ScriptVoid>(gxtName, text, timeMS, enable); }
	

///////////////////////////////////

    static void AddScore(Player playerIndex, int score) { NativeInvoke::Invoke<NATIVE_ADD_SCORE, ScriptVoid>(playerIndex, score); }
    static void AllowPlayerToCarryNonMissionObjects(Player playerIndex, bool allow) { NativeInvoke::Invoke<NATIVE_ALLOW_PLAYER_TO_CARRY_NON_MISSION_OBJECTS, ScriptVoid>(playerIndex, allow); }
    static void AlterWantedLevel(Player playerIndex,  unsigned int level) { NativeInvoke::Invoke<NATIVE_ALTER_WANTED_LEVEL, ScriptVoid>(playerIndex, level); }
    static void AlterWantedLevelNoDrop(Player playerIndex, unsigned int level) { NativeInvoke::Invoke<NATIVE_ALTER_WANTED_LEVEL_NO_DROP, ScriptVoid>(playerIndex, level); }
    static void ApplyWantedLevelChangeNow(Player playerIndex) { NativeInvoke::Invoke<NATIVE_APPLY_WANTED_LEVEL_CHANGE_NOW, ScriptVoid>(playerIndex); }
    //static void ChangePlayerModel(Player playerIndex, eModel model) { NativeInvoke::Invoke<NATIVE_CHANGE_PLAYER_MODEL, ScriptVoid>(playerIndex, model); }
    static void ClearPlayerHasDamagedAtLeastOnePed(Player playerIndex) { NativeInvoke::Invoke<NATIVE_CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED, ScriptVoid>(playerIndex); }
    //static Player ConvertIntToPlayerIndex(unsigned int playerId) { return NativeInvoke::Invoke<NATIVE_CONVERT_INT_TO_PLAYERINDEX, Player>(playerId); }
    static void ClearWantedLevel(Player playerIndex) { NativeInvoke::Invoke<NATIVE_CLEAR_WANTED_LEVEL, ScriptVoid>(playerIndex); }
    static void CreatePlayer(unsigned int playerId, float x, float y, float z, Player *pPlayerIndex) { NativeInvoke::Invoke<NATIVE_CREATE_PLAYER, ScriptVoid>(playerId, x, y, z, pPlayerIndex); }
    static void DisablePlayerLockon(Player playerIndex, bool disabled) { NativeInvoke::Invoke<NATIVE_DISABLE_PLAYER_LOCKON, ScriptVoid>(playerIndex, disabled); }
    static void DisablePlayerSprint(Player playerIndex, bool disabled) { NativeInvoke::Invoke<NATIVE_DISABLE_PLAYER_SPRINT, ScriptVoid>(playerIndex, disabled); }
    //static void GetPlayerChar(Player playerIndex, Ped *pPed) { NativeInvoke::Invoke<NATIVE_GET_PLAYER_CHAR, ScriptVoid>(playerIndex, pPed); }
    static void GetPlayerGroup(Player playerIndex, Group *pGroup) { NativeInvoke::Invoke<NATIVE_GET_PLAYER_GROUP, ScriptVoid>(playerIndex, pGroup); }
    //static unsigned int GetPlayerId() { return NativeInvoke::Invoke<NATIVE_GET_PLAYER_ID, unsigned int>(); }
    static void GetPlayersLastCarNoSave(Vehicle* pVehicle) { NativeInvoke::Invoke<NATIVE_GET_PLAYERS_LAST_CAR_NO_SAVE, ScriptVoid>(pVehicle); }
    static void GetPlayerMaxArmour(Player playerIndex, unsigned int *pMaxArmour) { NativeInvoke::Invoke<NATIVE_GET_PLAYER_MAX_ARMOUR, ScriptVoid>(playerIndex, pMaxArmour); }
    static const char *GetPlayerName(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_GET_PLAYER_NAME, const char *>(playerIndex); }
    static eModel GetPlayerSettingsModelChoice() { return NativeInvoke::Invoke<NATIVE_GET_PLAYERSETTINGS_MODEL_CHOICE, eModel>(); }
    static ScriptAny GetPlayerToPlaceBombInCar(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_GET_PLAYER_TO_PLACE_BOMB_IN_CAR, ScriptAny>(vehicle); }
    static unsigned int GetTimeSincePlayerDroveAgainstTraffic(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC, unsigned int>(playerIndex); }
    static unsigned int GetTimeSincePlayerDroveOnPavement(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT, unsigned int>(playerIndex); }
    static unsigned int GetTimeSincePlayerHitBuilding(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_PLAYER_HIT_BUILDING, unsigned int>(playerIndex); }
    static unsigned int GetTimeSincePlayerHitCar(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_PLAYER_HIT_CAR, unsigned int>(playerIndex); }
    static unsigned int GetTimeSincePlayerHitObject(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_PLAYER_HIT_OBJECT, unsigned int>(playerIndex); }
    static unsigned int GetTimeSincePlayerHitPed(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_PLAYER_HIT_PED, unsigned int>(playerIndex); }
    static unsigned int GetTimeSincePlayerRanLight(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_PLAYER_RAN_LIGHT, unsigned int>(playerIndex); }
    static bool HasPlayerCollectedPickup(Player playerIndex, Pickup pikcup) { return NativeInvoke::Invoke<NATIVE_HAS_PLAYER_COLLECTED_PICKUP, bool>(playerIndex, pikcup); }
    static bool HasPlayerDamagedAtLeastOnePed(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED, bool>(playerIndex); }
    static bool HasPlayerDamagedAtLeastOneVehicle(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_HAS_PLAYER_DAMAGED_AT_LEAST_ONE_VEHICLE, bool>(playerIndex); }
    static bool IsPlayerClimbing(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_CLIMBING, bool>(playerIndex); }
    static bool IsPlayerControlOn(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_CONTROL_ON, bool>(playerIndex); }
    static bool IsPlayerDead(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_DEAD, bool>(playerIndex); }
    static bool IsPlayerFreeAimingAtChar(Player playerIndex, Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_FREE_AIMING_AT_CHAR, bool>(playerIndex, ped); }
    static bool IsPlayerFreeForAmbientTask(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_FREE_FOR_AMBIENT_TASK, bool>(playerIndex); }
    static bool IsPlayerPlaying(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_PLAYING, bool>(playerIndex); }
    static bool IsPlayerPressingHorn(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_PRESSING_HORN, bool>(playerIndex); }
    static bool IsPlayerTargettingAnything(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_TARGETTING_ANYTHING, bool>(playerIndex); }
    static bool IsPlayerTargettingChar(Player playerIndex, Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_TARGETTING_CHAR, bool>(playerIndex, ped); }
    static bool IsPlayerTargettingObject(Player playerIndex, Object obj) { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_TARGETTING_OBJECT, bool>(playerIndex, obj); }
    static bool IsScoreGreater(Player playerIndex, unsigned int score) { return NativeInvoke::Invoke<NATIVE_IS_SCORE_GREATER, bool>(playerIndex, score); }
    static bool IsWantedLevelGreater(Player playerIndex, unsigned int level) { return NativeInvoke::Invoke<NATIVE_IS_WANTED_LEVEL_GREATER, bool>(playerIndex, level); }
    static bool PlayerHasChar(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_PLAYER_HAS_CHAR, bool>(playerIndex); }
    static bool PlayerHasFlashingStarsAboutToDrop(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_PLAYER_HAS_FLASHING_STARS_ABOUT_TO_DROP, bool>(playerIndex); }
    static bool PlayerHasGreyedOutStars(Player playerIndex) { return NativeInvoke::Invoke<NATIVE_PLAYER_HAS_GREYED_OUT_STARS, bool>(playerIndex); }
    static void RegisterPlayerRespawnCoords(Player playerIndex, float x, float y, float z) { NativeInvoke::Invoke<NATIVE_REGISTER_PLAYER_RESPAWN_COORDS, ScriptVoid>(playerIndex, x, y, z); }
    static void FlushAllPlayerRespawnCoords(Player playerIndex) { NativeInvoke::Invoke<NATIVE_FLUSH_ALL_PLAYER_RESPAWN_COORDS, ScriptVoid>(playerIndex); }
	static void SetEveryoneIgnorePlayer(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_EVERYONE_IGNORE_PLAYER, ScriptVoid>(playerIndex, value); }
    static void SetPlayerCanBeHassledByGangs(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_CAN_BE_HASSLED_BY_GANGS, ScriptVoid>(playerIndex, value); }
    static void SetPlayerCanDoDriveBy(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_CAN_DO_DRIVE_BY, ScriptVoid>(playerIndex, value); }
    static void SetPlayerCanUseCover(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_CAN_USE_COVER, ScriptVoid>(playerIndex, value); }
	static void SetPlayerControl(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_CONTROL, ScriptVoid>(playerIndex, value); }
    static void SetPlayerControlAdvanced(Player playerIndex, bool unknown1, bool unknown2, bool unknown3) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_CONTROL_ADVANCED, ScriptVoid>(playerIndex, unknown1, unknown2, unknown3); }
    static void SetPlayerFastReload(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_FAST_RELOAD, ScriptVoid>(playerIndex, value); }
    static void SetPlayerGroupToFollowAlways(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS, ScriptVoid>(playerIndex, value); }
    static void SetPlayerInvincible(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_INVINCIBLE, ScriptVoid>(playerIndex, value); }
    static void SetPlayerMoodNormal(Player playerIndex) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_MOOD_NORMAL, ScriptVoid>(playerIndex); }
    static void SetPlayerMoodPissedOff(Player playerIndex, unsigned int unknown150) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_MOOD_PISSED_OFF, ScriptVoid>(playerIndex, unknown150); }
    static void SetPlayerNeverGetsTired(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_PLAYER_NEVER_GETS_TIRED, ScriptVoid>(playerIndex, value); }
    static void SetPlayerSettingsModelVariationsChoice(Player playerIndex) { NativeInvoke::Invoke<NATIVE_SET_PLAYERSETTINGS_MODEL_VARIATIONS_CHOICE, ScriptVoid>(playerIndex); }
    static void SetPoliceIgnorePlayer(Player playerIndex, bool value) { NativeInvoke::Invoke<NATIVE_SET_POLICE_IGNORE_PLAYER, ScriptVoid>(playerIndex, value); }
    static void StoreScore(Player playerIndex, unsigned int* value) { NativeInvoke::Invoke<NATIVE_STORE_SCORE, ScriptVoid>(playerIndex, value); }
    static void StoreWantedLevel(Player playerIndex, unsigned int* value) { NativeInvoke::Invoke<NATIVE_STORE_WANTED_LEVEL, ScriptVoid>(playerIndex, value); }
    static void RemovePlayerHelmet(Player playerIndex, bool remove) { NativeInvoke::Invoke<NATIVE_REMOVE_PLAYER_HELMET, ScriptVoid>(playerIndex, remove); }
    static void AddHospitalRestart(float x, float y, float z, float r, int num_x3) { NativeInvoke::Invoke<NATIVE_ADD_HOSPITAL_RESTART, ScriptVoid>(x, y, z, r, num_x3); }
    static void AddPoliceRestart(float x, float y, float z, float r, int num_x3) { NativeInvoke::Invoke<NATIVE_ADD_POLICE_RESTART, ScriptVoid>(x, y, z, r, num_x3); }
	static void ThisScriptShouldBeSaved() { NativeInvoke::Invoke<NATIVE_THIS_SCRIPT_SHOULD_BE_SAVED, ScriptVoid>(); }
	static void SetSleepModeActive(bool active) { NativeInvoke::Invoke<NATIVE_SET_SLEEP_MODE_ACTIVE, bool>(active); }
	static void AllowThisScriptToBePaused(bool pause) { NativeInvoke::Invoke<NATIVE_ALLOW_THIS_SCRIPT_TO_BE_PAUSED, ScriptVoid>(pause); }
	static void SetPedNonCreationArea(float sx, float sy, float sz, float ex, float ey, float ez) { NativeInvoke::Invoke<NATIVE_SET_PED_NON_CREATION_AREA, ScriptVoid>(sx, sy, sz, ex, ey, ez); }

    // Ped
    static void AddAmmoToChar(Ped ped, eWeapon weapon, unsigned int amount) { NativeInvoke::Invoke<NATIVE_ADD_AMMO_TO_CHAR, ScriptVoid>(ped, weapon, amount); }
    //static void AddArmourToChar(Ped ped, unsigned int amount) { NativeInvoke::Invoke<NATIVE_ADD_ARMOUR_TO_CHAR, ScriptVoid>(ped, amount); }
    static void ApplyForceToPed(Ped ped, unsigned int unknown0_3, float x, float y, float z, float spinX, float spinY, float spinZ, unsigned int unknown4_0, unsigned int unknown5_1, unsigned int unknown6_1, unsigned int unknown7_1) { NativeInvoke::Invoke<NATIVE_APPLY_FORCE_TO_PED, ScriptVoid>(ped, unknown0_3, x, y, z, spinX, spinY, spinZ, unknown4_0, unknown5_1, unknown6_1, unknown7_1); }
    static void AttachPedToCar(Ped ped, Vehicle vehicle, unsigned int unknown0_0, float offsetX, float offsetY, float offsetZ, float unknown1_276, float unknown2_0, unsigned int unknown3_0, unsigned int unknown4_0) { NativeInvoke::Invoke<NATIVE_ATTACH_PED_TO_CAR, ScriptVoid>(ped, vehicle, unknown0_0, offsetX, offsetY, offsetZ, unknown1_276, unknown2_0, unknown3_0, unknown4_0); }
    static void BlockCharGestureAnims(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_BLOCK_CHAR_GESTURE_ANIMS, ScriptVoid>(ped, value); }
    static void BlockPedWeaponSwitching(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_BLOCK_PED_WEAPON_SWITCHING, ScriptVoid>(ped, value); }
    static void CancelCurrentlyPlayingAmbientSpeech(Ped ped) { NativeInvoke::Invoke<NATIVE_CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH, ScriptVoid>(ped); }
    static void ClearAllCharProps(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_ALL_CHAR_PROPS, ScriptVoid>(ped); }
    static void ClearCharLastDamageBone(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_LAST_DAMAGE_BONE, ScriptVoid>(ped); }
    static void ClearCharLastDamageEntity(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_LAST_DAMAGE_ENTITY, ScriptVoid>(ped); }
    static void ClearCharLastWeaponDamage(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_LAST_WEAPON_DAMAGE, ScriptVoid>(ped); } 
    static void ClearCharProp(Ped ped, bool unknown) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_PROP, ScriptVoid>(ped, unknown); }
    static void ClearCharSecondaryTask(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_SECONDARY_TASK, ScriptVoid>(ped); }
    //static void ClearCharTasks(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_TASKS, ScriptVoid>(ped); }
    static void ClearCharTasksImmediately(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_TASKS_IMMEDIATELY, ScriptVoid>(ped); }
    static void ClearRoomForChar(Ped ped) { NativeInvoke::Invoke<NATIVE_CLEAR_ROOM_FOR_CHAR, ScriptVoid>(ped); }
    //static void CreateChar(unsigned int type, eModel model, float x, float y, float z, Ped *pPed, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_CREATE_CHAR, ScriptVoid>(type, model, x, y, z, pPed, unknownTrue); }
    static void CreateRandomChar(float x, float y, float z, Ped *pPed) { NativeInvoke::Invoke<NATIVE_CREATE_RANDOM_CHAR, ScriptVoid>(x, y, z, pPed); }
    static void CreateRandomCharAsDriver(Vehicle vehicle, Ped *pPed) { NativeInvoke::Invoke<NATIVE_CREATE_RANDOM_CHAR_AS_DRIVER, ScriptVoid>(vehicle, pPed); }
    static void CreateRandomFemaleChar(float x, float y, float z, Ped *pPed) { NativeInvoke::Invoke<NATIVE_CREATE_RANDOM_FEMALE_CHAR, ScriptVoid>(x, y, z, pPed); }
    static void CreateRandomMaleChar(float x, float y, float z, Ped *pPed) { NativeInvoke::Invoke<NATIVE_CREATE_RANDOM_MALE_CHAR, ScriptVoid>(x, y, z, pPed); }
    static void DamageChar(Ped ped, unsigned int hitPoints, bool unknown) { NativeInvoke::Invoke<NATIVE_DAMAGE_CHAR, ScriptVoid>(ped, hitPoints, unknown); }
    static void DamagePedBodyPart(Ped ped, ePedBodyPart part, unsigned int hitPoints) { NativeInvoke::Invoke<NATIVE_DAMAGE_PED_BODY_PART, ScriptVoid>(ped, part, hitPoints); }
    //static void DeleteChar(Ped *pPed) { NativeInvoke::Invoke<NATIVE_DELETE_CHAR, ScriptVoid>(pPed); }
    static void DetachPed(Ped ped, bool unknown) { NativeInvoke::Invoke<NATIVE_DETACH_PED, ScriptVoid>(ped, unknown); }
    static void DetachPedFromWithinCar(Ped ped, bool unknown) { NativeInvoke::Invoke<NATIVE_DETACH_PED_FROM_WITHIN_CAR, ScriptVoid>(ped, unknown); }
    //static bool DoesCharExist(Ped ped) { return NativeInvoke::Invoke<NATIVE_DOES_CHAR_EXIST, bool>(ped); }
    static void DropObject(Ped ped, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_DROP_OBJECT, ScriptVoid>(ped, unknownTrue); }
    static void ExplodeCharHead(Ped ped) { NativeInvoke::Invoke<NATIVE_EXPLODE_CHAR_HEAD, ScriptVoid>(ped); }
    static void ExtinguishCharFire(Ped ped) { NativeInvoke::Invoke<NATIVE_EXTINGUISH_CHAR_FIRE, ScriptVoid>(ped); }
    static void FirePedWeapon(Ped ped, float x, float y, float z) { NativeInvoke::Invoke<NATIVE_FIRE_PED_WEAPON, ScriptVoid>(ped, x, y, z); }
    static void ForceCharToDropWeapon(Ped ped) { NativeInvoke::Invoke<NATIVE_FORCE_CHAR_TO_DROP_WEAPON, ScriptVoid>(ped); }
    static ScriptAny ForcePedPinnedDown(Ped ped, bool force, unsigned int timerMaybe) { return NativeInvoke::Invoke<NATIVE_FORCE_PED_PINNED_DOWN, ScriptAny>(ped, force, timerMaybe); }
    static void ForcePedToFleeWhilstDrivingVehicle(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_FORCE_PED_TO_FLEE_WHILST_DRIVING_VEHICLE, ScriptVoid>(ped, vehicle); }
    //static void FreezeCharPosition(Ped ped, bool frozen) { NativeInvoke::Invoke<NATIVE_FREEZE_CHAR_POSITION, ScriptVoid>(ped, frozen); }
    static void FreezeCharPositionAndDontLoadCollision(Ped ped, bool frozen) { NativeInvoke::Invoke<NATIVE_FREEZE_CHAR_POSITION_AND_DONT_LOAD_COLLISION, ScriptVoid>(ped, frozen); }
    static void GetAmmoInCharWeapon(Ped ped, eWeapon weapon, unsigned int *pAmmo) { NativeInvoke::Invoke<NATIVE_GET_AMMO_IN_CHAR_WEAPON, ScriptVoid>(ped, weapon, pAmmo); }
    static bool GetAmmoInClip(Ped ped, eWeapon weapon, unsigned int *pAmmo) { return NativeInvoke::Invoke<NATIVE_GET_AMMO_IN_CLIP, bool>(ped, weapon, pAmmo); }
    static const char *GetAnimGroupFromChar(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_ANIM_GROUP_FROM_CHAR, const char *>(ped); }
    //static void GetCharCoordinates(Ped ped, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_CHAR_COORDINATES, ScriptVoid>(ped, pX, pY, pZ); }
    //static void GetCharHealth(Ped ped, unsigned int *pHealth) { NativeInvoke::Invoke<NATIVE_GET_CHAR_HEALTH, ScriptVoid>(ped, pHealth); }
    static void GetCharAnimCurrentTime(Ped ped, const char *animGroup, const char *animName, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CHAR_ANIM_CURRENT_TIME, ScriptVoid>(ped, animGroup, animName, pValue); }
    static void GetCharAnimTotalTime(Ped ped, const char *animGroup, const char *animName, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CHAR_ANIM_TOTAL_TIME, ScriptVoid>(ped, animGroup, animName, pValue); }
    //static void GetCharArmour(Ped ped, unsigned int *pArmour) { NativeInvoke::Invoke<NATIVE_GET_CHAR_ARMOUR, ScriptVoid>(ped, pArmour); }
    //static unsigned int GetCharDrawableVariation(Ped ped, ePedComponent component) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_DRAWABLE_VARIATION, ScriptAny>(ped, component); }
    static void GetCharExtractedDisplacement(Ped ped, bool unknown, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_CHAR_EXTRACTED_DISPLACEMENT, ScriptVoid>(ped, unknown, pX, pY, pZ); }
    //static void GetCharHeading(Ped ped, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CHAR_HEADING, ScriptVoid>(ped, pValue); }
    static void GetCharHeightAboveGround(Ped ped, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CHAR_HEIGHT_ABOVE_GROUND, ScriptVoid>(ped, pValue); }
    static ScriptAny GetCharLastDamageBone(Ped ped, ePedBone *pBone) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_LAST_DAMAGE_BONE, ScriptAny>(ped, pBone); }
    static bool GetCharMeleeActionFlag0(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_MELEE_ACTION_FLAG0, bool>(ped); }
    static bool GetCharMeleeActionFlag1(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_MELEE_ACTION_FLAG1, bool>(ped); }
    //static void GetCharModel(Ped ped, eModel *pModel) { NativeInvoke::Invoke<NATIVE_GET_CHAR_MODEL, ScriptVoid>(ped, pModel); }
    static unsigned int GetCharMoney(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_MONEY, unsigned int>(ped); }
    static void GetCharPropIndex(Ped ped, bool unknown, unsigned int *pIndex) { NativeInvoke::Invoke<NATIVE_GET_CHAR_PROP_INDEX, ScriptVoid>(ped, unknown, pIndex); }
    static bool GetCharReadyToBeExecuted(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_READY_TO_BE_EXECUTED, bool>(ped); }
    static bool GetCharReadyToBeStunned(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_READY_TO_BE_STUNNED, bool>(ped); }
    static void GetCharSpeed(Ped ped, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CHAR_SPEED, ScriptVoid>(ped, pValue); }
    //static unsigned int GetCharTextureVariation(Ped ped, ePedComponent component) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_TEXTURE_VARIATION, unsigned int>(ped, component); }
    static void GetCharVelocity(Ped ped, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_CHAR_VELOCITY, ScriptVoid>(ped, pX, pY, pZ); }
    static void GetCharWeaponInSlot(Ped ped, eWeaponSlot slot, eWeapon *pWeapon, ScriptAny *pUnknown1, ScriptAny *pUnknown2) { NativeInvoke::Invoke<NATIVE_GET_CHAR_WEAPON_IN_SLOT, ScriptVoid>(ped, slot, pWeapon, pUnknown1, pUnknown2); }
    static bool GetCharWillCowerInsteadOfFleeing(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING, bool>(ped); }
    //static ScriptAny GetCurrentCharWeapon(Ped ped, eWeapon *pWeapon) { return NativeInvoke::Invoke<NATIVE_GET_CURRENT_CHAR_WEAPON, ScriptAny>(ped, pWeapon); }
    static unsigned int GetDamageToPedBodyPart(Ped ped, ePedBodyPart part) { return NativeInvoke::Invoke<NATIVE_GET_DAMAGE_TO_PED_BODY_PART, unsigned int>(ped, part); }
    static void GetDeadCharCoordinates(Ped ped, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_DEAD_CHAR_COORDINATES, ScriptVoid>(ped, pX, pY, pZ); }
    static void GetDeadCharPickupCoords(Ped ped, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_DEAD_CHAR_PICKUP_COORDS, ScriptVoid>(ped, pX, pY, pZ); }
    static void GetKeyForCharInRoom(Ped ped, eInteriorRoomKey *pKey) { NativeInvoke::Invoke<NATIVE_GET_KEY_FOR_CHAR_IN_ROOM, ScriptVoid>(ped, pKey); }
    static ScriptAny GetMaxAmmo(Ped ped, eWeapon weapon, unsigned int *pMaxAmmo) { return NativeInvoke::Invoke<NATIVE_GET_MAX_AMMO, ScriptAny>(ped, weapon, pMaxAmmo); }
    static void GetMaxAmmoInClip(Ped ped, eWeapon weapon, unsigned int *pMaxAmmo) { NativeInvoke::Invoke<NATIVE_GET_MAX_AMMO_IN_CLIP, ScriptVoid>(ped, weapon, pMaxAmmo); }
    static unsigned int GetNumberOfCharDrawableVariations(Ped ped, ePedComponent component) { return NativeInvoke::Invoke<NATIVE_GET_NUMBER_OF_CHAR_DRAWABLE_VARIATIONS, unsigned int>(ped, component); }
    static unsigned int GetNumberOfCharTextureVariations(Ped ped, ePedComponent component, unsigned int unknown1) { return NativeInvoke::Invoke<NATIVE_GET_NUMBER_OF_CHAR_TEXTURE_VARIATIONS, unsigned int>(ped, component, unknown1); }
    static Object GetObjectPedIsHolding(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_OBJECT_PED_IS_HOLDING, Object>(ped); }
    static void GetOffsetFromCharInWorldCoords(Ped ped, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ) { NativeInvoke::Invoke<NATIVE_GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS, ScriptVoid>(ped, x, y, z, pOffX, pOffY, pOffZ); }
    static ePedClimbState GetPedClimbState(Ped ped) { return NativeInvoke::Invoke<NATIVE_GET_PED_CLIMB_STATE, ePedClimbState>(ped); }
    static void GetPedBonePosition(Ped ped, ePedBone bone, float x, float y, float z, Vector3 *pPosition) { NativeInvoke::Invoke<NATIVE_GET_PED_BONE_POSITION, ScriptVoid>(ped, bone, x, y, z, pPosition); }
    static void GetPedGroupIndex(Ped ped, unsigned int* pIndex) { NativeInvoke::Invoke<NATIVE_GET_PED_GROUP_INDEX, ScriptVoid>(ped, pIndex); }
    static void GetPedType(Ped ped, ePedType *pType) { NativeInvoke::Invoke<NATIVE_GET_PED_TYPE, ScriptVoid>(ped, pType); }
    static void GivePedHelmet(Ped ped) { NativeInvoke::Invoke<NATIVE_GIVE_PED_HELMET, ScriptVoid>(ped); }
    //static void GiveWeaponToChar(Ped ped, eWeapon weapon, unsigned int ammo, bool unknown0) { NativeInvoke::Invoke<NATIVE_GIVE_WEAPON_TO_CHAR, ScriptVoid>(ped, weapon, ammo, unknown0); }
    static bool HasCharBeenDamagedByCar(Ped ped, Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_HAS_CHAR_BEEN_DAMAGED_BY_CAR, bool>(ped, vehicle); }
    static bool HasCharBeenDamagedByChar(Ped ped, Ped otherChar, bool unknownFalse) { return NativeInvoke::Invoke<NATIVE_HAS_CHAR_BEEN_DAMAGED_BY_CHAR, bool>(ped, otherChar, unknownFalse); }
    static bool HasCharBeenDamagedByWeapon(Ped ped, eWeapon weapon) { return NativeInvoke::Invoke<NATIVE_HAS_CHAR_BEEN_DAMAGED_BY_WEAPON, bool>(ped, weapon); }
    static bool HasCharGotWeapon(Ped ped, eWeapon weapon) { return NativeInvoke::Invoke<NATIVE_HAS_CHAR_GOT_WEAPON, bool>(ped, weapon); }
    static bool HasCharSpottedChar(Ped ped, Ped otherChar) { return NativeInvoke::Invoke<NATIVE_HAS_CHAR_SPOTTED_CHAR, bool>(ped, otherChar); }
    static bool HasCharSpottedCharInFront(Ped ped, Ped otherChar) { return NativeInvoke::Invoke<NATIVE_HAS_CHAR_SPOTTED_CHAR_IN_FRONT, bool>(ped, otherChar); }
    static bool IsAmbientSpeechPlaying(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_AMBIENT_SPEECH_PLAYING, bool>(ped); }
    static bool IsCharArmed(Ped ped, eWeaponSlot slot) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_ARMED, bool>(ped, slot); }
    static bool IsCharDead(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_DEAD, bool>(ped); }
    //static bool IsCharDucking(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_DUCKING, bool>(ped); }
    static bool IsCharFacingChar(Ped ped, Ped otherChar, float angle) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_FACING_CHAR, bool>(ped, otherChar, angle); }
    static bool IsCharFatallyInjured(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_FATALLY_INJURED, bool>(ped); }
    static bool IsCharGesturing(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_GESTURING, bool>(ped); }
    static bool IsCharGettingInToACar(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_GETTING_IN_TO_A_CAR, bool>(ped); }
    static bool IsCharGettingUp(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_GETTING_UP, bool>(ped); }
    static bool IsCharHealthGreater(Ped ped, unsigned int health) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_HEALTH_GREATER, bool>(ped, health); }
    //static bool IsCharInAir(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_AIR, bool>(ped); } 
    static bool IsCharInAngledArea2D(Ped ped, float x1, float y1, float x2, float y2, float unknown, bool unknownFalse) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANGLED_AREA_2D, bool>(ped, x1, y1, x2, y2, unknown, unknownFalse); }
    static bool IsCharInAngledArea3D(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, float unknown, bool unknownFalse) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANGLED_AREA_3D, bool>(ped, x1, y1, z1, x2, y2, z2, unknown, unknownFalse); }
    static bool IsCharInAnyBoat(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANY_BOAT, bool>(ped); }
    //static bool IsCharInAnyCar(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANY_CAR, bool>(ped); }
    static bool IsCharInAnyHeli(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANY_HELI, bool>(ped); }
    static bool IsCharInAnyPlane(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANY_PLANE, bool>(ped); }
    static bool IsCharInAnyPoliceVehicle(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANY_POLICE_VEHICLE, bool>(ped); }
    static bool IsCharInAnyTrain(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_ANY_TRAIN, bool>(ped); }
    static bool IsCharInArea2D(Ped ped, float x1, float y1, float x2, float y2, bool unknownFalse) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_AREA_2D, bool>(ped, x1, y1, x2, y2, unknownFalse); }
    static bool IsCharInArea3D(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, bool unknownFalse) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_AREA_3D, bool>(ped, x1, y1, z1, x2, y2, z2, unknownFalse); }
    static bool IsCharInAreaOnFoot2D(Ped ped, float x1, float y1, float x2, float y2, bool unknownFalse) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_AREA_ON_FOOT_2D, bool>(ped, x1, y1, x2, y2, unknownFalse); }
    static bool IsCharInCar(Ped ped, Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_CAR, bool>(ped, vehicle); }
    static bool IsCharInFlyingVehicle(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_FLYING_VEHICLE, bool>(ped); }
    static bool IsCharInMeleeCombat(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_MELEE_COMBAT, bool>(ped); }
    static bool IsCharInModel(Ped ped, eModel model) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_MODEL, bool>(ped, model); }
    static bool IsCharInTaxi(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_TAXI, bool>(ped); }
    static bool IsCharInWater(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_IN_WATER, bool>(ped); }
    static bool IsCharInjured(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_INJURED, bool>(ped); }
    static bool IsCharMale(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_MALE, bool>(ped); }
    static bool IsCharModel(Ped ped, eModel model) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_MODEL, bool>(ped, model); }
    static bool IsCharOnAnyBike(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_ON_ANY_BIKE, bool>(ped); }
    static bool IsCharOnFire(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_ON_FIRE, bool>(ped); }
    //static bool IsCharOnFoot(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_ON_FOOT, bool>(ped); }
    static bool IsCharOnScreen(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_ON_SCREEN, bool>(ped); }
    static bool IsCharPlayingAnim(Ped ped, char *animSet, char *animName) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_PLAYING_ANIM, bool>(ped, animSet, animName); }
    static bool IsCharShooting(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_SHOOTING, bool>(ped); }
    static bool IsCharShootingInArea(Ped ped, float x1, float y1, float x2, float y2, bool unknownFalse) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_SHOOTING_IN_AREA, bool>(ped, x1, y1, x2, y2, unknownFalse); }
    static bool IsCharSittingIdle(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_SITTING_IDLE, bool>(ped); }
    //static bool IsCharSittingInAnyCar(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_SITTING_IN_ANY_CAR, bool>(ped); }
    static bool IsCharSittingInCar(Ped ped, Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_SITTING_IN_CAR, bool>(ped, vehicle); }
    static bool IsCharStopped(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_STOPPED, bool>(ped); }
    static bool IsCharStuckUnderCar(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_STUCK_UNDER_CAR, bool>(ped); }
    static bool IsCharSwimming(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_SWIMMING, bool>(ped); }
    static bool IsCharTouchingChar(Ped ped, Ped otherChar) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_TOUCHING_CHAR, bool>(ped, otherChar); }
    static bool IsCharTouchingObject(Ped ped, Object obj) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_TOUCHING_OBJECT, bool>(ped, obj); }
    static bool IsCharTouchingObjectOnFoot(Ped ped, Object obj) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_TOUCHING_OBJECT_ON_FOOT, bool>(ped, obj); }
    static bool IsCharTouchingVehicle(ScriptAny p0, ScriptAny p1) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_TOUCHING_VEHICLE, bool>(p0, p1); }
    static bool IsCharTryingToEnterALockedCar(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_TRYING_TO_ENTER_A_LOCKED_CAR, bool>(ped); }
    static bool IsCharUsingAnyScenario(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_USING_ANY_SCENARIO, bool>(ped); }
    static bool IsCharUsingScenario(Ped ped, const char *scenarioName) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_USING_SCENARIO, bool>(ped, scenarioName); }
    static bool IsCharVisible(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_VISIBLE, bool>(ped); }
    static bool IsCharWaitingForWorldCollision(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_CHAR_WAITING_FOR_WORLD_COLLISION, bool>(ped); }
    static bool IsPedAMissionPed(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_A_MISSION_PED, bool>(ped); }
    static bool IsPedAttachedToAnyCar(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_ATTACHED_TO_ANY_CAR, bool>(ped); }
    static bool IsPedAttachedToObject(Ped ped, Object obj) { return NativeInvoke::Invoke<NATIVE_IS_PED_ATTACHED_TO_OBJECT, bool>(ped, obj); }
    static bool IsPedBeingJacked(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_BEING_JACKED, bool>(ped); }
    static bool IsPedDoingDriveby(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_DOING_DRIVEBY, bool>(ped); }
    static bool IsPedFleeing(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_FLEEING, bool>(ped); }
    static bool IsPedHoldingAnObject(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_HOLDING_AN_OBJECT, bool>(ped); }
    static bool IsPedInCombat(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_IN_COMBAT, bool>(ped); }
    static bool IsPedInCover(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_IN_COVER, bool>(ped); }
    static bool IsPedInGroup(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_IN_GROUP, bool>(ped); }
    static bool IsPedJacking(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_JACKING, bool>(ped); }
    static bool IsPedLookingAtPed(Ped ped, Ped otherChar) { return NativeInvoke::Invoke<NATIVE_IS_PED_LOOKING_AT_PED, bool>(ped, otherChar); }
    static bool IsPedRagdoll(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_RAGDOLL, bool>(ped); }
    static bool IsPedRetreating(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_PED_RETREATING, bool>(ped); }
    static bool IsScriptedSpeechPlaying(Ped ped) { return NativeInvoke::Invoke<NATIVE_IS_SCRIPTED_SPEECH_PLAYING, bool>(ped); }
    static void MarkCharAsNoLongerNeeded(Ped *pPed) { NativeInvoke::Invoke<NATIVE_MARK_CHAR_AS_NO_LONGER_NEEDED, ScriptVoid>(pPed); }
    static void ModifyCharMoveState(Ped ped, ePedMoveState state) { NativeInvoke::Invoke<NATIVE_MODIFY_CHAR_MOVE_STATE, ScriptVoid>(ped, state); }
    //static void RemoveAllCharWeapons(Ped ped) { NativeInvoke::Invoke<NATIVE_REMOVE_ALL_CHAR_WEAPONS, ScriptVoid>(ped); }
    static void RemoveCharDefensiveArea(Ped ped) { NativeInvoke::Invoke<NATIVE_REMOVE_CHAR_DEFENSIVE_AREA, ScriptVoid>(ped); }
    static void RemoveCharElegantly(Ped ped) { NativeInvoke::Invoke<NATIVE_REMOVE_CHAR_ELEGANTLY, ScriptVoid>(ped); }
    static void RemoveCharFromGroup(Ped ped) { NativeInvoke::Invoke<NATIVE_REMOVE_CHAR_FROM_GROUP, ScriptVoid>(ped); }
    static void ReviveInjuredPed(Ped ped) { NativeInvoke::Invoke<NATIVE_REVIVE_INJURED_PED, ScriptVoid>(ped); }
    static void SayAmbientSpeech(Ped ped, char *phraseName, ScriptAny unknown0_1, ScriptAny unknown1_1, ScriptAny unknown2_0) { NativeInvoke::Invoke<NATIVE_SAY_AMBIENT_SPEECH, ScriptVoid>(ped, phraseName, unknown0_1, unknown1_1, unknown2_0); }
    static ScriptAny SetAmmoInClip(Ped ped, eWeapon weapon, unsigned int ammo) { return NativeInvoke::Invoke<NATIVE_SET_AMMO_IN_CLIP, ScriptAny>(ped, weapon, ammo); }
    static void SetBlockingOfNonTemporaryEvents(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS, ScriptVoid>(ped, value); }
    static void SetCharAccuracy(Ped ped, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_ACCURACY, ScriptVoid>(ped, value); }
    static void SetCharAmmo(Ped ped, eWeapon weapon, unsigned int ammo) { NativeInvoke::Invoke<NATIVE_SET_CHAR_AMMO, ScriptVoid>(ped, weapon, ammo); }
    static void SetCharAsEnemy(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_AS_ENEMY, ScriptVoid>(ped, value); }
    static void SetCharAsMissionChar(Ped ped) { NativeInvoke::Invoke<NATIVE_SET_CHAR_AS_MISSION_CHAR, ScriptVoid>(ped); }
    static void SetCharCanBeKnockedOffBike(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE, ScriptVoid>(ped, value); }
    static void SetCharCanBeShotInVehicle(Ped ped, bool enabled) { NativeInvoke::Invoke<NATIVE_SET_CHAR_CAN_BE_SHOT_IN_VEHICLE, ScriptVoid>(ped, enabled); }
    static void SetCharCantBeDraggedOut(Ped ped, bool enabled) { NativeInvoke::Invoke<NATIVE_SET_CHAR_CANT_BE_DRAGGED_OUT, ScriptVoid>(ped, enabled); }
    //static void SetCharComponentVariation(Ped ped, ePedComponent component, unsigned int modelVariation, unsigned int textureVariation) { NativeInvoke::Invoke<NATIVE_SET_CHAR_COMPONENT_VARIATION, ScriptVoid>(ped, component, modelVariation, textureVariation); }
    //static void SetCharCoordinates(Ped ped, float x, float y, float z) { NativeInvoke::Invoke<NATIVE_SET_CHAR_COORDINATES, ScriptVoid>(ped, x, y, z); }
    //static void SetCharDefaultComponentVariation(Ped ped) { NativeInvoke::Invoke<NATIVE_SET_CHAR_DEFAULT_COMPONENT_VARIATION, ScriptVoid>(ped); }
    static void SetCharDesiredHeading(Ped ped, float heading) { NativeInvoke::Invoke<NATIVE_SET_CHAR_DESIRED_HEADING, ScriptVoid>(ped, heading); }
    static void SetCharDropsWeaponsWhenDead(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_DROPS_WEAPONS_WHEN_DEAD, ScriptVoid>(ped, value); }
    static void SetCharDruggedUp(Ped ped, bool drugged) { NativeInvoke::Invoke<NATIVE_SET_CHAR_DRUGGED_UP, ScriptVoid>(ped, drugged); }
    static void SetCharFireDamageMultiplier(Ped ped, float multiplier) { NativeInvoke::Invoke<NATIVE_SET_CHAR_FIRE_DAMAGE_MULTIPLIER, ScriptVoid>(ped, multiplier); }
    static void SetCharGravity(Ped ped, float value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_GRAVITY, ScriptVoid>(ped, value); }
    //static void SetCharHeading(Ped ped, float heading) { NativeInvoke::Invoke<NATIVE_SET_CHAR_HEADING, ScriptVoid>(ped, heading); }
    //static void SetCharHealth(Ped ped, unsigned int health) { NativeInvoke::Invoke<NATIVE_SET_CHAR_HEALTH, ScriptVoid>(ped, health); }
    static void SetCharInvincible(Ped ped, bool enable) { NativeInvoke::Invoke<NATIVE_SET_CHAR_INVINCIBLE, ScriptVoid>(ped, enable); }
    static void SetCharIsTargetPriority(Ped ped, bool enable) { NativeInvoke::Invoke<NATIVE_SET_CHAR_IS_TARGET_PRIORITY, ScriptVoid>(ped, enable); }
    static void SetCharMaxHealth(Ped ped, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_MAX_HEALTH, ScriptVoid>(ped, value); }
    //static void SetCharMoney(Ped ped, unsigned int amount) { NativeInvoke::Invoke<NATIVE_SET_CHAR_MONEY, ScriptVoid>(ped, amount); }
    static void SetCharNeverLeavesGroup(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_NEVER_LEAVES_GROUP, ScriptVoid>(ped, value); }
    static void SetCharProofs(Ped ped, bool unknown0, bool fallingDamage, bool unknown1, bool unknown2, bool unknown3) { NativeInvoke::Invoke<NATIVE_SET_CHAR_PROOFS, ScriptVoid>(ped, unknown0, fallingDamage, unknown1, unknown2, unknown3); }
    static void SetCharPropIndex(Ped ped, ePedPropType propType, unsigned int index) { NativeInvoke::Invoke<NATIVE_SET_CHAR_PROP_INDEX, ScriptVoid>(ped, propType, index); }
    static void SetCharRandomComponentVariation(Ped ped) { NativeInvoke::Invoke<NATIVE_SET_CHAR_RANDOM_COMPONENT_VARIATION, ScriptVoid>(ped); }
    static void SetCharSphereDefensiveArea(Ped ped, float x, float y, float z, float radius) { NativeInvoke::Invoke<NATIVE_SET_CHAR_SPHERE_DEFENSIVE_AREA, ScriptVoid>(ped, x, y, z, radius); }
    static void SetCharSuffersCriticalHits(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_SUFFERS_CRITICAL_HITS, ScriptVoid>(ped, value); }
    static void SetCharVelocity(Ped ped, float x, float y, float z) { NativeInvoke::Invoke<NATIVE_SET_CHAR_VELOCITY, ScriptVoid>(ped, x, y, z); }
    static void SetCharVisible(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_VISIBLE, ScriptVoid>(ped, value); }
    static void SetCharWantedByPolice(Ped ped, bool wanted) { NativeInvoke::Invoke<NATIVE_SET_CHAR_WANTED_BY_POLICE, ScriptVoid>(ped, wanted); }
    static void SetCharWillDoDrivebys(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_WILL_DO_DRIVEBYS, ScriptVoid>(ped, value); }
    static void SetCharWillFlyThroughWindscreen(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN, ScriptVoid>(ped, value); }
    static void SetCharWillMoveWhenInjured(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_WILL_MOVE_WHEN_INJURED, ScriptVoid>(ped, value); }
    static void SetCharWillUseCarsInCombat(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_WILL_USE_CARS_IN_COMBAT, ScriptVoid>(ped, value); }
    static void SetCharWillUseCover(Ped ped, CoverPoint coverPoint) { NativeInvoke::Invoke<NATIVE_SET_CHAR_WILL_USE_COVER, ScriptVoid>(ped, coverPoint); }
    //static void SetCurrentCharWeapon(Ped ped, eWeapon w, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_SET_CURRENT_CHAR_WEAPON, ScriptVoid>(ped, w, unknownTrue); }
    static void SetGroupCharDucksWhenAimedAt(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT, ScriptVoid>(ped, value); }
    static void SetIgnoreLowPriorityShockingEvents(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS, ScriptVoid>(ped, value); }
    static void SetPedDiesWhenInjured(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_PED_DIES_WHEN_INJURED, ScriptVoid>(ped, value); }
    static void SetPedIsBlindRaging(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_PED_IS_BLIND_RAGING, ScriptVoid>(ped, value); }
    static void SetPedIsDrunk(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_PED_IS_DRUNK, ScriptVoid>(ped, value); }
    static void SetPedPathMayDropFromHeight(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_PED_PATH_MAY_DROP_FROM_HEIGHT, ScriptVoid>(ped, value); }
    static void SetPedPathMayUseClimbovers(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_PED_PATH_MAY_USE_CLIMBOVERS, ScriptVoid>(ped, value); }
    static void SetPedPathMayUseLadders(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_PED_PATH_MAY_USE_LADDERS, ScriptVoid>(ped, value); }
    //static void SetRoomForCharByKey(Ped ped, eInteriorRoomKey key) { NativeInvoke::Invoke<NATIVE_SET_ROOM_FOR_CHAR_BY_KEY, ScriptVoid>(ped, key); }
    static void SetSenseRange(Ped ped, float value) { NativeInvoke::Invoke<NATIVE_SET_SENSE_RANGE, ScriptVoid>(ped, value); }
    static void SwitchPedToAnimated(Ped ped, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_SWITCH_PED_TO_ANIMATED, ScriptVoid>(ped, unknownTrue); }
    static ScriptAny SwitchPedToRagdoll(Ped ped, ScriptAny p1, ScriptAny p2, ScriptAny p3, ScriptAny p4, ScriptAny p5, ScriptAny p6) { return NativeInvoke::Invoke<NATIVE_SWITCH_PED_TO_RAGDOLL, ScriptAny>(ped, p1, p2, p3, p4, p5, p6); }    
    static void RemovePedHelmet(Ped ped, bool removed) { NativeInvoke::Invoke<NATIVE_REMOVE_PED_HELMET, ScriptVoid>(ped, removed); }
    static void RemoveWeaponFromChar(Ped ped, eWeapon weapon) { NativeInvoke::Invoke<NATIVE_REMOVE_WEAPON_FROM_CHAR, ScriptVoid>(ped, weapon); }
    static void UnlockRagdoll(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_UNLOCK_RAGDOLL, ScriptVoid>(ped, value); }
    static void WarpCharFromCarToCoord(Ped ped, float x, float y, float z) { NativeInvoke::Invoke<NATIVE_WARP_CHAR_FROM_CAR_TO_COORD, ScriptVoid>(ped, x, y, z); }
    static void WarpCharIntoCar(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_WARP_CHAR_INTO_CAR, ScriptVoid>(ped, vehicle); }
    static void WarpCharIntoCarAsPassenger(Ped ped, Vehicle vehicle, unsigned int seatIndex) { NativeInvoke::Invoke<NATIVE_WARP_CHAR_INTO_CAR_AS_PASSENGER, ScriptVoid>(ped, vehicle, seatIndex); }
    static void WarpCharFromCarToCar(Ped ped, Vehicle vehicle, unsigned int seatIndex) { NativeInvoke::Invoke<NATIVE_WARP_CHAR_FROM_CAR_TO_CAR, ScriptVoid>(ped, vehicle, seatIndex); }


    // Ped Tasks


	//static void TaskJump(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_TASK_JUMP, ScriptVoid>(ped, value); }
    //static void TaskToggleDuck(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_TASK_TOGGLE_DUCK, ScriptVoid>(ped, value); }
    //static void TaskAimGunAtCoord(Ped ped, float tX, float tY, float tZ, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_CAR_DRIVE_TO_COORD, ScriptVoid>(ped, tX, tY, tZ, duration); }
    //static void TaskCarDriveToCoord(Ped ped, Vehicle car, float x, float y, float z, float speed, unsigned int p1f_2b, unsigned int p2, unsigned int p3, unsigned int px2, unsigned int p45000) { NativeInvoke::Invoke<NATIVE_TASK_CAR_DRIVE_TO_COORD, ScriptVoid>(ped, car, x, y, z, speed, p1f_2b, p2, p3, px2, p45000); }
	//static void TaskShootAtCoord(Ped ped, float x, float y, float z, unsigned int time_ms, unsigned int type_5) { NativeInvoke::Invoke<NATIVE_TASK_SHOOT_AT_COORD, ScriptVoid>(ped, x, y, z, time_ms, type_5); }

    static void SetCharKeepTask(Ped ped, bool value) { NativeInvoke::Invoke<NATIVE_SET_CHAR_KEEP_TASK, ScriptVoid>(ped, value); }
    static void SetDriveTaskCruiseSpeed(Ped ped, float speed) { NativeInvoke::Invoke<NATIVE_SET_DRIVE_TASK_CRUISE_SPEED, ScriptVoid>(ped, speed); }
    static void TaskAchieveHeading(Ped ped, float heading) { NativeInvoke::Invoke<NATIVE_TASK_ACHIEVE_HEADING, ScriptVoid>(ped, heading); }
    static void TaskAimGunAtChar(Ped ped, Ped targetPed, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_AIM_GUN_AT_CHAR, ScriptVoid>(ped, targetPed, duration); } 
 //   static void TaskAimGunAtCoord(Ped ped, float tX, float tY, float tZ, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_AIM_GUN_AT_COORD, ScriptVoid>(ped, tX, tY, tZ, duration); }
    static void TaskCarDriveWander(Ped ped, Vehicle vehicle, float speed, eVehicleDrivingStyle drivingStyle) { NativeInvoke::Invoke<NATIVE_TASK_CAR_DRIVE_WANDER, ScriptVoid>(ped, vehicle, speed, drivingStyle); }
    static void TaskCarMission(Ped ped, Vehicle vehicle, ScriptHandle targetEntity, unsigned int missionType, float speed, eVehicleDrivingStyle drivingStyle, unsigned int unknown6_10, unsigned int unknown7_5) { NativeInvoke::Invoke<NATIVE_TASK_CAR_MISSION, ScriptVoid>(ped, vehicle, targetEntity, missionType, speed, drivingStyle, unknown6_10, unknown7_5); } // target is whatever missiontype requires (ie. vehicle or just 0). missiontypes: 5=wait(), 21=drivetoplayer()
    static void TaskCarMissionNotAgainstTraffic(Ped ped, Vehicle vehicle, ScriptHandle targetEntity, unsigned int missionType, float speed, eVehicleDrivingStyle  drivingStyle, unsigned int unknown6_10, unsigned int unknown7_5) { NativeInvoke::Invoke<NATIVE_TASK_CAR_MISSION_NOT_AGAINST_TRAFFIC, ScriptVoid>(ped, vehicle, targetEntity, missionType, speed, drivingStyle, unknown6_10, unknown7_5); }
    static void TaskCarMissionCoorsTarget(Ped ped, Vehicle vehicle, float x, float y, float z, unsigned int unknown0_4, float speed, unsigned int unknown2_1, unsigned int unknown3_5, unsigned int unknown4_10) { NativeInvoke::Invoke<NATIVE_TASK_CAR_MISSION_COORS_TARGET, ScriptVoid>(ped, vehicle, x, y, z, unknown0_4, speed, unknown2_1, unknown3_5, unknown4_10); }
    static void TaskCarMissionCoorsTargetNotAgainstTraffic(Ped ped, Vehicle vehicle, float x, float y, float z, unsigned int unknown0_4, float speed, unsigned int unknown2_1, unsigned int unknown3_5, unsigned int unknown4_10) { NativeInvoke::Invoke<NATIVE_TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC, ScriptVoid>(ped, vehicle, x, y, z, unknown0_4, speed, unknown2_1, unknown3_5, unknown4_10); }
    static void TaskCarMissionPedTarget(Ped ped, Vehicle vehicle, Ped target, unsigned int unknown0_4, float speed, unsigned int unknown2_1, unsigned int unknown3_5, unsigned int unknown4_10) { NativeInvoke::Invoke<NATIVE_TASK_CAR_MISSION_PED_TARGET, ScriptVoid>(ped, vehicle, target, unknown0_4, speed, unknown2_1, unknown3_5, unknown4_10); }
    static void TaskCarTempAction(Ped ped, Vehicle vehicle, unsigned int action, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_CAR_TEMP_ACTION, ScriptVoid>(ped, vehicle, action, duration); } // action 6 = wait?
    static void TaskCombat(Ped ped, Ped target) { NativeInvoke::Invoke<NATIVE_TASK_COMBAT, ScriptVoid>(ped, target); }
    static void TaskCombatHatedTargetsAroundChar(Ped ped, float radius) { NativeInvoke::Invoke<NATIVE_TASK_COMBAT_HATED_TARGETS_AROUND_CHAR, ScriptVoid>(ped, radius); }
    static void TaskCombatHatedTargetsAroundCharTimed(Ped ped, float radius, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_COMBAT_HATED_TARGETS_AROUND_CHAR_TIMED, ScriptVoid>(ped, radius, duration); }
    static void TaskCombatTimed(Ped ped, Char target, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_COMBAT_TIMED, ScriptVoid>(ped, target, duration); }
    static void TaskDie(Ped ped) { NativeInvoke::Invoke<NATIVE_TASK_DIE, ScriptVoid>(ped); }
    //static void TaskEnterCarAsDriver(Ped ped, Vehicle vehicle, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_ENTER_CAR_AS_DRIVER, ScriptVoid>(ped, vehicle, duration); }
    //static void TaskEnterCarAsPassenger(Ped ped, Vehicle vehicle, unsigned int duration, unsigned int seatIndex) { NativeInvoke::Invoke<NATIVE_TASK_ENTER_CAR_AS_PASSENGER, ScriptVoid>(ped, vehicle, duration, seatIndex); }
    static void TaskEveryoneLeaveCar(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_TASK_EVERYONE_LEAVE_CAR, ScriptVoid>(vehicle); }
    static void TaskFollowNavMeshToCoord(Ped ped, float x, float y, float z, unsigned int unknown0_2, unsigned int unknown1_minus1, float unknown2_1) { NativeInvoke::Invoke<NATIVE_TASK_FOLLOW_NAV_MESH_TO_COORD, ScriptVoid>(ped, x, y, z, unknown0_2, unknown1_minus1, unknown2_1); }
    static void TaskFollowNavMeshToCoordNoStop(Ped ped, float x, float y, float z,unsigned int unknown0_2, unsigned int unknown1_minus1, float unknown2_1) { NativeInvoke::Invoke<NATIVE_TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP, ScriptVoid>(ped, x, y, z, unknown0_2, unknown1_minus1, unknown2_1); }
    //static void TaskGoStraightToCoord(Ped ped, float x, float y, float z, unsigned int unknown2, unsigned int unknown45000) { NativeInvoke::Invoke<NATIVE_TASK_GO_STRAIGHT_TO_COORD, ScriptVoid>(ped, x, y, z, unknown2, unknown45000); }
    static void TaskGotoCharOffset(Ped ped, Ped target, unsigned int duration, float offsetRight, float offsetFront) { NativeInvoke::Invoke<NATIVE_TASK_GOTO_CHAR_OFFSET, ScriptVoid>(ped, target, duration, offsetRight, offsetFront); }
    static void TaskGuardCurrentPosition(Ped ped, float unknown0_15, float unknown1_10, unsigned int unknown2_1) { NativeInvoke::Invoke<NATIVE_TASK_GUARD_CURRENT_POSITION, ScriptVoid>(ped, unknown0_15, unknown1_10, unknown2_1); }
    static void TaskHandsUp(Ped ped, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_HANDS_UP, ScriptVoid>(ped, duration); }
    static void TaskHeliMission(Ped ped, Vehicle heli, unsigned int uk0_0, unsigned int uk1_0, float pX, float pY, float pZ, unsigned int uk2_4, float speed, unsigned int uk3_5, float uk4_minus1, unsigned int uk5_round_z_plus_1, unsigned int uk6_40) { NativeInvoke::Invoke<NATIVE_TASK_HELI_MISSION, ScriptVoid>(ped, heli, uk0_0, uk1_0, pX, pY, pZ, uk2_4, speed, uk3_5, uk4_minus1, uk5_round_z_plus_1, uk6_40); }
    //static void TaskLeaveAnyCar(Ped ped) { NativeInvoke::Invoke<NATIVE_TASK_LEAVE_ANY_CAR, ScriptVoid>(ped); }
    static void TaskLeaveCar(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_TASK_LEAVE_CAR, ScriptVoid>(ped, vehicle); }
    static void TaskLeaveCarDontCloseDoor(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_TASK_LEAVE_CAR_DONT_CLOSE_DOOR, ScriptVoid>(ped, vehicle); }
    static void TaskLeaveCarImmediately(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_TASK_LEAVE_CAR_IMMEDIATELY, ScriptVoid>(ped, vehicle); }
    static void TaskLookAtChar(Ped ped, Ped targetPed, unsigned int duration, unsigned int unknown_0) { NativeInvoke::Invoke<NATIVE_TASK_LOOK_AT_CHAR, ScriptVoid>(ped, targetPed, duration, unknown_0); }
    static void TaskLookAtCoord(Ped ped, float x, float y, float z, unsigned int duration, unsigned int unknown_0) { NativeInvoke::Invoke<NATIVE_TASK_LOOK_AT_COORD, ScriptVoid>(ped, x, y, z, duration, unknown_0); }
    static void TaskLookAtObject(Ped ped, Object targetObject, unsigned int duration, unsigned int unknown_0) { NativeInvoke::Invoke<NATIVE_TASK_LOOK_AT_OBJECT, ScriptVoid>(ped, targetObject, duration, unknown_0); }
    static void TaskLookAtVehicle(Ped ped, Vehicle targetVehicle, unsigned int duration, unsigned int unknown_0) { NativeInvoke::Invoke<NATIVE_TASK_LOOK_AT_VEHICLE, ScriptVoid>(ped, targetVehicle, duration, unknown_0); }
    static void TaskOpenDriverDoor(Ped ped, Vehicle vehicle, unsigned int unknown0) { NativeInvoke::Invoke<NATIVE_TASK_OPEN_DRIVER_DOOR, ScriptVoid>(ped, vehicle, unknown0); }
    static void TaskOpenPassengerDoor(Ped ped, Vehicle vehicle, unsigned int seatIndex, unsigned int unknown0) { NativeInvoke::Invoke<NATIVE_TASK_OPEN_PASSENGER_DOOR, ScriptVoid>(ped, vehicle, seatIndex, unknown0); }
    static void TaskPause(Ped ped, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_PAUSE, ScriptVoid>(ped, duration); }
    static void TaskPlayAnimWithFlags(Ped ped, const char *animName, const char *animSet, float unknown0_8, unsigned int unknown1_0, unsigned int flags) { NativeInvoke::Invoke<NATIVE_TASK_PLAY_ANIM_WITH_FLAGS, ScriptVoid>(ped, animName, animSet, unknown0_8, unknown1_0, flags); }
    static void TaskSetCharDecisionMaker(Ped ped, DecisionMaker dm) { NativeInvoke::Invoke<NATIVE_TASK_SET_CHAR_DECISION_MAKER, ScriptVoid>(ped, dm); }
    static void TaskSetCombatDecisionMaker(Ped ped, DecisionMaker dm) { NativeInvoke::Invoke<NATIVE_TASK_SET_COMBAT_DECISION_MAKER, ScriptVoid>(ped, dm); }
    static void TaskSmartFleeChar(Ped ped, Ped fleeFromPed, float unknown0_100, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_SMART_FLEE_CHAR, ScriptVoid>(ped, fleeFromPed, unknown0_100, duration); }
    static void TaskSmartFleeCharPreferringPavements(Ped ped, Ped fleeFromPed, float unknown0_100, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_SMART_FLEE_CHAR_PREFERRING_PAVEMENTS, ScriptVoid>(ped, fleeFromPed, unknown0_100, duration); }
    static void TaskSmartFleePoint(Ped ped, float x, float y, float z, float unknown0_100, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_SMART_FLEE_POINT, ScriptVoid>(ped, x, y, x, unknown0_100, duration); }
    static void TaskStandStill(Ped ped, int duration) { NativeInvoke::Invoke<NATIVE_TASK_STAND_STILL, ScriptVoid>(ped, duration); }
    //static void TaskSwapWeapon(Ped ped, eWeapon weapon) { NativeInvoke::Invoke<NATIVE_TASK_SWAP_WEAPON, ScriptVoid>(ped, weapon); }
    static void TaskTurnCharToFaceChar(Ped ped, Ped targetPed) { NativeInvoke::Invoke<NATIVE_TASK_TURN_CHAR_TO_FACE_CHAR, ScriptVoid>(ped, targetPed); }
    static void TaskTurnCharToFaceCoord(Ped ped, float x, float y, float z) { NativeInvoke::Invoke<NATIVE_TASK_TURN_CHAR_TO_FACE_COORD, ScriptVoid>(ped, x, y, z); }
    static void TaskUseMobilePhone(Ped ped, bool use) { NativeInvoke::Invoke<NATIVE_TASK_USE_MOBILE_PHONE, ScriptVoid>(ped, use); }
    static void TaskUseMobilePhoneTimed(Ped ped, unsigned int duration) { NativeInvoke::Invoke<NATIVE_TASK_USE_MOBILE_PHONE_TIMED, ScriptVoid>(ped, duration); }
    static void TaskWanderStandard(Ped ped) { NativeInvoke::Invoke<NATIVE_TASK_WANDER_STANDARD, ScriptVoid>(ped); }
    static void TaskWarpCharIntoCarAsDriver(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_TASK_WARP_CHAR_INTO_CAR_AS_DRIVER, ScriptVoid>(ped, vehicle); }
    static void TaskWarpCharIntoCarAsPassenger(Ped ped, Vehicle vehicle, unsigned int seatIndex) { NativeInvoke::Invoke<NATIVE_TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER, ScriptVoid>(ped, vehicle, seatIndex); }

    // Task Sequence
    static void OpenSequenceTask(TaskSequence *pTaskSequence) { NativeInvoke::Invoke<NATIVE_OPEN_SEQUENCE_TASK, ScriptVoid>(pTaskSequence); }
    //static void CloseSequenceTask(TaskSequence taskSequence) { NativeInvoke::Invoke<NATIVE_CLOSE_SEQUENCE_TASK, ScriptVoid>(taskSequence); }
    static void TaskPerformSequence(Ped ped, TaskSequence taskSequence) { NativeInvoke::Invoke<NATIVE_TASK_PERFORM_SEQUENCE, ScriptVoid>(ped, taskSequence); }
    static void ClearSequenceTask(TaskSequence taskSequence) { NativeInvoke::Invoke<NATIVE_CLEAR_SEQUENCE_TASK, ScriptVoid>(taskSequence); }

    // Ped Search
    static void AllowScenarioPedsToBeReturnedByNextCommand(bool value) { NativeInvoke::Invoke<NATIVE_ALLOW_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND, ScriptVoid>(value); }
    static void BeginCharSearchCriteria() { NativeInvoke::Invoke<NATIVE_BEGIN_CHAR_SEARCH_CRITERIA, ScriptVoid>(); }
    static void EndCharSearchCriteria() { NativeInvoke::Invoke<NATIVE_END_CHAR_SEARCH_CRITERIA, ScriptVoid>(); }
    static bool GetClosestChar(float x, float y, float z, float radius, unsigned int unknown1, unsigned int unknown2, Ped *pPed) { return NativeInvoke::Invoke<NATIVE_GET_CLOSEST_CHAR, bool>(x, y, z, radius, unknown1, unknown2, pPed); }
    static void GetRandomCharInAreaOffsetNoSave(float x, float y, float z, float sx, float sy, float sz, Ped *pPed) { NativeInvoke::Invoke<NATIVE_GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE, ScriptVoid>(x, y, z, sx, sy, sz, pPed); }
    static void SearchCriteriaConsiderPedsWithFlagTrue(unsigned int flagId) { NativeInvoke::Invoke<NATIVE_SEARCH_CRITERIA_CONSIDER_PEDS_WITH_FLAG_TRUE, ScriptVoid>(flagId); }
    static void SearchCriteriaRejectPedsWithFlagTrue(unsigned int flagId) { NativeInvoke::Invoke<NATIVE_SEARCH_CRITERIA_REJECT_PEDS_WITH_FLAG_TRUE, ScriptVoid>(flagId); }

    // Ped Groups
    static void CreateGroup(bool unknownFalse, Group *pGroup, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_CREATE_GROUP, ScriptVoid>(unknownFalse, pGroup, unknownTrue); }
    static bool DoesGroupExist(Group group) { return NativeInvoke::Invoke<NATIVE_DOES_GROUP_EXIST, bool>(group); }
    static void GetGroupLeader(Group group, Ped *pPed) { NativeInvoke::Invoke<NATIVE_GET_GROUP_LEADER, ScriptVoid>(group, pPed); }
    static void GetGroupMember(Group group, unsigned int index, Ped *pPed) { NativeInvoke::Invoke<NATIVE_GET_GROUP_MEMBER, ScriptVoid>(group, index, pPed); }
    static void GetGroupSize(Group group, unsigned int *pStartIndex, unsigned int *pCount) { NativeInvoke::Invoke<NATIVE_GET_GROUP_SIZE, ScriptVoid>(group, pStartIndex, pCount); }
    static bool IsGroupLeader(Ped ped, Group group) { return NativeInvoke::Invoke<NATIVE_IS_GROUP_LEADER, bool>(ped, group); }
    static bool IsGroupMember(Ped ped, Group g) { return NativeInvoke::Invoke<NATIVE_IS_GROUP_MEMBER, bool>(ped, g); }
    static void RemoveGroup(Group group) { NativeInvoke::Invoke<NATIVE_REMOVE_GROUP, ScriptVoid>(group); }
    static void SetGroupFollowStatus(Group group, unsigned int status) { NativeInvoke::Invoke<NATIVE_SET_GROUP_FOLLOW_STATUS, ScriptVoid>(group, status); }
    static void SetGroupFormation(Group group, unsigned int formation) { NativeInvoke::Invoke<NATIVE_SET_GROUP_FORMATION, ScriptVoid>(group, formation); }
    static void SetGroupFormationSpacing(Group group, float space) { NativeInvoke::Invoke<NATIVE_SET_GROUP_FORMATION_SPACING, ScriptVoid>(group, space); }
    static void SetGroupLeader(Group group, Ped leader) { NativeInvoke::Invoke<NATIVE_SET_GROUP_LEADER, ScriptVoid>(group, leader); }
    static void SetGroupMember(Group group, Ped member) { NativeInvoke::Invoke<NATIVE_SET_GROUP_MEMBER, ScriptVoid>(group, member); }
    static void SetGroupSeparationRange(Group group, float seperation) { NativeInvoke::Invoke<NATIVE_SET_GROUP_SEPARATION_RANGE, ScriptVoid>(group, seperation); }

    // Ped Relationships
    static void AllowGangRelationshipsToBeChangedByNextCommand(bool value) { NativeInvoke::Invoke<NATIVE_ALLOW_GANG_RELATIONSHIPS_TO_BE_CHANGED_BY_NEXT_COMMAND, ScriptVoid>(value); }
    static void SetCharNotDamagedByRelationshipGroup(Ped ped, unsigned int relationshipGroup, bool enable) { NativeInvoke::Invoke<NATIVE_SET_CHAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP, ScriptVoid>(ped, relationshipGroup, enable); }
    static void SetCharRelationship(Ped ped, unsigned int relationshipLevel, unsigned int relationshipGroup) { NativeInvoke::Invoke<NATIVE_SET_CHAR_RELATIONSHIP, ScriptVoid>(ped, relationshipLevel, relationshipGroup); }
    static void SetCharRelationshipGroup(Ped ped, unsigned int relationshipGroup) { NativeInvoke::Invoke<NATIVE_SET_CHAR_RELATIONSHIP_GROUP, ScriptVoid>(ped, relationshipGroup); }
    static void SetRelationship(unsigned int relationshipLevel, unsigned int relationshipGroup1, unsigned int relationshipGroup2) { NativeInvoke::Invoke<NATIVE_SET_RELATIONSHIP, ScriptVoid>(relationshipLevel, relationshipGroup1, relationshipGroup2); }

    // Vehicle
    static void AddUpsideDownCarCheck(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_ADD_UPSIDEDOWN_CAR_CHECK, ScriptVoid>(vehicle); }
    static void AnchorBoat(Vehicle boat, bool anchor) { NativeInvoke::Invoke<NATIVE_ANCHOR_BOAT, ScriptVoid>(boat, anchor); }
    static void ApplyForceToCar(Vehicle vehicle, unsigned int unknown0_3, float x, float y, float z, float spinX, float spinY, float spinZ, unsigned int unknown4_0, unsigned int unknown5_1, unsigned int unknown6_1, unsigned int unknown7_1) { NativeInvoke::Invoke<NATIVE_APPLY_FORCE_TO_CAR, ScriptVoid>(vehicle, unknown0_3, x, y, z, spinX, spinY, spinZ, unknown4_0, unknown5_1, unknown6_1, unknown7_1); }
    static bool AreTaxiLightsOn(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_ARE_TAXI_LIGHTS_ON, bool>(vehicle); }
    static void BreakCarDoor(Vehicle vehicle, eVehicleDoor door, bool unknownFalse) { NativeInvoke::Invoke<NATIVE_BREAK_CAR_DOOR, ScriptVoid>(vehicle, door, unknownFalse); }
    static void BurstCarTyre(Vehicle vehicle, eVehicleTyre tyre) { NativeInvoke::Invoke<NATIVE_BURST_CAR_TYRE, ScriptVoid>(vehicle, tyre); }
    //static void CreateCar(unsigned int nameHash, float x, float y, float z, Vehicle *pVehicle, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_CREATE_CAR, ScriptVoid>(nameHash, x, y, z, pVehicle, unknownTrue); }
    static void CreateCharAsPassenger(Vehicle vehicle, ePedType charType, eModel model, unsigned int passengerIndex, Ped *pPed) { NativeInvoke::Invoke<NATIVE_CREATE_CHAR_AS_PASSENGER, ScriptVoid>(vehicle, charType, model, passengerIndex, pPed); }
    static void CreateCharInsideCar(Vehicle vehicle, ePedType charType, eModel model, Ped *pPed) { NativeInvoke::Invoke<NATIVE_CREATE_CHAR_INSIDE_CAR, ScriptVoid>(vehicle, charType, model, pPed); }
    static void ChangeCarColour(Vehicle vehicle, ColourIndex colour1, ColourIndex colour2) { NativeInvoke::Invoke<NATIVE_CHANGE_CAR_COLOUR, ScriptVoid>(vehicle, colour1, colour2); }
    static void ClearCarLastDamageEntity(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_CLEAR_CAR_LAST_DAMAGE_ENTITY, ScriptVoid>(vehicle); }
    static void ClearCarLastWeaponDamage(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_CLEAR_CAR_LAST_WEAPON_DAMAGE, ScriptVoid>(vehicle); }
    static void ClearRoomForCar(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_CLEAR_ROOM_FOR_CAR, ScriptVoid>(vehicle); }
    static void CloseAllCarDoors(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_CLOSE_ALL_CAR_DOORS, ScriptVoid>(vehicle); }
    static void ControlCarDoor(Vehicle vehicle, eVehicleDoor door, unsigned int unknown_maybe_open, float angle) { NativeInvoke::Invoke<NATIVE_CONTROL_CAR_DOOR, ScriptVoid>(vehicle, door, unknown_maybe_open, angle); }
	//static bool CreateEmergencyServicesCar(eModel model, float x, float y, float z) { return NativeInvoke::Invoke<NATIVE_CREATE_EMERGENCY_SERVICES_CAR, bool>(model, x, y, z); }
    static void CreateRandomCharAsPassenger(Vehicle vehicle, unsigned int seat, Ped *pPed) { NativeInvoke::Invoke<NATIVE_CREATE_RANDOM_CHAR_AS_PASSENGER, ScriptVoid>(vehicle, seat, pPed); }
    static void DeleteCar(Vehicle *pVehicle) { NativeInvoke::Invoke<NATIVE_DELETE_CAR, ScriptVoid>(pVehicle); }
    static void DetachCar(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_DETACH_CAR, ScriptVoid>(vehicle); }
    static bool DoesCarHaveRoof(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_DOES_CAR_HAVE_ROOF, bool>(vehicle); }
    static bool DoesCarHaveStuckCarCheck(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_DOES_CAR_HAVE_STUCK_CAR_CHECK, bool>(vehicle); }
    //static bool DoesVehicleExist(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_DOES_VEHICLE_EXIST, bool>(vehicle); }
    static void EnablePedHelmet(Ped ped, bool enable) { NativeInvoke::Invoke<NATIVE_ENABLE_PED_HELMET, ScriptVoid>(ped, enable); }
    static void ExplodeCar(Vehicle vehicle, bool unknownTrue, bool unknownFalse) { NativeInvoke::Invoke<NATIVE_EXPLODE_CAR, ScriptVoid>(vehicle, unknownTrue, unknownFalse); }
    static void ExtinguishCarFire(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_EXTINGUISH_CAR_FIRE, ScriptVoid>(vehicle); }
    static void FixCar(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_FIX_CAR, ScriptVoid>(vehicle); }
    static void FixCarTyre(Vehicle vehicle, eVehicleTyre tyre) { NativeInvoke::Invoke<NATIVE_FIX_CAR_TYRE, ScriptVoid>(vehicle, tyre); }
    static void ForceVehicleLights(Vehicle vehicle, eVehicleLights lights) { NativeInvoke::Invoke<NATIVE_FORCE_CAR_LIGHTS, ScriptVoid>(vehicle, lights); }
    static void FreezeCarPosition(Vehicle vehicle, bool frozen) { NativeInvoke::Invoke<NATIVE_FREEZE_CAR_POSITION, ScriptVoid>(vehicle, frozen); }
    static void FreezeCarPositionAndDontLoadCollision(Vehicle vehicle, bool frozen) { NativeInvoke::Invoke<NATIVE_FREEZE_CAR_POSITION_AND_DONT_LOAD_COLLISION, ScriptVoid>(vehicle, frozen); }
    //static void GetCarCharIsUsing(Ped ped, Vehicle *pVehicle) { NativeInvoke::Invoke<NATIVE_GET_CAR_CHAR_IS_USING, ScriptVoid>(ped, pVehicle); }
    static void GetCarColours(Vehicle vehicle, ColourIndex *pColour1, ColourIndex *pColour2) { NativeInvoke::Invoke<NATIVE_GET_CAR_COLOURS, ScriptVoid>(vehicle, pColour1, pColour2); }
    //static void GetCarCoordinates(Vehicle vehicle, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_CAR_COORDINATES, ScriptVoid>(vehicle, pX, pY, pZ); }
    static void GetCarDeformationAtPos(Vehicle vehicle, float x, float y, float z, Vector3 *pDeformation) { NativeInvoke::Invoke<NATIVE_GET_CAR_DEFORMATION_AT_POS, ScriptVoid>(vehicle, x, y, z, pDeformation); }
    static void GetCarDoorLockStatus(Vehicle vehicle, eVehicleDoorLock *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_DOOR_LOCK_STATUS, ScriptVoid>(vehicle, pValue); }
    static void GetCarForwardX(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_FORWARD_X, ScriptVoid>(vehicle, pValue); }
    static void GetCarForwardY(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_FORWARD_Y, ScriptVoid>(vehicle, pValue); }
    //static void GetCarHeading(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_HEADING, ScriptVoid>(vehicle, pValue); }
    static void GetCarHealth(Vehicle vehicle, unsigned int *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_HEALTH, ScriptVoid>(vehicle, pValue); }
    static void GetCarModel(Vehicle vehicle, eModel *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_MODEL, ScriptVoid>(vehicle, pValue); }
    static void GetCarPitch(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_PITCH, ScriptVoid>(vehicle, pValue); }
    static void GetCarRoll(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_ROLL, ScriptVoid>(vehicle, pValue); }
    //static void GetCarSpeed(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_SPEED, ScriptVoid>(vehicle, pValue); }
    //static void GetCarSpeedVector(Vehicle vehicle, Vector3 *pVector, bool unknownFalse) { NativeInvoke::Invoke<NATIVE_GET_CAR_SPEED_VECTOR, ScriptVoid>(vehicle, pVector, unknownFalse); }
    static void GetCarUprightValue(Vehicle vehicle, float *pValue) { NativeInvoke::Invoke<NATIVE_GET_CAR_UPRIGHT_VALUE, ScriptVoid>(vehicle, pValue); }
    static void GetCharInCarPassengerSeat(Vehicle vehicle, unsigned int seatIndex, Ped *pPed) { NativeInvoke::Invoke<NATIVE_GET_CHAR_IN_CAR_PASSENGER_SEAT, ScriptVoid>(vehicle, seatIndex, pPed); }
    static Vehicle GetClosestCar(float x, float y, float z, float radius, unsigned int unknown0_0, unsigned int unknown1_70) { return NativeInvoke::Invoke<NATIVE_GET_CLOSEST_CAR, Vehicle>(x, y, z, radius, unknown0_0, unknown1_70); }
    static bool GetClosestCarNode(float x, float y, float z, float *pResX, float *pResY, float *pResZ) { return NativeInvoke::Invoke<NATIVE_GET_CLOSEST_CAR_NODE, bool>(x, y, z, pResX, pResY, pResZ); }
    static bool GetClosestCarNodeWithHeading(float x, float y, float z, float *pResX, float *pResY, float *pResZ, float *pHeading) { return NativeInvoke::Invoke<NATIVE_GET_CLOSEST_CAR_NODE_WITH_HEADING, bool>(x, y, z, pResX, pResY, pResZ, pHeading); }
    static bool GetClosestMajorCarNode(float x, float y, float z, float *pResX, float *pResY, float *pResZ) { return NativeInvoke::Invoke<NATIVE_GET_CLOSEST_MAJOR_CAR_NODE, bool>(x, y, z, pResX, pResY, pResZ); }
    static bool GetNthClosestCarNodeWithHeading(float x, float y, float z, unsigned int nodeNum,  float *pResX, float *pResY, float *pResZ, float *pHeading) { return NativeInvoke::Invoke<NATIVE_GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING, bool>(x, y, z, nodeNum, pResX, pResY, pResZ, pHeading); }
    static bool GetNthClosestCarNodeWithHeadingOnIsland(float x, float y, float z, unsigned int nodeNum, unsigned int areaId, float *pResX, float *pResY, float *pResZ, float *pHeading, unsigned int *pUnknownMaybeAreaId) { return NativeInvoke::Invoke<NATIVE_GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND, bool>(x, y, z, nodeNum, areaId, pResX, pResY, pResZ, pHeading, pUnknownMaybeAreaId); }
    static void GetDeadCarCoordinates(Vehicle vehicle, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_DEAD_CAR_COORDINATES, ScriptVoid>(vehicle, pX, pY, pZ); }
    static void GetDoorAngleRatio(Vehicle vehicle, eVehicleDoor door, float *pAngleRatio) { NativeInvoke::Invoke<NATIVE_GET_DOOR_ANGLE_RATIO, ScriptVoid>(vehicle, door, pAngleRatio); }
    static void GetDriverOfCar(Vehicle vehicle, Ped *pPed) { NativeInvoke::Invoke<NATIVE_GET_DRIVER_OF_CAR, ScriptVoid>(vehicle, pPed); }
    static float GetEngineHealth(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_GET_ENGINE_HEALTH, float>(vehicle); }
    static void GetExtraCarColours(Vehicle vehicle, ColourIndex *pColour1, ColourIndex *pColour2) { NativeInvoke::Invoke<NATIVE_GET_EXTRA_CAR_COLOURS, ScriptVoid>(vehicle, pColour1, pColour2); }
    static float GetHeightOfVehicle(Vehicle vehicle, float x, float y, float z, bool unknownTrue1, bool unknownTrue2) { return NativeInvoke::Invoke<NATIVE_GET_HEIGHT_OF_VEHICLE, float>(vehicle, x, y, z, unknownTrue1, unknownTrue2); }
    static void GetKeyForCarInRoom(Vehicle vehicle, unsigned int *pKey) { NativeInvoke::Invoke<NATIVE_GET_KEY_FOR_CAR_IN_ROOM, ScriptVoid>(vehicle, pKey); }
    //static void GetMaximumNumberOfPassengers(Vehicle vehicle, unsigned int *pMax) { NativeInvoke::Invoke<NATIVE_GET_MAXIMUM_NUMBER_OF_PASSENGERS, ScriptVoid>(vehicle, pMax); }
    static void GetNearestCableCar(float x, float y, float z, float radius, Vehicle *pVehicle) { NativeInvoke::Invoke<NATIVE_GET_NEAREST_CABLE_CAR, ScriptVoid>(x, y, z, radius, pVehicle); }
    static void GetNumCarColours(Vehicle vehicle, unsigned int *pNumColours) { NativeInvoke::Invoke<NATIVE_GET_NUM_CAR_COLOURS, ScriptVoid>(vehicle, pNumColours); }
    static void GetNumberOfPassengers(Vehicle vehicle, unsigned int *pNumPassengers) { NativeInvoke::Invoke<NATIVE_GET_NUMBER_OF_PASSENGERS, ScriptVoid>(vehicle, pNumPassengers); }
    static void GetOffsetFromCarGivenWorldCoords(Vehicle vehicle, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ) { NativeInvoke::Invoke<NATIVE_GET_OFFSET_FROM_CAR_GIVEN_WORLD_COORDS, ScriptVoid>(vehicle, x, y, z, pOffX, pOffY, pOffZ); }
    static void GetOffsetFromCarInWorldCoords(Vehicle vehicle, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ) { NativeInvoke::Invoke<NATIVE_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS, ScriptVoid>(vehicle, x, y, z, pOffX, pOffY, pOffZ); }
    static float GetPetrolTankHealth(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_GET_PETROL_TANK_HEALTH, float>(vehicle); }
    static void GetRandomCarModelInMemory(bool unknownTrue, unsigned int *pHash, ScriptAny *pUnknown) { NativeInvoke::Invoke<NATIVE_GET_RANDOM_CAR_MODEL_IN_MEMORY, ScriptVoid>(unknownTrue, pHash, pUnknown); }
    static void GetVehicleDirtLevel(Vehicle vehicle, float* pIntensity) { NativeInvoke::Invoke<NATIVE_GET_VEHICLE_DIRT_LEVEL, ScriptVoid>(vehicle, pIntensity); }
    static bool HasCarBeenDamagedByCar(Vehicle vehicle, Vehicle otherCar) { return NativeInvoke::Invoke<NATIVE_HAS_CAR_BEEN_DAMAGED_BY_CAR, bool>(vehicle, otherCar); }
    static bool HasCarBeenDamagedByChar(Vehicle vehicle, Ped ped) { return NativeInvoke::Invoke<NATIVE_HAS_CAR_BEEN_DAMAGED_BY_CHAR, bool>(vehicle, ped); }
    static bool HasCarBeenDamagedByWeapon(Vehicle vehicle, eWeapon weapon) { return NativeInvoke::Invoke<NATIVE_HAS_CAR_BEEN_DAMAGED_BY_WEAPON, bool>(vehicle, weapon); }
    static bool HasCarBeenResprayed(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_HAS_CAR_BEEN_RESPRAYED, bool>(vehicle); }
    static bool IsBigVehicle(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_BIG_VEHICLE, bool>(vehicle); }
    static bool IsCarAMissionCar(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_A_MISSION_CAR, bool>(vehicle); }
    static bool IsCarAttached(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_ATTACHED, bool>(vehicle); }
    static bool IsCarDead(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_DEAD, bool>(vehicle); }
    static bool IsCarDoorDamaged(Vehicle vehicle, eVehicleDoor door) { return NativeInvoke::Invoke<NATIVE_IS_CAR_DOOR_DAMAGED, bool>(vehicle, door); }
    static bool IsCarDoorFullyOpen(Vehicle vehicle, eVehicleDoor door) { return NativeInvoke::Invoke<NATIVE_IS_CAR_DOOR_FULLY_OPEN, bool>(vehicle, door); }
    static bool IsCarInAirProper(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_IN_AIR_PROPER, bool>(vehicle); }
    static bool IsCarInArea2D(Vehicle vehicle, float x1, float y1, float x2, float y2, bool unknownFalse) { return NativeInvoke::Invoke<NATIVE_IS_CAR_IN_AREA_2D, bool>(vehicle, x1, y1, x2, y2, unknownFalse); }
    static bool IsCarInArea3D(Vehicle vehicle, float x1, float y1, float z1, float x2, float y2, float z2, unsigned char unknownFalse) { return NativeInvoke::Invoke<NATIVE_IS_CAR_IN_AREA_3D, bool>(vehicle, x1, y1, z1, x2, y2, z2, unknownFalse); }
    static bool IsCarInWater(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_IN_WATER, bool>(vehicle); }
    static bool IsCarModel(Vehicle vehicle, eModel model) { return NativeInvoke::Invoke<NATIVE_IS_CAR_MODEL, bool>(vehicle, model); }
    static bool IsCarOnFire(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_ON_FIRE, bool>(vehicle); }
    static bool IsCarOnScreen(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_ON_SCREEN, bool>(vehicle); }
    static bool IsCarPassengerSeatFree(Vehicle vehicle, unsigned int seatIndex) { return NativeInvoke::Invoke<NATIVE_IS_CAR_PASSENGER_SEAT_FREE, bool>(vehicle, seatIndex); }
    static bool IsCarSirenOn(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_SIREN_ON, bool>(vehicle); }
    //static bool IsCarStopped(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_STOPPED, bool>(vehicle); }
    static bool IsCarStoppedAtTrafficLights(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_STOPPED_AT_TRAFFIC_LIGHTS, bool>(vehicle); }
    static bool IsCarStuckOnRoof(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_STUCK_ON_ROOF, bool>(vehicle); }
    static bool IsCarTouchingCar(Vehicle vehicle, Vehicle otherCar) { return NativeInvoke::Invoke<NATIVE_IS_CAR_TOUCHING_CAR, bool>(vehicle, otherCar); }
    static bool IsCarTyreBurst(Vehicle vehicle, eVehicleTyre tyre) { return NativeInvoke::Invoke<NATIVE_IS_CAR_TYRE_BURST, bool>(vehicle, tyre); }
    static bool IsCarUpright(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_UPRIGHT, bool>(vehicle); }
    static bool IsCarUpsidedown(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_UPSIDEDOWN, bool>(vehicle); }
    static bool IsCarWaitingForWorldCollision(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_WAITING_FOR_WORLD_COLLISION, bool>(vehicle); }
    static bool IsVehDriveable(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_VEH_DRIVEABLE, bool>(vehicle); }
    static bool IsVehWindowIntact(Vehicle vehicle, eVehicleWindow window) { return NativeInvoke::Invoke<NATIVE_IS_VEH_WINDOW_INTACT, bool>(vehicle, window); }
    static bool IsVehicleExtraTurnedOn(Vehicle vehicle, eVehicleExtra extra) { return NativeInvoke::Invoke<NATIVE_IS_VEHICLE_EXTRA_TURNED_ON, bool>(vehicle, extra); }
    static bool IsVehicleOnAllWheels(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_VEHICLE_ON_ALL_WHEELS, bool>(vehicle); }
    static void KnockPedOffBike(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_KNOCK_PED_OFF_BIKE, ScriptVoid>(vehicle); }
    static void LockCarDoors(Vehicle vehicle, eVehicleDoorLock value) { NativeInvoke::Invoke<NATIVE_LOCK_CAR_DOORS, ScriptVoid>(vehicle, value); }
    static void MarkCarAsConvoyCar(Vehicle vehicle, bool convoyCar) { NativeInvoke::Invoke<NATIVE_MARK_CAR_AS_CONVOY_CAR, ScriptVoid>(vehicle, convoyCar); }
    static void MarkCarAsNoLongerNeeded(Vehicle *pVehicle) { NativeInvoke::Invoke<NATIVE_MARK_CAR_AS_NO_LONGER_NEEDED, ScriptVoid>(pVehicle); }
    static void OpenCarDoor(Vehicle vehicle, eVehicleDoor door) { NativeInvoke::Invoke<NATIVE_OPEN_CAR_DOOR, ScriptVoid>(vehicle, door); }
    static void PopCarBoot(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_POP_CAR_BOOT, ScriptVoid>(vehicle); }
    static void RemoveVehicleWindow(Vehicle vehicle, eVehicleWindow window) { NativeInvoke::Invoke<NATIVE_REMOVE_CAR_WINDOW, ScriptVoid>(vehicle, window); }
    static void RemoveStuckCarCheck(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_REMOVE_STUCK_CAR_CHECK, ScriptVoid>(vehicle); }
    static void RemoveUpsidedownCarCheck(Vehicle vehicle) { NativeInvoke::Invoke<NATIVE_REMOVE_UPSIDEDOWN_CAR_CHECK, ScriptVoid>(vehicle); }
    static void SetCarCoordinates(Vehicle vehicle, float pX, float pY, float pZ) { NativeInvoke::Invoke<NATIVE_SET_CAR_COORDINATES, ScriptVoid>(vehicle, pX, pY, pZ); }
    static void SetCarHealth(Vehicle vehicle, unsigned int pValue) { NativeInvoke::Invoke<NATIVE_SET_CAR_HEALTH, ScriptVoid>(vehicle, pValue); }
    static void SetPetrolTankHealth(Vehicle vehicle, float value) { NativeInvoke::Invoke<NATIVE_SET_PETROL_TANK_HEALTH, ScriptVoid>(vehicle, value); }
    static void SetCarCanBeDamaged(Vehicle vehicle, bool value) { NativeInvoke::Invoke<NATIVE_SET_CAR_CAN_BE_DAMAGED, ScriptVoid>(vehicle, value); }
    static void SetCarCanBeVisiblyDamaged(Vehicle vehicle, bool value) { NativeInvoke::Invoke<NATIVE_SET_CAR_CAN_BE_VISIBLY_DAMAGED, ScriptVoid>(vehicle, value); }
    static void SetCarForwardSpeed(Vehicle vehicle, float speed) { NativeInvoke::Invoke<NATIVE_SET_CAR_FORWARD_SPEED, ScriptVoid>(vehicle, speed); }
    //static void SetCarHeading(Vehicle vehicle, float dir) { NativeInvoke::Invoke<NATIVE_SET_CAR_HEADING, ScriptVoid>(vehicle, dir); }
    static ScriptAny SetCarOnGroundProperly(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_SET_CAR_ON_GROUND_PROPERLY, ScriptAny>(vehicle); }
    static void SetCarProofs(Vehicle vehicle, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof) { NativeInvoke::Invoke<NATIVE_SET_CAR_PROOFS, ScriptVoid>(vehicle, bulletProof, fireProof, explosionProof, collisionProof, meleeProof); }
    static void SetCarStrong(Vehicle vehicle, bool strong) { NativeInvoke::Invoke<NATIVE_SET_CAR_STRONG, ScriptVoid>(vehicle, strong); }
    static void SetCarVisible(Vehicle vehicle, bool value) { NativeInvoke::Invoke<NATIVE_SET_CAR_VISIBLE, ScriptVoid>(vehicle, value); }
    static void SetExtraCarColours(Vehicle vehicle, ColourIndex colour1, ColourIndex colour2) { NativeInvoke::Invoke<NATIVE_SET_EXTRA_CAR_COLOURS, ScriptVoid>(vehicle, colour1, colour2); }
    static void SetEngineHealth(Vehicle vehicle, float health) { NativeInvoke::Invoke<NATIVE_SET_ENGINE_HEALTH, ScriptVoid>(vehicle, health); }
    static void SetVehHazardLights(Vehicle vehicle, bool on) { NativeInvoke::Invoke<NATIVE_SET_VEH_HAZARDLIGHTS, ScriptVoid>(vehicle, on); }
    static void SetVehicleDirtLevel(Vehicle vehicle, float intensity) { NativeInvoke::Invoke<NATIVE_SET_VEHICLE_DIRT_LEVEL, ScriptVoid>(vehicle, intensity); }
    static void ShutCarDoor(Vehicle vehicle, eVehicleDoor door) { NativeInvoke::Invoke<NATIVE_SHUT_CAR_DOOR, ScriptVoid>(vehicle, door); }
    static void SoundCarHorn(Vehicle vehicle, unsigned int duration) { NativeInvoke::Invoke<NATIVE_SOUND_CAR_HORN, ScriptVoid>(vehicle, duration); }
    static void WashVehicleTextures(Vehicle vehicle, unsigned int intensity) { NativeInvoke::Invoke<NATIVE_WASH_VEHICLE_TEXTURES, ScriptVoid>(vehicle, intensity); }
    static void GetVehicleQuaternion(Vehicle vehicle, float *pX, float *pY, float *pZ, float *scal) { NativeInvoke::Invoke<NATIVE_GET_VEHICLE_QUATERNION, ScriptVoid>(vehicle, pX, pY, pZ, scal); }
    static void SetVehicleQuaternion(Vehicle vehicle, float pX, float pY, float pZ, float scal) { NativeInvoke::Invoke<NATIVE_SET_VEHICLE_QUATERNION, ScriptVoid>(vehicle, pX, pY, pZ, scal); }
	static void SwitchCarSiren(Vehicle vehicle, bool siren) { NativeInvoke::Invoke<NATIVE_SWITCH_CAR_SIREN, ScriptVoid>(vehicle, siren); }

    // Train
    static void CreateMissionTrain(unsigned int unknown1, float x, float y, float z, bool unknown2, Train *pTrain) { NativeInvoke::Invoke<NATIVE_CREATE_MISSION_TRAIN, ScriptVoid>(unknown1, x, y, z, unknown2, pTrain); }
    static void DeleteMissionTrain(Train *pTrain) { NativeInvoke::Invoke<NATIVE_DELETE_MISSION_TRAIN, ScriptVoid>(pTrain); }
    static eTrainStation GetCurrentStationForTrain(Train train) { return NativeInvoke::Invoke<NATIVE_GET_CURRENT_STATION_FOR_TRAIN, eTrainStation>(train); }
    static eTrainStation GetNextStationForTrain(Train train) { return NativeInvoke::Invoke<NATIVE_GET_NEXT_STATION_FOR_TRAIN, eTrainStation>(train); }
    static const char *GetStationName(Train train, eTrainStation station) { return NativeInvoke::Invoke<NATIVE_GET_STATION_NAME, const char *>(train, station); }
    static void MarkMissionTrainAsNoLongerNeeded(Train train) { NativeInvoke::Invoke<NATIVE_MARK_MISSION_TRAIN_AS_NO_LONGER_NEEDED, ScriptVoid>(train); }
    static void MarkMissionTrainsAsNoLongerNeeded() { NativeInvoke::Invoke<NATIVE_MARK_MISSION_TRAINS_AS_NO_LONGER_NEEDED, ScriptVoid>(); }

    // Object
    static void AddObjectToInteriorRoomByKey(Object obj, eInteriorRoomKey roomKey) { NativeInvoke::Invoke<NATIVE_ADD_OBJECT_TO_INTERIOR_ROOM_BY_KEY, ScriptVoid>(obj, roomKey); }
    static void ApplyForceToObject(Object obj, unsigned int uk0_3, float pX, float pY, float pZ, float spinX, float spinY, float spinZ, unsigned int uk4_0, unsigned int uk5_1, unsigned int uk6_1, unsigned int uk7_1) { NativeInvoke::Invoke<NATIVE_APPLY_FORCE_TO_OBJECT, ScriptVoid>(obj, uk0_3, pX, pY, pZ, spinX, spinY, spinZ, uk4_0, uk5_1, uk6_1, uk7_1); }
    static void AttachObjectToCar(Object obj, Vehicle v, unsigned int unknown0_0, float pX, float pY, float pZ, float rX, float rY, float rZ) { NativeInvoke::Invoke<NATIVE_ATTACH_OBJECT_TO_CAR, ScriptVoid>(obj, v, unknown0_0, pX, pY, pZ, rX, rY, rZ); }
    static void AttachObjectToPed(Object obj, Ped c, ePedBone bone, float pX, float pY, float pZ, float rX, float rY, float rZ, unsigned int unknown1_0) { NativeInvoke::Invoke<NATIVE_ATTACH_OBJECT_TO_PED, ScriptVoid>(obj, c, bone, pX, pY, pZ, rX, rY, rZ, unknown1_0); }
    static void ClearObjectLastDamageEntity(Object obj) { NativeInvoke::Invoke<NATIVE_CLEAR_OBJECT_LAST_DAMAGE_ENTITY, ScriptVoid>(obj); }
    static void ClearRoomForObject(Object obj) { NativeInvoke::Invoke<NATIVE_CLEAR_ROOM_FOR_OBJECT, ScriptVoid>(obj); }
    static void CreateObject(eModel model, float x, float y, float z, Object *pObj, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_CREATE_OBJECT, ScriptVoid>(model, x, y, z, pObj, unknownTrue); }
    static void CreateObjectNoOffset(eModel model, float x, float y, float z, Object *pObj, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_CREATE_OBJECT_NO_OFFSET, ScriptVoid>(model, x, y, z, pObj, unknownTrue); }
    static void DeleteObject(Object *pObj) { NativeInvoke::Invoke<NATIVE_DELETE_OBJECT, ScriptVoid>(pObj); }
    static void DetachObject(Object obj, bool unknown) { NativeInvoke::Invoke<NATIVE_DETACH_OBJECT, ScriptVoid>(obj, unknown); }
    static bool DoesObjectExist(Object obj) { return NativeInvoke::Invoke<NATIVE_DOES_OBJECT_EXIST, bool>(obj); }
    static bool DoesObjectHavePhysics(Object obj) { return NativeInvoke::Invoke<NATIVE_DOES_OBJECT_HAVE_PHYSICS, bool>(obj); }
    static bool DoesObjectOfTypeExistAtCoords(float x, float y, float z, float radius, eModel model) { return NativeInvoke::Invoke<NATIVE_DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS, bool>(x, y, z, radius, model); }
    static void ExtinguishObjectFire(Object obj) { NativeInvoke::Invoke<NATIVE_EXTINGUISH_OBJECT_FIRE, ScriptVoid>(obj); }
    static void FreezeObjectPosition(Object obj, bool frozen) { NativeInvoke::Invoke<NATIVE_FREEZE_OBJECT_POSITION, ScriptVoid>(obj, frozen); }
    static Vehicle GetCarObjectIsAttachedTo(Object obj) { return NativeInvoke::Invoke<NATIVE_GET_CAR_OBJECT_IS_ATTACHED_TO, Vehicle>(obj); }
    static void GetObjectCoordinates(Object obj, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_OBJECT_COORDINATES, ScriptVoid>(obj, pX, pY, pZ); }
    static float GetObjectFragmentDamageHealth(Object obj, bool unknown) { return NativeInvoke::Invoke<NATIVE_GET_OBJECT_FRAGMENT_DAMAGE_HEALTH, float>(obj, unknown); }
    static void GetObjectHeading(Object obj, float *pHeading) { NativeInvoke::Invoke<NATIVE_GET_OBJECT_HEADING, ScriptVoid>(obj, pHeading); }
    static void GetObjectHealth(Object obj, float *pHealth) { NativeInvoke::Invoke<NATIVE_GET_OBJECT_HEALTH, ScriptVoid>(obj, pHealth); }
    static void GetObjectModel(Object obj, eModel *pModel) { NativeInvoke::Invoke<NATIVE_GET_OBJECT_MODEL, ScriptVoid>(obj, pModel); }
    static void GetObjectRotationVelocity(Object obj, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_OBJECT_ROTATION_VELOCITY, ScriptVoid>(obj, pX, pY, pZ); }
    static void GetObjectSpeed(Object obj, float *pSpeed) { NativeInvoke::Invoke<NATIVE_GET_OBJECT_SPEED, ScriptVoid>(obj, pSpeed); }
    static void GetObjectVelocity(Object obj, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_OBJECT_VELOCITY, ScriptVoid>(obj, pX, pY, pZ); }
    static void GetOffsetFromObjectInWorldCoords(Object obj, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ) { NativeInvoke::Invoke<NATIVE_GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS, ScriptVoid>(obj, x, y, z, pOffX, pOffY, pOffZ); }
    static Ped GetPedObjectIsAttachedTo(Object obj) { return NativeInvoke::Invoke<NATIVE_GET_PED_OBJECT_IS_ATTACHED_TO, Ped>(obj); }
    static bool HasObjectBeenDamaged(Object obj) { return NativeInvoke::Invoke<NATIVE_HAS_OBJECT_BEEN_DAMAGED, bool>(obj); }
    static bool HasObjectBeenDamagedByCar(Object obj, Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_HAS_OBJECT_BEEN_DAMAGED_BY_CAR, bool>(obj, vehicle); }
    static bool HasObjectBeenDamagedByChar(Object obj, Ped ped) { return NativeInvoke::Invoke<NATIVE_HAS_OBJECT_BEEN_DAMAGED_BY_CHAR, bool>(obj, ped); }
    static bool HasObjectBeenUprooted(Object obj) { return NativeInvoke::Invoke<NATIVE_HAS_OBJECT_BEEN_UPROOTED, bool>(obj); }
    static bool HasObjectCollidedWithAnything(Object obj) { return NativeInvoke::Invoke<NATIVE_HAS_OBJECT_COLLIDED_WITH_ANYTHING, bool>(obj); }
    //static bool HasPoolObjectCollidedWithCushion(Object obj) { return NativeInvoke::Invoke<NATIVE_HAS_POOL_OBJECT_COLLIDED_WITH_CUSHION, bool>(obj); }
    //static bool HasPoolObjectCollidedWithObject(Object obj, Object otherObj) { return NativeInvoke::Invoke<NATIVE_HAS_POOL_OBJECT_COLLIDED_WITH_OBJECT, bool>(obj, otherObj); }
    static bool IsObjectAttached(Object obj) { return NativeInvoke::Invoke<NATIVE_IS_OBJECT_ATTACHED, bool>(obj); }
    static bool IsObjectInWater(Object obj) { return NativeInvoke::Invoke<NATIVE_IS_OBJECT_IN_WATER, bool>(obj); }
    static bool IsObjectOnFire(Object obj) { return NativeInvoke::Invoke<NATIVE_IS_OBJECT_ON_FIRE, bool>(obj); }
    static bool IsObjectOnScreen(Object obj) { return NativeInvoke::Invoke<NATIVE_IS_OBJECT_ON_SCREEN, bool>(obj); }
    static bool IsObjectStatic(Object obj) { return NativeInvoke::Invoke<NATIVE_IS_OBJECT_STATIC, bool>(obj); }
    static bool IsObjectUpright(Object obj, float angle) { return NativeInvoke::Invoke<NATIVE_IS_OBJECT_UPRIGHT, bool>(obj, angle); }
    static bool IsObjectWithinBrainActivationRange(Object obj) { return NativeInvoke::Invoke<NATIVE_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE, bool>(obj); }
    static void LoadAllObjectsNow() { NativeInvoke::Invoke<NATIVE_LOAD_ALL_OBJECTS_NOW, ScriptVoid>(); }
    static void MakeObjectTargettable(Object obj, bool targettable) { NativeInvoke::Invoke<NATIVE_MAKE_OBJECT_TARGETTABLE, ScriptVoid>(obj, targettable); }
    static void MarkObjectAsNoLongerNeeded(Object *pObj) { NativeInvoke::Invoke<NATIVE_MARK_OBJECT_AS_NO_LONGER_NEEDED, ScriptVoid>(pObj); }
    static void SetObjectCollision(Object obj, bool value) { NativeInvoke::Invoke<NATIVE_SET_OBJECT_COLLISION, ScriptVoid>(obj, value); }
    static void SetObjectCoordinates(Object obj, float pX, float pY, float pZ) { NativeInvoke::Invoke<NATIVE_SET_OBJECT_COORDINATES, ScriptVoid>(obj, pX, pY, pZ); }
    static void SetObjectHeading(Object obj, float value) { NativeInvoke::Invoke<NATIVE_SET_OBJECT_HEADING, ScriptVoid>(obj, value); }
    static void SetObjectVisible(Object obj, bool value) { NativeInvoke::Invoke<NATIVE_SET_OBJECT_VISIBLE, ScriptVoid>(obj, value); }
    static ScriptAny StartObjectFire(Object obj) { return NativeInvoke::Invoke<NATIVE_START_OBJECT_FIRE, ScriptAny>(obj); }

    // Models
    //static bool HasModelLoaded(eModel model) { return NativeInvoke::Invoke<NATIVE_HAS_MODEL_LOADED, bool>(model); }
    //static void RequestModel(eModel model) { NativeInvoke::Invoke<NATIVE_REQUEST_MODEL, ScriptVoid>(model); }
    static void GetCurrentBasicCopModel(eModel *pModel) { NativeInvoke::Invoke<NATIVE_GET_CURRENT_BASIC_COP_MODEL, ScriptVoid>(pModel); }
    static void GetCurrentBasicPoliceCarModel(eModel *pModel) { NativeInvoke::Invoke<NATIVE_GET_CURRENT_BASIC_POLICE_CAR_MODEL, ScriptVoid>(pModel); }
    //static void GetCurrentCopModel(eModel *pModel) { NativeInvoke::Invoke<NATIVE_GET_CURRENT_COP_MODEL, ScriptVoid>(pModel); }
    static void GetCurrentPoliceCarModel(eModel *pModel) { NativeInvoke::Invoke<NATIVE_GET_CURRENT_POLICE_CAR_MODEL, ScriptVoid>(pModel); }
    static void GetCurrentTaxiCarModel(eModel *pModel) { NativeInvoke::Invoke<NATIVE_GET_CURRENT_TAXI_CAR_MODEL, ScriptVoid>(pModel); }
    static const char *GetDisplayNameFromVehicleModel(eModel model) { return NativeInvoke::Invoke<NATIVE_GET_DISPLAY_NAME_FROM_VEHICLE_MODEL, const char *>(model); }
    static void GetModelDimensions(eModel model, Vector3 *pMinVector, Vector3 *pMaxVector) { NativeInvoke::Invoke<NATIVE_GET_MODEL_DIMENSIONS, ScriptVoid>(model, pMinVector, pMaxVector); }
    static const char *GetModelNameForDebug(eModel model) { return NativeInvoke::Invoke<NATIVE_GET_MODEL_NAME_FOR_DEBUG, const char *>(model); }
    static bool IsThisModelABike(eModel model) { return NativeInvoke::Invoke<NATIVE_IS_THIS_MODEL_A_BIKE, bool>(model); }
    static bool IsThisModelABoat(eModel model) { return NativeInvoke::Invoke<NATIVE_IS_THIS_MODEL_A_BOAT, bool>(model); }
    static bool IsThisModelACar(eModel model) { return NativeInvoke::Invoke<NATIVE_IS_THIS_MODEL_A_CAR, bool>(model); }
    static bool IsThisModelAHeli(eModel model) { return NativeInvoke::Invoke<NATIVE_IS_THIS_MODEL_A_HELI, bool>(model); }
    static bool IsThisModelAPed(eModel model) { return NativeInvoke::Invoke<NATIVE_IS_THIS_MODEL_A_PED, bool>(model); }
    static bool IsThisModelAPlane(eModel model) { return NativeInvoke::Invoke<NATIVE_IS_THIS_MODEL_A_PLANE, bool>(model); }
    static bool IsThisModelATrain(eModel model) { return NativeInvoke::Invoke<NATIVE_IS_THIS_MODEL_A_TRAIN, bool>(model); }
    static bool IsThisModelAVehicle(eModel model) { return NativeInvoke::Invoke<NATIVE_IS_THIS_MODEL_A_VEHICLE, bool>(model); }
    //static void MarkModelAsNoLongerNeeded(eModel model) { NativeInvoke::Invoke<NATIVE_MARK_MODEL_AS_NO_LONGER_NEEDED, ScriptVoid>(model); }

    // Interiors
    static void ActivateInterior(Interior interior, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_ACTIVATE_INTERIOR, ScriptVoid>(interior, unknownTrue); }
    static void GetInteriorAtCoords(float x, float y, float z, Interior *pInterior) { NativeInvoke::Invoke<NATIVE_GET_INTERIOR_AT_COORDS, ScriptVoid>(x, y, z, pInterior); }
    static void GetInteriorFromCar(Vehicle vehicle, Interior *pInterior) { NativeInvoke::Invoke<NATIVE_GET_INTERIOR_FROM_CAR, ScriptVoid>(vehicle, pInterior); }
    static void GetInteriorFromChar(Ped ped, Interior *pInterior) { NativeInvoke::Invoke<NATIVE_GET_INTERIOR_FROM_CHAR, ScriptVoid>(ped, pInterior); }
    static void GetInteriorHeading(Interior interior, float *pHeading) { NativeInvoke::Invoke<NATIVE_GET_INTERIOR_HEADING, ScriptVoid>(interior, pHeading); }
    static void GetOffsetFromInteriorInWorldCoords(Interior interior, float x, float y, float z, float *pOffset) { NativeInvoke::Invoke<NATIVE_GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS, ScriptVoid>(interior, x, y, z, pOffset); }
    static void GetRoomKeyFromObject(Object obj, eInteriorRoomKey *pRoomKey) { NativeInvoke::Invoke<NATIVE_GET_ROOM_KEY_FROM_OBJECT, ScriptVoid>(obj, pRoomKey); }
    static void RequestInteriorModels(eModel model, const char *interiorName) { NativeInvoke::Invoke<NATIVE_REQUEST_INTERIOR_MODELS, ScriptVoid>(model, interiorName); }

    // Decision Maker
    static void AddCharDecisionMakerEventResponse(DecisionMaker dm, unsigned int eventid, unsigned int responseid, float param1, float param2, float param3, float param4, unsigned int unknown0_1, unsigned int unknown1_1) { NativeInvoke::Invoke<NATIVE_ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE, ScriptVoid>(dm, eventid, responseid, param1, param2, param3, param4, unknown0_1, unknown1_1); }
    static void AddCombatDecisionMakerEventResponse(DecisionMaker dm, unsigned int eventid, unsigned int responseid, float param1, float param2, float param3, float param4, unsigned int unknown0_1, unsigned int unknown1_1) { NativeInvoke::Invoke<NATIVE_ADD_COMBAT_DECISION_MAKER_EVENT_RESPONSE, ScriptVoid>(dm, eventid, responseid, param1, param2, param3, param4, unknown0_1, unknown1_1); }
    static void AddGroupDecisionMakerEventResponse(DecisionMaker dm, unsigned int eventid, unsigned int responseid, float param1, float param2, float param3, float param4, unsigned int unknown0_1, unsigned int unknown1_1) { NativeInvoke::Invoke<NATIVE_ADD_GROUP_DECISION_MAKER_EVENT_RESPONSE, ScriptVoid>(dm, eventid, responseid, param1, param2, param3, param4, unknown0_1, unknown1_1); }
    static void ClearCharDecisionMakerEventResponse(DecisionMaker dm, unsigned int eventid) { NativeInvoke::Invoke<NATIVE_CLEAR_CHAR_DECISION_MAKER_EVENT_RESPONSE, ScriptVoid>(dm, eventid); }
    static void ClearCombatDecisionMakerEventResponse(DecisionMaker dm, unsigned int eventid) { NativeInvoke::Invoke<NATIVE_CLEAR_COMBAT_DECISION_MAKER_EVENT_RESPONSE, ScriptVoid>(dm, eventid); }
    static void ClearGroupDecisionMakerEventResponse(DecisionMaker dm, unsigned int eventid) { NativeInvoke::Invoke<NATIVE_CLEAR_GROUP_DECISION_MAKER_EVENT_RESPONSE, ScriptVoid>(dm, eventid); }
    static void CopyCharDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_COPY_CHAR_DECISION_MAKER, ScriptVoid>(type, pDM); }
    static void CopyCombatDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_COPY_COMBAT_DECISION_MAKER, ScriptVoid>(type, pDM); }
    static void CopyGroupCharDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_COPY_GROUP_CHAR_DECISION_MAKER, ScriptVoid>(type, pDM); }
    static void CopyGroupCombatDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_COPY_GROUP_COMBAT_DECISION_MAKER, ScriptVoid>(type, pDM); }
    static void CopySharedCharDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_COPY_SHARED_CHAR_DECISION_MAKER, ScriptVoid>(type, pDM); }
    static void CopySharedCombatDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_COPY_SHARED_COMBAT_DECISION_MAKER, ScriptVoid>(type, pDM); }
    static bool DoesDecisionMakerExist(DecisionMaker dm) { return NativeInvoke::Invoke<NATIVE_DOES_DECISION_MAKER_EXIST, bool>(dm); }
    static void LoadCharDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_LOAD_CHAR_DECISION_MAKER, ScriptVoid>(type, pDM); }
    static void LoadCombatDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_LOAD_COMBAT_DECISION_MAKER, ScriptVoid>(type, pDM); }
    // nullsub in 104  // static void LoadGroupDecisionMaker(unsigned int type, DecisionMaker *pDM) { NativeInvoke::Invoke<NATIVE_LOAD_GROUP_DECISION_MAKER, ScriptVoid>(type, pDM); }
    static void RemoveDecisionMaker(DecisionMaker dm) { NativeInvoke::Invoke<NATIVE_REMOVE_DECISION_MAKER, ScriptVoid>(dm); }
    static void SetCharDecisionMaker(Ped ped, DecisionMaker dm) { NativeInvoke::Invoke<NATIVE_SET_CHAR_DECISION_MAKER, ScriptVoid>(ped, dm); }
    static void SetCharDecisionMakerToDefault(Ped ped) { NativeInvoke::Invoke<NATIVE_SET_CHAR_DECISION_MAKER_TO_DEFAULT, ScriptVoid>(ped); }
    static void SetCombatDecisionMaker(Ped ped, DecisionMaker dm) { NativeInvoke::Invoke<NATIVE_SET_COMBAT_DECISION_MAKER, ScriptVoid>(ped, dm); }
    static void SetDecisionMakerAttributeCanChangeTarget(DecisionMaker dm, bool value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_CAN_CHANGE_TARGET, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeCaution(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_CAUTION, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeFireRate(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_FIRE_RATE, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeLowHealth(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_LOW_HEALTH, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeMovementStyle(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_MOVEMENT_STYLE, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeNavigationStyle(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_NAVIGATION_STYLE, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeRetreatingBehaviour(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_RETREATING_BEHAVIOUR, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeSightRange(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeStandingStyle(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_STANDING_STYLE, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeTargetInjuredReaction(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_TARGET_INJURED_REACTION, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeTargetLossResponse(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_TARGET_LOSS_RESPONSE, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeTeamwork(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_TEAMWORK, ScriptVoid>(dm, value); }
    static void SetDecisionMakerAttributeWeaponAccuracy(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_DECISION_MAKER_ATTRIBUTE_WEAPON_ACCURACY, ScriptVoid>(dm, value); }
    static void SetGroupCharDecisionMaker(Group group, DecisionMaker dm) { NativeInvoke::Invoke<NATIVE_SET_GROUP_CHAR_DECISION_MAKER, ScriptVoid>(group, dm); }
    static void SetGroupCombatDecisionMaker(Group group, DecisionMaker dm) { NativeInvoke::Invoke<NATIVE_SET_GROUP_COMBAT_DECISION_MAKER, ScriptVoid>(group, dm); }
    // nullsub in 104 static void SetGroupDecisionMaker(Group group, DecisionMaker dm) { NativeInvoke::Invoke<NATIVE_SET_GROUP_DECISION_MAKER, ScriptVoid>(group, dm); }

    // Blips
    static void AddBlipForCar(Vehicle vehicle, Blip *pBlip) { NativeInvoke::Invoke<NATIVE_ADD_BLIP_FOR_CAR, ScriptVoid>(vehicle, pBlip); }
    static void AddBlipForChar(Ped ped, Blip *pBlip) { NativeInvoke::Invoke<NATIVE_ADD_BLIP_FOR_CHAR, ScriptVoid>(ped, pBlip); }
    static void AddBlipForContact(float x, float y, float z, Blip *pBlip) { NativeInvoke::Invoke<NATIVE_ADD_BLIP_FOR_CONTACT, ScriptVoid>(x, y, z, pBlip); }
    static void AddBlipForCoord(float x, float y, float z, Blip *pBlip) { NativeInvoke::Invoke<NATIVE_ADD_BLIP_FOR_COORD, ScriptVoid>(x, y, z, pBlip); }
    static void AddBlipForObject(Object obj, Blip *pBlip) { NativeInvoke::Invoke<NATIVE_ADD_BLIP_FOR_OBJECT, ScriptVoid>(obj, pBlip); }
    static void AddBlipForPickup(Pickup pickup, Blip *pBlip) { NativeInvoke::Invoke<NATIVE_ADD_BLIP_FOR_PICKUP, ScriptVoid>(pickup, pBlip); }
    static void AddSimpleBlipForPickup(Pickup pickup) { NativeInvoke::Invoke<NATIVE_ADD_SIMPLE_BLIP_FOR_PICKUP, ScriptVoid>(pickup); }
    static void ChangeBlipAlpha(Blip blip, ScriptAny alpha) { NativeInvoke::Invoke<NATIVE_CHANGE_BLIP_ALPHA, ScriptVoid>(blip, alpha); }
    static void ChangeBlipColour(Blip blip, ColourIndex colour) { NativeInvoke::Invoke<NATIVE_CHANGE_BLIP_COLOUR, ScriptVoid>(blip, colour); }
    static void ChangeBlipDisplay(Blip blip, eBlipDisplay display) { NativeInvoke::Invoke<NATIVE_CHANGE_BLIP_DISPLAY, ScriptVoid>(blip, display); }
    static void ChangeBlipNameFromAscii(Blip blip, const char *blipName) { NativeInvoke::Invoke<NATIVE_CHANGE_BLIP_NAME_FROM_ASCII, ScriptVoid>(blip, blipName); }
    static void ChangeBlipNameFromTextFile(Blip blip, const char *gxtName) { NativeInvoke::Invoke<NATIVE_CHANGE_BLIP_NAME_FROM_TEXT_FILE, ScriptVoid>(blip, gxtName); }
    static void ChangeBlipPriority(Blip blip, eBlipPriority priority) { NativeInvoke::Invoke<NATIVE_CHANGE_BLIP_PRIORITY, ScriptVoid>(blip, priority); }
    static void ChangeBlipScale(Blip blip, float scale) { NativeInvoke::Invoke<NATIVE_CHANGE_BLIP_SCALE, ScriptVoid>(blip, scale); }
    static void ChangeBlipSprite(Blip blip, eBlipSprite sprite) { NativeInvoke::Invoke<NATIVE_CHANGE_BLIP_SPRITE, ScriptVoid>(blip, sprite); }
    static void DimBlip(Blip blip, bool unknownTrue) { NativeInvoke::Invoke<NATIVE_DIM_BLIP, ScriptVoid>(blip, unknownTrue); }
    static bool DoesBlipExist(Blip blip) { return NativeInvoke::Invoke<NATIVE_DOES_BLIP_EXIST, bool>(blip); }
    static void FlashBlip(Blip blip, bool on) { NativeInvoke::Invoke<NATIVE_FLASH_BLIP, ScriptVoid>(blip, on); }
    static void FlashBlipAlt(Blip blip, bool on) { NativeInvoke::Invoke<NATIVE_FLASH_BLIP_ALT, ScriptVoid>(blip, on); }
    static void GetBlipColour(Blip blip, ColourIndex *pColour) { NativeInvoke::Invoke<NATIVE_GET_BLIP_COLOUR, ScriptVoid>(blip, pColour); }
    static void GetBlipCoords(Blip blip, Vector3 *pVector) { NativeInvoke::Invoke<NATIVE_GET_BLIP_COORDS, ScriptVoid>(blip, pVector); }
    static eBlipType GetBlipInfoIdType(Blip blip) { return NativeInvoke::Invoke<NATIVE_GET_BLIP_INFO_ID_TYPE, eBlipType>(blip); }
    static Vehicle GetBlipInfoIdCarIndex(Blip blip) { return NativeInvoke::Invoke<NATIVE_GET_BLIP_INFO_ID_CAR_INDEX, Vehicle>(blip); }
    static unsigned int GetBlipInfoIdDisplay(Blip blip) { return NativeInvoke::Invoke<NATIVE_GET_BLIP_INFO_ID_DISPLAY, bool>(blip); }
    static Object GetBlipInfoIdObjectIndex(Blip blip) { return NativeInvoke::Invoke<NATIVE_GET_BLIP_INFO_ID_OBJECT_INDEX, Object>(blip); }
    static Ped GetBlipInfoIdPedIndex(Blip blip) { return NativeInvoke::Invoke<NATIVE_GET_BLIP_INFO_ID_PED_INDEX, Ped>(blip); }
    static Pickup GetBlipInfoIdPickupIndex(Blip blip) { return NativeInvoke::Invoke<NATIVE_GET_BLIP_INFO_ID_PICKUP_INDEX, Pickup>(blip); }
    // No longer in 104 static const char *GetBlipName(Blip blip) { return NativeInvoke::Invoke<NATIVE_GET_BLIP_NAME, const char *>(blip); }
    static eBlipSprite GetBlipSprite(Blip blip) { return NativeInvoke::Invoke<NATIVE_GET_BLIP_SPRITE, eBlipSprite>(blip); }
    static Blip GetFirstBlipInfoId(eBlipSprite type) { return NativeInvoke::Invoke<NATIVE_GET_FIRST_BLIP_INFO_ID, Blip>(type); }
    static Blip GetNextBlipInfoId(eBlipSprite type) { return NativeInvoke::Invoke<NATIVE_GET_NEXT_BLIP_INFO_ID, Blip>(type); }
    static bool IsBlipShortRange(Blip blip) { return NativeInvoke::Invoke<NATIVE_IS_BLIP_SHORT_RANGE, bool>(blip); }
    static void RemoveBlip(Blip blip) { NativeInvoke::Invoke<NATIVE_REMOVE_BLIP, ScriptVoid>(blip); }
    static void SetBlipAsFriendly(Blip blip, bool value) { NativeInvoke::Invoke<NATIVE_SET_BLIP_AS_FRIENDLY, ScriptVoid>(blip, value); }
    static void SetBlipAsShortRange(Blip blip, bool value) { NativeInvoke::Invoke<NATIVE_SET_BLIP_AS_SHORT_RANGE, ScriptVoid>(blip, value); }
    static void SetRoute(Blip blip, bool value) { NativeInvoke::Invoke<NATIVE_SET_ROUTE, ScriptVoid>(blip, value); }

    // Pickups
    static void AddPickupToInteriorRoomByName(Pickup pickup, const char *roomName) { NativeInvoke::Invoke<NATIVE_ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME, ScriptVoid>(pickup, roomName); }
    static void CreateMoneyPickup(float x, float y, float z, unsigned int amount, bool unknownTrue, Pickup *pPickup) { NativeInvoke::Invoke<NATIVE_CREATE_MONEY_PICKUP, ScriptVoid>(x, y, z, amount, unknownTrue, pPickup); }
    static void CreatePickup(eModel model, ePickupType pickupType, float x, float y, float z, Pickup *pPickup, bool unknownFalse) { NativeInvoke::Invoke<NATIVE_CREATE_PICKUP, ScriptVoid>(model, pickupType, x, y, z, pPickup, unknownFalse); }
    static void CreatePickupRotate(eModel model, ePickupType pickupType, unsigned int unknown, float x, float y, float z, float rX, float rY, float rZ, Pickup *pPickup) { NativeInvoke::Invoke<NATIVE_CREATE_PICKUP_ROTATE, ScriptVoid>(model, pickupType, unknown, x, y, z, rX, rY, rZ, pPickup); }
    static void CreatePickupWithAmmo(eModel model, ePickupType pickupType, unsigned int unknown, float x, float y, float z, Pickup *pPickup) { NativeInvoke::Invoke<NATIVE_CREATE_PICKUP_WITH_AMMO, ScriptVoid>(model, pickupType, unknown, x, y, z, pPickup); }
    static bool DoesPickupExist(Pickup pickup) { return NativeInvoke::Invoke<NATIVE_DOES_PICKUP_EXIST, bool>(pickup); }
    static void GetPickupCoordinates(Pickup pickup, float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_PICKUP_COORDINATES, ScriptVoid>(pickup, pX, pY, pZ); }
    static bool HasPickupBeenCollected(Pickup pickup) { return NativeInvoke::Invoke<NATIVE_HAS_PICKUP_BEEN_COLLECTED, bool>(pickup); }
    static void PickupsPassTime(unsigned int time) { NativeInvoke::Invoke<NATIVE_PICKUPS_PASS_TIME, ScriptVoid>(time); }
    static void RemovePickup(Pickup pickup) { NativeInvoke::Invoke<NATIVE_REMOVE_PICKUP, ScriptVoid>(pickup); }
    static void RemoveTemporaryRadarBlipsForPickups() { NativeInvoke::Invoke<NATIVE_REMOVE_TEMPORARY_RADAR_BLIPS_FOR_PICKUPS, ScriptVoid>(); }
    static void RenderWeaponPickupsBigger(bool value) { NativeInvoke::Invoke<NATIVE_RENDER_WEAPON_PICKUPS_BIGGER, ScriptVoid>(value); }

    // Camera
    //static bool CamIsSphereVisible(Camera camera, float pX, float pY, float pZ, float radius) { return NativeInvoke::Invoke<NATIVE_CAM_IS_SPHERE_VISIBLE, bool>(camera, pX, pY, pZ, radius); }
    static void CreateCam(unsigned int camtype_usually14, Camera *camera) { NativeInvoke::Invoke<NATIVE_CREATE_CAM, ScriptVoid>(camtype_usually14, camera); }
    static void DestroyCam(Camera camera) { NativeInvoke::Invoke<NATIVE_DESTROY_CAM, ScriptVoid>(camera); }
    static bool DoesCamExist(Camera camera) { return NativeInvoke::Invoke<NATIVE_DOES_CAM_EXIST, bool>(camera); }
    static void SetCamActive(Camera camera, bool value) { NativeInvoke::Invoke<NATIVE_SET_CAM_ACTIVE, ScriptVoid>(camera, value); }
    static void GetCamFov(Camera camera, float *fov) { NativeInvoke::Invoke<NATIVE_GET_CAM_FOV, ScriptVoid>(camera, fov); }
    //static void GetCamPos(Camera camera,  float *pX, float *pY, float *pZ) { NativeInvoke::Invoke<NATIVE_GET_CAM_POS, ScriptVoid>(camera, pX, pY, pZ); }
    //static void GetCamRot(Camera camera, float *angleX, float *angleY, float *angleZ) { NativeInvoke::Invoke<NATIVE_GET_CAM_ROT, ScriptVoid>(camera, angleX, angleY, angleZ); }
    //static void GetGameCam(Camera *camera) { NativeInvoke::Invoke<NATIVE_GET_GAME_CAM, ScriptVoid>(camera); }
    static void GetGameCamChild(Camera *camera) { NativeInvoke::Invoke<NATIVE_GET_GAME_CAM_CHILD, ScriptVoid>(camera); }
    static bool IsCamActive(Camera camera) { return NativeInvoke::Invoke<NATIVE_IS_CAM_ACTIVE, bool>(camera); }
    static bool IsCamInterpolating() { return NativeInvoke::Invoke<NATIVE_IS_CAM_INTERPOLATING, bool>(); }
    static bool IsCamPropagating(Camera camera) { return NativeInvoke::Invoke<NATIVE_IS_CAM_PROPAGATING, bool>(camera); }
    static void SetCamBehindPed(Ped ped) { NativeInvoke::Invoke<NATIVE_SET_CAM_BEHIND_PED, ScriptVoid>(ped); }
    static void SetCamFov(Camera camera, float fov) { NativeInvoke::Invoke<NATIVE_SET_CAM_FOV, ScriptVoid>(camera, fov); }
    //static void SetCamInFrontOfPed(Ped ped) { NativeInvoke::Invoke<NATIVE_SET_CAM_IN_FRONT_OF_PED, ScriptVoid>(ped); }
    static void SetCamPos(Camera camera, float pX, float pY, float pZ) { NativeInvoke::Invoke<NATIVE_SET_CAM_POS, ScriptVoid>(camera, pX, pY, pZ); }
    static void SetCamPropagate(Camera camera, bool value) { NativeInvoke::Invoke<NATIVE_SET_CAM_PROPAGATE, ScriptVoid>(camera, value); }
    static void SetCamRot(Camera camera, float angleX, float angleY, float angleZ) { NativeInvoke::Invoke<NATIVE_SET_CAM_ROT, ScriptVoid>(camera, angleX, angleY, angleZ); }
    static void SetCamTargetPed(Camera camera, Ped ped) { NativeInvoke::Invoke<NATIVE_SET_CAM_TARGET_PED, ScriptVoid>(camera, ped); }
	static void ActivateScriptedCams(bool a1, bool a2) { NativeInvoke::Invoke<NATIVE_ACTIVATE_SCRIPTED_CAMS, ScriptVoid>(a1, a2); }

    // Network
    static bool NetworkIsGameRanked() { return NativeInvoke::Invoke<NATIVE_NETWORK_IS_GAME_RANKED, bool>(); }
    static bool NetworkIsSessionStarted() { return NativeInvoke::Invoke<NATIVE_NETWORK_IS_SESSION_STARTED, bool>(); }

    // World
    static bool AreAllNavmeshRegionsLoaded() { return NativeInvoke::Invoke<NATIVE_ARE_ALL_NAVMESH_REGIONS_LOADED, bool>(); }
    static void ClearArea(float x, float y, float z, float radius, bool unknown) { NativeInvoke::Invoke<NATIVE_CLEAR_AREA, ScriptVoid>(x, y, z, radius, unknown); }
    static void ClearAreaOfCars(float x, float y, float z, float radius) { NativeInvoke::Invoke<NATIVE_CLEAR_AREA_OF_CARS, ScriptVoid>(x, y, z, radius); }
    //static void ClearAreaOfChars(float x, float y, float z, float radius) { NativeInvoke::Invoke<NATIVE_CLEAR_AREA_OF_CHARS, ScriptVoid>(x, y, z, radius); }
    //static void ClearAreaOfCops(float x, float y, float z, float radius) { NativeInvoke::Invoke<NATIVE_CLEAR_AREA_OF_COPS, ScriptVoid>(x, y, z, radius); }
    static void ClearAreaOfObjects(float x, float y, float z, float radius) { NativeInvoke::Invoke<NATIVE_CLEAR_AREA_OF_OBJECTS, ScriptVoid>(x, y, z, radius); }
    static void ClearPedNonCreationArea() { NativeInvoke::Invoke<NATIVE_CLEAR_PED_NON_CREATION_AREA, ScriptVoid>(); }
    static void ClearPedNonRemovalArea() { NativeInvoke::Invoke<NATIVE_CLEAR_PED_NON_REMOVAL_AREA, ScriptVoid>(); }
    static void ExtinguishFireAtPoint(float x, float y, float z, float radius) { NativeInvoke::Invoke<NATIVE_EXTINGUISH_FIRE_AT_POINT, ScriptVoid>(x, y, z, radius); }
    static void ForceWeather(eWeather weather) { NativeInvoke::Invoke<NATIVE_FORCE_WEATHER, ScriptVoid>(weather); }
    static void ForceWeatherNow(eWeather weather) { NativeInvoke::Invoke<NATIVE_FORCE_WEATHER_NOW, ScriptVoid>(weather); }
    static void ForceWind(float wind) { NativeInvoke::Invoke<NATIVE_FORCE_WIND, ScriptVoid>(wind); }
    static void FreezePositionOfClosestObjectOfType(float x, float y, float z, float radius, eModel model, bool frozen) { NativeInvoke::Invoke<NATIVE_FREEZE_POSITION_OF_CLOSEST_OBJECT_OF_TYPE, ScriptVoid>(x, y, z, radius, model, frozen); }
    static Vehicle GetClosestCar(float x, float y, float z, float radius, bool unknownFalse, unsigned int unknown70) { return NativeInvoke::Invoke<NATIVE_GET_CLOSEST_CAR, Vehicle>(x, y, z, radius, unknownFalse, unknown70); }
    static bool GetClosestChar(float x, float y, float z, float radius, bool unknown1, bool unknown2, Ped *pPed) { return NativeInvoke::Invoke<NATIVE_GET_CLOSEST_CHAR, bool>(x, y, z, radius, unknown1, unknown2, pPed); }
    static void GetCurrentWeather(eWeather *pWeather) { NativeInvoke::Invoke<NATIVE_GET_CURRENT_WEATHER, ScriptVoid>(pWeather); }
    static ScriptAny GetGroundZFor3DCoord(float x, float y, float z, float *pGroundZ) { return NativeInvoke::Invoke<NATIVE_GET_GROUND_Z_FOR_3D_COORD, ScriptAny>(x, y, z, pGroundZ); }
    static unsigned int GetNumberOfFiresInRange(float x, float y, float z, float radius) { return NativeInvoke::Invoke<NATIVE_GET_NUMBER_OF_FIRES_IN_RANGE, unsigned int>(x, y, z, radius); }
    static void GetSafePickupCoords(float x, float y, float z, float *pSafeX, float *pSafeY, float *pSafeZ) { NativeInvoke::Invoke<NATIVE_GET_SAFE_PICKUP_COORDS, ScriptVoid>(x, y, z, pSafeX, pSafeY, pSafeZ); }
    static bool GetSafePositionForChar(float x, float y, float z, bool unknownTrue, float *pSafeX, float *pSafeY, float *pSafeZ) { return NativeInvoke::Invoke<NATIVE_GET_SAFE_POSITION_FOR_CHAR, bool>(x, y, z, unknownTrue, pSafeX, pSafeY, pSafeZ); }
    static bool HasClosestObjectOfTypeBeenDamagedByChar(float x, float y, float z, float radius, eModel objectModel, Ped ped) { return NativeInvoke::Invoke<NATIVE_HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED_BY_CHAR, bool>(x, y, z, radius, objectModel, ped); }
    static bool IsAreaOccupied(float x1, float y1, float z1, float x2, float y2, float z2, bool unknownFalse1, bool unknownTrue, bool unknownFalse2, bool unknownFalse3, bool unknownFalse4) { return NativeInvoke::Invoke<NATIVE_IS_AREA_OCCUPIED, bool>(x1, y1, z1, x2, y2, z2, unknownFalse1, unknownTrue, unknownFalse2, unknownFalse3, unknownFalse4); }
    static bool IsBulletInArea(float x, float y, float z, float radius, bool unknownTrue) { return NativeInvoke::Invoke<NATIVE_IS_BULLET_IN_AREA, bool>(x, y, z, radius, unknownTrue); }
    static bool IsBulletInBox(float x1, float y1, float z1, float x2, float y2, float z2, bool unknown) { return NativeInvoke::Invoke<NATIVE_IS_BULLET_IN_BOX, bool>(x1, y1, z1, x2, y2, z2, unknown); }
    static bool IsPointObscuredByAMissionEntity(float pX, float pY, float pZ, float sizeX, float sizeY, float sizeZ) { return NativeInvoke::Invoke<NATIVE_IS_POINT_OBSCURED_BY_A_MISSION_ENTITY, bool>(pX, pY, pZ, sizeX, sizeY, sizeZ); }
    static void LoadScene(float x, float y, float z) { NativeInvoke::Invoke<NATIVE_LOAD_SCENE, ScriptVoid>(x, y, z); }
    static void RemoveAllPickupsOfType(ePickupType type) { NativeInvoke::Invoke<NATIVE_REMOVE_ALL_PICKUPS_OF_TYPE, ScriptVoid>(type); }
    static void RequestCollisionAtPosn(float x, float y, float z) { NativeInvoke::Invoke<NATIVE_REQUEST_COLLISION_AT_POSN, ScriptVoid>(x, y, z); }
    //static void SwitchAmbientPlanes(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_AMBIENT_PLANES, ScriptVoid>(on); }  
    //static void SwitchArrowAboveBlippedPickups(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_ARROW_ABOVE_BLIPPED_PICKUPS, ScriptVoid>(on); }
    //static void SwitchRandomBoats(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_RANDOM_BOATS, ScriptVoid>(on); }
    //static void SwitchRandomTrains(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_RANDOM_TRAINS, ScriptVoid>(on); }
    //static void SwitchGarbageTrucks(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_GARBAGE_TRUCKS, ScriptVoid>(on); }
    //static void SwitchMadDrivers(bool on) { NativeInvoke::Invoke<NATIVE_SWITCH_MAD_DRIVERS, ScriptVoid>(on); }

    // Garages
    static void CloseGarage(const char *garageName) { NativeInvoke::Invoke<NATIVE_CLOSE_GARAGE, ScriptVoid>(garageName); }
    //static bool IsCarInGarageArea(const char *garageName, Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_IS_CAR_IN_GARAGE_AREA, bool>(garageName, vehicle); }
    static ScriptAny IsGarageClosed(const char *garageName) { return NativeInvoke::Invoke<NATIVE_IS_GARAGE_CLOSED, ScriptAny>(garageName); }
    static ScriptAny IsGarageOpen(const char *garageName) { return NativeInvoke::Invoke<NATIVE_IS_GARAGE_OPEN, ScriptAny>(garageName); }
    static void OpenGarage(const char *name) { NativeInvoke::Invoke<NATIVE_OPEN_GARAGE, ScriptVoid>(name); }

    // Text (GXT stuff)
    static void DisplayText(float x, float y, const char *gxtName) { NativeInvoke::Invoke<NATIVE_DISPLAY_TEXT, ScriptVoid>(x, y, gxtName); }
    static void DisplayTextWith2Numbers(float x, float y, const char *gxtName, int number1, int number2) { NativeInvoke::Invoke<NATIVE_DISPLAY_TEXT_WITH_2_NUMBERS, ScriptVoid>(x, y, gxtName, number1, number2); }
    static void DisplayTextWithFloat(float x, float y, const char *gxtName, float value, unsigned int unknown) { NativeInvoke::Invoke<NATIVE_DISPLAY_TEXT_WITH_FLOAT, ScriptVoid>(x, y, gxtName, value, unknown); }
    static void DisplayTextWithLiteralString(float x, float y, const char *gxtName, const char *literalStr) { NativeInvoke::Invoke<NATIVE_DISPLAY_TEXT_WITH_LITERAL_STRING, ScriptVoid>(x, y, gxtName, literalStr); }
    static void DisplayTextWithNumber(float x, float y, const char *gxtName, int value) { NativeInvoke::Invoke<NATIVE_DISPLAY_TEXT_WITH_NUMBER, ScriptVoid>(x, y, gxtName, value); }
    static void DisplayTextWithString(float x, float y, const char *gxtName, const char *gxtStringName) { NativeInvoke::Invoke<NATIVE_DISPLAY_TEXT_WITH_STRING, ScriptVoid>(x, y, gxtName, gxtStringName); }
    static void DisplayTextWithTwoLiteralStrings(float x, float y, const char *gxtName, const char *literalStr1, const char *literalStr2) { NativeInvoke::Invoke<NATIVE_DISPLAY_TEXT_WITH_TWO_LITERAL_STRINGS, ScriptVoid>(x, y, gxtName, literalStr1, literalStr2); }
    static void DisplayTextWithTwoStrings(float x, float y, const char *gxtName, const char *gxtStringName1, const char *gxtStringName2) { NativeInvoke::Invoke<NATIVE_DISPLAY_TEXT_WITH_TWO_STRINGS, ScriptVoid>(x, y, gxtName, gxtStringName1, gxtStringName2); }
    static unsigned int GetLengthOfStringWithThisTextLabel(const char *gxtName) { return NativeInvoke::Invoke<NATIVE_GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL, unsigned int>(gxtName); }
    static const char *GetFirstNCharactersOfString(const char *gxtName, unsigned int chars) { return NativeInvoke::Invoke<NATIVE_GET_FIRST_N_CHARACTERS_OF_STRING, const char *>(gxtName, chars); }
    //static void GetMobilePhoneRenderId(unsigned int *pRenderId) { NativeInvoke::Invoke<NATIVE_GET_MOBILE_PHONE_RENDER_ID, ScriptVoid>(pRenderId); }
    static const char *GetNthIntegerInString(const char *gxtName, unsigned int index) { return NativeInvoke::Invoke<NATIVE_GET_NTH_INTEGER_IN_STRING, const char *>(gxtName, index); }
    //static void GetScriptRenderTargetRenderId(unsigned int *pRenderId) { NativeInvoke::Invoke<NATIVE_GET_SCRIPT_RENDERTARGET_RENDER_ID, ScriptVoid>(pRenderId); }
    static const char *GetStringFromHashKey(unsigned int hashKey) { return NativeInvoke::Invoke<NATIVE_GET_STRING_FROM_HASH_KEY, const char *>(hashKey); }
    static ScriptAny GetStringWidth(const char *gxtName) { return NativeInvoke::Invoke<NATIVE_GET_STRING_WIDTH, ScriptAny>(gxtName); }
    static ScriptAny GetStringWidthWithNumber(const char *gxtName, int number) { return NativeInvoke::Invoke<NATIVE_GET_STRING_WIDTH_WITH_NUMBER, ScriptAny>(gxtName, number); }
    static ScriptAny GetStringWidthWithString(const char *gxtName, const char *literalString) { return NativeInvoke::Invoke<NATIVE_GET_STRING_WIDTH_WITH_STRING, ScriptAny>(gxtName, literalString); }
    static bool HasAdditionalTextLoaded(unsigned int textIndex) { return NativeInvoke::Invoke<NATIVE_HAS_ADDITIONAL_TEXT_LOADED, bool>(textIndex); }
    static bool HasThisAdditionalTextLoaded(const char *textName, unsigned int textIndex) { return NativeInvoke::Invoke<NATIVE_HAS_THIS_ADDITIONAL_TEXT_LOADED, bool>(textName, textIndex); }
    static bool IsFontLoaded(eTextFont font) { return NativeInvoke::Invoke<NATIVE_IS_FONT_LOADED, bool>(font); }
    static bool IsStreamingAdditionalText(unsigned int textIndex) { return NativeInvoke::Invoke<NATIVE_IS_STREAMING_ADDITIONAL_TEXT, bool>(textIndex); }
    static void LoadAdditionalText(const char *textName, unsigned int textIndex) { NativeInvoke::Invoke<NATIVE_LOAD_ADDITIONAL_TEXT, ScriptVoid>(textName, textIndex); }
    static void LoadTextFont(eTextFont font) { NativeInvoke::Invoke<NATIVE_LOAD_TEXT_FONT, ScriptVoid>(font); }
    static void Print(const char *gxtName, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT, ScriptVoid>(gxtName, timeMS, enable); }
    static void PrintBig(const char *gxtName, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_BIG, ScriptVoid>(gxtName, timeMS, enable); }
    static void PrintHelp(const char *gxtName) { NativeInvoke::Invoke<NATIVE_PRINT_HELP, ScriptVoid>(gxtName); }
    static void PrintHelpForever(const char *gxtName) { NativeInvoke::Invoke<NATIVE_PRINT_HELP_FOREVER, ScriptVoid>(gxtName); }
    static void PrintHelpForeverWithNumber(const char *gxtName, int value) { NativeInvoke::Invoke<NATIVE_PRINT_HELP_FOREVER_WITH_NUMBER, ScriptVoid>(gxtName, value); }
    static void PrintHelpForeverWithString(const char *gxtName, const char *gxtText) { NativeInvoke::Invoke<NATIVE_PRINT_HELP_FOREVER_WITH_STRING, ScriptVoid>(gxtName, gxtText); }
    static void PrintHelpForeverWithStringNoSound(const char *gxtName, const char *gxtText) { NativeInvoke::Invoke<NATIVE_PRINT_HELP_FOREVER_WITH_STRING_NO_SOUND, ScriptVoid>(gxtName, gxtText); }
    static void PrintHelpWithNumber(const char *gxtName, int value) { NativeInvoke::Invoke<NATIVE_PRINT_HELP_WITH_NUMBER, ScriptVoid>(gxtName, value); }
    static void PrintHelpWithString(const char *gxtName, const char *gxtText) { NativeInvoke::Invoke<NATIVE_PRINT_HELP_WITH_STRING, ScriptVoid>(gxtName, gxtText); }
    static void PrintHelpWithStringNoSound(const char *gxtName, const char *gxtText) { NativeInvoke::Invoke<NATIVE_PRINT_HELP_WITH_STRING_NO_SOUND, ScriptVoid>(gxtName, gxtText); }
    static void PrintNow(const char *gxtName, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_NOW, ScriptVoid>(gxtName, timeMS, enable); }
    static void PrintStringInString(const char *gxtName, const char *gxtText, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_STRING_IN_STRING, ScriptVoid>(gxtName, gxtText, timeMS, enable); }
    static void PrintStringInStringNow(const char *gxtName, const char *gxtText, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_STRING_IN_STRING_NOW, ScriptVoid>(gxtName, gxtText, timeMS, enable); }
    //static void PrintStringWithLiteralStringNow(const char *gxtName, const char *text, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_STRING_WITH_LITERAL_STRING_NOW, ScriptVoid>(gxtName, text, timeMS, enable); }
    static void PrintWith2Numbers(const char *gxtName, int value1, int value2, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_WITH_2_NUMBERS, ScriptVoid>(gxtName, value1, value2, timeMS, enable); }
    static void PrintWith2NumbersNow(const char *gxtName, int value1, int value2, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_WITH_2_NUMBERS_NOW, ScriptVoid>(gxtName, value1, value2, timeMS, enable); }
    static void PrintWithNumber(const char *gxtName, int value, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_WITH_NUMBER, ScriptVoid>(gxtName, value, timeMS, enable); }
    static void PrintWithNumberBig(const char *gxtName, int value, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_WITH_NUMBER_BIG, ScriptVoid>(gxtName, value, timeMS, enable); }
    static void PrintWithNumberNow(const char *gxtName, int value, unsigned int timeMS, bool enable) { NativeInvoke::Invoke<NATIVE_PRINT_WITH_NUMBER_NOW, ScriptVoid>(gxtName, value, timeMS, enable); }
    static void PrintFloat(float value) { NativeInvoke::Invoke<NATIVE_PRINTFLOAT, ScriptVoid>(value); }
    static void PrintInt(int value) { NativeInvoke::Invoke<NATIVE_PRINTINT, ScriptVoid>(value); }
    static void PrintNL() { NativeInvoke::Invoke<NATIVE_PRINTNL, ScriptVoid>(); }
    static void PrintString(const char *value) { NativeInvoke::Invoke<NATIVE_PRINTSTRING, ScriptVoid>(value); }
    static void PrintVector(float x, float y, float z) { NativeInvoke::Invoke<NATIVE_PRINTVECTOR, ScriptVoid>(x, y, z); }
    static void RequestAdditionalText(const char *textName, unsigned int textIndex) { NativeInvoke::Invoke<NATIVE_REQUEST_ADDITIONAL_TEXT, ScriptVoid>(textName, textIndex); }
    static void SetTextScale(float w, float h) { NativeInvoke::Invoke<NATIVE_SET_TEXT_SCALE, ScriptVoid>(w, h); }
    static void SetTextBackground(bool value) { NativeInvoke::Invoke<NATIVE_SET_TEXT_BACKGROUND, ScriptVoid>(value); }
    static void SetTextCentre(bool value) { NativeInvoke::Invoke<NATIVE_SET_TEXT_CENTRE, ScriptVoid>(value); }
    static void SetTextColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { NativeInvoke::Invoke<NATIVE_SET_TEXT_COLOUR, ScriptVoid>(r, g, b, a); }
    static void SetTextDrawBeforeFade(bool value) { NativeInvoke::Invoke<NATIVE_SET_TEXT_DRAW_BEFORE_FADE, ScriptVoid>(value); }
    static void SetTextDropshadow(bool displayShadow, unsigned char r, unsigned char g, unsigned char b, unsigned char a) { NativeInvoke::Invoke<NATIVE_SET_TEXT_DROPSHADOW, ScriptVoid>(displayShadow, r, g, b, a); }
    static void SetTextEdge(bool displayEdge, unsigned char r, unsigned char g, unsigned char b, unsigned char a) { NativeInvoke::Invoke<NATIVE_SET_TEXT_EDGE, ScriptVoid>(displayEdge, r, g, b, a); }
    static void SetTextFont(eTextFont font) { NativeInvoke::Invoke<NATIVE_SET_TEXT_FONT, ScriptVoid>(font); }
    static void SetTextJustify(bool value) { NativeInvoke::Invoke<NATIVE_SET_TEXT_JUSTIFY, ScriptVoid>(value); }
    static void SetTextLineDisplay(unsigned int unk1, unsigned int unk2) { NativeInvoke::Invoke<NATIVE_SET_TEXT_LINE_DISPLAY, ScriptVoid>(unk1, unk2); }
    static void SetTextLineHeightMult(float lineHeight) { NativeInvoke::Invoke<NATIVE_SET_TEXT_LINE_HEIGHT_MULT, ScriptVoid>(lineHeight); }
    static void SetTextProportional(bool value) { NativeInvoke::Invoke<NATIVE_SET_TEXT_PROPORTIONAL, ScriptVoid>(value); }
    static void SetTextRenderId(unsigned int renderId) { NativeInvoke::Invoke<NATIVE_SET_TEXT_RENDER_ID, ScriptVoid>(renderId); }
    static void SetTextRightJustify(bool value) { NativeInvoke::Invoke<NATIVE_SET_TEXT_RIGHT_JUSTIFY, ScriptVoid>(value); }
    static void SetTextToUseTextFileColours(bool value) { NativeInvoke::Invoke<NATIVE_SET_TEXT_TO_USE_TEXT_FILE_COLOURS, ScriptVoid>(value); }
    static void SetTextUseUnderscore(bool value) { NativeInvoke::Invoke<NATIVE_SET_TEXT_USE_UNDERSCORE, ScriptVoid>(value); }
    static void SetTextWrap(float unk1, float unk2) { NativeInvoke::Invoke<NATIVE_SET_TEXT_WRAP, ScriptVoid>(unk1, unk2); }

    // Textures
    static Texture GetTexture(TextureDict dictionary, const char *textureName) { return NativeInvoke::Invoke<NATIVE_GET_TEXTURE, Texture>(dictionary, textureName); }
    static Texture GetTextureFromStreamedTxd(const char *txdName, const char *textureName) { return NativeInvoke::Invoke<NATIVE_GET_TEXTURE_FROM_STREAMED_TXD, Texture>(txdName, textureName); }
    static TextureDict GetTxd(const char *txdName) { return NativeInvoke::Invoke<NATIVE_GET_TXD, TextureDict>(txdName); }
    static bool HasStreamedTxdLoaded(const char *txdName) { return NativeInvoke::Invoke<NATIVE_HAS_STREAMED_TXD_LOADED, bool>(txdName); }
    static TextureDict LoadTxd(const char *txdName) { return NativeInvoke::Invoke<NATIVE_LOAD_TXD, TextureDict>(txdName); }
    static void MarkStreamedTxdAsNoLongerNeeded(const char *txdName) { NativeInvoke::Invoke<NATIVE_MARK_STREAMED_TXD_AS_NO_LONGER_NEEDED, ScriptVoid>(txdName); }
    static void ReleaseTexture(Texture texture) { NativeInvoke::Invoke<NATIVE_RELEASE_TEXTURE, ScriptVoid>(texture); }
    static void RequestStreamedTxd(const char *txdName, bool unknown) { NativeInvoke::Invoke<NATIVE_REQUEST_STREAMED_TXD, ScriptVoid>(txdName, unknown); }
    static void RemoveTxd(TextureDict txd) { NativeInvoke::Invoke<NATIVE_REMOVE_TXD, ScriptVoid>(txd); }

    // Stats
    static void DecrementIntStat(eIntStatistic stat, unsigned int amount) { NativeInvoke::Invoke<NATIVE_DECREMENT_INT_STAT, ScriptVoid>(stat, amount); }
    static unsigned int GetIntStat(eIntStatistic stat) { return NativeInvoke::Invoke<NATIVE_GET_INT_STAT, unsigned int>(stat); }
    static void IncrementFloatStatNoMessage(eFloatStatistic stat, float value) { NativeInvoke::Invoke<NATIVE_INCREMENT_FLOAT_STAT_NO_MESSAGE, ScriptVoid>(stat, value); }
    static void IncrementIntStat(eIntStatistic stat, unsigned int value) { NativeInvoke::Invoke<NATIVE_INCREMENT_INT_STAT, ScriptVoid>(stat, value); }
    static void IncrementIntStatNoMessage(eIntStatistic stat, unsigned int value) { NativeInvoke::Invoke<NATIVE_INCREMENT_INT_STAT_NO_MESSAGE, ScriptVoid>(stat, value); }
    //static void SetIntStat(eIntStatistic stat, unsigned int value) { NativeInvoke::Invoke<NATIVE_SET_INT_STAT, ScriptVoid>(stat, value); }

    // Pad (controls)
    static bool GetPadPitchRoll(unsigned int padIndex, float *pPitch, float *pRoll) { return NativeInvoke::Invoke<NATIVE_GET_PAD_PITCH_ROLL, bool>(padIndex, pPitch, pRoll); }
    static void GetPositionOfAnalogueSticks(unsigned int padIndex, unsigned int *pLeftX, unsigned int *pLeftY, unsigned int *pRightX, unsigned int *pRightY) { NativeInvoke::Invoke<NATIVE_GET_POSITION_OF_ANALOGUE_STICKS, ScriptVoid>(padIndex, pLeftX, pLeftY, pRightX, pRightY); }
    static bool IsButtonJustPressed(unsigned int padIndex, ePadButton button) { return NativeInvoke::Invoke<NATIVE_IS_BUTTON_JUST_PRESSED, bool>(padIndex, button); }
    static bool IsButtonPressed(unsigned int padIndex, ePadButton button) { return NativeInvoke::Invoke<NATIVE_IS_BUTTON_PRESSED, bool>(padIndex, button); }

    // Sound
    static eSound GetSoundId() { return NativeInvoke::Invoke<NATIVE_GET_SOUND_ID, eSound>(); }
    static bool HasSoundFinished(eSound sound) { return NativeInvoke::Invoke<NATIVE_HAS_SOUND_FINISHED, bool>(sound); }
    static void PlayAudioEvent(char *name) { NativeInvoke::Invoke<NATIVE_PLAY_AUDIO_EVENT, ScriptVoid>(name); }
    static void PlaySoundFrontend(eSound sound, char *soundName) { NativeInvoke::Invoke<NATIVE_PLAY_SOUND_FRONTEND, ScriptVoid>(sound, soundName); }
    static void SetVariableOnSound(eSound sound, char *varname, float value) { NativeInvoke::Invoke<NATIVE_SET_VARIABLE_ON_SOUND, ScriptVoid>(sound, varname, value); }
    static void StopSound(eSound sound) { NativeInvoke::Invoke<NATIVE_STOP_SOUND, ScriptVoid>(sound); }
    static void ReleaseSoundId(eSound sound) { NativeInvoke::Invoke<NATIVE_RELEASE_SOUND_ID, ScriptVoid>(sound); }

    // Time
    static void ForceTimeOfDay(unsigned int hour, unsigned int minute) { NativeInvoke::Invoke<NATIVE_FORCE_TIME_OF_DAY, ScriptVoid>(hour, minute); }
    static void ForwardToTimeOfDay(unsigned int hour, unsigned int minute) { NativeInvoke::Invoke<NATIVE_FORWARD_TO_TIME_OF_DAY, ScriptVoid>(hour, minute); }
    static void GetCurrentDate(unsigned int *day, unsigned int *month) { NativeInvoke::Invoke<NATIVE_GET_CURRENT_DATE, ScriptVoid>(day, month); }
    static unsigned int GetCurrentDayOfWeek() { return NativeInvoke::Invoke<NATIVE_GET_CURRENT_DAY_OF_WEEK, unsigned int>(); }
    static unsigned int GetHoursOfDay() { return NativeInvoke::Invoke<NATIVE_GET_HOURS_OF_DAY, unsigned int>(); }
    static unsigned int GetMinutesOfDay() { return NativeInvoke::Invoke<NATIVE_GET_MINUTES_OF_DAY, unsigned int>(); }
    static unsigned int GetMinutesToTimeOfDay(unsigned int hour, unsigned int minute) { return NativeInvoke::Invoke<NATIVE_GET_MINUTES_TO_TIME_OF_DAY, unsigned int>(hour, minute); }
    static void GetTimeOfDay(unsigned int *hour, unsigned int *minute) { NativeInvoke::Invoke<NATIVE_GET_TIME_OF_DAY, ScriptVoid>(hour, minute); }
    static void ReleaseTimeOfDay() { NativeInvoke::Invoke<NATIVE_RELEASE_TIME_OF_DAY, ScriptVoid>(); }
    //static void SetTimeOfDay(unsigned int hour, unsigned int minute) { NativeInvoke::Invoke<NATIVE_SET_TIME_OF_DAY, ScriptVoid>(hour, minute); }
    static void SetTimeOneDayBack() { NativeInvoke::Invoke<NATIVE_SET_TIME_ONE_DAY_BACK, ScriptVoid>(); }
    static void SetTimeOneDayForward() { NativeInvoke::Invoke<NATIVE_SET_TIME_ONE_DAY_FORWARD, ScriptVoid>(); }
    static void SetTimeScale(float scale) { NativeInvoke::Invoke<NATIVE_SET_TIME_SCALE, ScriptVoid>(scale); }

    // Fires
    static bool IsScriptFireExtinguished(FireId fire) { return NativeInvoke::Invoke<NATIVE_IS_SCRIPT_FIRE_EXTINGUISHED, bool>(fire); }
    static void RemoveScriptFire(FireId fire) { NativeInvoke::Invoke<NATIVE_REMOVE_SCRIPT_FIRE, ScriptVoid>(fire); }
    //static FireId StartCarFire(Vehicle vehicle) { return NativeInvoke::Invoke<NATIVE_START_CAR_FIRE, ScriptAny>(vehicle); }
    static FireId StartCharFire(Ped ped) { return NativeInvoke::Invoke<NATIVE_START_CHAR_FIRE, ScriptAny>(ped); }
    static FireId StartScriptFire(float x, float y, float z, unsigned char numGenerationsAllowed = 0, unsigned int strength = 1) { return NativeInvoke::Invoke<NATIVE_START_SCRIPT_FIRE, unsigned int>(x, y, z, numGenerationsAllowed, strength); }

    // Radio
    static void DisableFrontEndRadio() { NativeInvoke::Invoke<NATIVE_DISABLE_FRONTEND_RADIO, ScriptVoid>(); }
    static void EnableFrontEndRadio() { NativeInvoke::Invoke<NATIVE_ENABLE_FRONTEND_RADIO, ScriptVoid>(); }
    static void FreezeRadioStation(const char *stationName) { NativeInvoke::Invoke<NATIVE_FREEZE_RADIO_STATION, ScriptVoid>(stationName); }
    static eRadioStation GetPlayerRadioStationIndex() { return NativeInvoke::Invoke<NATIVE_GET_PLAYER_RADIO_STATION_INDEX, eRadioStation>(); }
    static const char *GetPlayerRadioStationName() { return NativeInvoke::Invoke<NATIVE_GET_PLAYER_RADIO_STATION_NAME, const char *>(); }
    static bool IsRadioRetuning() { return NativeInvoke::Invoke<NATIVE_IS_RADIO_RETUNING, bool>(); }
    static void RetuneRadioToStationIndex(eRadioStation radioStation) { NativeInvoke::Invoke<NATIVE_RETUNE_RADIO_TO_STATION_INDEX, ScriptVoid>(radioStation); }

    // Game/Misc
    static void AbortAllGarageActivity() { NativeInvoke::Invoke<NATIVE_ABORT_ALL_GARAGE_ACTIVITY, ScriptVoid>(); }
    static void ActivateCheat(eCheat cheat) { NativeInvoke::Invoke<NATIVE_ACTIVATE_CHEAT, ScriptVoid>(cheat); }
    static void ActivateFrontEnd() { NativeInvoke::Invoke<NATIVE_ACTIVATE_FRONTEND, unsigned int>(); }
    static void ActivateSaveMenu() { NativeInvoke::Invoke<NATIVE_ACTIVATE_SAVE_MENU, ScriptVoid>(); }
    static void AddExplosion(float x, float y, float z, unsigned int p3, float p4, unsigned int p5, unsigned int p6, float p7) { NativeInvoke::Invoke<NATIVE_ADD_EXPLOSION, ScriptVoid>(x, y, z, p3, p4, p5, p6, p7); }
    //static void AllowEmergencyServices(bool allow) { NativeInvoke::Invoke<NATIVE_ALLOW_EMERGENCY_SERVICES, ScriptVoid>(allow); }
    static void AllowGameToPauseForStreaming(bool allow) { NativeInvoke::Invoke<NATIVE_ALLOW_GAME_TO_PAUSE_FOR_STREAMING, ScriptVoid>(allow); }
    static void AllowStuntJumpsToTrigger(bool allow) { NativeInvoke::Invoke<NATIVE_ALLOW_STUNT_JUMPS_TO_TRIGGER, ScriptVoid>(allow); }
    //static bool AreWidescreenBordersActive() { return NativeInvoke::Invoke<NATIVE_ARE_WIDESCREEN_BORDERS_ACTIVE, bool>(); }
    static ScriptAny AwardAchievement(eAchievement achievement) { return NativeInvoke::Invoke<NATIVE_AWARD_ACHIEVEMENT, ScriptAny>(achievement); }
    //static bool CanPhoneBeSeenOnScreen() { return NativeInvoke::Invoke<NATIVE_CAN_PHONE_BE_SEEN_ON_SCREEN, bool>(); }
    static void CancelOverrideRestart() { NativeInvoke::Invoke<NATIVE_CANCEL_OVERRIDE_RESTART, ScriptVoid>(); }
    static void ClearShakePlayerPadWhenControllerDisabled() { NativeInvoke::Invoke<NATIVE_CLEAR_SHAKE_PLAYERPAD_WHEN_CONTROLLER_DISABLED, ScriptVoid>(); }
    static void ClearTimeCycleModifier() { NativeInvoke::Invoke<NATIVE_CLEAR_TIMECYCLE_MODIFIER, ScriptVoid>(); }
    static void DeactivateFrontEnd() { NativeInvoke::Invoke<NATIVE_DEACTIVATE_FRONTEND, ScriptVoid>(); }
    static bool DidSaveCompleteSuccessfully() { return NativeInvoke::Invoke<NATIVE_DID_SAVE_COMPLETE_SUCCESSFULLY, bool>(); }
    static void DisablePauseMenu(bool disabled) { NativeInvoke::Invoke<NATIVE_DISABLE_PAUSE_MENU, ScriptVoid>(disabled); }
    static void DisablePoliceScanner() { NativeInvoke::Invoke<NATIVE_DISABLE_POLICE_SCANNER, ScriptVoid>(); }
    static void DisplayAmmo(bool display) { NativeInvoke::Invoke<NATIVE_DISPLAY_AMMO, ScriptVoid>(display); }
    static void DisplayAreaName(bool display) { NativeInvoke::Invoke<NATIVE_DISPLAY_AREA_NAME, ScriptVoid>(display); }
    static void DisplayCash(bool display) { NativeInvoke::Invoke<NATIVE_DISPLAY_CASH, ScriptVoid>(display); }
    static void DisplayFrontEndMapBlips(bool display) { NativeInvoke::Invoke<NATIVE_DISPLAY_FRONTEND_MAP_BLIPS, ScriptVoid>(display); }
    static void DisplayHUD(bool display) { NativeInvoke::Invoke<NATIVE_DISPLAY_HUD, ScriptVoid>(display); }
    static void DisplayRadar(bool display) { NativeInvoke::Invoke<NATIVE_DISPLAY_RADAR, ScriptVoid>(display); }
    static void DisplaySniperScopeThisFrame() { NativeInvoke::Invoke<NATIVE_DISPLAY_SNIPER_SCOPE_THIS_FRAME, ScriptVoid>(); }
    static void DoAutoSave() { NativeInvoke::Invoke<NATIVE_DO_AUTO_SAVE, ScriptVoid>(); }
    static void DoScreenFadeIn(unsigned int timeMS) { NativeInvoke::Invoke<NATIVE_DO_SCREEN_FADE_IN, ScriptVoid>(timeMS); }
    static void DoScreenFadeInUnhacked(unsigned int timeMS) { NativeInvoke::Invoke<NATIVE_DO_SCREEN_FADE_IN_UNHACKED, ScriptVoid>(timeMS); }
    static void DoScreenFadeOut(unsigned int timeMS) { NativeInvoke::Invoke<NATIVE_DO_SCREEN_FADE_OUT, ScriptVoid>(timeMS); }
    static void DoScreenFadeOutUnhacked(unsigned int timeMS) { NativeInvoke::Invoke<NATIVE_DO_SCREEN_FADE_OUT_UNHACKED, ScriptVoid>(timeMS); }
    static void DrawRect(float x1, float y1, float x2, float y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a) { NativeInvoke::Invoke<NATIVE_DRAW_RECT, ScriptVoid>(x1, y1, x2, y2, r, g, b, a); }
    static void EnableMaxAmmoCap(bool enable) { NativeInvoke::Invoke<NATIVE_ENABLE_MAX_AMMO_CAP, ScriptVoid>(enable); }
    static void EnablePoliceScanner() { NativeInvoke::Invoke<NATIVE_ENABLE_POLICE_SCANNER, ScriptVoid>(); }
    static void EnableSceneStreaming(bool enable) { NativeInvoke::Invoke<NATIVE_ENABLE_SCENE_STREAMING, ScriptVoid>(enable); }
    static void FakeDeathArrest() { NativeInvoke::Invoke<NATIVE_FAKE_DEATHARREST, ScriptVoid>(); }
    static void FindStreetNameAtPosition(float pX, float pY, float pZ, unsigned int *strHash0, unsigned int *strHash1) { NativeInvoke::Invoke<NATIVE_FIND_STREET_NAME_AT_POSITION, ScriptVoid>(pX, pY, pZ, strHash0, strHash1); }
    static void FireSingleBullet(float x, float y, float z, float targetX, float targetY, float targetZ, unsigned int unknown) { NativeInvoke::Invoke<NATIVE_FIRE_SINGLE_BULLET, ScriptVoid>(x, y, z, targetX, targetY, targetZ, unknown); }
    //static void FlashWeaponIcon(bool on) { NativeInvoke::Invoke<NATIVE_FLASH_WEAPON_ICON, ScriptVoid>(on); }
    static void ForceInitialPlayerStation(const char *stationName) { NativeInvoke::Invoke<NATIVE_FORCE_INITIAL_PLAYER_STATION, ScriptVoid>(stationName); }
    static void ForceLoadingScreen(bool force) { NativeInvoke::Invoke<NATIVE_FORCE_LOADING_SCREEN, ScriptVoid>(force); }
    static void GetCorrectedColour(unsigned int r, unsigned int g, unsigned int b, unsigned int *pR, unsigned int *pG, unsigned int *pB) { NativeInvoke::Invoke<NATIVE_GET_CORRECTED_COLOUR, ScriptVoid>(r, g, b, pR, pG, pB); }
    static bool GetCreateRandomCops() { return NativeInvoke::Invoke<NATIVE_GET_CREATE_RANDOM_COPS, bool>(); }
    static unsigned int GetCurrentEpisode() { return NativeInvoke::Invoke<NATIVE_GET_CURRENT_EPISODE, unsigned int>(); }
    static eLanguage GetCurrentLanguage() { return NativeInvoke::Invoke<NATIVE_GET_CURRENT_LANGUAGE, eLanguage>(); }
    static unsigned int GetEpisodeIndexFromSummons() { return NativeInvoke::Invoke<NATIVE_GET_EPISODE_INDEX_FROM_SUMMONS, ScriptAny>(); }
    static const char * GetEpisodeName(unsigned int episodeIndex) { return NativeInvoke::Invoke<NATIVE_GET_EPISODE_NAME, const char *>(episodeIndex); }
    static float GetFloatStat(eFloatStatistic stat) { return NativeInvoke::Invoke<NATIVE_GET_FLOAT_STAT, float>(stat); }
    static void GetFrameTime(float *time) { NativeInvoke::Invoke<NATIVE_GET_FRAME_TIME, ScriptVoid>(time); }
    static void GetGameTimer(unsigned int *pTimer) { NativeInvoke::Invoke<NATIVE_GET_GAME_TIMER, ScriptVoid>(pTimer); }
    static unsigned int GetHashKey(const char *value) { return NativeInvoke::Invoke<NATIVE_GET_HASH_KEY, ScriptAny>(value); }
    static void GetHUDColour(eHUDType type, unsigned int *pR, unsigned int *pG, unsigned int *pB, ScriptAny *pUnknown) { NativeInvoke::Invoke<NATIVE_GET_HUD_COLOUR, ScriptVoid>(type, pR, pG, pB, pUnknown); }
    static unsigned int GetIdOfThisThread() { return NativeInvoke::Invoke<NATIVE_GET_ID_OF_THIS_THREAD, unsigned int>(); }
    static bool GetIsDepositAnimRunning() { return NativeInvoke::Invoke<NATIVE_GET_IS_DEPOSIT_ANIM_RUNNING, bool>(); }
    static bool GetIsHiDef() { return NativeInvoke::Invoke<NATIVE_GET_IS_HIDEF, bool>(); }
    static bool GetIsWidescreen() { return NativeInvoke::Invoke<NATIVE_GET_IS_WIDESCREEN, bool>(); }
    static unsigned int GetLeftPlayerCashToReachLevel(unsigned int playerRank) { return NativeInvoke::Invoke<NATIVE_GET_LEFT_PLAYER_CASH_TO_REACH_LEVEL, unsigned int>(playerRank); }
    static eMapArea GetMapAreaFromCoords(float x, float y, float z) { return NativeInvoke::Invoke<NATIVE_GET_MAP_AREA_FROM_COORDS, eMapArea>(x, y, z); }
    static bool GetMissionFlag() { return NativeInvoke::Invoke<NATIVE_GET_MISSION_FLAG, bool>(); }
    static void GetMaxWantedLevel(unsigned int *pMaxWantedLevel) { NativeInvoke::Invoke<NATIVE_GET_MAX_WANTED_LEVEL, ScriptVoid>(pMaxWantedLevel); }
    static const char *GetNameOfInfoZone(float x, float y, float z) { return NativeInvoke::Invoke<NATIVE_GET_NAME_OF_INFO_ZONE, const char *>(x, y, z); }
    static const char *GetNameOfZone(float x, float y, float z) { return NativeInvoke::Invoke<NATIVE_GET_NAME_OF_ZONE, const char *>(x, y, z); }
    static unsigned int GetNumStreamingRequests() { return NativeInvoke::Invoke<NATIVE_GET_NUM_STREAMING_REQUESTS, unsigned int>(); }
    static unsigned int GetNumberOfInstancesOfStreamedScript(const char *scriptName) { return NativeInvoke::Invoke<NATIVE_GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT, unsigned int>(scriptName); }
    static unsigned int GetNumberOfPlayers() { return NativeInvoke::Invoke<NATIVE_GET_NUMBER_OF_PLAYERS, unsigned int>(); }
    static unsigned int GetTimeSinceLastArrest() { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_LAST_ARREST, unsigned int>(); }
    static unsigned int GetTimeSinceLastDeath() { return NativeInvoke::Invoke<NATIVE_GET_TIME_SINCE_LAST_DEATH, unsigned int>(); }
    static bool HasAchievementBeenPassed(eAchievement achievement) { return NativeInvoke::Invoke<NATIVE_HAS_ACHIEVEMENT_BEEN_PASSED, bool>(achievement); }
    static bool HasDeathArrestExecuted() { return NativeInvoke::Invoke<NATIVE_HAS_DEATHARREST_EXECUTED, bool>(); }
    static bool HasResprayHappened() { return NativeInvoke::Invoke<NATIVE_HAS_RESPRAY_HAPPENED, bool>(); }
    static bool HasScriptLoaded(const char *scriptName) { return NativeInvoke::Invoke<NATIVE_HAS_SCRIPT_LOADED, bool>(scriptName); }
    static bool HaveAnimsLoaded(const char *animName) { return NativeInvoke::Invoke<NATIVE_HAVE_ANIMS_LOADED, bool>(animName); }
    static bool HaveRequestedPathNodesBeenLoaded(unsigned int requestId) { return NativeInvoke::Invoke<NATIVE_HAVE_REQUESTED_PATH_NODES_BEEN_LOADED, bool>(requestId); }
    static void HideHelpTextThisFrame() { NativeInvoke::Invoke<NATIVE_HIDE_HELP_TEXT_THIS_FRAME, ScriptVoid>(); }
    static void HideHUDAndRadarThisFrame() { NativeInvoke::Invoke<NATIVE_HIDE_HUD_AND_RADAR_THIS_FRAME, ScriptVoid>(); }
    static bool IsAussieVersion() { return NativeInvoke::Invoke<NATIVE_IS_AUSSIE_VERSION, bool>(); }
    static bool IsAutoAimingOn() { return NativeInvoke::Invoke<NATIVE_IS_AUTO_AIMING_ON, bool>(); }
    static bool IsAutoSaveInProgress() { return NativeInvoke::Invoke<NATIVE_IS_AUTO_SAVE_IN_PROGRESS, bool>(); }
    static bool IsInteriorScene() { return NativeInvoke::Invoke<NATIVE_IS_INTERIOR_SCENE, bool>(); }
    static bool IsFrontEndFading() { return NativeInvoke::Invoke<NATIVE_IS_FRONTEND_FADING, bool>(); }
    static bool IsGameInControlOfMusic() { return NativeInvoke::Invoke<NATIVE_IS_GAME_IN_CONTROL_OF_MUSIC, bool>(); }
    static bool IsGermanVersion() { return NativeInvoke::Invoke<NATIVE_IS_GERMAN_VERSION, bool>(); }
    static bool IsHelpMessageBeingDisplayed() { return NativeInvoke::Invoke<NATIVE_IS_HELP_MESSAGE_BEING_DISPLAYED, bool>(); }
    //static bool IsHintRunning() { return NativeInvoke::Invoke<NATIVE_IS_HINT_RUNNING, bool>(); }
    static bool IsHUDPreferenceSwitchedOn() { return NativeInvoke::Invoke<NATIVE_IS_HUD_PREFERENCE_SWITCHED_ON, bool>(); }
    static bool IsHUDReticuleComplex() { return NativeInvoke::Invoke<NATIVE_IS_HUD_RETICULE_COMPLEX, bool>(); }
    static bool IsInSpectatorMode() { return NativeInvoke::Invoke<NATIVE_IS_IN_SPECTATOR_MODE, bool>(); }
    static bool IsLookInverted() { return NativeInvoke::Invoke<NATIVE_IS_LOOK_INVERTED, bool>(); }
    static bool IsMemoryCardInUse() { return NativeInvoke::Invoke<NATIVE_IS_MEMORY_CARD_IN_USE, bool>(); }
    static bool IsMessageBeingDisplayed() { return NativeInvoke::Invoke<NATIVE_IS_MESSAGE_BEING_DISPLAYED, bool>(); }
    static bool IsMinigameInProgress() { return NativeInvoke::Invoke<NATIVE_IS_MINIGAME_IN_PROGRESS, bool>(); }
    static bool IsMissionCompletePlaying() { return NativeInvoke::Invoke<NATIVE_IS_MISSION_COMPLETE_PLAYING, bool>(); }
    static bool IsMobilePhoneCallOngoing() { return NativeInvoke::Invoke<NATIVE_IS_MOBILE_PHONE_CALL_ONGOING, bool>(); }
    static bool IsMobilePhoneRadioActive() { return NativeInvoke::Invoke<NATIVE_IS_MOBILE_PHONE_RADIO_ACTIVE, bool>(); }
    static bool IsPauseMenuActive() { return NativeInvoke::Invoke<NATIVE_IS_PAUSE_MENU_ACTIVE, bool>(); }
    static bool IsPayNSprayActive() { return NativeInvoke::Invoke<NATIVE_IS_PAY_N_SPRAY_ACTIVE, bool>(); }
    static bool IsPlayerBeingArrested() { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_BEING_ARRESTED, bool>(); }
    static bool IsPlayerOnline() { return NativeInvoke::Invoke<NATIVE_IS_PLAYER_ONLINE, bool>(); }
    static bool IsScreenFadedIn() { return NativeInvoke::Invoke<NATIVE_IS_SCREEN_FADED_IN, bool>(); }
    static bool IsScreenFadedOut() { return NativeInvoke::Invoke<NATIVE_IS_SCREEN_FADED_OUT, bool>(); }
    static bool IsScreenFading() { return NativeInvoke::Invoke<NATIVE_IS_SCREEN_FADING, bool>(); }
    static bool IsScreenFadingIn() { return NativeInvoke::Invoke<NATIVE_IS_SCREEN_FADING_IN, bool>(); }
    static bool IsScreenFadingOut() { return NativeInvoke::Invoke<NATIVE_IS_SCREEN_FADING_OUT, bool>(); }
    static bool IsSniperInverted() { return NativeInvoke::Invoke<NATIVE_IS_SNIPER_INVERTED, bool>(); }
    static bool IsSystemUIShowing() { return NativeInvoke::Invoke<NATIVE_IS_SYSTEM_UI_SHOWING, bool>(); }
    static bool IsThisAMinigameScript() { return NativeInvoke::Invoke<NATIVE_IS_THIS_A_MINIGAME_SCRIPT, bool>(); }
    static bool IsThreadActive(unsigned int threadId) { return NativeInvoke::Invoke<NATIVE_IS_THREAD_ACTIVE, bool>(threadId); }
    static unsigned int LoadAllPathNodes(bool value) { return NativeInvoke::Invoke<NATIVE_LOAD_ALL_PATH_NODES, ScriptAny>(value); }
    static void MarkScriptAsNoLongerNeeded(const char *scriptName) { NativeInvoke::Invoke<NATIVE_MARK_SCRIPT_AS_NO_LONGER_NEEDED, ScriptVoid>(scriptName); }
    static void PauseGame() { NativeInvoke::Invoke<NATIVE_PAUSE_GAME, ScriptVoid>(); }
    static void PlayMovie() { NativeInvoke::Invoke<NATIVE_PLAY_MOVIE, ScriptVoid>(); }
    static void PopulateNow() { NativeInvoke::Invoke<NATIVE_POPULATE_NOW, ScriptVoid>(); }
    static void RequestAnims(const char *animName) { NativeInvoke::Invoke<NATIVE_REQUEST_ANIMS, ScriptVoid>(animName); }
    static void ReleaseMovie() { NativeInvoke::Invoke<NATIVE_RELEASE_MOVIE, ScriptVoid>(); }
    static void ReleaseWeather() { NativeInvoke::Invoke<NATIVE_RELEASE_WEATHER, ScriptVoid>(); }
    static void RemoveAnims(const char *animName) { NativeInvoke::Invoke<NATIVE_REMOVE_ANIMS, ScriptVoid>(animName); }
    static void RemoveCoverPoint(CoverPoint coverPoint) { NativeInvoke::Invoke<NATIVE_REMOVE_COVER_POINT, ScriptVoid>(coverPoint); }
    static void RemoveIpl(const char *iplName) { NativeInvoke::Invoke<NATIVE_REMOVE_IPL, ScriptVoid>(iplName); }
    static void RequestIpl(const char *iplName) { NativeInvoke::Invoke<NATIVE_REQUEST_IPL, ScriptVoid>(iplName); }
	//static void SetCameraControlsDisabledWithPlayerControls(bool value) { NativeInvoke::Invoke<NATIVE_SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS, ScriptVoid>(value); }
    static void SetMissionFlag(bool isMission) { NativeInvoke::Invoke<NATIVE_SET_MISSION_FLAG, ScriptVoid>(isMission); }
    //static void SetFloatStat(eFloatStatistic stat, float value) { NativeInvoke::Invoke<NATIVE_SET_FLOAT_STAT, ScriptVoid>(stat, value); }
    static void SetRadarZoom(float zoom) { NativeInvoke::Invoke<NATIVE_SET_RADAR_ZOOM, ScriptVoid>(zoom); }
    static void SetTimerA(unsigned int value) { NativeInvoke::Invoke<NATIVE_SETTIMERA, ScriptVoid>(value); }
    static void SetTimerB(unsigned int value) { NativeInvoke::Invoke<NATIVE_SETTIMERB, ScriptVoid>(value); }
    static void SetWantedMultiplier(float multiplier) { NativeInvoke::Invoke<NATIVE_SET_WANTED_MULTIPLIER, ScriptVoid>(multiplier); }
    //static void TerminateThisScript() { NativeInvoke::Invoke<NATIVE_TERMINATE_THIS_SCRIPT, ScriptVoid>(); }   // Don't use this from a NativeThread (NativeFiberThread overrides this function)
    static unsigned int TimerA() { return NativeInvoke::Invoke<NATIVE_TIMERA, unsigned int>(); }
    static unsigned int TimerB() { return NativeInvoke::Invoke<NATIVE_TIMERB, unsigned int>(); }
    static unsigned int TimeStep() { return NativeInvoke::Invoke<NATIVE_TIMESTEP, unsigned int>(); }
    static void UnlockLazlowStation() { NativeInvoke::Invoke<NATIVE_UNLOCK_LAZLOW_STATION, ScriptVoid>(); }
    static void UnregisterScriptWithAudio() { NativeInvoke::Invoke<NATIVE_UNREGISTER_SCRIPT_WITH_AUDIO, ScriptVoid>(); }
    static void UnPauseGame() { NativeInvoke::Invoke<NATIVE_UNPAUSE_GAME, ScriptVoid>(); }
    //static void Wait(unsigned int timeInMs) { NativeInvoke::Invoke<NATIVE_WAIT, ScriptVoid>(timeInMs); }   // Don't use this from a NativeThread (NativeFiberThread overrides this function)

    // General
    static float AbsF(float value) { return NativeInvoke::Invoke<NATIVE_ABSF, float>(value); }        // Prefer using function from <math.h> instead for performance
    static float AbsI(float value) { return NativeInvoke::Invoke<NATIVE_ABSI, float>(value); }        // Prefer using function from <math.h> instead for performance
    static float ASin(float value) { return NativeInvoke::Invoke<NATIVE_ASIN, float>(value); }        // Prefer using function from <math.h> instead for performance
    static float ATan(float value) { return NativeInvoke::Invoke<NATIVE_ATAN, float>(value); }        // Prefer using function from <math.h> instead for performance
    static int Ceil(float value) { return NativeInvoke::Invoke<NATIVE_CEIL, int>(value); }        // Prefer using function from <math.h> instead for performance
    static float Cos(float value) { return NativeInvoke::Invoke<NATIVE_COS, float>(value); }          // Prefer using function from <math.h> instead for performance
    static float ToFloat(unsigned int value) { return NativeInvoke::Invoke<NATIVE_TO_FLOAT, float>(value); } // Prefer casting instead for performance
    static unsigned int Floor(float value) { return NativeInvoke::Invoke<NATIVE_FLOOR, unsigned int>(value); }      // Prefer using function from <math.h> instead for performance
    static void GenerateRandomFloatInRange(float min, float max, float *pValue) { NativeInvoke::Invoke<NATIVE_GENERATE_RANDOM_FLOAT_IN_RANGE, ScriptVoid>(min, max, pValue); }
    static void GenerateRandomIntInRange(unsigned int min, unsigned int max, unsigned int *pValue) { NativeInvoke::Invoke<NATIVE_GENERATE_RANDOM_INT_IN_RANGE, ScriptVoid>(min, max, pValue); }
    static void GetAngleBetween2DVectors(float x1, float y1, float x2, float y2, float *pResult) { NativeInvoke::Invoke<NATIVE_GET_ANGLE_BETWEEN_2D_VECTORS, ScriptVoid>(x1, y1, x2, y2, pResult); }
    static void GetDistanceBetweenCoords2D(float x1, float y1, float x2, float y2, float *pDist) { NativeInvoke::Invoke<NATIVE_GET_DISTANCE_BETWEEN_COORDS_2D, ScriptVoid>(x1, y1, x2, y2, pDist); }
    static void GetDistanceBetweenCoords3D(float x1, float y1, float z1, float x2, float y2, float z2, float *pDist) { NativeInvoke::Invoke<NATIVE_GET_DISTANCE_BETWEEN_COORDS_3D, ScriptVoid>(x1, y1, z1, x2, y2, z2, pDist); }
    static const char *GetFirstNCharactersOfLiteralString(const char *literalString, unsigned int chars) { return NativeInvoke::Invoke<NATIVE_GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING, const char *>(literalString, chars); }
    static void GetHeadingFromVector2D(float x, float y, float *pHeading) { NativeInvoke::Invoke<NATIVE_GET_HEADING_FROM_VECTOR_2D, ScriptVoid>(x, y, pHeading); }
    static unsigned int GetLengthOfLiteralString(const char *literalString) { return NativeInvoke::Invoke<NATIVE_GET_LENGTH_OF_LITERAL_STRING, unsigned int>(literalString); }
    static bool IsStringNull(const char *str) { return NativeInvoke::Invoke<NATIVE_IS_STRING_NULL, bool>(str); }
    static float Sin(float value) { return NativeInvoke::Invoke<NATIVE_SIN, float>(value); }          // Prefer using function from <math.h> instead for performance
    static float Sqrt(float value) { return NativeInvoke::Invoke<NATIVE_SQRT, float>(value); }        // Prefer using function from <math.h> instead for performance
    static float Tan(float value) { return NativeInvoke::Invoke<NATIVE_TAN, float>(value); }          // Prefer using function from <math.h> instead for performance
	/**/
}
