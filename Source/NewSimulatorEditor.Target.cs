using UnrealBuildTool;
using System.Collections.Generic;

public class NewSimulatorEditorTarget : TargetRules
{
    public NewSimulatorEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("NewSimulator");
    }
}
