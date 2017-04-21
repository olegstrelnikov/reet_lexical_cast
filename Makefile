INCLUDE=./include
COMPILER=g++ -I"$(INCLUDE)" -Wall
SOURCE=test.cpp
EXE=reet-lexical-cast-test
HEADER=$(INCLUDE)/reet_lexical_cast.hpp

$(EXE): $(SOURCE) $(HEADER)
	$(COMPILER) -o $@ $(SOURCE)

clean:
	rm -rf $(EXE)
