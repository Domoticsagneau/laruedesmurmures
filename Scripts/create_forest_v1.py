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
# HELPERS / INITIALIZATION
# --------------------------------------------------

# Initialisation moderne via le sous-système de l'éditeur (évite les warnings)
editor_subsystem = unreal.UnrealEditorSubsystem()
world = editor_subsystem.get_editor_world()

def log(msg):
    unreal.log_warning(msg)

def load_mesh(path):
    mesh = unreal.EditorAssetLibrary.load_asset(path)
    if not mesh:
        raise RuntimeError(f"Missing mesh: {path}")
    return mesh

# Utilisation de spawn_actor_from_object pour éviter les crashs headless
def spawn_static_mesh_actor(mesh_asset, location, scale, label="StaticMeshActor"):
    actor = unreal.EditorLevelLibrary.spawn_actor_from_object(mesh_asset, location)
    if actor:
        actor.set_actor_label(label)
        actor.set_actor_scale3d(scale)
    return actor

# Pour les acteurs sans mesh (Lumières, Caméras, Managers)
def spawn_editor_actor(actor_class, location, rotation=unreal.Rotator(0,0,0), label="Actor"):
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(actor_class, location, rotation)
    if actor:
        actor.set_actor_label(label)
    return actor

# Chargement des formes de base
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
# PLAYER START (Correctif anti-écran noir)
# --------------------------------------------------
log("Spawning secure Player Start...")

# On place le point d'apparition à (0, 0) mais surélevé de 500 unités (5 mètres en l'air)
# pour que le joueur atterrisse proprement sur la map à sa connexion.
player_start = spawn_editor_actor(
    unreal.PlayerStart,
    unreal.Vector(0, 0, 500),
    unreal.Rotator(0, 0, 0),
    "ServerPlayerStart"
)

if player_start:
    log("Player Start généré avec succès à (0, 0, 500) !")


# --------------------------------------------------
# LIGHTING (Version corrigée pour de bon)
# --------------------------------------------------

log("Creating lighting")

sun = spawn_editor_actor(
    unreal.DirectionalLight, 
    unreal.Vector(0, 0, 3000), 
    unreal.Rotator(-35, 45, 0), 
    "Sun"
)

# La mobilité appartient au RootComponent de l'acteur de lumière
if sun and sun.root_component:
    sun.root_component.set_editor_property("mobility", unreal.ComponentMobility.MOVABLE)

sky_light = spawn_editor_actor(unreal.SkyLight, unreal.Vector(0, 0, 1000), label="SkyLight")
if sky_light and sky_light.root_component:
    # Le SkyLight utilise son propre composant ou son root pour la mobilité
    sky_light.root_component.set_editor_property("mobility", unreal.ComponentMobility.MOVABLE)

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
# CAMERA INITIALIZATION & FOCUS (Version corrigée UE5)
# --------------------------------------------------
log("Spawning Camera and Focusing Viewport...")

cam_actor = spawn_editor_actor(
    unreal.CameraActor,
    unreal.Vector(-5000, 0, 2000), 
    unreal.Rotator(-15, 0, 0),     
    "VueGenerale_Cam"
)

if cam_actor:
    camera_component = cam_actor.get_component_by_class(unreal.CameraComponent)
    if camera_component:
        camera_component.set_editor_property("aspect_ratio", 1.777)
    
    # FORCE L'ÉDITEUR À SÉLECTIONNER ET REGARDER LA CAMÉRA via le bon Subsystem
    actor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    if actor_subsystem:
        actor_subsystem.set_actor_selection_state(cam_actor, True)
        
    # Aligne le viewport de l'hôte sur l'acteur sélectionné
    unreal.SystemLibrary.execute_console_command(world, "CAMERA ALIGN ACTIVEVIEWPORTONLY")


# --------------------------------------------------
# FORCE RECAPTURE & RAFRAÎCHISSEMENT APPARENCE
# --------------------------------------------------
log("Rafraîchissement forcé des lumières et du Viewport...")

sky_light_actors = unreal.GameplayStatics.get_all_actors_of_class(world, unreal.SkyLight)
for actor in sky_light_actors:
    if actor:
        sky_light_comp = actor.get_component_by_class(unreal.SkyLightComponent)
        if sky_light_comp:
            sky_light_comp.recapture_sky()

# IMPORTANT : Force Unreal à redessiner le Viewport immédiatement
unreal.EditorLevelLibrary.editor_invalidate_viewports()

# --------------------------------------------------
# SCREENSHOT CONTROL (Version Éditeur Hôte)
# --------------------------------------------------
log("Prise de la capture d'écran sur l'hôte...")

# Sur l'hôte, HighResShot a besoin qu'on lui laisse une frame pour s'afficher
# On utilise la commande de base qui capture exactement ce que l'éditeur voit
unreal.SystemLibrary.execute_console_command(world, "HighResShot 1920x1080")

# --------------------------------------------------
# SAVE & EXIT
# --------------------------------------------------
log("Saving map and assets...")
unreal.EditorLoadingAndSavingUtils.save_packages([world.get_package()], False)

log("Forest generation complete and saved successfully!")
