# Game
This game is made in tower defence ganre.
Main language for this project was a choosen a C++. Together with 2 libraries: SFML and SQLite3.
SFML was chosen in order to provide simple graphical user interface and 2D computer graphics.
SQLite3 was chosen in order to provide access and make possible to manage the database through the program.

# Description of the application architecture
In the game, main function main() first of all check whether database is created and whether it have a necessary table with an admin inside it (login – admin, password - admin),
then it creates a window of resolution 800x600 and pushes the MainMenuState into the StateManger. Then we enter the main loop that goes till the end of the program:
  1) Getting the information about user’s inputs through keyboard and mouse, updating the data, drawing all objects that must be seen be user and displaying them.
   ![image](https://github.com/user-attachments/assets/23c1390e-7352-49e8-b358-1bed4e702d91)
  2) State managing: As were shown above each loop we get the data, update it and then draw. In order not to make program too complex I separated the program into different states. In the result the final program has 4 states: main menu state, leader board state, login state and gameplay state. And to
make possible switching between them and manipulating them there was created a special class called StateManager that keep all states in form of stack.
![image](https://github.com/user-attachments/assets/9b6a4317-7c1a-4d0d-b7db-da07a65b7c78)
  3) LoginState: Makes login possible. Login system is made as follows: User inputs name and password, then it checks whether user with this username exists,
  if not, it creates new one with this name and password, otherwise it checks whether password is correct if yes it logins,
  otherwise it displays a message that password is incorrect. The login by itself isn’t necessary, but in that case the user’s score won’t be saved into the DB and later displayed on the leader board.
  4) LeaderBoardState: Displays top 5 users by their max score. In these state admin can delete users.
  5) GameplayState: GameplayState is the main game class that deals with many classes. In general, it was created in order to keep all related to game classes in the same place, Gameplay class by itself doesn’t do much, it just calls needed functions from different classes.
  ![image](https://github.com/user-attachments/assets/8e2b140a-8029-455a-9cbd-5216ad9b055d)
# Descryption of application functionality
1) Core gameplay:
  The primary goal is to achieve the highest score possible.
  The game ends when:
  - The player’s lives reach 0.
  - The player manually exits the game.
  The game follows the Tower Defense genre, where the player must build and strategically place towers to defeat enemies before they reach the end of the path.
2) Towers and their functions:
  The game features two main tower types with three variations each:
  Civil Towers (Support & Production)
  - Factory Tower – Produces money.
  - Research Tower – Produces Research Points (RP) and increases the damage of nearby military towers by 25%.
  - Housing Tower – Produces lives and boosts the production of nearby civil towers.
  Military Towers (Attack)
  - Military towers attack enemies automatically when they enter their attack radius.
  - Each tower has unique damage, attack cooldown, cost, and attack range.
    
  Towers can only be placed in pre-marked building areas:
  ![image](https://github.com/user-attachments/assets/5d4eacfe-5560-4e45-9418-5037d38b7353)
3) Enemy Types and Behavior:
  The game features two types of enemies:
    - Ground Enemies: Higher health and armor but move slowly.
    - Flying Enemies: Lower health but move significantly faster.
  Enemy Progression:
    - Each enemy follows a predefined path with 6 checkpoints.
    - If an enemy reaches the end, the player loses 1 life.
    - Starting from 500 points, every additional 500 points will double enemy health.
    ![image](https://github.com/user-attachments/assets/bfd1832f-4376-461a-b82c-80e6fddfa51a)

4) Hero Mechanics:
  - The Hero is a special playable entity that starts inactive.
  - The player can activate the Hero by clicking on it.
  - The Hero can move using the keyboard (W, A, S, D) and attack\defend using the mouse (LMB/RMB).
  - If the Hero dies, it respawns after 30 seconds.

5) Battle System (Hero vs. Enemy):
  - The battle begins when an enemy enters the Hero's action radius.
  - Combat Mechanics:
    1) The Hero can attack freely.
    2) Every 3 seconds, the enemy attacks using a lightning strike that deals 25 damage (Hero starts with 100 HP).
    3) If the enemy dies, a new enemy (if available) will replace it in battle.
    4) If the Hero dies, the enemy continues its path.
    5) The Hero can escape by moving out of the enemy’s attack range.
   
6) Research Tree (Upgrades):
  - Players can spend Research Points (RP) to unlock buffs for towers.
  - Buffs improve attack power or production speed.
  - Most of the researches have multiple stages, requiring players to unlock previous tiers first.
    
# Descryption of user interface

1) Main Menu
- Purpose: The main hub where the player can start the game, view the leaderboard, or exit.
- Buttons:
  1) Start Game - Begins a new game.
  2) Leader Board - Opens the leaderboard screen.
  3) Exit - Closes the application.
  4) Login button (top right corner): Allows users to authenticate before starting the game.
2. Leaderboard Screen
- Purpose: Displays a ranked list of players and their scores.
- GUI:
  1) A back button Return that returns user to Main Menu (top left corner).
  2) A list of usernames with their respective scores displayed below.
3. Login System
- Purpose: Allows players to log in using a username and password.
- GUI:
  1) A Return button at the top left to go back to the previous screen.
  2) Two input fields:
- Username: A text field for the player’s username.
- Password: A password field for authentication.
  1) Login Button: Submits the entered credentials.
  2) Message: Display message about incorrect password (left bottom corner)
4. Game
- GUI:
  1) Money, research points, and lives (top right corner)
  2) Research tree button (top left corner)
  3) Current Score (top right corner)
  4) Towers and shovel (left side)
