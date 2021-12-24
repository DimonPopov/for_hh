G = g++
GFLAGS = -Wall -std=c++17
OBJ = main.o


.PHONY: clean task


task: $(OBJ)
	$(G) $(GFLAGS) $^ -o $@

main.o: main.cpp ServerInfo.hpp
	$(G) $(GFLAGS) -c $<

clean:
	-rm *.o task