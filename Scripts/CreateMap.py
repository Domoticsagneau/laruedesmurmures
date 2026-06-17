import unreal

map_path = "/Game/Maps/MainMap"

world_factory = unreal.WorldFactory()

asset_tools = unreal.AssetToolsHelpers.get_asset_tools()

world = asset_tools.create_asset(
    "MainMap",
    "/Game/Maps",
    unreal.World,
    world_factory
)

unreal.EditorAssetLibrary.save_loaded_asset(world)

print("Map créée :", map_path)
