# /project/scripts/test_spawn_object.py

import unreal

unreal.log_warning("STEP 1")

mesh = unreal.EditorAssetLibrary.load_asset(
    "/Engine/BasicShapes/Cube.Cube"
)

unreal.log_warning("STEP 2")

actor = unreal.EditorLevelLibrary.spawn_actor_from_object(
    mesh,
    unreal.Vector(0,0,100),
    unreal.Rotator(0,0,0)
)

unreal.log_warning("STEP 3")
