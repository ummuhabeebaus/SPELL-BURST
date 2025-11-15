Spell Burst

Spell Burst is a puzzle–action mini game developed in C using the SDL2 multimedia framework. The game combines interactive bubble-bursting mechanics with word-formation challenges, offering an engaging blend of fast-paced action and cognitive skill development. Players burst bubbles to uncover hidden letters and use them to construct valid words to advance through stages.

Key Features

Interactive Gameplay: Burst dynamic, colorful bubbles to collect letters.

Word Formation Module: Form valid words using collected letters with real-time validation.

Smooth Rendering: Built with SDL2 for efficient 2D graphics and responsive controls.

Audio Integration: Background music and sound effects powered by SDL_mixer.

Structured Game Flow: Two-stage system—bubble popping followed by word building.

Technologies Used

Programming Language: C

Graphics & Media: SDL2, SDL_image, SDL_mixer, SDL_ttf

Development Environment: Visual Studio Code

Gameplay Overview

Players burst bubbles using the mouse to reveal letters.

Collected letters are used to form meaningful words.

Successful word formation allows progression to the next stage.

Project Structure
│── main.c
│── bubble_shooting.c / .h
│── word_forming.c / .h
│── utils.c / .h
│── assets/
│     ├── bubbles/
│     ├── sounds/
│     ├── fonts/
│     └── valid_words.txt

Future Enhancements

Additional level designs and difficulty variations

Power-ups and boosters for gameplay support

Multiplayer and competitive modes

Advanced word-puzzle variations

Acknowledgment

Developed as part of the BCA Mini Project under the guidance of Ms. Varsha Ganesh,
Department of Computer Science, Christ College (Autonomous), Irinjalakuda.
