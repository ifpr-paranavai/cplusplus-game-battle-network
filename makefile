# Flags do compilador
CXXFLAGS = -I src/include -std=c++20 -MMD -MP -g -O0
LDFLAGS = -L src/lib -std=c++20
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# Lista de arquivos fonte
SOURCES = main.cpp $(wildcard src/application/*/*.cpp) $(wildcard src/adapters/*/*/*.cpp) $(wildcard src/domain/*/*/*.cpp) $(wildcard src/utils/*/*.cpp) $(wildcard src/domain/*/*/*/*.cpp)

# Objetos gerados a partir dos arquivos fonte
OBJECTS = $(SOURCES:.cpp=.o)

# Arquivos de dependência
DEPS = $(OBJECTS:.o=.d)

# Nome do executável
EXECUTABLE = main

# Regra para compilar os objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar o executável
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

# Incluir arquivos de dependência
-include $(DEPS)

# Limpeza
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DEPS)
