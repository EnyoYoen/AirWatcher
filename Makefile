CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Igoogletest/googletest/include -Igoogletest/googletest
LDFLAGS = -pthread

APP_SRC = src/model/Provider.cpp src/model/Cleaner.cpp src/model/User.cpp src/model/PrivateUser.cpp
APP_OBJ = $(APP_SRC:.cpp=.o)

# Tous les fichiers à compiler
TESTS = src/tests/test_provider.cpp src/tests/test_cleaner.cpp src/tests/test_user.cpp  src/tests/test_privateUser.cpp
TEST_SRC = $(TESTS) $(APP_SRC) googletest/googletest/src/gtest-all.cc
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_OBJ := $(TEST_OBJ:.cc=.o)

# Exécutables
APP_EXEC = app_exe
TEST_EXEC = test_exe

# To add : $(APP_EXEC) lorsqu'on aura un main fonctionnel
all: $(TEST_EXEC)

$(APP_EXEC): $(APP_OBJ)
	$(CXX) -o $@ $^

$(TEST_EXEC): $(TEST_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(APP_OBJ) $(TEST_OBJ) $(APP_EXEC) $(TEST_EXEC)
