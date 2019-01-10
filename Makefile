PKGCONFIG_NESS := sdl2pp sdl2
CXXFLAGS := -std=c++17 $(shell pkg-config --cflags $(PKGCONFIG_NESS))
LDFLAGS := $(shell pkg-config --libs $(PKGCONFIG_NESS))
# You might need to change this to g++ or clang++ if you don't have a symlink
CXX := c++

SRCS := main.cpp sdl_renderer.cpp
OBJS := $(SRCS:%.cpp=%.o)

colpeachstein3d: $(OBJS) Makefile
	$(CXX) -o colpeachstein3d $(LDFLAGS) $(OBJS)

%.d: %.cpp
	@set -e; rm -f $@; \
	  $(CXX) -M $(CXXFLAGS) $< > $@.$$$$; \
	  sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	  rm -f $@.$$$$

include $(SRCS:%.cpp=%.d)

run: colpeachstein3d
	./colpeachstein3d

clean:
	rm -f colpeachstein3d *.o *.d

%.o: %.cpp Makefile
	$(CXX) -c $(CXXFLAGS) -o $@ $<


