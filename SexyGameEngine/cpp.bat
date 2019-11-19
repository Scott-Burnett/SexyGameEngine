Start
Call "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvars64"
Call "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx64/x64/cl.exe" /W4 /EHsc main.cpp window.cpp Game.cpp Entity.cpp Vector2D.cpp Collision_Mesh.cpp Sprite.cpp Player.cpp Level.cpp Tile.cpp /link ../dependencies/lib/SDL2.lib ../dependencies/lib/SDL2main.lib ../dependencies/lib/SDL2_image.lib ../dependencies/lib/SDL2test.lib /out:Sexy.exe

@echo off

if errorlevel 1 (
    pause
)