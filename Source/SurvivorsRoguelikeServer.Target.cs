using UnrealBuildTool;
using System.Collections.Generic;

public class SurvivorsRoguelikeServerTarget : TargetRules
{
	public SurvivorsRoguelikeServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SurvivorsRoguelike");
	}
}
