# Arkanoid
This project is a clone (in a simpler version) of the famous Arkanoid game. It was developed as the project of the Base C++ Programming course (Game Development Master).
It implements an infinite generation of random levels, with different hit counts for different brick types, and the platform controlled by the player bounces the ball (more or less) like in the original game.
The movement of the ball is controlled by a simple but effective collision and physics system.

![Screenshot 2023-11-27 224010](https://github.com/Ccipo1998/Arkanoid/assets/61557131/7dced311-d8af-4168-847b-de8eee331424)

![Screenshot 2023-11-27 224041](https://github.com/Ccipo1998/Arkanoid/assets/61557131/96221f36-12d9-4ee2-a9ce-00b4f8aaca94)

![Screenshot 2023-11-27 224102](https://github.com/Ccipo1998/Arkanoid/assets/61557131/e5f60e56-3fcd-4149-b7a4-a341e80380ff)

# Build

Arkanoid uses CMake to generate build files, via VSCode CMake Tools Extension or via command line:

  1. Navigate to project folder;
  2. cmake -S . -B build
  3. cmake --build build
