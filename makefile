CC := g++
CFLAGS := -std=c++11 -Wall

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

APP_SRC_DIR := $(SRC_DIR)/app
APP_LIB_SRC_DIR := $(SRC_DIR)/app_lib

APP_SRCS := $(wildcard $(APP_SRC_DIR)/*.cpp)
APP_OBJS := $(patsubst $(APP_SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(APP_SRCS))

APP_LIB_SRCS := $(wildcard $(APP_LIB_SRC_DIR)/*.cpp)
APP_LIB_OBJS := $(patsubst $(APP_LIB_SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(APP_LIB_SRCS))

APP_TARGET := $(BIN_DIR)/app

LIB_TARGET := $(OBJ_DIR)/libpython_lib.a

all: $(APP_TARGET)

$(APP_TARGET): $(APP_OBJS) $(LIB_TARGET)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(APP_SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(APP_LIB_SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_TARGET): $(APP_LIB_OBJS)
	@mkdir -p $(OBJ_DIR)
	ar rcs $@ $^

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
