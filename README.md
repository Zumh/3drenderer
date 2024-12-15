# 3dgraphics
## install 
```
// gnu utils
sudo apt install build-essential

// sdl libraries
sudo apt install libsdl2-dev
```

## how to run the program
```
gcc main.c -o renderer

// show the warning and standard of C
gcc -Wall -std=c99 src/*.c -o renderer -lSDL2
create multiple files using bash command
touch ./myfolder/{readme,utils}.txt
```

## mac
```
brew install sdl2
```

## folder structures
```
	mkdir 3drenderer
	mkdir 3drenderer/src
	
```
## Create make file 
- build is for building the out put
- run is for running command
- clean will clean up the executable
```
	build:
		gcc -Wall -std=c99 src/*.c -o renderer -lSDL2
	run:
		./renderer
```

