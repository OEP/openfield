INC = inc
SRC = src
LIBNAME = openfield
MAJOR_VERSION = 1
FULL_VERSION = 1.0.0
MKTEMP = mktemp
SED = sed -i'' -e

SO = lib$(LIBNAME).so
CPPS = $(shell find $(SRC) -name *.cpp)
DEPS = $(CPPS:.cpp=.d)
OBJS = $(CPPS:.cpp=.o)

CXXFLAGS = -I$(INC) -Wall -Wextra -Weffc++

all: $(SO)

clean:
	rm -rf $(DEPS) $(OBJS)
	rm -f  $(SO) $(SO).$(FULL_VERSION)

$(SO): $(OBJS)
	$(CXX) -shared -Wl,-soname,$(SO).$(MAJOR_VERSION) -o $(SO).$(FULL_VERSION) $(OBJS)
	ln -sf $(SO).$(FULL_VERSION) $@

$(OBJS): %.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(DEPS): %.d: %.cpp
	$(eval TMP := $(shell $(MKTEMP)))
	@echo generating $@
	@$(CXX) $(CXXFLAGS) -MM $< > $(TMP)
	@$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' $(TMP)
	@mv $(TMP) $@

include $(DEPS)
