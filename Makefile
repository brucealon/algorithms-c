
.DEFAULT_GOAL := help
.PHONY: help sort valgrind
.SUFFIXES: .c .o

INTDIR   ?= data
INTFILES ?= smallW.txt
INTFILEM ?= mediumW.txt
INTFILET ?= tinyW.txt

clean:  ## Clean up object files, binaries, and Valgrind cores
	rm -f `find . -maxdepth 1 -executable -type f`  vgcore.* *.o

count_change: count_change.c  ## Compile the count_change binary
	gcc -g -o count_change count_change.c

count_change_run: count_change ## Run the already compiled count_change binary
	@echo
	@./count_change
	@echo

count_change_valgrind: count_change  ## Test count_change with valgrind
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./count_change stack 100
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./count_change array 100
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./count_change recursion 100
	@echo --------------------------------------------------------

help:  ## Default target that shows this help information
	@echo
	@grep -E '^[a-zA-Z0-9_-]+:.*?##' $(MAKEFILE_LIST) \
	| sed -n 's/^\(.*\): .*##\(.*\)/\1:\2/p' \
	| column -t  -s ':'
	@echo

.c.o:
	gcc -g -c -o $@ $<

priority_queue_test: priority_queue.o priority_queue_test.c
	gcc -g -o priority_queue_test priority_queue.o priority_queue_test.c

priority_queue_test_run: priority_queue_test  ## Run the already compiled priority_queue_test binary
	@echo
	./priority_queue_test
	@echo

priority_queue_test_valgrind: priority_queue_test  ## Test the priority_queue library with valgrind
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./priority_queue_test
	@echo --------------------------------------------------------

queue_test: queue_test.c queue.o input.o output.o  ## Test the queue functions
	gcc -g -o queue_test queue_test.c queue.o input.o output.o

queue_test_run: queue_test ## Run already compiled queue_test binary
	./queue_test

queue_test_valgrind: queue_test  ## Test the queue library with valgrind
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./queue_test
	@echo --------------------------------------------------------

sorting: sorting.c sorting_basic.o input.o output.o ## Compile and run sorting
	gcc -g -o sorting sorting.c sorting_basic.o input.o output.o

sorting_run: sorting ## Run already compiled sorting binary
	@echo
	./sorting $(INTDIR)/$(INTFILET)
	@echo

sorting_valgrind: sorting  ## Test the sorting_test binary with valgrind
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./sorting $(INTDIR)/$(INTFILET)
	@echo --------------------------------------------------------

sorting_test: sorting_test.c sorting_basic.o input.o output.o ## Test the sorting functions
	gcc -g -o sorting_test sorting_test.c sorting_basic.o input.o output.o

sorting_test_run: sorting_test ## Run already compiled sorting_test binary
	@echo
	@./sorting_test
	@echo

sorting_test_valgrind: sorting_test  ## Test the sorting_test binary with valgrind
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./sorting_test
	@echo --------------------------------------------------------

stack_test: stack.o stack_test.c ## Test the stack library
	gcc -g -o stack_test stack.o stack_test.c

stack_test_run: stack_test ## Run the already compiled stack_test binary
	@echo
	./stack_test
	@echo

stack_test_valgrind: stack_test  ## Test the stack library with valgrind
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./stack_test
	@echo --------------------------------------------------------

two_stack_evaluator_run: two_stack_evaluator
	@echo
	./two_stack_evaluator
	@echo

two_stack_evaluator_valgrind: two_stack_evaluator  ## Test two_stack_evaluator with Valgrind
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./two_stack_evaluator
	@echo --------------------------------------------------------

valgrind:  ## Run all valgrind targets
	@for target in $$(make help | grep _valgrind | cut -d ' ' -f1) ; do echo Running $$target ; make $$target ; if [ $$? -gt 0 ] ; then exit 1 ; fi done

search_linked_list: search_linked_list.o input.o  ## Test word counting (searching) with a linked list
	gcc -g -o search_linked_list search_linked_list.o input.o

search_linked_list_valgrind: search_linked_list ## Test search_linked_list with Valgrind
	@echo --------------------------------------------------------
	@valgrind --track-origins=yes --leak-check=full -s ./search_linked_list data/tinyTale.txt
	@echo --------------------------------------------------------

search: search.o input.o
	gcc -g -o search search.o input.o
	./search
