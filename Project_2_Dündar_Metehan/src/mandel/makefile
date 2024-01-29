all: mandel_seq mandel_omp

mandel_seq: mandel_seq.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng

mandel_omp: mandel_omp.c pngwriter.c
	gcc-13 -o $@ -I. -O3 $^ -L/opt/homebrew/Cellar/libpng/1.6.40/lib -I/opt/homebrew/Cellar/libpng/1.6.40/include/libpng16 -lpng16 -fopenmp

clean:
	rm -rf mandel_seq mandel_omp
