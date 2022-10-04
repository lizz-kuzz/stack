FLAGS = -g -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations    \
		-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion \
		-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers       \
		-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel   \
		-Wtype-limits -Wwrite-strings -D_DEBUG
СС = g++
release:
	$(CC) $(FLAGS) main.cpp stack.cpp debug.cpp -DRELEASE -o do.exe 
canary:
	$(CC) $(FLAGS) main.cpp stack.cpp debug.cpp -DCANARY_ON -o do.exe 
hash:
	$(CC) $(FLAGS) main.cpp stack.cpp debug.cpp -DHASH_ON -o do.exe 
debug:
	$(CC) $(FLAGS) main.cpp stack.cpp debug.cpp -DDEBUG -o do.exe 

