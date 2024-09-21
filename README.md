# Freecell Game - Developed in C

## Project Overview

This project implements the classic solitaire card game **FreeCell** using the **C programming language** with a focus on efficient card movement through the **stack data structure**. 
The game is designed to be played in a command-line interface with user-friendly interactions, ensuring smooth gameplay while adhering to the rules of FreeCell.

### Features:
- Full implementation of FreeCell game mechanics.
- Stack-based data structures to manage card columns and movement.
- User-friendly console interface.
- Validation of card moves to ensure rules compliance.
- Simple and intuitive game reset and victory conditions.

## Project Structure

The project is organized into several key components:

### 1. Data Structures:
- **Card**: A structure representing each card, with members for rank, suit, and pointers to manage cards in a stack.
- **Game Zones**: Divided into:
  - **Zone1**: 8 columns where cards are stacked and moved based on the game's rules.
  - **Zone2**: Free cells that temporarily hold individual cards.
  - **Zone3**: Foundation piles where cards are collected by suit and in ascending order.

### 2. Initialization:
- **initializeVariables**: Sets up the initial game state.
- **createCard**: Generates a card with specified rank and suit.
- **shuffleDeck**: Randomizes the deck to start a new game.
- **generateFullDeck**: Creates and distributes the full deck of 52 cards.

### 3. Game Play:
- **Empiler and Depiler**: Used to push and pop cards from stacks.
- **ismove_valid**: Validates whether a card movement adheres to FreeCell rules.
- **move_Card_inside_Zone1, move_cards_zone1to2, move_cards_zone2to1**: Functions to move cards between columns and free cells.
- **win_check**: Checks the victory condition, ensuring all cards are in the foundation piles.

### 4. User Interface:
- **print_cards_zone1, print_zone2, print_Zone3**: Functions to display the current state of the game zones.
- **getValidChoice**: Ensures valid user input, enhancing the gameplay experience.

### 5. Reset and Victory Conditions:
- **Addcardstozone1**: Resets the game by refilling Zone1 with all 52 cards.
- **win_check**: Verifies if the player has successfully moved all cards to the foundation piles.
