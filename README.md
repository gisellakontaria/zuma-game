# **Zuma Game**
## Background
Zuma is an existing "tile-matching puzzle video game" that runs on 
PCs, mobile phones, etc. I personally loved this game when I was younger,
which is what inspired me to recreate a simpler, modified version of it for this project.

### Game Introduction
Zuma is a C++ mini-game consisting of 3 difficulty levels to choose from. 

Different color-coded particles will shoot down in a random manner 
from the top of the container, and the player's job is to catch the particle using the basket that glides left and right. 
The basket is operated through the player's right and left keyboard keys. 

Each particle has a different behavior. At higher levels, bombs that steals the
player's life are introduced, along with recovery balls that give away extra lives.

### What does it take to win?
In order to win this game, player should accomplish the mission stated on the screen before the life count runs out.

### How do I set this game up?
To be able to build the game properly, please make sure that you have the following installed:
* A working C++ compiler
* Cinder library
* Xcode for Mac, or Visual Studio 2015 for Windows
Other than that, make sure you are using a device with an operating keyboard, since the basket can only be moved by keyboard keys.
