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

# Utilisation de spawn_actor_from_object pour éviter les crashs headless
def spawn_static_mesh_actor(mesh_asset, location, scale, label="StaticMeshActor"):
    # On crée l'acteur à partir du mesh directement, plus stable sous Docker
    actor = unreal.EditorLevelLibrary.spawn_actor_from_object(mesh_asset, location)
    if actor:
        actor.set_actor_label(label)
        actor.set_actor_scale3d(scale)
    return actor

# Pour les acteurs sans mesh (Lumières, Brouillard, etc.), on passe par le package de base
def spawn_editor_actor(actor_class, location, rotation=unreal.Rotator(0,0,0), label="Actor"):
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(actor_class, location, rotation)
    if actor:
        actor.set_actor_label(label)
    return actor

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

ground = spawn_static_mesh_actor(
    PLANE, 
    unreal.Vector(0, 0, 0), 
    unreal.Vector(500, 500, 1), 
    "ForestGround"
)

# --------------------------------------------------
# LIGHTING
# --------------------------------------------------

log("Creating lighting")

sun = spawn_editor_actor(
    unreal.DirectionalLight, 
    unreal.Vector(0, 0, 3000), 
    unreal.Rotator(-35, 45, 0), 
    "Sun"
)

sky_light = spawn_editor_actor(unreal.SkyLight, unreal.Vector(0, 0, 1000), label="SkyLight")
sky = spawn_editor_actor(unreal.SkyAtmosphere, unreal.Vector(0, 0, 0), label="SkyAtmosphere")
fog = spawn_editor_actor(unreal.ExponentialHeightFog, unreal.Vector(0, 0, 0), label="Fog")
clouds = spawn_editor_actor(unreal.VolumetricCloud, unreal.Vector(0, 0, 0), label="Clouds")

# --------------------------------------------------
# PATH
# --------------------------------------------------

log("Creating path")

path_points = []

for i in range(PATH_SEGMENTS):
    x = -22000 + i * 2200
    y = random.randint(-5000, 5000)
    path_points.append((x, y))

for i, (x, y) in enumerate(path_points):
    path_piece = spawn_static_mesh_actor(
        CUBE,
        unreal.Vector(x, y, 5),
        unreal.Vector(10, PATH_WIDTH / 100.0, 0.05),
        f"PathPiece_{i}"
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
    trunk = spawn_static_mesh_actor(
        CYLINDER,
        unreal.Vector(x, y, trunk_height * 50),
        unreal.Vector(0.25, 0.25, trunk_height),
        f"TreeTrunk_{i}"
    )

    # crown
    crown = spawn_static_mesh_actor(
        SPHERE,
        unreal.Vector(x, y, trunk_height * 100 + 200),
        unreal.Vector(crown_size, crown_size, crown_size),
        f"TreeCrown_{i}"
    )

# --------------------------------------------------
# ROCKS
# --------------------------------------------------

log("Generating rocks")

for i in range(150):
    s = random.uniform(0.2, 1.0)
    rock = spawn_static_mesh_actor(
        SPHERE,
        unreal.Vector(random.uniform(-24000, 24000), random.uniform(-24000, 24000), 20),
        unreal.Vector(s, s, s * 0.5),
        f"Rock_{i}"
    )

# --------------------------------------------------
# SAVE
# --------------------------------------------------
# --------------------------------------------------
# SAVE (Mise à jour)
# --------------------------------------------------

log("Saving map and assets...")

# --------------------------------------------------
# SAVE (Version corrigée et stable)
# --------------------------------------------------

log("Saving map and assets...")

# 1. On récupère le sous-système de l'éditeur (plus moderne, évite le warning)
editor_subsystem = unreal.UnrealEditorSubsystem()
current_world = editor_subsystem.get_editor_world()

# 2. On récupère le nom du package de la map
world_package_name = current_world.get_package().get_path_name()

# 3. On sauvegarde proprement le package de la map
# unreal.EditorLoadingAndSavingUtils est la méthode la plus robuste en headless
unreal.EditorLoadingAndSavingUtils.save_packages([current_world.get_package()], False)

log("Forest generation complete and saved successfully!")


# --------------------------------------------------
# CAMERA INITIALIZATION (Version sécurisée pour Docker)
# --------------------------------------------------
log("Spawning Camera Manager and Safe Camera...")



# On utilise une CameraActor standard pour éviter la division par zéro (SIGFPE) sous Docker
cam_actor = spawn_editor_actor(
    unreal.CameraActor,
    unreal.Vector(-5000, 0, 2000), 
    unreal.Rotator(-15, 0, 0),     
    "VueGenerale_Cam"
)

# Optionnel : Forcer les propriétés pour éviter qu'elle ne cherche à s'ajuster au viewport
if cam_actor:
    camera_component = cam_actor.get_component_by_class(unreal.CameraComponent)
    if camera_component:
        camera_component.set_editor_property("aspect_ratio", 1.777) # Force un 16:9 strict en dur

# Au tour de ton CameraManager personnalisé
# --------------------------------------------------
# SOURCE FIX: Spawning Custom C++ CameraManager
# --------------------------------------------------

# 1. On récupère la classe générée par Unreal pour ton code C++
# Le format est "/Script/[NomDeTonProjet].[NomDeLaClasseSansLeA]"
# Exemple si ton projet s'appelle "MonProjet": "/Script/MonProjet.CameraManager"
camera_manager_class = unreal.CommandLineBlueprintLibrary.load_asset_class("/Script/LaRueDesMurmures.CameraManager")

if camera_manager_class:
    camera_manager = spawn_editor_actor(
        camera_manager_class, 
        unreal.Vector(0, 0, 0),
        label="MyCameraManager"
    )
else:
    log("Erreur : Impossible de charger la classe C++ CameraManager. Vérifie le nom de ton projet C++.")


