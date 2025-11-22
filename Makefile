TOPTARGETS := run clean

PROJECTS := $(wildcard */.)

.PHONY: $(TOPTARGETS)
$(TOPTARGETS): $(PROJECTS)

.PHONY: $(PROJECTS)
$(PROJECTS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: fmt
fmt:
	clang-format -i ./**/*.[ch]
