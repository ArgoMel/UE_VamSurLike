using UnrealBuildTool;

public class SurvivorsRoguelike : ModuleRules
{
	public SurvivorsRoguelike(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "AIModule",
            "GameplayTasks",
            "NavigationSystem",
            "UMG",
            "CinematicCamera",
            "EnhancedInput",
            "Niagara",
            "MovieScene",
            "LevelSequence",
            "MediaAssets",
            "Networking",
            "Sockets"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
