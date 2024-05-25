// Copyright JGodwin

using UnrealBuildTool;
using System.Collections.Generic;

public class LastStandTarget : TargetRules
{
	public LastStandTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "LastStand" } );
	}
}
