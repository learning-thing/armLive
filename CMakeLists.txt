cmake_minimum_required(VERSION 3.29.2)
project( ArmLive )


#add_subdirectory(vendor/somelib)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories( src/State src/Instruction src)
add_executable( main
	src/main.cpp
	src/State/ArmState.cpp
	src/Instruction/Instruction.cpp
)

#target_link_libraries(main lib)
