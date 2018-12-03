# default Flags 
flags = -g -Wall -Wextra -pedantic -std=c++11

# list of object files
objects = ExtSortRange.o Page.o

# make object files
%.o: %.cpp
	g++ $(flags) $*.cpp -c -o $@

# main executable
exec: main.cpp $(objects)
	g++ $(flags) $(objects) main.cpp -o extsort.exe

# make will not remove intermediate .o files
.PRECIOUS: $.o

clean:
	rm -f $(objects) *.exe