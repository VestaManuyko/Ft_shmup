#-------------------------------------------------------------------------------
# PART 1 -- collection of all SOURCE files
#-------------------------------------------------------------------------------
SRC_DIR	=	source/
SRC_MAN	=	main.c init.c utils.c \
			ncurses_setup.c ncurses_windows.c ncurses_resize.c \
			world_populate.c world_update.c \
			game_over.c game_restart.c input.c\
			move_player_1.c move_helper.c \
			spawn.c collision.c collision_helper.c \
			draw.c draw_info.c timer.c
SRC_BON	= 	main.c init_bonus.c utils.c\
			ncurses_setup_bonus.c \
			ncurses_windows_bonus.c \
			ncurses_resize_bonus.c \
			world_populate.c world_update_bonus.c \
			game_over.c game_restart_bonus.c input_bonus.c\
			move_player_1.c move_player_2_bonus.c move_helper.c \
			collision.c collision_helper.c spawn_bonus.c \
			draw_bonus.c draw_info_bonus.c timer.c
#-------------------------------------------------------------------------------
# PART 2 -- combining SRC into collection of all OBJECT files
#-------------------------------------------------------------------------------
O_FILES_MAN	= $(SRC_MAN:.c=.o)
O_FILES_BON	= $(SRC_BON:.c=.o)
OBJ_DIR	= build/
OBJ_MAN	= $(addprefix $(OBJ_DIR), $(O_FILES_MAN))
OBJ_BON = $(addprefix $(OBJ_DIR), $(O_FILES_BON))
#-------------------------------------------------------------------------------
# PART 3 -- libft
#-------------------------------------------------------------------------------
# none
#-------------------------------------------------------------------------------
# PART 4 -- environment variables
#-------------------------------------------------------------------------------
C			= cc
C_FLAGS		= -Wall -Wextra -Werror
C_LIBS		= -lncurses
#-------------------------------------------------------------------------------
PROG_NAME	= ft_shmup
#-------------------------------------------------------------------------------
FLAG_MAN	= .man
FLAG_BON	= .bon
FLAG_BUG	= .bug
FLAG_CLEAN_M= .clean_m
FLAG_CLEAN_B= .clean_b
#-------------------------------------------------------------------------------
HEADER		= include/shmup.h
INC_DIR		= -Iinclude/
#-------------------------------------------------------------------------------
# PART 5 -- command targets
#-------------------------------------------------------------------------------
# default target depends on file to create
all:		switch_mode $(PROG_NAME)
# delete all object files
clean:
	@rm -f $(OBJ_MAN) $(OBJ_BON)
	@rm -f $(FLAG_MAN) $(FLAG_BON) $(FLAG_BUG) $(FLAG_CLEAN_B) $(FLAG_CLEAN_M)
# calls clean target then deletes PROG_NAME
fclean:		clean
	@rm -f $(PROG_NAME)
# rebuilds everything by calling fclean and then all
re:			fclean all
# responsible for the bonus part
bonus:		C_FLAGS += -D BONUS
bonus:		switch_mode $(FLAG_BON)
# build and execute the program
run:		all
	@./$(PROG_NAME)
# debug target to check variable contents
print:
	@echo ---SRC---
	@echo "<man>\n$(SRC_MAN)\n<bon>\n$(SRC_BON)"
	@echo ---OBJ---
	@echo "<man>\n$(OBJ_MAN)\n<bon>\n$(OBJ_BON)"
	@echo "---C_FLAGS & C_LIBS---"
	@echo "$(C_FLAGS)\n$(C_LIBS)"
	@echo ---headers---
	@echo $(HEADER)
# custom debug flags for mandatory part
#-------------------------------------------------------------------------------
val:	C_FLAGS += -g -fno-omit-frame-pointer -O0
val:	all
#debug: C_FLAGS += -g -fno-omit-frame-pointer -O0
debug: C_FLAGS += -g -fsanitize=address -fno-omit-frame-pointer -O0
debug: switch_mode $(FLAG_BUG)
	@./$(PROG_NAME)

# debug flags for bonus part
#debug_b: C_FLAGS += -g -fno-omit-frame-pointer -O0
debug_b: C_FLAGS += -g -fsanitize=address -fno-omit-frame-pointer -O0
debug_b: switch_mode bonus
# NOTE: can use new CLEAN flags to switch between modes!
switch_mode:
	@if [ "$(MAKECMDGOALS)" = "debug" ]; then \
		if [ ! -f $(FLAG_BUG) ]; then \
			rm -f $(OBJ_MAN) $(OBJ_BON) $(FLAG_MAN) $(FLAG_BON) $(PROG_NAME); \
			echo "Switching to DEBUG mode."; \
		else \
			echo "Already in DEBUG mode."; \
		fi \
	else \
		if [ -f $(FLAG_BUG) ]; then \
			rm -f $(OBJ_MAN) $(OBJ_BON) $(FLAG_MAN) $(FLAG_BON) $(PROG_NAME); \
			echo "Switching to REGULAR mode."; \
		else \
			echo "Already in REGULAR mode."; \
		fi \
	fi
# lists all targets that are not files and ensures executions of commands
.PHONY:	all clean fclean re bonus run print debug debug_b switch_mode val
#-------------------------------------------------------------------------------
# PART 6 -- file specific targets
#-------------------------------------------------------------------------------
# creates MANDATORY executable with DEBUG flags
$(FLAG_BUG):	all
	@touch $(FLAG_BUG)
# creates MANDATORY executable
$(PROG_NAME):	$(FLAG_MAN)
$(FLAG_MAN):	$(FLAG_CLEAN_B) $(OBJ_DIR) $(OBJ_MAN)
	$(C) $(C_FLAGS) $(OBJ_MAN) $(C_LIBS) -o $(PROG_NAME)
	@touch $(FLAG_MAN)
# creates BONUS executable
$(FLAG_BON):	$(FLAG_CLEAN_M) $(OBJ_DIR) $(OBJ_BON)
	$(C) $(C_FLAGS) $(OBJ_BON) $(C_LIBS) -o $(PROG_NAME)
	@touch $(FLAG_BON)
$(FLAG_CLEAN_M):
	@rm -f $(OBJ_MAN) $(OBJ_BON) $(PROG_NAME)
	@rm -f $(FLAG_MAN) $(FLAG_BON) $(FLAG_BUG) $(FLAG_CLEAN_B)
	@touch $(FLAG_CLEAN_M)
$(FLAG_CLEAN_B):
	@rm -f $(OBJ_MAN) $(OBJ_BON) $(PROG_NAME)
	@rm -f $(FLAG_MAN) $(FLAG_BON) $(FLAG_BUG) $(FLAG_CLEAN_M)
	@touch $(FLAG_CLEAN_B)
# each .o file depends on its .c file and the headers, $@=target, $<=depen
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADER)
	$(C) $(C_FLAGS) $(INC_DIR) -c $< -o $@
# ensure existence of build directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)