# WHO LET THE DOG JUMP?
### By Genís Bayó Salgado and Lucas García Mateu

## Team
Who let the dog jump? was born as the product of three different University assignments, made by Genís Bayó and Lucas García, students from the UPC. The assignments consisted on creating a 2D platform game with Artificial Intelligence and a User Interface, as well as implementing several tech aspects, such as FPS management or XML loading variables.

Everything was developed in C++, using SDL2, Tiled and PugiXML.

### Lucas García and Genís Bayó
<br><img src="LINKDELAFOTO?raw=true" width = "2448" height = "2288" alt="Error loading img"><br>

### Lucas García Mateu
<br><img src="https://github.com/Skyway666/Assignment-3--UI/blob/master/Webpage%20pictures/LucasWebPic.jpg?raw=true" width = "243" height = "324" alt="Error loading img"><br>
[GitHub](https://github.com/Skyway666)

-Implementing map and colliders loading from XML

-Implementing load and save methods for the player and maps

-Designing and implementing entity system

-Implementing flying, pathfinding enemies, as well as their save and load methods

-Designing and implementing User Interface system

-Implementing main menu, options and pause windows

### Genís Bayó Salgado
<br><img src="https://github.com/Skyway666/Assignment-3--UI/blob/master/Webpage%20pictures/Gen%C3%ADsWebPic.jpg?raw=true" width = "245" height = "229" alt="Error loading img"><br>
[GitHub](https://github.com/retsnom9)

-Designing and implementing collision system

-Implementing a method to measure the length and height of adjacent colliders

-Designing and implementing player’s character and its mechanics

-Implementing FPS management system

-Implementing ground, pathfinding enemies, as well as their save and load methods

-Designing UI system

-Implementing pause method

-Implementing HUD, collectable coins, lives, time and punctuation system

## Subsystems

-Every important variable is load from an XML file named confing.xml

-Maps are made with Tiled and loaded via XML

-The player can save/load the game by pressing F5/F6 (or “Continue” from the main menu)

-FPS can be capped to 30 or uncapped upon pressing F11. The cap can also be changed from config file

-Game audio can be lowered or highered from the “Options” menu

-Player can pause the game at any point by pressing P

-Player can press F8, F9 and F10 in order to enter the debug modes for UI, colliders and godmode

-Fying enemies pathfind to the player if the terrain is accessible, and ground enemies follow the player by jumping pits and platforms if they are able to do so

-Adjacent colliders' lenght and height are measured in order to determine whether the ground enemies can jump over them or not

-There is a "main menu" in which the player can choose between starting a new game, continuing from the last saved point, modifying the game volume, consulting the credits, license and his/her maximum score and exiting

## Links

[Code repository](https://github.com/Skyway666/Assignment-3--UI)

[Latest release](https://github.com/Skyway666/Assignment-3--UI/releases/tag/2.0)

[One minute video](https://www.youtube.com/watch?v=N-DDTzSzeDo)
