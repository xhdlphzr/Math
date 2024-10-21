.\build\main.exe: .\src\main.cpp .\lib\init.cpp .\lib\dijkstra.cpp .\lib\print.cpp
	g++ .\src\main.cpp .\lib\init.cpp .\lib\dijkstra.cpp .\lib\print.cpp -o .\build\main.exe

run: .\build\main.exe
	cd .\build
	.\main.exe

clean:
	del .\build\main.exe