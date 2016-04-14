#!/bin/bash
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_BrasilRJ14e.txt > logs/BrasilRJ14e_$i.txt
	echo "BrasilRJ14e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_BrasilMG30e.txt > logs/BrasilMG30e_$i.txt
	echo "BrasilMG30e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_BrasilCO40e.txt > logs/BrasilCO40e_$i.txt
	echo "BrasilCO40e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_BoaVista80e.txt > logs/BoaVista80e_$i.txt
	echo "BoaVista80e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_Betim100e.txt > logs/Betim100e_$i.txt
	echo "Betim100e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_PortoVelho200e.txt > logs/PortoVelho200e_$i.txt
	echo "PortoVelho200e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_Belem300e.txt > logs/Belem300e_$i.txt
	echo "Belem300e: $i...ok!"
done
for i in $(seq 10)
do
	./CaRS-ILS $i < instances/insts/dados_rat99eB.txt > logs/rat99eB_$i.txt
	echo "rat99eB: $i...ok!"
done