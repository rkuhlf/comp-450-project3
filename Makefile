CXX_FLAGS=-std=c++11 -O2 -Wall -Wextra

INCLUDE_FLAGS=`pkg-config --cflags ompl eigen3`
# Linker options
LD_FLAGS= `pkg-config --libs-only-l ompl`

# The c++ compiler to invoke
CXX=g++
all: Project3Exercise2 Project3Exercise3

clean:
	rm -f *.o
	rm -f Project3Exercise2 Project3Exercise3
	rm -f *.console

%.o: src/%.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_FLAGS) $< -o $@

Project3Exercise2: Project3Exercise2.o RTP.o CollisionChecking.o
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -Lsrc/. -o $@ $^ $(LD_FLAGS)

Project3Exercise3: Project3Exercise3.o RTP.o CollisionChecking.o
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -Lsrc/. -o $@ $^ $(LD_FLAGS)
