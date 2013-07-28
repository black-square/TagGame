# GemsGame

Board game where you need to match three of the same color gems in a row.

[mango2d engine demo](https://github.com/black-square/mango2d)

**[Download binaries for Mac and Windows](https://github.com/black-square/TagGame/releases)**

## Features
- Animations, sounds, particles, fonts, gui widgets and gui states
-	Distinguish between game logic (10 fps, grid based) and presentation (max fps) code. Deterministic 
  logic is very useful when it comes to synchronizing it by the network
-	Unit movement looks as if there is no logic grid under the hood. At the presentation level, unit moves 
  only along straight lines, but at the logic level unit can move only in eight directions. Straight lines 
  approximate to the discrete grid by Bresenham’s algorithm. The logic unit position is marked under 
  the unit by the gray square
-	Enemies have some kind of group behaviour: Each enemy unit reports about player position to the close units. 
  This approach makes unit behaviour more interesting
-	Smooth camera animation: Physically reliable spring formula
-	Intensive smart-pointers usage
-	Careful OOP design
-	Efficient and robust [solution](Engine/Logic/GameFieldBase.hpp) for Destroy During the Update problem. Special 
  [shared_ptr deleter](Engine/Logic/DefferedSharedPtrDeleter.hpp) which keeps object destruction until `Update()` 
  method finishes, but weak pointers become expired immediately.
 
![GemsGame screenshot](https://raw.github.com/wiki/black-square/mango2d/img/TagGame.png)

