cmake_minimum_required(VERSION 3.15)

project(KibiEngineCore LANGUAGES CXX)

# Исходные файлы
file(GLOB_RECURSE ENGINE_SOURCES
    "src/*.cpp"
    "src/*.c"
)

file(GLOB_RECURSE ENGINE_HEADERS
    "includes/*.h"
    "includes/*.hpp"
)

# Создание статической библиотеки
add_library(${PROJECT_NAME} STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

# Линковка с raylib
target_link_libraries(${PROJECT_NAME} PRIVATE
	raylib
	rlImGui
	imgui
)

# Настройка include-директорий
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<INSTALL_INTERFACE:includes>
    PRIVATE
        src
)

# Группировка файлов в IDE
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} 
    FILES 
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES}
)