// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpaceWar : ModuleRules
{
	public SpaceWar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayCameras", //摄像机
			"GameplayTags", "GameplayAbilities", "GameplayTasks", //Gameplay技能
			"GameplayStateTreeModule", "StateTreeModule" //状态树
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}