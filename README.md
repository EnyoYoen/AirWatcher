# AirWatcher Project

**INSA Lyon 3IF UML-GL**

**Authors:** Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.  

---

# 🧪 Running project
```bash
# Go to project root and run :
make && ./app_exe
```

---

# 🧪 Running Specific Tests with Google Test

This project uses **Google Test** for unit testing.  

You have to write tests in the src/tests folder then add this path in the Makefile and run the make command.

By default, **all tests** are run when you execute ./test_exe.  
However, it is possible to **filter which tests to run** using the `--gtest_filter` option.

---

## ✅ Running tests with filtering

```bash
./test_exe --gtest_filter=TestDataLoader.loadSensorsOK
```
You can use the wildcard character `*` to run multiple tests from the same TestCase, e.g. all tests from TestDataLoader:
```bash
./test_exe --gtest_filter=TestDataLoader.*
```