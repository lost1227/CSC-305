CXX = g++
CPPFLAGS = -Wall -Werror -pedantic -g -std=c++11

CPPFLAGS += -DLITTLE_ENDIAN
CPPFLAGS += -Wno-error=char-subscripts -Wno-error=parentheses
CPPFLAGS += -fsanitize=undefined -fsanitize=address

SRCS = $(shell find . -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)
MAIN = BoardTest

DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

%.o : %.c $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

all: $(MAIN)

$(MAIN) : $(OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) -o $(MAIN)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))

clean:
	rm -f $(OBJS) $(MAIN) $(DEPFILES)