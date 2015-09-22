# Detecting OS
UNAME_S=$(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CC=g++-4.8
    GTEST_LL=-I /usr/local/opt/gtest/include/ -lgtest_main -lpthread
else
    ifeq ($(UNAME_S),Darwin)
        CC=g++
        GTEST_LL=-I /usr/local/opt/gtest/include/ -L /usr/local/opt/gtest/lib/ -lgtest_main -lgtest -lpthread
    else
        CC=g++
        GTEST_LL=-I /usr/local/opt/gtest/include/ -L /usr/local/lib/ -lgtest_main -lgtest -lpthread
    endif
endif

CPPFLAGS=-std=c++11 -Wall -g -I$(LIB_DIR)/
LIB_DIR=lib
BIN_DIR=bin
TEST_DIR=tests

# Test Cases
_TEST_CASES=$(patsubst $(TEST_DIR)/%,$(BIN_DIR)/%,$(wildcard $(TEST_DIR)/*.cpp))
TEST_CASES=$(patsubst %.cpp,%.test.o,$(_TEST_CASES))

GTEST_CPPFLAGS = -Wall -g -I$(LIB_DIR) -Wextra -pthread -std=gnu++0x

.PHONY: clean
.PHONY: tests

all:  $(BIN_DIR)/movie.o $(BIN_DIR)/user.o $(BIN_DIR)/moviesite 

$(BIN_DIR)/moviesite: $(BIN_DIR)/.dirstamp moviesite.cpp $(LIB_DIR)/map.h $(LIB_DIR)/set.h $(LIB_DIR)/mergesort.h
	$(CC) moviesite.cpp $(BIN_DIR)/movie.o $(BIN_DIR)/user.o -o $@ $(CPPFLAGS) 

$(BIN_DIR)/movie.o: $(BIN_DIR)/.dirstamp movie.cpp
	$(CC) -c movie.cpp -o $@ $(CPPFLAGS)

$(BIN_DIR)/user.o: $(BIN_DIR)/.dirstamp user.cpp
	$(CC) -c user.cpp -o $@ $(CPPFLAGS)

#Test compile
$(BIN_DIR)/%.test.o: $(TEST_DIR)/%.cpp $(LIB_DIR)/* $(BIN_DIR)/.dirstamp
	$(CC) $(GTEST_CPPFLAGS) $(GTEST_LL) -c $< -o $@

$(BIN_DIR)/SiteTest: $(TEST_CASES)
	$(CC) $(GTEST_CPPFLAGS) $^ $(GTEST_LL) -o $@ 

$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR) && touch $@


tests:$(BIN_DIR)/SiteTest
	-@$(BIN_DIR)/SiteTest
	-@echo "--- All Tested!---"

clean:
	-@rm -Rf $(BIN_DIR)