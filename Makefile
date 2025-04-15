TOPTARGETS := run clean

PROJECTS := $(wildcard */.)

.PHONY: $(TOPTARGETS) $(PROJECTS)
$(TOPTARGETS): $(PROJECTS)
$(PROJECTS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: format
format:
	clang-format -i -- ./**/*.c ./**/*.h
