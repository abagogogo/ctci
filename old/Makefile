LATEST_CPP = $(shell find . -type f -name "*.cpp" | xargs stat --format '%Y:%n' | sort -nr | awk -F: '{print $$2}' | head -n1)
LATEST_EXE = ./a.out

default: $(LATEST_EXE) run

$(LATEST_EXE): $(LATEST_CPP)
	@echo "---- Compiling $< ----"	
	g++ -std=c++0x -o $@ $<
	@echo "---- Output: $@ ----"	

run:
	@echo "---- running $(LATEST_EXE) ----"	
	$(LATEST_EXE)

edit:
	vim $(LATEST_CPP)

clean:
	rm -f *~
	rm -f a.out
