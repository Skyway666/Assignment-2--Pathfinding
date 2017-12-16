# WHO LET THE DOG JUMP?
### By Genís Bayó Salgado and Lucas García Mateu

## Team
Who let the dog jump? was born as the product of three different University assignments, made by Genís Bayó and Lucas García, students from the UPC. The assignments consisted on creating a 2D platformer game with Artificial Intelligence and a User Interface, as well as implementing several tech aspects, such as FPS management or XML loading variables.

Everything was developed in C++, using SDL2, Tiled and PugiXML.

### Lucas García and Genís Bayó
<br><img src="LINK?raw=true" width = "2448" height = "2288" alt="Error loading img"><br>

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
·Every important variable is load from an XML file named confing.xml

·Maps are made with Tiled and loaded via XML

·The player can save/load the game by pressing F5/F6 (or “Continue” from the main menu)

·FPS can be capped to 30 or uncapped upon pressing F11. The cap can also be changed from config file

·Game audio can be lowered or highered from the “Options” menu

·Player can pause the game at any point by pressing P

·Player can press F8, F9 and F10 in order to enter the debug modes for UI, colliders and godmode

·Fying enemies pathfind to the player if the terrain is accessible, and ground enemies follow the player by jumping pits and platforms if they are able to do so

·Adjacent colliders' lenght and height are measured in order to determine whether the ground enemies can jump over them or not

·There is a "main menu" in which the player can choose between starting a new game, continuing from the last saved point, modifying the game volume, consulting the credits, license and his/her maximum score and exiting

## Links
[Code repository](https://github.com/Skyway666/Assignment-3--UI)

[Latest release](https://github.com/Skyway666/Assignment-3--UI/releases/tag/2.0)

[One minute video](https://www.youtube.com/watch?v=N-DDTzSzeDo)

## Instructions
### Controls

·A	→	Move Left

·D	→	Move Right

·W	→	Jump

·S	→	Slide

·P	→	Pause/Unpause the game

### Mechanics
·Wall slide → Jump next to a wall and advance towards it to start sliding on it

·Wall jump	→	When sliding on a wall, press "W" to jump again

·Slide      →	Slide to go faster and pass under certain obstacles

### Enemies and obstacles
·Pits         → If the player falls down a pit, he/she dies

·Spikes       →	If hit by one, the player dies

·Flying enemy → It pathfinds towards the player, avoiding non-accessible terrain, but if it gets too far from his starting point, it                     goes back to idle state

·Ground enemy → Runs from one side to the other jumping over pits and falling down platforms, and follows the player if nearby. If the                   player is too far away, it starts running from one side to the other again

*If the player gets hit by any enemy or obstacle (dies), he/she loses a life and must restart from the current level

### Punctuation system
·Every small bone gives 1 point

·Beating level 1 gives 200 points

·Win 5 points every 2 seconds while being chased by flying enemies

·Upon beating the game, your points will be increased depending on how much time it took you do so and how many remaining lives you have

## Art
### Audio from

[Menu music](https://www.youtube.com/watch?v=jgETNzUqDP0)

[In game music](https://www.youtube.com/watch?v=mKnDjMMsdAo)

[Pushing button sound](https://www.youtube.com/watch?v=vkHiTnm_P3Y)

[Picking up coin sound](https://freesound.org/people/sergeeo/sounds/202575/)

### Animations and map textures from

[Map and characters art](https://www.gameart2d.com)

[Hourglass sprites](https://www.spriters-resource.com/fullview/98810/)

## License
MIT License

Copyright (c) 2017 Lucas García Mateu, Genís Bayó Salgado

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
