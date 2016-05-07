shared_libraries:
	gcc -c -fPIC c1.c -o c1.o
	gcc -shared -o libc1.so c1.o
	gcc -c -fPIC c0.c -o c0.o
	gcc -shared -o libc0.so c0.o

static_library:
	gcc -c WeatherQueue.c -o WeatherQueue.o
	ar rcs libWeatherQueue.a WeatherQueue.o
app: main.c static_library shared_libraries
	gcc main.c -lWeatherQueue -L. -ldl

all: app
