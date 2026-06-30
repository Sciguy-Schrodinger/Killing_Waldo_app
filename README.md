# 🔍 Killing Waldo

A fast-paced hidden-object shooter built with **C++** and **Raylib**.  
Find and shoot Waldo among a crowd of pedestrians — but watch out for friendly fire!

---

## 🎮 Features

- **Hidden-object gameplay** — Waldo is hidden among pedestrians
- **Shooting mechanics** — click to shoot at the target
- **Score tracking** — hits, shots, and civilian casualties are tracked
- **Dynamic crowd** — pedestrians move randomly and multiply after each shot
- **Waldo movement** — Waldo moves and changes direction unpredictably
- **Crosshair cursor** — custom crosshair for precise aiming
- **Sound effects** — gunshot and hit sounds for feedback

---

## 🛠️ Technologies Used

- **C++** — core logic
- **Raylib** — 2D rendering, input handling, audio

---

## 🚀 How to Build

### Requirements

Install Raylib:

bash
# Ubuntu / Debian
sudo apt install libraylib-dev

# Or build from source
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake ..
make
sudo make install


## Compile

g++ -o killing_waldo killing_waldo.cpp \
    -lraylib -lm -lpthread -ldl -lrt -lX11

# Run

./killing_waldo

🎮 Controls
Mouse / Key	Action
Left Click	Shoot at the cursor position
Close Window	Exit the game

🧠 How It Works

1.    Waldo — moves randomly and changes direction periodically

2.    Pedestrians — move randomly and change direction periodically

3.    Shooting — click to shoot at the crosshair position

4.    Hit detection — if you hit Waldo, you score a hit

5.    Casualties — shooting a pedestrian counts as a casualty

6.    Crowd growth — each successful shot adds more pedestrians





