main: src/main.cpp src/utils.h
	g++ src/main.cpp -o bin/main `pkg-config opencv --cflags --libs`
