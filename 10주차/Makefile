.SUFFIXES: .cpp .o

OBJECTS = vehicle.o car.o bike.o

TEST_FILE = main.o $(OBJECTS)

CXX = g++

TEST = main

$(TEST) : $(TEST_FILE)
	$(CXX) -o $(TEST) $(TEST_FILE)

clean :
	rm -rf $(TEST) $(TEST_FILE)

main.o : main.cpp
vehicle.o : vehicle.cpp
car.o : car.cpp
bike.o : bike.cpp

