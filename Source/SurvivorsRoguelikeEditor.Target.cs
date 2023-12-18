using UnrealBuildTool;
using System.Collections.Generic;

public class SurvivorsRoguelikeEditorTarget : TargetRules
{
	public SurvivorsRoguelikeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange( new string[] { "SurvivorsRoguelike" } );
	}
}
