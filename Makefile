# Kompilátor a flagy (C++17, varování pro čistý kód)
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Název výsledného programu
TARGET = main

# Všechny zdrojové soubory podle tvého screenu
SRCS = main.cpp \
       enduranceSimulation.cpp \
       hardCompound.cpp \
       raceCar.cpp \
       softCompound.cpp \
       trackEnvironment.cpp \
       wetTyre.cpp

# Vygeneruje seznam .o souborů z .cpp souborů
OBJS = $(SRCS:.cpp=.o)

# Hlavní pravidlo - spouští se příkazem 'make'
all: $(TARGET)

# Jak se má slinkovat finální program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Jak se má zkompilovat každý jednotlivý .cpp na .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Úklid - spouští se příkazem 'make clean'
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe