add_subdirectory(freetype)
add_subdirectory(imgui)
add_subdirectory(MinHook)

target_compile_definitions(OsirisOBJ PRIVATE NOMINMAX)
target_include_directories(OsirisOBJ PUBLIC range-v3)
