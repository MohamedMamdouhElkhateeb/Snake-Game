This C++ program implements a classic Snake Game using the OpenGL graphics library and GLUT (OpenGL Utility Toolkit) for window management. The game features a grid-based playing area where a snake, controlled by the player, moves around to collect randomly generated food items. The objective is to eat the food, grow the snake in length, and accumulate points while avoiding collisions with the game boundaries and the snake itself.

Key Features:
1. Graphics and Display:The game utilizes OpenGL for rendering graphics and GLUT for window management. The grid-based layout provides a visually appealing representation of the game world.
2. Snake Movement: The snake moves in four directions: up, down, left, and right. The player can control the snake's direction using arrow keys.
3. Food Generation: Food items appear randomly on the grid, and the snake must consume them to increase its length and score.
4. Collision Detection: The game includes collision detection mechanisms to check for collisions with the game boundaries and the snake's own body. If a collision occurs, the game ends.
5. Score Tracking: The player's score is displayed on the screen, increasing each time the snake consumes food.
6. Game Over Message: When the game ends, a message box displays the player's final score, and the program terminates.

Usage:
To compile and run the program, ensure that you have the necessary OpenGL and GLUT libraries installed. Users can control the snake's movement using arrow keys. The game continues until a collision occurs or the user decides to exit.
