CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -MMD -MP -g -std=c++17

INCLUDES = -I includes -I includes/server

NAME = expert-system

SRCS =	src/main.cpp \
		src/Rule.cpp \
		src/ConditionType.cpp \
		src/FactState.cpp \
		src/ConditionNode.cpp

OBJDIR = obj
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.cpp=$(OBJDIR)/%.d)

all:
	@make -j compile --no-print-directory

compile: $(NAME)

re: fclean all

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo Cleaning objects
	@rm -rf $(OBJDIR)

fclean: clean
	@echo Cleaning $(NAME)
	@rm -rf $(NAME)

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean run re

-include $(DEPS)
