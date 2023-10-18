EXE = bank
INPUT = inputFiles/clientes.txt inputFiles/transacoes.txt 

.PHONY: run clean

all:
	cd build && cmake .. && make && cd ..

run:
	./$(EXE) $(INPUT)

clean:
	rm -rf $(EXE) build/*