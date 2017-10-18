TARGET=exemploClase
SRCFILES = Disk.cpp FS.cpp main.cpp 
OBJ_FILE = ${SRCFILES:.cpp=.o}

.PHONY: clean 

$(TARGET): $(OBJ_FILE)
	g++  -o $@ $(OBJ_FILE)

%.o: %.cpp 
	g++ -c -o $@ $<

clean:
	rm -f *.o
	rm -f $(TARGET)
