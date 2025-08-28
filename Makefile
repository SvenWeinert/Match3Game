all: compile link

compile: 
	g++ -c main.cpp -I"<your-sfml-path>\include" -DSFML_STATIC

link:
	g++ main.o -o main -L"<your-sfml-path>\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

clean:
	rm -f main.exe