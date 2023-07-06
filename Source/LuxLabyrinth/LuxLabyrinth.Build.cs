// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LuxLabyrinth : ModuleRules
{
	public LuxLabyrinth(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule", "GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "MetasoundEngine" });
	}
}
