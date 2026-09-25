CXX      = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

MODULES  = Framebuffer.cpp
APP_SRC  = main.cpp $(MODULES)
TEST_SRC = $(wildcard tests/*.cpp) $(MODULES)

OUT      = softrasterizer
TEST_OUT = tests/run

$(OUT): $(APP_SRC) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(APP_SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)

view: run
	open framebuffer.tga zbuffer.tga

test: $(TEST_SRC) $(wildcard *.h) $(wildcard tests/*.h)
	$(CXX) $(CXXFLAGS) -I. $(TEST_SRC) -o $(TEST_OUT)
	./$(TEST_OUT)

# Address sanitiser build; reports the file and line on a crash.
debug: $(APP_SRC) $(wildcard *.h)
	$(CXX) -std=c++17 -Wall -Wextra -g -fsanitize=address $(APP_SRC) -o $(OUT)_debug
	./$(OUT)_debug

clean:
	rm -rf $(OUT) $(OUT)_debug $(TEST_OUT) *.tga *.dSYM tests/*.dSYM

.PHONY: run view test debug clean
