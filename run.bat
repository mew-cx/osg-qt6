@echo off

set VCPKG_ROOT=e:\usr\ap\osgearth_mew_tools\vcpkg

set PATH=%PATH%;c:\Qt\6.8.2\msvc2022_64\bin
set PATH=%PATH%;%VCPKG_ROOT%\installed\x64-windows\bin
set PATH=%PATH%;%VCPKG_ROOT%\installed\x64-windows\plugins
set PATH=%PATH%;%VCPKG_ROOT%\installed\x64-windows\tools\osgearth
set PATH=%PATH%;%VCPKG_ROOT%\installed\x64-windows\debug\bin
set PATH=%PATH%;%VCPKG_ROOT%\installed\x64-windows\debug\plugins

set PATH=%PATH%;e:\usr\ap\osg-qt6\_BUILD\Release

set PROJ_LIB=C:\Program Files\GDAL\projlib
set GDAL_DATA=C:\Program Files\GDAL\gdal-data
set GDAL_DRIVER_PATH=C:\Program Files\GDAL\gdalplugins

set OSG_NOTIFY_LEVEL=DEBUG
set OSG_NOTIFY_LEVEL=

set OSGEARTH_NOTIFY_LEVEL=DEBUG
set OSGEARTH_NOTIFY_LEVEL=

::osgearth_version.exe --caps
osgearth_viewer.exe apg.earth
::example-gl.exe
::example-osg.exe
example-osgearth.exe apg.earth
