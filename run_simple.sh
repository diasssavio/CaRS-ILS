#!/bin/bash
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_BrasilRJ14e.txt >> logs/BrasilRJ14e.csv
	echo "BrasilRJ14e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_BrasilMG30e.txt >> logs/BrasilMG30e.csv
	echo "BrasilMG30e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_BrasilCO40e.txt >> logs/BrasilCO40e.csv
	echo "BrasilCO40e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_BoaVista80e.txt >> logs/BoaVista80e.csv
	echo "BoaVista80e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_Betim100e.txt >> logs/Betim100e.csv
	echo "Betim100e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_PortoVelho200e.txt >> logs/PortoVelho200e.csv
	echo "PortoVelho200e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_Belem300e.txt >> logs/Belem300e.csv
	echo "Belem300e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_rat99eB.txt >> logs/rat99eB.csv
	echo "rat99eB: $i...ok!"
done