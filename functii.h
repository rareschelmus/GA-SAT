#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<ctime>

using namespace std;

#define lungime_clauza 16
#define lungime_cromozom 450
#define clauze_max 2000
#define max_pop 200




void parse_and_build_matrix(short propozitie[][lungime_clauza], int & nr_var, int & nr_clauze);

int fitness(short propozitie[][lungime_clauza] ,short cromozom[], short nr_var, int nr_clauze);

void genereaza_cromozom(short v[], short nr_var);

void mutatie(short p[], double Pm, short nr_var);

void incrucisare(short p1[], short p2[], short c1[], short c2[], short nr_var, short taieri);

double AG(double Pm, double Pc, int nr_generatii, int pop_size, short taieri, short nr_var,int nr_clauze, short propozitie[][lungime_clauza]);

void genereaza_populatie(short pop[][lungime_cromozom], int pop_size, short nr_var);

void sort(int v[], short n);

int rmhc(short nr_var, int nr_clauze, short propozitie[][lungime_clauza]);

void selectie(short pop[][lungime_cromozom], short pop_size, short & actual_pop_size, short nr_var, int nr_clauze, short propozitie[][lungime_clauza], double Pm, double Pc);
