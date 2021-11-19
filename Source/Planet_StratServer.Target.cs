
using UnrealBuildTool;
using System.Collections.Generic;

public class Planet_StratServerTarget : TargetRules 
{
    public Planet_StratServerTarget(TargetInfo Target) : base(Target) 
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.Add("Planet_Strat"); 
    }
}