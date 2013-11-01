INC = inc
SRC = src
LIB = libopenfield.so
VERSION = 1.0
MKTEMP = mktemp
SED = sed -i'' -e

CPPS = $(shell find $(SRC) -name *.cpp)
DEPS = $(CPPS:.cpp=.d)
OBJS = $(CPPS:.cpp=.o)

CXXFLAGS = -I$(INC) -Wall -Wextra -Weffc++

all: $(OBJS)

clean:
	rm -rf $(DEPS) $(OBJS)

$(OBJS): %.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) $< -o $@

$(DEPS): %.d: %.cpp
	$(eval TMP := $(shell $(MKTEMP)))
	@echo generating $@
	@$(CXX) $(CXXFLAGS) -MM $< > $(TMP)
	@$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' $(TMP)
	@mv $(TMP) $@
	@rm -f $(TMP)
