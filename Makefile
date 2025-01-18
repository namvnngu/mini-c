TOPTARGETS := dev release clean

PROJECTS := $(wildcard */.)

.PHONY: $(TOPTARGETS) $(PROJECTS)

$(TOPTARGETS): $(PROJECTS)
$(PROJECTS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
