
Path=C:\Windows\system32;C:\Program Files\CMake\bin;e:\usr\ap\osgearth_mew\vcpkg\installed\x64-windows\bin\;e:\usr\ap\osgearth_mew\vcpkg\installed\x64-windows\debug\bin\;e:\usr\ap\osgearth_mew\vcpkg\installed\x64-windows\debug\plugins;e:\usr\ap\osgearth_mew\vcpkg\installed\x64-windows\plugins;c:\Qt\6.8.2\msvc2022_64\bin\


.\example-gl.exe

set PROJ_LIB=C:\Program Files\GDAL\projlib
set GDAL_DATA=C:\Program Files\GDAL\gdal-data
set GDAL_DRIVER_PATH=C:\Program Files\GDAL\gdalplugins
REM dir %GDAL_DRIVER_PATH%

REM set OSG_NOTIFY_LEVEL=DEBUG
.\example-osg.exe

REM set OSG_NOTIFY_LEVEL=DEBUG
REM set OSGEARTH_NOTIFY_LEVEL=DEBUG
.\example-osgearth.exe
