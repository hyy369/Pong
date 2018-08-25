![alt text](https://github.com/hyy369/Pong/blob/master/screenshot.png)
# Pong

Reimplementation of the classic arcade game ‘pong’ using SFML and an OO approach.

## Assignment Report

### Time required to finish the core requirements
About 10 hours

### Time spend on bonus features
About 5 hours

### External libraries
None

### Core features that do not work correctly
Keyboard controls only works in Debug mode, not working in Release mode.

### Implemented bonus features
- The game pauses when the window loses focus. The game enters the PAUSED state.
- Window can be resized at any time during the game. After resizing, the paddle on the right side is replaced to near the right edge. Game will enter the PAUSED state when window is resized.
- A gray pause screen appears in the PAUSED state. Player has to press Enter (Return) key to resume the game.
- Sound effects are played when hitting a ball, pad, or when the ball is leaving the screen.
- A blue background title screen shows up when the game is opened or restarted. Player can choose from three difficulty levels.
- Objects move faster in harder games.
- If the computer wins, the message background is white. If the player wins, the background is red.
- The reflection vector of the ball is multiplied by a random number between 0.9 and 1.1 to create uncertainty.
- Real time movement information of the ball, including position and speed vector, is shown on the screen for debugging purposes. This functionality is commented out in submission.
