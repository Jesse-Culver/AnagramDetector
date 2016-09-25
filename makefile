all:
	g++ main.cpp interface.cpp interface.h -o AnagramDetector.exe
debug:
	g++ main.cpp interface.cpp interface.h -D DEBUG_ -o AnagramDetector_DEBUG.exe
