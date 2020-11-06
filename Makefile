# Makefile by Jaime Feldman B. 2020.
#
######################################################################
# MACROS
######################################################################
# $(1) : Source file.
define CPP2OBJ
	$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1)))
endef

# $(1) : Nombre del archivo compilando.
define PRINTOK
	echo -n ${1}; \
	printf %$$(($(TERMIANL_HALF_COLS_SIZE) - $(shell echo -n $(1) | wc -c)))s | tr " " "."; \
	echo -e "[${green}OK${NOC}]"
endef

# $(1) : Nombre del archivo compilando.
define PRINTFAIL
	echo -n ${1}; \
	printf %$$(($(TERMIANL_HALF_COLS_SIZE) - $(shell echo -n $(1) | wc -c)))s | tr " " "."; \
	echo -e "[${red}STOP${NOC}]"
endef

######################################################################
# CONFIG  
######################################################################

red		=\033[0;31m
green	=\033[0;32m
NOC		=\033[0m

SHELL    := /bin/bash
APP      := bin/ejecutable
APPLINK  := appEjecutable
CCFLAGAS := -std=c++17 -Wall -O3 -Wno-c++11-extensions
INCLUDES := src/class/
CC       := g++
MKDIR    := mkdir -p
SRC      := src
OBJ      := obj
BIN      := bin

ALLCPPS       := $(shell find $(SRC) -type f -iname *.cpp)
SUBDIRS       := $(shell find $(SRC) -type d)
OBJSUBDIRS    := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
OBJECTS_FILES := $(foreach F,$(ALLCPPS),$(call CPP2OBJ,$(F)))
FIND_RESULTS  := $(shell find $(OBJ) -type f -iname *.o | wc -l)

TERMINAL_COLS_SIZE      :=$(shell tput cols)
TERMIANL_HALF_COLS_SIZE :=$$(($(TERMINAL_COLS_SIZE) / 2 ))

.PHONY: info clean project
.SILENT: clean $(APP) $(OBJECTS_FILES) 

$(APP): $(OBJSUBDIRS) $(OBJECTS_FILES) 
	if [ -d "bin" ]; then \
		$(CC) -o $(APP) $(OBJECTS_FILES) $(CCFLAGAS); \
	else \
		mkdir -p bin; \
		$(CC) -o $(APP) $(OBJECTS_FILES) $(CCFLAGAS); \
	fi 

	$(call PRINTOK,"Creando $(APP)")

	if [ -a $(APP) ]; then \
		ln -f -s $(APP) $(APPLINK); \
		$(call PRINTOK,"Crando enalce simbolico $(APPLINK)"); \
	else \
		$(call PRINTFAIL,"Creando enlace simbolico $(APPLINK)"); \
	fi


$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -I $(INCLUDES) -c $^ $(CCFLAGAS)
	$(call PRINTOK, $@)

info:
	$(info $(ALLCPPS))
	$(info $(OBJECTS_FILES))

$(OBJSUBDIRS): 
	$(MKDIR) $(OBJSUBDIRS) 

clean:
	if [ $(FIND_RESULTS) -gt 0 ]; then \
		find $(OBJ) -type f -iname *.o -delete; \
		rm -f $(APP); \
		rm -f $(APPLINK); \
		$(call PRINTOK, "Limpiando el proyecto"); \
	else \
		$(call PRINTFAIL,"El proyecto se encuentra limpio"); \
    fi

