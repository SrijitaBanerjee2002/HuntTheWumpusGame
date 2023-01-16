# HuntTheWumpusGame
Welcome to "Hunt the Wumpus", a classic text-based adventure game by Gregory Yob from 1972.  The Wumpus lives in a completely dark cave of 20 rooms. Each room has 3 tunnels leading to other rooms.

The goal of this game is to help the player kill the wumpus without getting killed instead. There are a number of obstacles (and game objects) in the player's path such as- the player hears rustling of bat wings, which indicates that there might be a bat in any of the 3 adjacent rooms. If they enter one such room, the bat transports them to a completely different room where:
1) The player feels a draft (a light breeze) which indicates that he is close to a pit. If, by any chance, the player makes a wrong move, he falls into the pit and dies.
2) The player smells a stench which indicates that he is close to the wumpus. Here, 1 of 2 things happen: 
  i) If the player and wumpus together are in an odd numbered room, the wumpus moves to the lowest numbered room that is adjacent to it
  ii) If the player and wumpus together are in an even numbered room, the wumpus snaps the player's neck and kills them. 
The player is also provided with an arrow which they can use with the following strategy:
1) The player can shoot the array at any of the 3 adjacent rooms, else it will be considered an invalid move. 
2) The arrow ricochets and goes to the lowest numbered room if an attempt of invalid move is being made
3) While ricochet, if the wumpus is killed by the player, the player is lucky enough and wins the game!
4) While ricochet, if the player is killed by their own arrow, they will unfortunately die!
5) If the wumpus is killed when the arrow is shot, the player wins
6) If somehow the player is hit by their own arrow, they will lose the game and die. 
