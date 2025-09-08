all: compile link

compile: 
	g++ -c main.cpp ColorManager.cpp Tile.cpp game_board.cpp menu.cpp game.cpp -I"<your-sfml-path>\include" -DSFML_STATIC

link:
	g++ main.o ColorManager.o Tile.o game_board.o menu.o game.o -o MatchThree -L"<your-sfml-path>\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

clean:

	rm -f main.exe

