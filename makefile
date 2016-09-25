all:
	g++ -std=c++11 main.cpp interface.cpp anagramdetector.cpp interface.h anagramdetector.h -o AnagramDetector.exe
debug:
	g++ -std=c++11main.cpp interface.cpp anagramdetector.cpp interface.h anagramdetector.h -D DEBUG_ -o AnagramDetector_DEBUG.exe
