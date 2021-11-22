// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CycleRacingProject : ModuleRules
{
	public CycleRacingProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ChaosVehicles", "HeadMountedDisplay", "PhysicsCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
