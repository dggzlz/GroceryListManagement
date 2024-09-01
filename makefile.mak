TARGET=a4p2
OBJECTS=a4p2.o GroceryList.o
CPPFLAGS=-ansi -pedantic-errors -Wall -g

$(TARGET): $(OBJECTS)
          g++ $(OBJECTS) -o $(TARGET)
clean:
          /bin/rm -f [^G]*.o $(TARGET)

 all: clean $(TARGET)

 a4p1.o:  a4p2.cpp GroceryList.h
         g++ -c $(CPPFLAGS) a4p1.cpp

 GroceryList.o:  GroceryList.cpp GroceryList.h
         g++ -c $(CPPFLAGS) GroceryList.cpp
