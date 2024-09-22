clear

if [[ `whoami` != root ]]; then
	echo "you must be root to execute this program"
	echo "if you have sudo installed you can use sudo su"
	exit
fi

sdl2-config --version 2> /dev/null

if [[ $? != 0 ]]; then
	echo "SDL2 is not installed on this machine,"
	echo "SDL2 needs to be installed so the code can compile"
	echo  -n "do you want this script to temporary install SDL2? [Y/n]: "
	read choice

	if [[ "$choice" == "y" ]]; then
		sudo apt install libsdl2-dev -y
		g++ -o main src/*.cpp main.cpp -lSDL2
		sudo apt purge libsdl2-dev -y
		./main
	
	else
		echo "Have a good day!"
	fi


else
	g++ -o main src/*.cpp main.cpp -lSDL2
	./main
fi
