add_compile_options($<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>,$<C_COMPILER_ID:GNU>>:-s>)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --no-gnu-unique")
endif()
	
add_compile_options(/MP)

add_library(OsirisOBJ OBJECT "")
set_target_properties(OsirisOBJ PROPERTIES CXX_VISIBILITY_PRESET hidden C_VISIBILITY_PRESET hidden)

target_compile_definitions(OsirisOBJ PUBLIC NOMINMAX)

add_subdirectory(Dependencies)

set_target_properties(OsirisOBJ PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_precompile_headers(OsirisOBJ PRIVATE "${CMAKE_SOURCE_DIR}/Source/pch.h")
target_include_directories(OsirisOBJ PUBLIC "${CMAKE_SOURCE_DIR}/Source")
target_include_directories(OsirisOBJ PUBLIC "${CMAKE_SOURCE_DIR}/Dependencies")

target_compile_definitions(OsirisOBJ PRIVATE _USE_MATH_DEFINES)
target_compile_options(OsirisOBJ PRIVATE /utf-8)
add_subdirectory(Source/Resources/Shaders)
add_dependencies(OsirisOBJ Shaders)


add_library(Osiris SHARED "${CMAKE_SOURCE_DIR}/Source/Osiris.cpp")
target_link_libraries(Osiris PUBLIC OsirisOBJ)

target_link_options(Osiris PRIVATE /ENTRY:DllEntryPoint)

target_sources(OsirisOBJ PRIVATE
  AntiDetection.cpp
  Config.cpp
  ConfigStructs.cpp
  EventListener.cpp
  GameData.cpp
  GUI.cpp
  Helpers.cpp
  Hooks.cpp
  imguiCustom.cpp
  InputUtil.cpp
  Logger.cpp
  Memory.cpp
  Netvars.cpp
  Texture.cpp
)

add_subdirectory(Hacks)
add_subdirectory(Hooks)
add_subdirectory(SDK)