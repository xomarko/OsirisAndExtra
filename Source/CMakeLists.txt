target_sources(OsirisOBJ PRIVATE
  Config.cpp
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

if (WIN32)
  add_subdirectory(MinHook)
endif()