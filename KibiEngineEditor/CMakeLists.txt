cmake_minimum_required(VERSION 3.15)

project(KibiEngineEditor LANGUAGES CXX)

# Исполняемый файл
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Линковка с ядром
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        KibiEngineCore
        raylib
		#rlImGui
)

#target_include_directories(${PROJECT_NAME} PRIVATE
#    "${CMAKE_SOURCE_DIR}/submodules/imgui"
#    "${CMAKE_SOURCE_DIR}/submodules/rlImgui"
#)


# Настройка выходной директории
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
)