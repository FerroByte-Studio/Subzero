// Copyright FerroByte Studio

using UnrealBuildTool;
using System.Collections.Generic;

public class SubzeroEditorTarget : TargetRules
{
	public SubzeroEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Subzero" } );
	}
}
