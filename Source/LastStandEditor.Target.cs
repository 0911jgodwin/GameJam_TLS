// Copyright JGodwin

using UnrealBuildTool;
using System.Collections.Generic;

public class LastStandEditorTarget : TargetRules
{
	public LastStandEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "LastStand" } );
	}
}
