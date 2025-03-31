using UnrealBuildTool;
using System.Collections.Generic;

public class SurvivorsRoguelikeTarget : TargetRules
{
	public SurvivorsRoguelikeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange( new string[] { "SurvivorsRoguelike" } );
	}
}
