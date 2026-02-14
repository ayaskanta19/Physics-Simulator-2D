override CXX := C:\Users\AshKiller47\Documents\MinGW\bin\g++.exe

override SOURCES := src\PhySim2\Interface\\*.cpp src\PhySim2\Physics\\*.cpp src\PhySim2\Simulator\\*.cpp

all: compile move link execute

compile:
	$(CXX) -std=c++17 -c src\PhySim2.cpp -c $(SOURCES) -IC:\Retrofit\Libraries\SFML-2.6.1\include -Iinclude -DSFML_STATIC

move:
	move /Y "*.o" obj

link:
	$(CXX) -static obj\\*.o -o bin\PhySim2 -LC:\Retrofit\Libraries\SFML-2.6.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

execute:
	cd bin && PhySim2

clean:
	del obj\\*.o bin\PhySim2.exe