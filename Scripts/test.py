# /project/scripts/test_spawn.py

import unreal

world = unreal.EditorLevelLibrary.get_editor_world()

sphere = unreal.EditorAssetLibrary.load_asset(
    "/Engine/BasicShapes/Sphere.Sphere"
)

actor = unreal.EditorLevelLibrary.spawn_actor_from_object(
    sphere,
    unreal.Vector(0, 0, 100),
    unreal.Rotator(0, 0, 0)
)

unreal.log_warning("SPHERE CREATED")
