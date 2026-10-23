
# ==========================
# CONFIGURACOES
# ==========================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC

QT_PACKAGES = Qt6Widgets Qt6Sql

# ==========================
# DEPENDENCIAS
# ==========================
.PHONY: all dependencias compilar run clean

all: dependencias
	$(MAKE) compilar

dependencias:
	sudo apt update
	sudo apt install -y build-essential pkg-config qt6-base-dev qt6-base-dev-tools

# ==========================
# DIRETORIOS
# ==========================
QT_DIR = ./QT
BUILD_DIR = ./build-qt

QT_CFLAGS = $(shell pkg-config --cflags $(QT_PACKAGES))
QT_LIBS = $(shell pkg-config --libs $(QT_PACKAGES))

UIC = $(shell command -v uic 2>/dev/null || find /usr/lib/qt6 -type f -name uic 2>/dev/null | head -n 1)
MOC = $(shell command -v moc 2>/dev/null || find /usr/lib/qt6 -type f -name moc 2>/dev/null | head -n 1)

CXXFLAGS += $(QT_CFLAGS) -I$(QT_DIR) -I$(BUILD_DIR)

# ==========================
# ARQUIVOS OBJETO
# ==========================
OBJ = $(BUILD_DIR)/main.o \
      $(BUILD_DIR)/loginwindow.o \
      $(BUILD_DIR)/mainwindow.o \
      $(BUILD_DIR)/form.o \
      $(BUILD_DIR)/moc_loginwindow.o \
      $(BUILD_DIR)/moc_mainwindow.o \
      $(BUILD_DIR)/moc_form.o

# ==========================
# DIRETORIO DE BUILD
# ==========================
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ==========================
# INTERFACES DO QT
# ==========================
$(BUILD_DIR)/ui_%.h: $(QT_DIR)/%.ui | $(BUILD_DIR)
	$(UIC) $< -o $@

$(BUILD_DIR)/loginwindow.o: $(BUILD_DIR)/ui_loginwindow.h
$(BUILD_DIR)/mainwindow.o: $(BUILD_DIR)/ui_mainwindow.h
$(BUILD_DIR)/form.o: $(BUILD_DIR)/ui_form.h

# ==========================
# CODIGO AUXILIAR DO QT
# ==========================
$(BUILD_DIR)/moc_%.cpp: $(QT_DIR)/%.h | $(BUILD_DIR)
	$(MOC) $< -o $@

$(BUILD_DIR)/moc_%.o: $(BUILD_DIR)/moc_%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# ==========================
# COMPILACAO
# ==========================
$(BUILD_DIR)/%.o: $(QT_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(OBJ:.o=.d)

# ==========================
# EXECUTAVEL
# ==========================
NAHLA_Biblioteca: $(OBJ)
	$(CXX) $(OBJ) -o $@ $(QT_LIBS)

compilar: NAHLA_Biblioteca

# ==========================
# EXECUCAO
# ==========================
run: NAHLA_Biblioteca
	./NAHLA_Biblioteca

# ==========================
# LIMPEZA
# ==========================
clean:
	rm -rf $(BUILD_DIR) NAHLA_Biblioteca
