# /project/scripts/test_level.py

import unreal

unreal.log_warning("START TEST LEVEL")

try:
    world = unreal.EditorLevelLibrary.get_editor_world()
    unreal.log_warning(f"WORLD OK : {world}")
except Exception as e:
    unreal.log_error(str(e))

unreal.log_warning("END TEST LEVEL")
