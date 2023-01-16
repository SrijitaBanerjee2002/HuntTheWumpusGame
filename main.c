/*
CS 211 Fall 2022: Program 2 - Hunt the Wumpus (
Welcome to Hunt the Wumpus, a classic text-based adventure game by Gregory Yob
from 1972.  The Wumpus lives in a completely dark cave of 20 rooms. Each room
has 3 tunnels leading to other rooms.

Name: Srijita Banerjee
System used: Replit
Instructors: Dale Reed, Ellen Kidane
*/

#include <ctype.h>   //for toupper()
#include <stdbool.h> //for boolean values: true/false
#include <stdio.h>
#include <stdlib.h> // for srand

//--------------------------------------------------------------------------------
// This function simply assigns the correct rooms connected to 1 particular room in the dodecahedron
void connecting_rooms(int **rooms) {
  // connecting rooms for room 0
  rooms[0][0] = 0; rooms[0][1] = 0; rooms[0][2] = 0;
  // connecting rooms for room 1
  rooms[1][0] = 5; rooms[1][1] = 2; rooms[1][2] = 8;
  // connecting rooms for room 2
  rooms[2][0] = 10; rooms[2][1] = 3; rooms[2][2] = 1;
  // connecting rooms for room 3
  rooms[3][0] = 4; rooms[3][1] = 12; rooms[3][2] = 2;
  // connecting rooms for room 4
  rooms[4][0] = 14; rooms[4][1] = 3; rooms[4][2] = 5;
  // connecting rooms for room 5
  rooms[5][0] = 6; rooms[5][1] = 4; rooms[5][2] = 1;
  // connecting rooms for room 6
  rooms[6][0] = 7; rooms[6][1] = 15; rooms[6][2] = 5;
  // connecting rooms for room 7
  rooms[7][0] = 6; rooms[7][1] = 8; rooms[7][2] = 17;
  // connecting rooms for room 8
  rooms[8][0] = 7; rooms[8][1] = 9; rooms[8][2] = 1;
  // connecting rooms for room 9
  rooms[9][0] = 8; rooms[9][1] = 10; rooms[9][2] = 18;
  // connecting rooms for room 10
  rooms[10][0] = 9; rooms[10][1] = 2; rooms[10][2] = 12;
  // connecting rooms for room 11
  rooms[11][0] = 10; rooms[11][1] = 19; rooms[11][2] = 12;
  // connecting rooms for room 12
  rooms[12][0] = 3; rooms[12][1] = 11; rooms[12][2] = 13;
  // connecting rooms for room 13
  rooms[13][0] = 14; rooms[13][1] = 20; rooms[13][2] = 12;
  // connecting rooms for room 14
  rooms[14][0] = 13; rooms[14][1] = 15; rooms[14][2] = 4;
  // connecting rooms for room 15
  rooms[15][0] = 14; rooms[15][1] = 6; rooms[15][2] = 16;
  // connecting rooms for room 16
  rooms[16][0] = 17; rooms[16][1] = 20; rooms[16][2] = 15;
  // connecting rooms for room 17
  rooms[17][0] = 7; rooms[17][1] = 16; rooms[17][2] = 18;
  // connecting rooms for room 18
  rooms[18][0] = 17; rooms[18][1] = 9; rooms[18][2] = 19;
  // connecting rooms for room 19
  rooms[19][0] = 18; rooms[19][1] = 20; rooms[19][2] = 11;
  // connecting rooms for room 20
  rooms[20][0] = 19; rooms[20][1] = 16; rooms[20][2] = 13;
}
//--------------------------------------------------------------------------------
// This function displays the cave
void displayCave() {
  printf("\n"
         "       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}

//--------------------------------------------------------------------------------
// This function displays the menu options/directions for the game.
void displayInstructions() {
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you fall "
         "and die.   \n"
         "2. Two other rooms have super-bats.  If you go there, the bats grab "
         "you and     \n"
         "   fly you to some random room, which could be troublesome.  Then "
         "those bats go \n"
         "   to a new room different from where they came from and from the "
         "other bats.   \n"
         "3. The Wumpus is not bothered by the pits or bats, as he has sucker "
         "feet and    \n"
         "   is too heavy for bats to lift.  Usually he is asleep.  Two things "
         "wake       \n"
         "    him up: Anytime you shoot an arrow, or you entering his room.  "
         "The Wumpus   \n"
         "    will move into the lowest-numbered adjacent room anytime you "
         "shoot an arrow.\n"
         "    When you move into the Wumpus' room, then he wakes and moves if "
         "he is in an \n"
         "    odd-numbered room, but stays still otherwise.  After that, if he "
         "is in your \n"
         "    room, he snaps your neck and you die!                            "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Shoot your guided arrow through a list of up to three adjacent "
         "rooms, which  \n"
         "   you specify.  Your arrow ends up in the final room.               "
         "           \n"
         "   To shoot enter 'S' followed by the number of rooms (1..3), and "
         "then the      \n"
         "   list of the desired number (up to 3) of adjacent room numbers, "
         "separated     \n"
         "   by spaces. If an arrow can't go a direction because there is no "
         "connecting   \n"
         "   tunnel, it ricochets and moves to the lowest-numbered adjacent "
         "room and      \n"
         "   continues doing this until it has traveled the designated number "
         "of rooms.   \n"
         "   If the arrow hits the Wumpus, you win! If the arrow hits you, you "
         "lose. You  \n"
         "   automatically pick up the arrow if you go through a room with the "
         "arrow in   \n"
         "   it.                                                               "
         "           \n"
         "3. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "4. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "5. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "6. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
} // end displayInstructions()

//--------------------------------------------------------------------------------
//This function initializes the locations for the game elements before starting the game, uses srand() for this purpose
void initialize_locations(int *player, int *wumpus, int *pit1, int *pit2, int *bats1, int *bats2, int *arrow) {
  srand(1);
  *player = rand() % 20 + 1;
  *wumpus = rand() % 20 + 1;
  *pit1 = rand() % 20 + 1;
  *pit2 = rand() % 20 + 1;
  *bats1 = rand() % 20 + 1;
  rand() % 20 + 1;
  rand() % 20 + 1;
  *bats2 = rand() % 20 + 1;
  *arrow = rand() % 20 + 1;
}

//--------------------------------------------------------------------------------
//This function implements option c- explicitely displaying locations of game elements
void option_c_cheating(int *player, int *wumpus, int *pit1, int *pit2, int *bats1, int *bats2, int *arrow) {
  printf("Cheating! Game elements are in the following rooms: \n"
         "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
         "%4d %5d %6d %5d %5d %5d %5d \n\n",
         *player, *wumpus, *pit1, *pit2, *bats1, *bats2, *arrow);
}

//--------------------------------------------------------------------------------
// This function resets the position of all the game elements
void option_r_reset(int *player, int *wumpus, int *pit1, int *pit2, int *bats1, int *bats2, int *arrow) {
  printf(" Enter the room locations (1..20) for player, wumpus, pit1, pit2, "
         "bats1, bats2, and arrow:");
  scanf("%i", player);
  scanf("%i", wumpus);
  scanf("%i", pit1);
  scanf("%i", pit2);
  scanf("%i", bats1);
  scanf("%i", bats2);
  scanf("%i", arrow);
  printf("\n\n");
}

//--------------------------------------------------------------------------------
//This function checks whether the player smells a stench in the room they're in; returns true if they do, else false
bool check_for_stench(int *player, int *wumpus, int **rooms) {
  for (int i = 0; i < 3; ++i) {
    if (rooms[*player][i] == *wumpus) {
      return true;
    }
  }
  return false;
}

//--------------------------------------------------------------------------------
//This function checks whether the player feels a draft in the room they're in; returns true if they do, else false
bool check_for_drafts(int *player, int *pit1, int *pit2, int **rooms) {
  for (int i = 0; i < 3; ++i) {
    if (rooms[*player][i] == *pit1 || rooms[*player][i] == *pit2) {
      return true;
    }
  }
  return false;
}

//--------------------------------------------------------------------------------
//This function checks whether the player hears rustling of bat wings in the room they're in; returns true if they do, else false
bool check_for_bat_wings(int *player, int *bats1, int *bats2, int **rooms) {
  for (int i = 0; i < 3; ++i) {
    if (rooms[*player][i] == *bats1 || rooms[*player][i] == *bats2) {
      return true;
    }
  }
  return false;
}

//--------------------------------------------------------------------------------
//This function prints the appropriate error messages by calling each of the above 3 helper functions
void check_for_hazards(int *player, int *wumpus, int *pit1, int *pit2, int *bats1, int *bats2, int *arrow, int **rooms) {
  if (check_for_stench(player, wumpus, rooms)) {
    printf("You smell a stench. ");
  }

  if (check_for_drafts(player, pit1, pit2, rooms)) {
    printf("You feel a draft. ");
  }

  if (check_for_bat_wings(player, bats1, bats2, rooms)) {
    printf("You hear rustling of bat wings. ");
  }
}

//--------------------------------------------------------------------------------
//This function checks whether the move entered by the user is valid or; returns true if move is valid, else false
bool move_is_valid(int *player, int *new_move, int **rooms) {
  for (int i = 0; i < 3; ++i) {
    if (rooms[*player][i] == *new_move) {
      return true;
    }
  }
  return false;
}

//--------------------------------------------------------------------------------
//This function shifts the position of player into the new valid room
void perform_move(int *player, int *new_move) { *player = *new_move; }

//--------------------------------------------------------------------------------
//This function checks whether the player and wumpus are in the same room: 
//if they're in the same room and-
// 1. the room is even numbered - wumpus kills the player (returns 1)
// 2. the room is odd numbered - wumpus moves to the lowest numbered adjacent room (returns 0)
// if they're not in the same room, returns -1
int same_player_and_wumpus(int *player, int *wumpus, int **rooms) {
  if (*player == *wumpus) {
    // when the wumpus is in an even numbered room
    if (*wumpus % 2 == 0) {
      return 1; // program terminates in main
    } else {
      return 0; // player and wumpus are in an odd numbered room
    }
  } else {
    return -1; // player and wumpus are not in the same room
  }
}

//--------------------------------------------------------------------------------
//This function moves the wumpus to the lowest adjacent room
void move_wumpus_to_lowest_room(int *wumpus, int **rooms) {
  int smallest_room = rooms[*wumpus][0];
  for (int i = 0; i < 3; ++i) {
    if (rooms[*wumpus][i] < smallest_room) {
      smallest_room = rooms[*wumpus][i];
    }
  }
  *wumpus = smallest_room;
}

//--------------------------------------------------------------------------------
//This function checks whether the player and either of the pits are in the same room. returns 1 if true, else false
bool same_player_and_pit(int *player, int *pit1, int *pit2) {
  if (*player == *pit1 || *player == *pit2) {
    return true;
  } else {
    return false;
  }
}

//--------------------------------------------------------------------------------
//This function checks and transports players and bats to different random locations
bool check_and_transport_player_and_bats(int *player, int *wumpus, int *pit1, int *pit2, int *bats1, int *bats2) {
  int old_player = *player;
  if (*player == *bats1) {
    int old_bat = *bats1;
    *player = rand() % 20 + 1;
    *bats1 = rand() % 20 + 1;
    while (*bats1 == old_bat || *bats1 == *bats2) {
      *bats1 = rand() % 20 + 1;
      
    }
    return true;
  }
  if (*player == *bats2) {
    int old_bat = *bats2;
    *player = rand() % 20 + 1;
    *bats2 = rand() % 20 + 1;
    while (*bats2 == old_bat || *bats2 == *bats1) {
      *bats2 = rand() % 20 + 1;
    }
    return true;
  }
  return false;
}

//--------------------------------------------------------------------------------
//This function moves the player to the the new (and valid) rooms as entered by the user. Returns 1 if the function needs to terminate in main (player+wumpus in even numbered room, player+pits in the same room), returns 0 for valid moves, -1 for invalid moves
int option_m_moves(int *player, int *wumpus, int *pit1, int *pit2, int *bats1, int *bats2, int *arrow, int **rooms) {
  int new_move = 0;

  scanf("%i", &new_move);
  if (move_is_valid(player, &new_move, rooms)) {
    perform_move(player, &new_move);
    int verify_wumpus = same_player_and_wumpus(player, wumpus, rooms);
    if (verify_wumpus == 1) {
      printf(
          "You briefly feel a slimy tentacled arm as your neck is snapped. \n"
          "It is over.\n");
      return 0;
    }
    if (verify_wumpus == 0) {
      move_wumpus_to_lowest_room(wumpus, rooms);
      printf("You hear a slithering sound, as the Wumpus slips away. \n"
             "Whew, that was close! \n");
      return 1;
    }
    if (same_player_and_pit(player, pit1, pit2)) {
      printf("Aaaaaaaaahhhhhh....   \n");
      printf("    You fall into a pit and die. \n");
      return 0;
    }
    if (check_and_transport_player_and_bats(player, wumpus, pit1, pit2, bats1, bats2)) {
      printf("Woah... you're flying! \n");
      printf("You've just been transported by bats to room %d.\n", *player);
      return 1;
    }
    return 1;
  } else {
    printf("Invalid move.  Please retry. \n");
    return -1;
  }
}

//--------------------------------------------------------------------------------
//This function checks whether the guess of wumpus room entered by the user is correct or not; this terminates in main
void option_g_guess(int *wumpus) {
  int guess = 0;
  printf("Enter room (1..20) you think Wumpus is in: ");
  scanf("%i", &guess);
  if (guess == *wumpus) {
    printf("You won!\n");
  } else {
    printf("You lost.\n");
  }
}

//--------------------------------------------------------------------------------
//This function checks the various conditions when the player shoots an arrow
// - you need to have the arrow in order to shoot it
// - you can atmost shoot the 1 arrow in 3 rooms
// - arrow ricochets and goes to the lowest numbered room if an attempt of invalid move is being made
// - while ricochet, if the wumpus is killed by the player, the player is lucky enough and wins the game!
// - while ricochet, if the player is killed by their own arrow, they will unfortunately die!
// - if the wumpus is killed when the arrow is shot, the player wins
// - if somehow the player is hit by their own arrow, they will lose the game and die
bool option_s_shoot_arrow(int *player, int *wumpus, int *arrow, int **rooms) {
  int no_of_shoots=0, count=1; 
  bool ricochet=false;
  if(*arrow!=-1) {
    	printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
  } else{
    printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
	  scanf("%i", &no_of_shoots);
    if(no_of_shoots>3) { 
      printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
      no_of_shoots=3;
    } 
    int arrow_rooms[no_of_shoots];
    int current_arrow=*player;
    for(int i=0; i<no_of_shoots; ++i) {
      scanf("%i",&arrow_rooms[i]);
    }
    
    
    for(int i=0; i<no_of_shoots; ++i) {
      if(move_is_valid(&current_arrow, &arrow_rooms[i], rooms)==true) {
          current_arrow=arrow_rooms[i];
          //move_wumpus_to_lowest_room(wumpus, rooms);
        } else{
          printf("Room %d is not adjacent.  Arrow ricochets...\n", arrow_rooms[i]);
          ricochet=true;
          int smallest_room=rooms[current_arrow][0];
          for(int i=0; i<3; ++i) {
            if(rooms[current_arrow][i]<smallest_room) { smallest_room = rooms[current_arrow][i];}
          }
          current_arrow = smallest_room; 
        }
      *arrow=current_arrow;
      if(*arrow==*player) {
        if(ricochet) {
          	printf( "You just shot yourself, and are dying.\n"
            "It didn't take long, you're dead.\n");
        } else{
          	printf( "You just shot yourself.  \n"
            "Maybe Darwin was right.  You're dead.\n");
        }
        return true;
      }
      if(*arrow==*wumpus) {
        if(ricochet) {
          	printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
            "Accidental victory, but still you win!\n");
        } else {
          	printf( "Wumpus has just been pierced by your deadly arrow! \n"
            "Congratulations on your victory, you awesome hunter you.\n");
        }
        return true;
      } 
    }
    if(*wumpus!=arrow_rooms[no_of_shoots-1]) { //if wumpus is in neither of the rooms, it can still hear the shooting of the arrow. So it slithers into the lowest numbered adjacent room. 
      move_wumpus_to_lowest_room(wumpus, rooms);
      return false;
    }
  }
  return false;
}

//--------------------------------------------------------------------------------
//This function prints a congratulatory message when the player again finds the arrow
void check_for_arrow(int *player, int *arrow) {
  if(*player==*arrow){
    *arrow=-1;
    printf("Congratulations, you found the arrow and can once again shoot. \n");
  }
}

//--------------------------------------------------------------------------------
//Driver function
int main(void) {
  int count = 1, player = 0, wumpus = 0, pit1 = 0, pit2 = 0, bats1 = 0, bats2 = 0, arrow = 0, result = 0;
  char choice;
  int **rooms = malloc(21 * sizeof(int *)); //dynamic allocation of memory for the rooms
  for (int i = 0; i < 21; ++i) {
    rooms[i] = malloc(3 * sizeof(int)); //dynamic allocation of memory for the connecting rooms
  }
  connecting_rooms(rooms); // dynamically allocating the rooms
  initialize_locations(&player, &wumpus, &pit1, &pit2, &bats1, &bats2, &arrow); // locations for game players initialized
  while (true) {
    check_for_arrow(&player, &arrow); 
    printf("You are in room %i. ", player);
    check_for_hazards(&player, &wumpus, &pit1, &pit2, &bats1, &bats2, &arrow, rooms);
    printf("\n\n%i. Enter your move (or 'D' for directions): ", count);
    scanf(" %c", &choice);
    choice = toupper(choice);
    bool break_out_of_loop = false;
    switch (choice) {
    case 'C':
      // cheating function
      option_c_cheating(&player, &wumpus, &pit1, &pit2, &bats1, &bats2, &arrow);
      break;
    case 'M':
      // move function
      result = option_m_moves(&player, &wumpus, &pit1, &pit2, &bats1, &bats2, &arrow, rooms);
      if (result == 1) {
        count++;
      }
      if (result == 0) {
        break_out_of_loop = true; //the while(true) loop breaks and program ends
      }
      break;
    case 'R':
      // reset function
      option_r_reset(&player, &wumpus, &pit1, &pit2, &bats1, &bats2, &arrow);
      break;
    case 'S':
      // shoot function
      count++;
      if(option_s_shoot_arrow(&player,&wumpus,&arrow,rooms)) {
        break_out_of_loop = true; //the while(true) loop breaks and program ends
      }
      break;
    case 'D':
      // display instructions
      displayInstructions();
      break;
    case 'P':
      // display cave
      displayCave();
      break;
    case 'G':
      // guess wumpus room
      option_g_guess(&wumpus);
      break_out_of_loop = true; //the while(true) loop breaks and program ends
      break;
    default:
      // exits the program
      break_out_of_loop = true; //the while(true) loop breaks and program ends
    }
    if (break_out_of_loop) {
      printf("\nExiting Program ...\n");
      break;
    }
  }
  return 0; //keep C happy
}
