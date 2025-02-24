# ImGui
add_library(imgui STATIC
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_raylib.cpp
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

# rlImGui
add_library(rlimgui STATIC
    rlImGui/rlImGui.cpp
)

target_include_directories(rlimgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/rlImGui
)

target_link_libraries(rlimgui PRIVATE imgui raylib)