INC = inc
SRC = src
TEST = test
LIBNAME = openfield
MAJOR_VERSION = 1
MINOR_VERSION = 0
PATCH_VERSION = 0
MKTEMP = mktemp
SED = sed -i'' -e

SO_BASE = lib$(LIBNAME).so
SO_MAJOR = $(SO_BASE).$(MAJOR_VERSION)
SO_MINOR = $(SO_MAJOR).$(MINOR_VERSION)
SO_PATCH = $(SO_MINOR).$(PATCH_VERSION)
SO_LINKS = $(SO_MAJOR) $(SO_MINOR) $(SO_BASE)
SO = $(SO_PATCH)
CPPS = $(shell find $(SRC) -name *.cpp)
DEPS = $(CPPS:.cpp=.d)
OBJS = $(CPPS:.cpp=.o)
TEST_CPPS = $(shell find $(TEST) -name *.cpp)
TEST_DEPS = $(TEST_CPPS:.cpp=.d)
TEST_OBJS = $(TEST_CPPS:.cpp=.o)
TEST_EXEC = $(LIBNAME)_test

CXXFLAGS = -I$(INC) -g -Wall -Wextra -Weffc++ -std=c++0x
LDFLAGS = -lexpat

.PHONY: all lib testexec test

all: lib testexec

lib: $(SO)

testexec: $(TEST_EXEC)

test: $(TEST_EXEC)
	LD_LIBRARY_PATH=.:$(LD_LIBRARY_PATH) ./$(TEST_EXEC)

clean:
	rm -rf $(DEPS) $(OBJS)
	rm -rf $(TEST_DEPS) $(TEST_OBJS) $(TEST_EXEC)
	rm -f  $(SO) $(SO_LINKS)

$(TEST_EXEC): $(TEST_OBJS) $(SO)
	$(CXX) -o $@ $(TEST_OBJS) -lcppunit -L . -l$(LIBNAME) $(LDFLAGS)

$(SO): $(OBJS)
	$(CXX) -shared -Wl,-soname,$(SO_MAJOR) -o $(SO) $(OBJS) $(LDFLAGS)
	@for x in $(SO_LINKS); do echo making link $$x; ln -sf $(SO) $$x; done

$(OBJS) $(TEST_OBJS): %.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(DEPS) $(TEST_DEPS): %.d: %.cpp
	$(eval TMP := $(shell $(MKTEMP)))
	@echo generating $@
	@$(CXX) $(CXXFLAGS) -MM $< > $(TMP)
	@$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' $(TMP)
	@mv $(TMP) $@

include $(DEPS) $(TEST_DEPS)
