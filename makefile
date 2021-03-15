.SUFFIXES:
.PHONY: all clean

CXX := g++
CXXFLAGS := -Wall -g
INCLUDES := -Iinclude
LIBS := -lm
TARGET := demo.exe

SRCDIR := src
UIDIR := ui
SRCOBJS := $(patsubst %.cpp, %.o, $(wildcard $(SRCDIR)/*.cpp))
TESTOBJS := $(patsubst %.cpp, %.o, $(wildcard $(UIDIR)/*.cpp))
OBJS := $(SRCOBJS) $(TESTOBJS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) $^ -o $@

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

clean:
	-@rm -f $(TARGET)
	-@rm -f $(OBJS)