cmake_minimum_required(VERSION 3.20)
project(project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(image_processor
		image_processor.cpp
		cmd_arg_parser.h
		cmd_arg_parser.cpp
		base_filters.h
		base_filters.cpp
		bitmap.h
		bitmap.cpp
		image.h
		image.cpp
		filter_factory.h
		filter_factory.cpp
		)