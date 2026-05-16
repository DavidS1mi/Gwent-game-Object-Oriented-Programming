# C++ Gwent Game

## Overview
This project is a C++ console-based simulation of the popular card game, Gwent. It is a two-player, turn-based game where players strategically place cards onto a battlefield to outscore their opponent and deplete their life points. 

## Key Features
* **Turn-Based Strategy:** Players alternate turns, placing cards from their hand onto the board to build their score.
* **Dynamic Board:** A visual, text-based grid represents the battlefield, divided into three tactical rows: melee, ranged, and siege.
* **Resource Management:** Players start with a deck of 22 cards and draw a hand of 10 random cards.
* **Strategic Passing:** Players can choose to play a card or pass their turn. A player cannot pass without playing at least one card first. If a hand is empty, the game auto-passes.
* **Life Points System:** The player with the lowest score at the end of a round loses 1 life point. The game ends when a player's life points reach 0.

## Project Architecture (OOP Approach)
The game is built heavily on Object-Oriented Programming principles, featuring four main classes:

1.  **`Character` (Base Class):** Represents a generic entity with core attributes like player name, ID, and life points.
2.  **`Player` (Derived Class):** Inherits from `Character` and manages player-specific states, including their 22-card deck, 10-card hand, round score, and turn logic. It handles external file loading via `ifstream`.
3.  **`Card`:** Represents an individual card, storing its name, power strength, and designated row (0 = melee, 1 = ranged, 2 = siege). 
4.  **`Board`:** Manages the visual state of the game. It handles rendering the text-based matrix, updating row values, and syncing player life points to the screen.

## How to Play
1. The game initializes by loading decks from external text files.
2. Both players draw 10 random cards into their hand.
3. On your turn, select a card from your hand to place on the board, or choose to pass. (Note: You must play a card before you can pass).
4. The round ends when a player passes. Scores are tallied based on the strength of the cards on the board.
5. The round loser loses 1 life point. Used cards are replaced with random ones from the deck, and the board resets.
6. The first player to reach 0 life points loses the match!

