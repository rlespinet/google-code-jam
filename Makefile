SUBDIRS := $(wildcard */*/*)

.PHONY : all
all : $(SUBDIRS)
	$(foreach DIR, $(SUBDIRS), $(MAKE) -C $(DIR) $@;)

.PHONY : run
run : $(SUBDIRS)
	$(foreach DIR, $(SUBDIRS), $(MAKE) -C $(DIR) $@;)
