using UnrealBuildTool;
using System.Collections.Generic;

public class SurvivorsRoguelikeTarget : TargetRules
{
	public SurvivorsRoguelikeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange( new string[] { "SurvivorsRoguelike" } );
	}
}
