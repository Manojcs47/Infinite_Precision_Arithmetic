CC=g++
CFLAGS=-c -I include
lib_dependencys=build/Integer.o build/Float.o
prog_dependencys=build/my_inf_arith.o

all : my_inf_arith

my_inf_arith : $(prog_dependencys) $(lib_dependencys)
	$(CC) $(prog_dependencys) $(lib_dependencys) -o my_inf_arith

$(lib_dependencys) : src/Integer.cpp src/Float.cpp
	@mkdir -p build
	$(CC) $(CFLAGS) src/Integer.cpp -o build/Integer.o
	$(CC) $(CFLAGS) src/Float.cpp -o build/Float.o

$(prog_dependencys) : my_inf_arith.cpp
	@mkdir -p build
	$(CC) $(CFLAGS) my_inf_arith.cpp -o build/my_inf_arith.o

libmy_inf_arith : $(lib_dependencys)
	ar rcs libmy_inf_arith.a build/*.o

clean:
	rm -rf build
	rm -f my_inf_arith libmy_inf_arith.a