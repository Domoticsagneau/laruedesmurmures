import unreal

unreal.log_warning("STEP 1")

ground = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.StaticMeshActor,
    unreal.Vector(0,0,0)
)

unreal.log_warning("STEP 2")

comp = ground.get_component_by_class(unreal.StaticMeshComponent)

unreal.log_warning("STEP 3")

mesh = unreal.EditorAssetLibrary.load_asset(
    "/Engine/BasicShapes/Plane.Plane"
)

unreal.log_warning("STEP 4")

comp.set_static_mesh(mesh)

unreal.log_warning("STEP 5")
