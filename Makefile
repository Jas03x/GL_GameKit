SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)

FLAGS = -std=c++11
INCLUDES = -I../GL_Context/src/

all: $(OBJS)
	mv *.o ./bin

%.o: %.cpp
	g++ -c $< $(INCLUDES) $(FLAGS)

clean:
	cd bin && rm *.o