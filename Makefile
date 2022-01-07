all : std ft

std :
	clang++ -D TEST_NAME=std main_vector.cpp -o std
ft :
	clang++ -D TEST_NAME=ft main_vector.cpp -o ft

clean :
	rm -f a.out ft std