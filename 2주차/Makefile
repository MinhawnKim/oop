.SUFFIXES : .cpp .o

OBJECTS = print.o student_id.o main.o

CXX = g++
CFLAGS = -c

TARGET  = test

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

clean :
	rm -rf $(OBJECTS) $(TARGET)

main.o : main.cpp
print.o : print.cpp
student_id.o : student_id.cpp
