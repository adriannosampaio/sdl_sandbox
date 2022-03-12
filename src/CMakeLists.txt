# CMakeList.txt: projeto de CMake para Lightning, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Adicione a origem ao executável deste projeto.
add_executable (Lightning "Lightning.cpp" "Lightning.h")
target_include_directories(Lightning PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(Lightning ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
