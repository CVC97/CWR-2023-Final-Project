# files to be compiled (without suffix)
BINARY := spread_of_infection
HEADER1 := cvc_numerics
HEADER2 := cvc_rng


# flags
FLAGS := -lm -lgsl -lgslcblas -Wall -std=c99


# compile
$(BINARY): $(BINARY).o $(HEADER1).o $(HEADER2).o
	gcc $(BINARY).o $(HEADER1).o $(HEADER2).o -o $(BINARY) $(FLAGS)

$(BINARY).o: $(BINARY).c
	gcc -c $(BINARY).c

$(HEADER1).o: $(HEADER1).c
	gcc -c $(HEADER1).c

$(HEADER2).o: $(HEADER2).c
	gcc -c $(HEADER2).c


# run
run: $(BINARY)
	./$< $(ARGS)


# plot and animate
plot: 
	cd soi_data && python3 soi_plotting.py 

animate:
	cd soi_animations && manim -pqh --fps 60 soi_animations.py soi_main_scene

# compile and move PDF to main folder without (make pdf) or with (make bib) renewing bibliography
pdf:
	cd soi_pdf && xelatex main.tex && mv main.pdf ../$(BINARY).pdf

bib:
	cd soi_pdf && xelatex main.tex && biber main && xelatex main.tex && xelatex main.tex && mv main.pdf ../$(BINARY).pdf	


# clean
clean:
	rm -f *.o
	rm -f $(HEADER1).o
	rm -f $(HEADER2).o
	rm -f *.exe
	rm -f $(BINARY)
	rm -f *.dat *.csv *.txt
	rm -f ../*.o