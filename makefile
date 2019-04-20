game:game.cpp
	g++ $^ -o $@ -lpthread

.PHONY:clean
clean:
	rm game
