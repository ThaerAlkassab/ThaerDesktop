#!/usr/bin/python3
import random
# generate a number from 1 to 100
gen = random.randint( 1, 100 )
inp = None
c = 0

# while input != generated
while inp != gen:
    inp = int(input("Tell me your guess: "))
    c += 1
    if inp > gen:
        print("Need smaller number!")
    elif inp < gen:
        print("Need bigger number!")

print(f'You guessed the number! You needed {c} guesses.')

# ask input from user
# if equal, print message and exit
# otherwise goto ask input

# end while
