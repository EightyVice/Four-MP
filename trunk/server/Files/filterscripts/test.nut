function OnFilterScriptInit()
{
	SetScriptName("Test filterscript");
	SetScriptVersion("1.0.0.0");
	SetScriptAuthor("FaTony");
	print("Filterscript loaded");
}

function OnFilterScriptExit()
{
	print("Filterscript unloading");
}