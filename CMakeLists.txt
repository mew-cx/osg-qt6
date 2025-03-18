cmake_minimum_required(VERSION 3.16)
project(qt6-oe3)

set(CMAKE_PREFIX_PATH "c:/qt/6.8.2/msvc2022_64;e:/usr/ap/osgearth_mew_tools/vcpkg/installed/x64-windows")

find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets Widgets)
find_package(OpenSceneGraph REQUIRED
	osg
	osgDB
	osgGA
	osgViewer
	osgUtil
	osgFX
	osgText
	osgWidget
	osgAnimation
)

set(CMAKE_AUTOMOC ON)

function(EXAMPLE_EXE name)
	add_executable(example-${name} "example-${name}.cpp")

	target_link_libraries(example-${name} PRIVATE
		Qt6::OpenGLWidgets Qt6::Widgets
		${OPENSCENEGRAPH_LIBRARIES}
		osgEarth
		#GL
		#GLEW
		#gdal
	)
	target_include_directories(example-${name} PRIVATE
		${OPENSCENEGRAPH_INCLUDE_DIRS}
	)
	target_link_directories(example-${name} PRIVATE
		"e:/usr/ap/osgearth_mew_tools/vcpkg/installed/x64-windows/lib"
	)
#"e:/usr/ap/osgearth_mew_tools/vcpkg/installed/x64-windows/debug/lib"
#"e:/usr/ap/gits/osg-qt6"
endfunction()

example_exe("gl")
example_exe("osg")
example_exe("osgearth")
