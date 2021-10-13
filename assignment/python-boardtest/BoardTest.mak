CXX = g++
CPPFLAGS = -Wall -Werror -pedantic -g -std=c++2a -fPIC

CPPFLAGS += -DLITTLE_ENDIAN
CPPFLAGS += -Wno-error=char-subscripts -Wno-error=parentheses -Wno-error=delete-incomplete
# CPPFLAGS += -fsanitize=undefined -fsanitize=address

LINKFLAGS = -static-libstdc++

SRCS = $(shell find . -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)
MAIN = boardtest.so

DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

%.o : %.c $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

all: $(MAIN)

$(MAIN) : $(OBJS)
	$(CXX) $(LINKFLAGS) $(CPPFLAGS) $(OBJS) -shared -o $(MAIN)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))

clean:
	rm -f $(OBJS) $(MAIN) $(DEPFILES)