all:
	g++ dial.cpp -o dial -lglut -lGLU -lGL -lm

clean:
	rm -f dial
