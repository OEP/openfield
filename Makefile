INC = inc
SRC = src
TEST = test
LIBNAME = openfield
MAJOR_VERSION = 1
FULL_VERSION = 1.0.0
MKTEMP = mktemp
SED = sed -i'' -e

SO = lib$(LIBNAME).so
CPPS = $(shell find $(SRC) -name *.cpp)
DEPS = $(CPPS:.cpp=.d)
OBJS = $(CPPS:.cpp=.o)
TEST_CPPS = $(shell find $(TEST) -name *.cpp)
TEST_DEPS = $(TEST_CPPS:.cpp=.d)
TEST_OBJS = $(TEST_CPPS:.cpp=.o)
TEST_EXEC = $(LIBNAME)_test

CXXFLAGS = -I$(INC) -Wall -Wextra -Weffc++ -std=c++11

all: lib unittest

lib: $(SO)

unittest: $(TEST_EXEC)

print:
	@echo $(TEST_OBJS)

clean:
	rm -rf $(DEPS) $(OBJS)
	rm -f  $(SO) $(SO).$(FULL_VERSION)

$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) -o $@ $(TEST_OBJS) -lcppunit

$(SO): $(OBJS)
	$(CXX) -shared -Wl,-soname,$(SO).$(MAJOR_VERSION) -o $(SO).$(FULL_VERSION) $(OBJS)
	ln -sf $(SO).$(FULL_VERSION) $@

$(OBJS) $(TEST_OBJS): %.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(DEPS) $(TEST_DEPS): %.d: %.cpp
	$(eval TMP := $(shell $(MKTEMP)))
	@echo generating $@
	@$(CXX) $(CXXFLAGS) -MM $< > $(TMP)
	@$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' $(TMP)
	@mv $(TMP) $@

include $(DEPS) $(TEST_DEPS)
