# Homework 3

## Diagram

diagram.xml can be modified with ipe (http://ipe.otfried.org/)

## K_i

K_i is the operation constant, it's calculated at the beginning of every operation as the combination of a prime number and the state.

K_i = ((2926415965689092963) + ((A & ~B) ^ (C & D))) + ~A

## Functions

### F

F(A, B, C) = (A & B) ^ (A & C) ^ (B & C)

### F2

F2(A, B, K_i) = (A & B) ^ (~B & K_i)

### Fr

This is the random function generator, for any operation of the hash it will perform the following operation

((A ^ ~B) & (C ^ B)) % 4

Depending on the result of this the function will be one of the following functions which were obtained from the SHA-2 wikipedia page.

- F(A, B, C) = (A & B) ^ (~A & C)
- F(A, B, C) = (A & B) ^ (A & C) ^ (B & C)
- F(A) = (A >> 2) ^ (A >> 13) ^ (A >> 22)
- F(C) = (C >> 6) ^ (C >> 11) ^ (C >> 25)

## Initial Values

These are random ~64 bit prime numbers obtained from a prime number generator.

- A = 539958729876229229
- B = 881213617895827187
- C = 1619298787036835669
- D = 4571622384984713413