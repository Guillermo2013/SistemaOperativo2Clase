TARGET=exemploClase
SRCFILES = SuperBlock.cpp Directory.cpp File.cpp Disk.cpp FS.cpp Bitmap.cpp  main.cpp 
OBJ_FILE = ${SRCFILES:.cpp=.o}

.PHONY: clean 

$(TARGET): $(OBJ_FILE)
	g++  -o $@ $(OBJ_FILE)

%.o: %.cpp 
	g++ -c -o $@ $<

run:
	./$(TARGET)
clean:
	rm -f *.o
	rm -f $(TARGET)
