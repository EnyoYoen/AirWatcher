CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Igoogletest/googletest/include -Igoogletest/googletest -g
LDFLAGS = -pthread

# Dependencies for the main app executable
APP_SRC = src/model/Cleaner.cpp src/model/Admin.cpp src/model/Attribute.cpp src/model/Cleaner.cpp src/model/Measurement.cpp src/model/PrivateUser.cpp src/model/Provider.cpp src/model/Sensor.cpp src/model/User.cpp src/services/AirWatcher.cpp src/utils/DataLoader.cpp src/utils/DateTime.cpp src/utils/GPS.cpp src/ui/Menu.cpp
APP_MAIN = src/main.cpp
APP_OBJ = $(APP_SRC:.cpp=.o) $(APP_MAIN:.cpp=.o)

# Dependencies for the test exe
TESTS = src/tests/test_provider.cpp src/tests/test_cleaner.cpp src/tests/test_user.cpp  src/tests/test_privateUser.cpp src/tests/test_dataLoader.cpp src/tests/test_sensor.cpp src/tests/test_airWatcher.cpp
TEST_SRC = $(TESTS) $(APP_SRC) googletest/googletest/src/gtest-all.cc
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_OBJ := $(TEST_OBJ:.cc=.o)

# Executables
APP_EXEC = app_exe
TEST_EXEC = test_exe

all: $(APP_EXEC) $(TEST_EXEC)

$(APP_EXEC): $(APP_OBJ)
	$(CXX) -o $@ $^

$(TEST_EXEC): $(TEST_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /q log.txt
	del /q *.exe
	del /s /q src\*.o
else
	rm -f $(APP_OBJ) $(TEST_OBJ) $(APP_EXEC) $(TEST_EXEC) log.txt;
endif
