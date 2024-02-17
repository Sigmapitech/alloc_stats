.POSIX:

CC = cc

CFLAGS += -std=c99 -pedantic
CFLAGS += -Wall -Wextra
CFLAGS += -iquote .
CFLAGS += -fPIC
CFLAGS += -O2

VPATH += .
SRC += resolve_symbol.c
SRC += print_stats.c
SRC += wrap_allocation.c
SRC += wrap_exit.c

vpath %.c $(VPATH)

BUILD_DIR := .build

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
LIB := liballoc_stats.so

V ?= 0
ifneq ($(V),0)
  Q :=
else
  Q := @
endif

ifneq ($(shell command -v tput),)
  ifneq ($(shell tput colors),0)

C_RESET := \033[00m
C_BOLD := \e[1m
C_RED := \e[31m
C_GREEN := \e[32m
C_YELLOW := \e[33m
C_BLUE := \e[34m
C_PURPLE := \e[35m
C_CYAN := \e[36m

C_BEGIN := \033[A

  endif
endif

NOW = $(shell date +%s%3N)
STIME := $(call NOW)
TIME_NS = $(shell expr $(call NOW) - $(STIME))
TIME_MS = $(shell expr $(call TIME_NS))

BOXIFY = "[$(C_BLUE)$(1)$(C_RESET)] $(2)"

ifneq ($(shell command -v printf),)
  LOG_TIME = printf $(call BOXIFY, %6s , %b\n) "$(call TIME_MS)"
else
  LOG_TIME = echo -e $(call BOXIFY, $(call TIME_MS) ,)
endif

.SUFFIXES:

.PHONY: all
all: $(LIB)

$(LIB): $(OBJ)
	@ $(CC) $(CFLAGS) -shared -o $@ $^
	@ $(LOG_TIME) "CC $(C_PURPLE) $(notdir $@) $(C_RESET)"

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	$Q $(CC) $(CFLAGS) -o $@ -c $<
	@ $(LOG_TIME) "CC $(C_PURPLE) $(notdir $@) $(C_RESET)"

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(LIB)

.PHONY: re
re: fclean
	$(MAKE) all
