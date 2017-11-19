# Assignment-2--Pathfinding
In a previous project a 2D platformer was developed. The goal with this one is adding  enemies (AI) that 
are able to pathfind, and controll execution so every computer is able to run the game at the same speed.

The objective of the game is reaching the giant floating bone situated in the final part of the screen.


Controls

A -> Move Left
D -> Move Right
W -> Jump
S -> Slide

Debug Features

F1 -> Restart from first level
F2 -> Restart from current level
F5 -> Save
F6 -> Load
F9 -> See colliders and pathfinding
F10-> Enter godmode
F10 + SHIFT-> Enter supergodmode
F11-> Enable/Disable FPS cap to 30

Mechanics:

Wall slide -> Jump next to a wall to start sliding on it
Wall jump -> When sliding on a wall, press "W" to jump again
Slide -> Slide to go faster and pass under certain obstacles
Spikes -> If hit by one, the player must restart the current level

Enemies:

Flying enemy: It pathfinds through non walkable terrain towards the player, but if it is too far from his starting
point goes back to idle state.
Ground enemy: Runs from one side to the other jumping pits and falling down platforms.

Innovations:

-Enemies are loaded from the map xml
-Enmy initial values can be set from the config xml
-Save/Load works with enemies as well, and it is implemented as a mechanism in the entity system

Tip of the developer -> In order to avoid most enemies, it is usefull to walljump after activating their 
"agro state"

GitHub Link to previous project: https://github.com/Skyway666/Assignment-1--2D-Platformer
GitHub Link to this project: https://github.com/Skyway666/Assignment-2--Pathfinding


Game by:

Genís Bayó Salgado: github.com/retsnom9

Lucas García Mateu: github.com/Skyway666

----------------------------------------------------------------------------------------------------

Audio from:

https://www.youtube.com/watch?v=jgETNzUqDP0

Animations and map textures from:

gameart2d.com
