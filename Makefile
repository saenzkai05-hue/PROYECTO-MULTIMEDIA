# Makefile genérico y portable para compilar en consola
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude

SRCS = main.cpp src/production.cpp src/fileio.cpp src/utils.cpp src/menu.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = programa.exe

.PHONY: all clean

all: $(MAIN)
	@echo [INFO] Proyecto compilado exitosamente. Ejecute programa.exe para iniciar.

$(MAIN): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(MAIN)

clean:
	del /q /f $(MAIN) *.o src\*.o 2>nul
