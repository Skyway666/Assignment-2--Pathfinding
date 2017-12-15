# Assignment-3--UI
In previous projects a 2D platformer with enemies that were able to pathfind was developed.
For this one, the objective was having Graphic User Interface(a menu before starting the game and a HUD
with information for the player).


Controls:

A	->	Move Left
D	->	Move Right
W	->	Jump
S	->	Slide
P	->	Pause/Unpause the game


Debug Features:

F1	->	Restart from first level
F2	->	Restart from current level
F5	->	Save
F6	->	Load
F8	->	See Graphic User Interface logic (only interactables use logic)
F9	->	See colliders and pathfinding
F10	->	Enter godmode(ignore any collisions and gravity, move large distances if pressing X / C)
F11	->	Enable/Disable FPS cap to 30


Rules:

The player starts the game with three lives. If killed, he will restart the current level. The objective is reaching 
the floating bone at the end of the level, which will allow the player to pass to the next level or finish the game if
there are no levels left (currently there are two levels). There are some coins which the player can collect to increase
the score, but they are not mandatory to beat the game. The player also gets rewarded for long enemy persecutions and 
not dying. Ending a level also provides points.

Punctuation system:
- Every small bone gives 1 point
- Beating level 1 gives 200 points
- Win 5 points every 2 seconds while being chased by flying enemies
- Upon beating the game, your points will be increased depending on
  how much time it took you do so and how many remaining lives you have.


Mechanics:

Wall slide	->	Jump next to a wall and advance towards it to start sliding on it
Wall jump	->	When sliding on a wall, press "W" to jump again
Slide		->	Slide to go faster and pass under certain obstacles
Spikes		->	If hit by one, the player must restart the current level


Enemies:

Flying enemy: It pathfinds towards the player, avoiding non-walkable terrain, but if it is too far from his starting
point goes back to idle state.

Ground enemy: Runs from one side to the other jumping pits and falling down platforms, and follows the player if nearby.
If the player is too far away, it starts running from one side to the other again.


Graphic User Interface:

Main menu: Allows for starting a new game from scratch, continuing a previously saved game (the button only appears if there was a saved game)
modifying music and fx sounds, seeing the credits and exiting the application.

HUD: Provides coins collected, players lifes, punctuation and time.

Pause Menu: It is a draggable window which allows to return to the main menu or resume the game.


Innovations:

From previous project:
- Enemies are loaded from the map xml
- Enemy initial values and ground enemies' pathfinding distance can be set from the config xml
- Every entity in the entity system has its own save and load
- Walls' height and pits' width are calulated, so the ground enemies know whether if they can jump them or not.
- "Walkable tiles" for ground enemies are positioned automatically on top of wall colliders without anything on top of them.

From this project:
- Pause implemented


Tips of the developers:

-In order to avoid most enemies, it is usefull to walljump after activating their "agro state". 
Also, if timed correctly, slide can go under flying enemies.


GitHub Link to previous project: https://github.com/Skyway666/Assignment-1--2D-Platformer
GitHub Link to this project(from commit "Assignment 2 finished. Beggining assignment 3" onwards): https://github.com/Skyway666/Assignment-3--UI


Game by:

Genís Bayó Salgado: github.com/retsnom9

Lucas García Mateu: github.com/Skyway666

----------------------------------------------------------------------------------------------------

Audio from:

https://www.youtube.com/watch?v=jgETNzUqDP0
https://www.youtube.com/watch?v=mKnDjMMsdAo ("Price Ali" instrumental, from the Disney movie "Aladin")
https://www.youtube.com/watch?v=vkHiTnm_P3Y (Coin sound from Street Fighter 2)

Animations and map textures from:

https://www.gameart2d.com
https://www.spriters-resource.com/fullview/98810/


