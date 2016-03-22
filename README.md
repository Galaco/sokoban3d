# Sokoban3D

Sokoban 3D is your standard Sokoban game, except that it is played around the faces of a cube, instead of the standard flat board traditionally used.

This allows the game to support wrapping: 
* Scenarios where the player or a block were blocked in may now become solvable.
* New levels can be designed to take advantage of iterating around faces. The whole gameboard state can be completely reconsidered if a player can access squares that were previously inaccessible




# Software features
* Game engine written in C++
* OpenGL for rendering & lighting
* Supports Lua scripting to enhance, or completely replace the Sokoban game layer
* Basic material support, some configurable options, like transparency and ignore lighting
* 2d and 3d rendering support - nice for specifying menu's and displaying text (also supported)



# What you get
One would hope you can tell by looking at the repo, here we go:
* /release contains a prebuilt binary and the necessary libs. It SHOULD just work. No promises though.
* /source contains the project source, including prebuilt libs (due to there being no readily available vs2013 assimp or SFML lib/dlls at the time). Under vs2013 it SHOULD just build (again no promises).
