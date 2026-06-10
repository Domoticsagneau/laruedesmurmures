using UnrealBuildTool;
using System.Collections.Generic;

public class LaRueDesMurmuresEditorTarget : TargetRules
{
    public LaRueDesMurmuresEditorTarget(
        TargetInfo Target)
        : base(Target)
    {
        Type = TargetType.Editor;

        DefaultBuildSettings =
            BuildSettingsVersion.V5;

        IncludeOrderVersion =
            EngineIncludeOrderVersion.Unreal5_4;

        ExtraModuleNames.Add(
            "LaRueDesMurmures"
        );
    }
}
