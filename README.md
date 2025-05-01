# BowlingGame
Let's Play Bowling
# Bowling Game Calculator 

This project implements a Bowling Game score calculator in C++. The program takes user input in a bowling scoring format (e.g., `X`, `/`, numbers) and calculates the frame-wise scores and total score according to standard bowling rules.

---

## 📂 Project Structure

- `BowlingGame.cpp`: core file for playing game.


---

## 🛠 Features

- Supports Strike (`X`), Spare (`/`), and numeric scores.
- Calculates score frame-by-frame.
- Handles invalid inputs gracefully.
- Prevents scoring if input is incomplete for 10 frames.
- No bonus is added in the 10th frame (as per the modified rules).
- Includes exception handling.

---
## Getting Started

1. Compile the code:
    ```bash
    g++ BowlingGame.cpp -o bowling
    ```

2. Run the application:
    ```bash
    ./bowling
    ```

3. Enter bowling input:
    ```
    Enter bowling scores ( X is strike, / is spare ): X7/9-X-88/-6XXX81
    ```

---
