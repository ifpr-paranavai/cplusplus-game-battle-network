# Flags do compilador
CXXFLAGS = -I src/include -std=c++20 -MMD -MP -g -O0
LDFLAGS = -L src/lib -std=c++20
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# Lista de arquivos fonte
SOURCES = src/main.cpp $(wildcard src/application/*/*.cpp) $(wildcard src/adapters/*/*/*.cpp) $(wildcard src/domain/*/*/*.cpp) $(wildcard src/utils/*/*.cpp) $(wildcard src/domain/*/*/*/*.cpp)

# Objetos gerados a partir dos arquivos fonte
OBJECTS = $(SOURCES:.cpp=.o)

# Arquivos de dependência
DEPS = $(OBJECTS:.o=.d)

# Diretório de saída para o executável
BIN_DIR = bin

# Diretório das DLLs
DLL_DIR = dlls

# Diretório dos recursos
ASSETS_DIR = assets

# Nome do executável
EXECUTABLE = $(BIN_DIR)/battle-network.exe

# Regra para compilar os objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar o executável
$(EXECUTABLE): $(OBJECTS)
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@if not exist "$(BIN_DIR)/assets" mkdir "$(BIN_DIR)/assets"
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@
	@echo Copying DLLs...
	xcopy /y /d /i "$(DLL_DIR)\*.dll" "$(BIN_DIR)\"
	@echo Copying assets...
	xcopy /y /d /s "$(ASSETS_DIR)\*" "$(BIN_DIR)\assets\"

# Incluir arquivos de dependência
-include $(DEPS)

# Limpeza
clean:
	del /q $(OBJECTS) $(EXECUTABLE) $(DEPS)
	if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"
