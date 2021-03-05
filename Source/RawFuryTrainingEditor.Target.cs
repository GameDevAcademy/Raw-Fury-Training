// GameDev Academy 2021 - RawFury Training v1.0

using UnrealBuildTool;
using System.Collections.Generic;

public class RawFuryTrainingEditorTarget : TargetRules
{
	public RawFuryTrainingEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("RawFuryTraining");
	}
}
