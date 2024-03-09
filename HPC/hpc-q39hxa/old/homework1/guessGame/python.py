#!/usr/bin/python
import random

def human_guess():
    guess = 0
    num = 0

    print("Guess a number: ")
    answer = random.randint(1,100)

    while guess != answer:
        num += 1
        guess = int(input("Make your guess: "))
        if guess < answer:
            print("Higher")
        elif guess > answer:
            print("Lower")
    print("Correct! Num of guesses {}".format(num))

def cpu_guess():
    guess = 0
    lower = 1
    maxi = 101
    num = 0

    answer = int(input("Choose a number: "))

    while guess != answer:
        num += 1
        guess = random.randint(lower,maxi)
        print("CPU guess is: " + str(guess))
        if guess < answer:
            print("Higher")
            lower = guess
        elif guess > answer:
            print("Lower")
            maxi = guess
    print("Correct! Num of guesses {}".format(num))

def cpu_vs_cpu():
    guess = 0
    lower = 1
    maxi = 101
    num = 0

    answer = random.randint(1,100)
    print("CPU1 number is " + str(answer))

    while guess != answer:
        num += 1
        guess = random.randint(lower,maxi)
        print("CPU2 guess is: " + str(guess))
        if guess < answer:
            print("Higher")
            lower = guess
        elif guess > answer:
            print("Lower")
            maxi = guess
    print("Correct! Num of guesses {}".format(num))


def main():
    print("1) human guess")
    print("2) cpu guess")
    print("3) cpu vs cpu")
    mode = int(input("Select a game mode: "))
    if mode == 1:
        human_guess()
    elif mode == 2:
        cpu_guess()
    else:
        cpu_vs_cpu()

main()