using UnrealBuildTool;

public class LaRueDesMurmuresServerTarget : TargetRules
{
    public LaRueDesMurmuresServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
        ExtraModuleNames.Add("LaRueDesMurmures");
    }
}
