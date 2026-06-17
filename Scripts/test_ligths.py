# /project/scripts/test_lights.py

import unreal

unreal.log_warning("LIGHT TEST START")

try:
    sun = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.DirectionalLight,
        unreal.Vector(0,0,1000)
    )
    unreal.log_warning("SUN OK")
except Exception as e:
    unreal.log_error(f"SUN FAIL {e}")

try:
    sky = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.SkyLight,
        unreal.Vector(0,0,0)
    )
    unreal.log_warning("SKYLIGHT OK")
except Exception as e:
    unreal.log_error(f"SKYLIGHT FAIL {e}")

try:
    atmosphere = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.SkyAtmosphere,
        unreal.Vector(0,0,0)
    )
    unreal.log_warning("ATMOSPHERE OK")
except Exception as e:
    unreal.log_error(f"ATMOSPHERE FAIL {e}")

unreal.log_warning("LIGHT TEST END")
