SUBDIRS = pdev adap

GIT_HOOKS := .git/hooks/applied
$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

.PHONY: all clean $(SUBDIRS)
all: $(GIT_HOOKS) subdirs

subdirs: $(SUBDIRS)
	for dir in $(SUBDIRS); do \
          $(MAKE) -C $$dir; \
        done

clean: $(SUBDIRS)
	for dir in $(SUBDIRS); do \
          $(MAKE) -C $$dir clean; \
        done
