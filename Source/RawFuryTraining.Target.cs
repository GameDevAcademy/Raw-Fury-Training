// GameDev Academy 2021 - RawFury Training v1.0

using UnrealBuildTool;
using System.Collections.Generic;

public class RawFuryTrainingTarget : TargetRules
{
	public RawFuryTrainingTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("RawFuryTraining");
	}
}
