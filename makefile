# Diretório onde os objetos e arquivos de dependência serão armazenados
MAKEFLAGS += -j
BUILD_DIR = build
BUILD_DIR_TEST = build-test

# Flags do compilador
CXXFLAGS = -I src/include -std=c++20 -MMD -MP -g -O0
LDFLAGS = -L src/lib -std=c++20
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# Lista de arquivos fonte
SOURCES = src/main.cpp $(wildcard src/application/*/*.cpp) $(wildcard src/adapters/*/*/*.cpp) $(wildcard src/domain/*/*/*.cpp) $(wildcard src/utils/*/*.cpp) $(wildcard src/domain/*/*/*/*.cpp)

# Objetos gerados a partir dos arquivos fonte, agora armazenados no BUILD_DIR
OBJECTS = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Arquivos de dependência
DEPS = $(OBJECTS:.o=.d)

# Diretório de saída para o executável
BIN_DIR = bin

# Diretório das DLLs
DLL_DIR = dlls

# Diretório dos recursos
ASSETS_DIR = assets

# Nome do executável principal
EXECUTABLE = $(BIN_DIR)/battle-network.exe

# Flags de compilação para testes
CXXFLAGS_TEST = -I src/include -std=c++20 -MMD -MP -g -O0
LDFLAGS_TEST = -L src/lib -std=c++20
LIBS_TEST = -lmingw32
SOURCES_TEST = src/main-test.cpp $(wildcard src/application/*/*.cpp) $(wildcard src/domain/*/*/*.cpp) $(wildcard src/utils/*/*.cpp) $(wildcard src/domain/*/*/*/*.cpp)
OBJECTS_TEST = $(patsubst src/%.cpp,$(BUILD_DIR_TEST)/%.o,$(SOURCES_TEST))

# Arquivos de dependência para testes
DEPS_TEST = $(OBJECTS_TEST:.o=.d)

# Diretório de saída para o executável de teste
BIN_DIR_TEST = bin-test

# Nome do executável de teste
EXECUTABLE_TEST = $(BIN_DIR_TEST)/battle-network-test.exe

# Criação de diretórios automaticamente, quando necessário (Windows)
$(BUILD_DIR)/%.o: src/%.cpp
	@if not exist "$(BUILD_DIR)\$(dir $*)" mkdir "$(BUILD_DIR)\$(dir $*)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR_TEST)/%.o: src/%.cpp
	@if not exist "$(BUILD_DIR_TEST)\$(dir $*)" mkdir "$(BUILD_DIR_TEST)\$(dir $*)"
	$(CXX) $(CXXFLAGS_TEST) -c $< -o $@

# Regra para compilar o executável principal
$(EXECUTABLE): $(OBJECTS)
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@if not exist "$(BIN_DIR)\assets" mkdir "$(BIN_DIR)\assets"
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@
	@echo Copying DLLs...
	xcopy /y /d /i "$(DLL_DIR)\*.dll" "$(BIN_DIR)\" > nul
	@echo Copying assets...
	xcopy /y /d /s "$(ASSETS_DIR)\*" "$(BIN_DIR)\assets\" > nul

# Regra para compilar o executável de teste
$(EXECUTABLE_TEST): $(OBJECTS_TEST)
	@if not exist "$(BIN_DIR_TEST)" mkdir "$(BIN_DIR_TEST)"
	$(CXX) $(LDFLAGS_TEST) $(OBJECTS_TEST) $(LIBS_TEST) -o $@

# Alvo para compilar os testes
tests: $(EXECUTABLE_TEST)

# Incluir arquivos de dependência
-include $(DEPS)
-include $(DEPS_TEST)

# Limpeza (Windows)
clean:
	del /q /f $(EXECUTABLE) $(OBJECTS) $(DEPS)
	if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"
	del /q /f $(EXECUTABLE_TEST) $(OBJECTS_TEST) $(DEPS_TEST)
	if exist "$(BIN_DIR_TEST)" rmdir /s /q "$(BIN_DIR_TEST)"
	if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	if exist "$(BUILD_DIR_TEST)" rmdir /s /q "$(BUILD_DIR_TEST)"
