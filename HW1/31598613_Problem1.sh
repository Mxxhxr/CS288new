#!/bin/bash

echo "Hello, welcome to Rock, Paper, Scissors!"
printf "Rules: \n  - Rock beats Scissors (by crushing them).\n  - Scissors beats Paper (by cutting it).\n"
echo "  - Paper beats Rock (by covering it)."
printf "\n\n"

function play() {

    echo "Please enter your choice (rock, paper, or scissors) in all lowercase:"
    read player1_choice

    player2_choice=$((RANDOM % 3))

    case $player2_choice in
        0)
            player2_choice="rock" ;;
        1)
            player2_choice="paper" ;;
        2)
            player2_choice="scissors" ;;
    esac

    echo "Player 2 selection (computer): $player2_choice"

}

is_tie=0
while [ $is_tie -eq 0 ]
do
    play

    if [ $player1_choice == $player2_choice ]; then
        printf "Its a tie! Lets play again.\n\n"
        is_tie=0
    elif [[ $player1_choice == "rock" && $player2_choice == "paper" ]]; then
        printf "\nPlayer 2 wins!\n"
        is_tie=1
    elif [[ $player1_choice == "rock" && $player2_choice == "scissors" ]]; then
        printf "\nPlayer 1 wins!\n"
        is_tie=1
    elif [[ $player1_choice == "paper" && $player2_choice == "rock" ]]; then
        printf "\nPlayer 1 wins!\n"
        is_tie=1
    elif [[ $player1_choice == "paper" && $player2_choice == "scissors" ]]; then
        printf "\nPlayer 2 wins!\n"
        is_tie=1
    elif [[ $player1_choice == "scissors" && $player2_choice == "rock" ]]; then
        printf "\nPlayer 2 wins!\n"
        is_tie=1
    elif [[ $player1_choice == "scissors" && $player2_choice == "paper" ]]; then
        printf "\nPlayer 1 wins!\n"
        is_tie=1
    else
        printf "Invalid input. Please enter rock, paper, or scissors.\n"
        is_tie=0
    fi
done