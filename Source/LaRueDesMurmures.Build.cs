using UnrealBuildTool;
using System.Collections.Generic;

public class LaRueDesMurmuresTarget : TargetRules
{
    public LaRueDesMurmuresTarget(TargetInfo Target)
        : base(Target)
    {
        Type = TargetType.Game;

        DefaultBuildSettings =
            BuildSettingsVersion.V5;

        IncludeOrderVersion =
            EngineIncludeOrderVersion.Unreal5_4;

        ExtraModuleNames.Add(
            "LaRueDesMurmures"
        );
    }
}
