# Compiler
CC = g++
# Compiler flags
CFLAGS = -std=c++11 -Wall
# Include directories
INCLUDEDIRS = -I"C:/msys64/mingw64/include"
# Library directories
LIBDIRS = -L"C:/msys64/mingw64/lib"
# Libraries to link
LIBS = -lssl -lcrypto
# Source files
SRCS = test.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)
# Executable name
EXEC = test

# NOTE: If your code changes (e.g., in test.cpp) do not seem to apply after running 'mingw32-make run',
# it might be because 'make' doesn't see the source file as newer than the compiled object file.
# To force a complete rebuild:
# 1. Save your source file (e.g., test.cpp).
# 2. Run 'mingw32-make clean' in your terminal.
# 3. Run 'mingw32-make run' (or 'mingw32-make' then '.\test.exe').
# This ensures all old compiled files are removed and everything is rebuilt from the latest sources.

# mingw32-make run
# Default target
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $(LIBDIRS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDEDIRS) -c $< -o $@

clean:
	del $(OBJS) $(EXEC).exe 2>nul || rem
# Sử dụng 'del' cho Windows và '2>nul || rem' để bỏ qua lỗi nếu không có tệp nào để xóa.
# Hoặc nếu bạn dùng MSYS2/Git Bash, bạn có thể dùng 'rm -f'
# rm -f $(OBJS) $(EXEC)

run: all
	.\$(EXEC).exe

.PHONY: all clean run