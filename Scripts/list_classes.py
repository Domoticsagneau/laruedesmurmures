# /project/scripts/list_classes.py

import unreal

classes = [
    "DirectionalLight",
    "SkyLight",
    "SkyAtmosphere",
    "ExponentialHeightFog",
    "VolumetricCloud",
    "StaticMeshActor"
]

for c in classes:
    try:
        obj = getattr(unreal, c)
        unreal.log_warning(f"FOUND {c}")
    except:
        unreal.log_warning(f"MISSING {c}")
