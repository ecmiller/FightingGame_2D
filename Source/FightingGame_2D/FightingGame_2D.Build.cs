// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FightingGame_2D : ModuleRules
{
	public FightingGame_2D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
