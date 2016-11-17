CC=gcc
CFLAGS=-Wextra -Wall
LDFLAGS=
EXEC=projet_C
OBJ_DIR=obj
SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR)/utils.o:     utils.h
$(OBJ_DIR)/file.o:              file.h
$(OBJ_DIR)/directory.o: utils.h file.h directory.h
$(OBJ_DIR)/main.o:              file.h directory.h

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf $(OBJ_DIR)/*.o
	@if [ -z "`ls -A $(OBJ_DIR) 2>/dev/null`" ]; then rm -rf $(OBJ_DIR); fi

mrproper: clean
	@rm -rf $(EXEC)
