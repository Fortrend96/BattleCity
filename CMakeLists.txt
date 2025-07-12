cmake_minimum_required(VERSION 3.13 FATAL_ERROR) # минимальная версия cmake для проекта

set(PROJECT_NAME BattleCity) # переменная, хранящая название проекта

project(${PROJECT_NAME}) # устанавливаем название проекта

add_executable(${PROJECT_NAME} src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


# добавление внешней библеотеки glfw
add_subdirectory(external/glfw) # добавление папки внешней библеотеки
target_link_libraries(${PROJECT_NAME} glfw) # линковка файлов основного проекта и внешней библеотеки

# добавление внешней библеотеки glad
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)
