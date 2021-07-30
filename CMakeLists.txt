cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(PROJECT_NAME battle-city)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/Renderer/shaderProgram.cpp
	src/Renderer/shaderProgram.h
	src/Renderer/texture2D.cpp
	src/Renderer/texture2D.h
	src/Renderer/sprite.cpp
	src/Renderer/sprite.h 
	src/Renderer/AnimatedSprite.cpp
	src/Renderer/AnimatedSprite.h
	src/Renderer/vertexBuffer.cpp
	src/Renderer/vertexBuffer.h
	src/Renderer/indexBuffer.cpp
	src/Renderer/indexBuffer.h
	src/Renderer/vertexArray.cpp
	src/Renderer/vertexArray.h
	src/Renderer/vertexBufferLayout.cpp
	src/Renderer/vertexBufferLayout.h
	src/Renderer/renderer.cpp
	src/Renderer/renderer.h
	src/Resources/resourceManager.cpp
	src/Resources/resourceManager.h
	src/Resources/stb_image.h
	src/Game/game.cpp
	src/Game/game.h
	src/Game/tank.cpp
	src/Game/tank.h

)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)