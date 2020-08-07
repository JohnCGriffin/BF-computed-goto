

#CXXFLAGS = --std=c++11 -Wall
#CXX = g++ -O2

CXXFLAGS = -Wall --std=c++17
CXX = clang++ -O3

OBJS = bf.o bf_instruction.o bf_io.o 


bf-demo: bf-labels bf-switch
	time ./bf-switch mandelbrot.bf && time ./bf-labels mandelbrot.bf

bf-labels: $(OBJS) bf_execute_labels.o
	$(CXX) $(CXXFLAGS) $(OBJS) bf_execute_labels.o -o $@

bf-switch: $(OBJS) bf_execute_switch.o
	$(CXX) $(CXXFLAGS) $(OBJS) bf_execute_switch.o -o $@

clean:
	rm -f *.o bf-switch bf-labels
