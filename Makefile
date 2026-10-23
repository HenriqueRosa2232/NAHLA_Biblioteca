
# ==========================
# CONFIGURACOES
# ==========================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC

PKG_CONFIG = pkg-config
QT_PACKAGES = Qt6Widgets Qt6Sql

QT_CFLAGS = $(shell $(PKG_CONFIG) --cflags $(QT_PACKAGES))
QT_LIBS = $(shell $(PKG_CONFIG) --libs $(QT_PACKAGES))

QT_HOST_BINS = $(shell qmake6 -query QT_HOST_BINS 2>/dev/null)
UIC = $(QT_HOST_BINS)/uic
MOC = $(QT_HOST_BINS)/moc

# ==========================
# DIRETORIOS
# ==========================
QT_DIR = ./QT
BUILD_DIR = ./build-qt

CXXFLAGS += $(QT_CFLAGS) -I$(QT_DIR) -I$(BUILD_DIR)

# ==========================
# OBJETOS
# ==========================
OBJ = $(BUILD_DIR)/main.o \
      $(BUILD_DIR)/loginwindow.o \
      $(BUILD_DIR)/mainwindow.o \
      $(BUILD_DIR)/form.o \
      $(BUILD_DIR)/moc_loginwindow.o \
      $(BUILD_DIR)/moc_mainwindow.o \
      $(BUILD_DIR)/moc_form.o

# ==========================
# COMPILACAO PRINCIPAL
# ==========================
.PHONY: all run clean

all: NAHLA_Biblioteca

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ==========================
# GERACAO DAS INTERFACES
# ==========================
$(BUILD_DIR)/ui_%.h: $(QT_DIR)/%.ui | $(BUILD_DIR)
	$(UIC) $< -o $@

$(BUILD_DIR)/loginwindow.o: $(BUILD_DIR)/ui_loginwindow.h
$(BUILD_DIR)/mainwindow.o: $(BUILD_DIR)/ui_mainwindow.h
$(BUILD_DIR)/form.o: $(BUILD_DIR)/ui_form.h

# ==========================
# GERACAO DO CODIGO DO MOC
# ==========================
$(BUILD_DIR)/moc_%.cpp: $(QT_DIR)/%.h | $(BUILD_DIR)
	$(MOC) $(QT_CFLAGS) $< -o $@

$(BUILD_DIR)/moc_%.o: $(BUILD_DIR)/moc_%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# ==========================
# COMPILACAO DOS .CPP
# ==========================
$(BUILD_DIR)/%.o: $(QT_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(OBJ:.o=.d)

# ==========================
# LINKEDICAO
# ==========================
NAHLA_Biblioteca: $(OBJ)
	$(CXX) $(OBJ) -o $@ $(QT_LIBS)

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
