CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_opt

GIT_HOOKS := .git/hooks/applied
.DEFAULT_GOAL := fgets
.PHONY: all
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo
SRCS_fgets = main_fgets.c
SRCS_mmap = main_mmap.c

fgets: orig_fgets opt_fgets
mmap: orig_mmap opt_mmap

orig_fgets: $(SRCS_fgets) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"phonebook_orig.h\"" -o phonebook_orig \
		$(SRCS_fgets) phonebook_orig.c

opt_fgets: $(SRCS_fgets) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"phonebook_opt.h\"" -o phonebook_opt \
		$(SRCS_fgets) phonebook_opt.c

orig_mmap: $(SRCS_mmap) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"phonebook_orig.h\"" -o phonebook_orig \
		$(SRCS_mmap) phonebook_orig.c

opt_mmap: $(SRCS_mmap) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"phonebook_opt.h\"" -o phonebook_opt \
		$(SRCS_mmap) phonebook_opt.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	rm -rf *.txt
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt

output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png
