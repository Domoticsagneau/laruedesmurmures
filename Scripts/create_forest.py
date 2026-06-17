import unreal
import random

# --------------------------------------------------
# CONFIG
# --------------------------------------------------

MAP_SIZE = 50000      # 500m UE units
TREE_COUNT = 800
PATH_WIDTH = 500
PATH_SEGMENTS = 20

# --------------------------------------------------
# HELPERS
# --------------------------------------------------

world = unreal.EditorLevelLibrary.get_editor_world()

def log(msg):
    unreal.log_warning(msg)

def load_mesh(path):
    mesh = unreal.EditorAssetLibrary.load_asset(path)
    if not mesh:
        raise RuntimeError(f"Missing mesh: {path}")
    return mesh

SPHERE = load_mesh("/Engine/BasicShapes/Sphere.Sphere")
CYLINDER = load_mesh("/Engine/BasicShapes/Cylinder.Cylinder")
CUBE = load_mesh("/Engine/BasicShapes/Cube.Cube")
PLANE = load_mesh("/Engine/BasicShapes/Plane.Plane")

# --------------------------------------------------
# CLEAN WORLD
# --------------------------------------------------

log("Deleting existing actors...")

for actor in unreal.EditorLevelLibrary.get_all_level_actors():
    try:
        unreal.EditorLevelLibrary.destroy_actor(actor)
    except:
        pass

# --------------------------------------------------
# GROUND
# --------------------------------------------------

log("Creating ground")

ground = unreal.EditorLevelLibrary.spawn_actor_from_object(
    mesh,
    unreal.StaticMeshActor,
    unreal.Vector(0, 0, 0)
)

ground.set_actor_label("ForestGround")

ground_mesh = ground.static_mesh_component
ground_mesh.set_static_mesh(PLANE)

ground.set_actor_scale3d(
    unreal.Vector(500, 500, 1)
)

# --------------------------------------------------
# LIGHTING
# --------------------------------------------------

log("Creating lighting")

sun = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.DirectionalLight,
    unreal.Vector(0, 0, 3000)
)

sun.set_actor_rotation(
    unreal.Rotator(-35, 45, 0)
)

sky_light = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.SkyLight,
    unreal.Vector(0, 0, 1000)
)

sky = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.SkyAtmosphere,
    unreal.Vector(0, 0, 0)
)

fog = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.ExponentialHeightFog,
    unreal.Vector(0, 0, 0)
)

clouds = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.VolumetricCloud,
    unreal.Vector(0, 0, 0)
)

# --------------------------------------------------
# PATH
# --------------------------------------------------

log("Creating path")

path_points = []

for i in range(PATH_SEGMENTS):

    x = -22000 + i * 2200
    y = random.randint(-5000, 5000)

    path_points.append((x, y))

for x, y in path_points:

    path_piece = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.StaticMeshActor,
        unreal.Vector(x, y, 5)
    )

    path_piece.static_mesh_component.set_static_mesh(CUBE)

    path_piece.set_actor_scale3d(
        unreal.Vector(
            10,
            PATH_WIDTH / 100.0,
            0.05
        )
    )

# --------------------------------------------------
# TREES
# --------------------------------------------------

log("Generating trees")

for i in range(TREE_COUNT):

    x = random.uniform(-24000, 24000)
    y = random.uniform(-24000, 24000)

    skip = False

    for px, py in path_points:
        if ((x - px) ** 2 + (y - py) ** 2) ** 0.5 < 1200:
            skip = True
            break

    if skip:
        continue

    trunk_height = random.uniform(5, 10)
    crown_size = random.uniform(2.5, 5)

    # trunk
    trunk = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.StaticMeshActor,
        unreal.Vector(x, y, trunk_height * 50)
    )

    trunk.static_mesh_component.set_static_mesh(CYLINDER)

    trunk.set_actor_scale3d(
        unreal.Vector(
            0.25,
            0.25,
            trunk_height
        )
    )

    # crown
    crown = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.StaticMeshActor,
        unreal.Vector(
            x,
            y,
            trunk_height * 100 + 200
        )
    )

    crown.static_mesh_component.set_static_mesh(SPHERE)

    crown.set_actor_scale3d(
        unreal.Vector(
            crown_size,
            crown_size,
            crown_size
        )
    )

# --------------------------------------------------
# ROCKS
# --------------------------------------------------

log("Generating rocks")

for i in range(150):

    rock = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.StaticMeshActor,
        unreal.Vector(
            random.uniform(-24000, 24000),
            random.uniform(-24000, 24000),
            20
        )
    )

    rock.static_mesh_component.set_static_mesh(SPHERE)

    s = random.uniform(0.2, 1.0)

    rock.set_actor_scale3d(
        unreal.Vector(
            s,
            s,
            s * 0.5
        )
    )

# --------------------------------------------------
# SAVE
# --------------------------------------------------

log("Forest generation complete")
