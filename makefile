# Datei, die kompiliert werden soll (ohne Endung)
BINARY := spread_of_infection
HEADER1 := cvc_numerics
HEADER2 := cvc_rng


# Flags
FLAGS := -lm -lgsl -lgslcblas -Wall -std=c99


# Kompilieren
$(BINARY): $(BINARY).o ../$(HEADER1).o ../$(HEADER2).o
	gcc $(BINARY).o ../$(HEADER1).o ../$(HEADER2).o -o $(BINARY) $(FLAGS)

$(BINARY).o: $(BINARY).c
	gcc -c $(BINARY).c

$(HEADER1).o: ../$(HEADER1).c
	gcc -c ../$(HEADER1).c

$(HEADER2).o: ../$(HEADER2).c
	gcc -c ../$(HEADER2).c



# Ausführen
run: $(BINARY)
	./$< $(ARGS)


# PDF erstellen
pdf:
	cd soi_pdf && lualatex main.tex && mv main.pdf ../$(BINARY).pdf
	

# Clean
clean:
	rm -f *.o
	rm -f $(HEADER1).o
	rm -f $(HEADER2).o
	rm -f *.exe
	rm -f $(BINARY)
	rm -f *.dat *.csv *.txt
	rm -f ../*.o