# available projects
PROJS := webserver

# target variables
BUILD := $(PROJS:%=%_build)
TESTS := $(PROJS:%=%_test)
CLEAN := $(PROJS:%=%_clean)
INSTALL := $(PROJ:%=%_install)

# targets
all: $(PROJS)

install: all $(INSTALL)

test: $(TESTS)

run: install
	bin/*

doc:
	doxygen default

clean: $(CLEAN)

distclean: clean
	rm -rf bin doc lib

# subtargets
$(PROJS): %: %_build %_test

$(BUILD): %_build: src/%
	$(MAKE) -C $<

$(CLEAN): %_clean: src/%
	$(MAKE) -C $< clean

$(TESTS): %_test: tests/%
	$(MAKE) -C $<


.PHONY: all install test run doc clean distclean $(PROJS) $(SRCS) $(TESTS)

