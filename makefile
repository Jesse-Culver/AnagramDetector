all:
	g++ -std=c++11 main.cpp interface.cpp anagramdetector.cpp wordfixup.cpp interface.h anagramdetector.h wordfixup.h -o AnagramDetector.exe
debug:
	g++ -std=c++11 main.cpp interface.cpp anagramdetector.cpp wordfixup.cpp interface.h anagramdetector.h wordfixup.h -D DEBUG_ -o AnagramDetector_DEBUG.exe
