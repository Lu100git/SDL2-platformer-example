# SDL2-platformer-example (Linux)
this is a simple platformer project in SDL2 covering all the logic behind a platformer game
the building script works only on Debian based distros, if you are not using a Debian based distro
you can still compile this project as long as you have SDL2 installed, I didn't had time to do a CMAKE file
so this is what I got so far.

Instructions, switch to root user on the terminal, or use sudo su
then run the build.sh script example: 
./build.sh

The reason is, if you do not have SDL2 installed, this script will temporary install SDL2
to compile the CPP files, once the project compiles, it will delete SDL2 from your system so you don’t have to deal with it
