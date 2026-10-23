using UnrealBuildTool;
using System.Collections.Generic;

public class NewSimulatorTarget : TargetRules
{
    public NewSimulatorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("NewSimulator");
    }
}
