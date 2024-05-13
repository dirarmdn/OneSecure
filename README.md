# OneSecure

Welcome to the project repository for Project 2: Library-based Application Development.

## Overview

OneSecure is a library-based application developed as part of a college project.

## About This Program

This application is a library-based application, aiming to secure a message or text using Advanced Encryption Standard (AES) and Pixel Value Differencing (PVD) cryptographic encryption methods.

This application allows users to input a text which will then be encrypted using AES method and can also be encrypted using PVD method.

The application is also equipped with a decryption feature that allows users to decrypt messages or texts that have been previously encrypted by AES or PVD methods.

## Features
1. Encrypt Message (AES)
2. Decrypt Message (AES)
3. Encrypt Message (PVD)
4. Decrypt Message (PVD)

## Getting Started

To get started with OneSecure, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/dirarmdn/OneSecure.git
   cd onesecure
  
## About Us
1B / D3 - Informatics Engineering

Our Team Member(s) 🤖:
1. Alya Gustiani N. A (231511035) [https://github.com/alyagustiani]
2. Dhira Ramadini (231511041) [https://github.com/dirarmdn]
3. Dwika Ali Ramdhan I (231511042) [https://github.com/DAliRIJTK]
4. Muammar Syahid R (231511052) [https://github.com/syahiddrr]
5. M Raihan Pratama (231511055) [https://github.com/marukoderu]

Our Manager 😎:
Yadhi Aditya Permana, ST, M.Kom 
NIP 197912242008121001

## Function and Procedure

AES :
1. subBytes
2. shiftRows
3. invSubBytes
4. shiftRow
5. invShiftRows
6. invShiftRow
7. aes_decrypt
8. aes_encrypt
9. printHex
10. printASCII
11. getSBoxValue
12. rotate
13. getSBoxInvert
14. getRconValue
15. core
16. expandKey
17. addRoundKey
18. mixColumns
19. mixColumn
20. aes_round
21. createRoundKey
22. aes_main
23. invMixColumns
24. invMixColumn
25. aes_invMain

PVD :
1. readPNG
2. savePNG
3. embedMessage
4. extractMessage
