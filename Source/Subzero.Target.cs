// Copyright FerroByte Studio

using UnrealBuildTool;
using System.Collections.Generic;

public class SubzeroTarget : TargetRules
{
	public SubzeroTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Subzero" } );
	}
}
