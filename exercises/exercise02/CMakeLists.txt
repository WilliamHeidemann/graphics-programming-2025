
set(libraries glad glfw itugl ${APPLE_LIBRARIES})

file(GLOB_RECURSE target_inc "*.h" )
file(GLOB_RECURSE target_src "*.cpp" )

file(GLOB_RECURSE shaders "*.vert" "*.frag" "*.geom" "*.glsl")
source_group("Shaders" FILES ${shaders})

add_executable(${TARGETNAME} ${target_inc} ${target_src} ${shaders}
        ../exercise03/GearsApplication.cpp)
target_link_libraries(${TARGETNAME} ${libraries})
