INC = inc
SRC = src
LIB = libopenfield.so
MAJOR_VERSION = 1
FULL_VERSION = 1.0.0
MKTEMP = mktemp
SED = sed -i'' -e

CPPS = $(shell find $(SRC) -name *.cpp)
DEPS = $(CPPS:.cpp=.d)
OBJS = $(CPPS:.cpp=.o)

CXXFLAGS = -I$(INC) -Wall -Wextra -Weffc++

all: $(LIB)

clean:
	rm -rf $(DEPS) $(OBJS)

$(LIB): $(OBJS)
	$(CXX) -shared -Wl,-soname,$(LIB).$(MAJOR_VERSION) -o $(LIB).$(FULL_VERSION) $(OBJS)
	ln -s $(LIB).$(FULL_VERSION) $@

$(OBJS): %.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(DEPS): %.d: %.cpp
	$(eval TMP := $(shell $(MKTEMP)))
	@echo generating $@
	@$(CXX) $(CXXFLAGS) -MM $< > $(TMP)
	@$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' $(TMP)
	@mv $(TMP) $@
	@rm -f $(TMP)
