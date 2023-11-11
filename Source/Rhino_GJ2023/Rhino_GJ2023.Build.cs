// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Rhino_GJ2023 : ModuleRules
{
	public Rhino_GJ2023(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "UMG" });
    }
}
