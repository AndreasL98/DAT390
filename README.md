# DAT390

Labb5 consists of Dubbelpong folder

## DUBBELPONG

From Simserver connect an LC display to GPIOE(0-15) and a keypad to GPIOD 8-15

### GAME CONTROL

Player 1 uses keys 1 and 7 to move their padel up and down respectively.

Player 2 uses keys 3 and 9.

### GAME RULES

After each point the ball is moved to the middle and key 5 has to be pressed in order to start the game again. From a standstill the ball will move towards the player with the least amount of points. If the score is equal, it will move towards Player 2.

The first player to reach 11 points win. However you must win by atleast 2 points.

After a win, in order to restart the game from scratch key 5 must be pressed.
