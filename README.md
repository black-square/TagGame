# TagGame

Grid-based game where you need to decoy enemies to the traps but at the same time you need to avoid 
situation when they touch hero.

[mango2d engine demo](https://github.com/black-square/mango2d)

**[Download binaries for Mac and Windows](https://github.com/black-square/TagGame/releases)**

## Features
- Multiplatform code: Mac OS and Windows
- Animations, sounds, particles, fonts, gui widgets and gui states
- Each game object has its own logic and interacts with others units units only through abstract interface
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
-	Efficient and robust [solution](https://github.com/black-square/mango2d/blob/master/Logic/GameFieldBase.hpp) 
  for Destroy During the Update problem. Special [shared_ptr deleter](https://github.com/black-square/mango2d/blob/master/Logic/DefferedSharedPtrDeleter.hpp) 
  which keeps object destruction until `Update()` method finishes, but weak pointers become expired immediately.
 
![GemsGame screenshot](https://raw.github.com/wiki/black-square/mango2d/img/TagGame.png)

