cmake_minimum_required(VERSION 3.15)

# ImGui Library
add_library(imgui STATIC
    "imgui/imgui.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
	"imgui/imgui_demo.cpp"
)

target_include_directories(imgui PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui"
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui/style"
)

# rlImGui Library
add_library(rlImGui STATIC
    "rlImgui/rlImGui.cpp"
)

target_include_directories(rlImGui PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/rlImgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui"  # Для доступа к imgui.h из rlImGui
)

target_link_libraries(rlImGui PRIVATE imgui raylib)