TOPTARGETS := run clean

PROJECTS := $(wildcard */.)

.PHONY: $(TOPTARGETS) $(PROJECTS)
$(TOPTARGETS): $(PROJECTS)
$(PROJECTS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: fmt
fmt:
	clang-format -i ./**/*.[ch]
