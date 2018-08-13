function OnFilterScriptInit()
{
	SetScriptName("Console test");
	SetScriptVersion("1.0.0.0");
	SetScriptAuthor("FaTony");
	print("Console test filterscript");
	CreateConVar("sqcvar", "default", "Test squirrel variable", 0);
	RegServerCmd("sqtest", "Command_sqtest", "Test squirrel command", 0);
}

function Command_sqtest(args)
{
	print("Squirrel test command");
	print("Args = "+args+"");
	for (local i = 1; i <= args; i++)
	{
		switch (GetCmdArgType(i))
		{
			case 0:
			{
			print("Arg "+i+" - type = float, value = "+GetCmdArgFloat(i)+"");
			break;
			}
			case 1:
			{
			print("Arg "+i+" - type = int, value = "+GetCmdArgInt(i)+"");
			break;
			}
			case 2:
			{
			print("Arg "+i+" - type = string, value = "+GetCmdArgString(i)+"");
			break;
			}
		}
	}
}