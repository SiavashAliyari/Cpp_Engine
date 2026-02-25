@echo off
setlocal

set ASSIMP_DIR=%~dp0..\Vendor\assimp
set BUILD_DIR=%ASSIMP_DIR%\build

cmake -S "%ASSIMP_DIR%" -B "%BUILD_DIR%" ^
  -DASSIMP_BUILD_TESTS=OFF ^
  -DASSIMP_BUILD_ASSIMP_TOOLS=OFF ^
  -DBUILD_SHARED_LIBS=OFF ^
  -DASSIMP_BUILD_ZLIB=ON ^
  -DASSIMP_BUILD_MINIZIP=ON ^
  -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>DLL

cmake --build "%BUILD_DIR%" --config Debug
cmake --build "%BUILD_DIR%" --config Release

endlocal