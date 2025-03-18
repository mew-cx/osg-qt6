REM run.bat - launch Qt6 demo


set PATH=C:\Windows\system32;C:\Program Files\CMake\bin;e:\usr\ap\osgearth_mew_tools\vcpkg\installed\x64-windows\bin\;e:\usr\ap\osgearth_mew_tools\vcpkg\installed\x64-windows\plugins;c:\Qt\6.8.2\msvc2022_64\bin

REM e:\usr\ap\osgearth_mew_tools\vcpkg\installed\x64-windows\debug\bin\
REM e:\usr\ap\osgearth_mew_tools\vcpkg\installed\x64-windows\debug\plugins


set OEI=e:\usr\ap\osgearth_mew_tools\vcpkg\installed\x64-windows\tools\osgearth\osgearth_imgui.exe
set OEV=e:\usr\ap\osgearth_mew_tools\vcpkg\installed\x64-windows\tools\osgearth\osgearth_viewer.exe
REM %OEV% cr-qt6.earth

REM e:\usr\ap\osg-qt6\_BUILD\Release
REM e:\usr\ap\osg-qt6\_BUILD\Release\example-gl.exe

set PROJ_LIB=C:\Program Files\GDAL\projlib
set GDAL_DATA=C:\Program Files\GDAL\gdal-data
set GDAL_DRIVER_PATH=C:\Program Files\GDAL\gdalplugins

REM set OSG_NOTIFY_LEVEL=DEBUG
REM e:\usr\ap\osg-qt6\_BUILD\Release\example-osg.exe

REM set OSG_NOTIFY_LEVEL=DEBUG
REM set OSGEARTH_NOTIFY_LEVEL=DEBUG
REM e:\usr\ap\osg-qt6\_BUILD\Release\example-osgearth.exe


e:\usr\ap\osg-qt6\_BUILD\Release\example-osgearth-qt6.exe cr-qt6.earth
