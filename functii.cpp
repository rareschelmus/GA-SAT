#include"functii.h"

void parse_and_build_matrix(short propozitie[][lungime_clauza], int & nr_var,int & nr_clauze)
{
	int var_in, i,k;

	ifstream fin("sat1.txt");

	
	fin >> nr_var >> nr_clauze;

	for (i = 0; i < nr_clauze; i++)
	{
		k = 0;
		do
		{
			fin >> var_in;
			
			propozitie[i][k++]=var_in;
		} while (var_in!=0);
	}

	fin.close();
}

int fitness(short propozitie[][lungime_clauza], short cromozom[], short nr_var, int nr_clauze)
{
	int sum = 0, k = 0, i, vari,clauza;

	for (i = 0; i < nr_clauze; i++)
	{
		k = 0;
		clauza = 0;
		while (propozitie[i][k] != 0)
		{
			vari = propozitie[i][k];

			if (vari < 0)
			{
				vari = (-1)*vari;
				if (cromozom[vari-1] == 0)
					clauza++;
			}
			else
			{
				//cout << cromozom[vari - 1] << " ";
				if (cromozom[vari - 1] == 1)
					clauza++;
			}
			k++;
		}
		if (clauza == k)
			sum++;
	}
	//cout << "\n";
	return sum;
}

void genereaza_cromozom(short v[], short nr_var)
{
	int i;
	for (i = 0; i < nr_var; i++)
		v[i] = rand() % 2;
}

void mutatie(short p[], double Pm, short nr_var)
{
	int i;
	for (i = 0; i < nr_var; i++)
		if (((double)(rand() % 99 + 1) / 100) <= Pm)
			if (p[i] == 0)
				p[i] = 1;
			else
				p[i] = 0;
}

void incrucisare(short p1[], short p2[], short c1[], short c2[], short nr_var, short taieri)
{
	int punct_taiere[10];
	long i, j, aux;
	memcpy(c1, p1, sizeof(short)*nr_var);
	memcpy(c2, p2, sizeof(short)*nr_var);

	for (i = 1; i <= taieri; i++)
		punct_taiere[i] = rand() % (nr_var);
	punct_taiere[0] = 0;
	sort(punct_taiere, taieri);
	for (i = 1; i <= taieri; i += 2)
		for (j = punct_taiere[i - 1]; j < punct_taiere[i]; j++)
			if (p1[j] != p2[j])
			{
				aux = c1[j];
				c1[j] = c2[j];
				c2[j] = aux;
			}
}

void genereaza_populatie(short pop[][lungime_cromozom], int pop_size, short nr_var)
{
	int i;
	for (i = 0; i < pop_size; i++)
		genereaza_cromozom(pop[i], nr_var);
}


void sort(int v[], short n)
{
	int ok, i, aux;
	do
	{
		ok = 0;
		for (i = 1; i < n; i++)
			if (v[i - 1]>v[i])
			{
				aux = v[i - 1];
				v[i - 1] = v[i];
				v[i] = aux;
				ok = 1;
			}
	} while (ok);
}


void selectie(short pop[][lungime_cromozom], short pop_size, short & actual_pop_size, short nr_var, int nr_clauze, short propozitie[][lungime_clauza], double Pm, double Pc)
{
	int i, j, new_pop_size,k=0;
	double  T = 0, p[lungime_cromozom], q[lungime_cromozom+1], max = -99999, r;
	short eval[lungime_cromozom], new_pop[max_pop][lungime_cromozom];
	
	for (i = 0; i < actual_pop_size; i++)
	{
		eval[i] = fitness(propozitie,pop[i],nr_var,nr_clauze);
		if (eval[i] > max)
			max = eval[i];
		T += eval[i];
	}
	for (i = 0; i < actual_pop_size; i++)
		p[i] = eval[i] / T;
	q[0] = 0;
	for (i = 0; i < actual_pop_size; i++)
		q[i + 1] = p[i] + q[i];

	for (i = 0; i <= actual_pop_size&&k<pop_size/10;i++)
		if (eval[i] == max)
			memcpy(new_pop[k++], pop[i], sizeof(short)*nr_var);

	for (i = k; i < pop_size; i++)
	{
		r = (double)(rand() % 999 + 1) / 1000;
		for (j = 0; j < actual_pop_size; j++)
			if (r >= q[j] && r < q[j + 1])
			{
				memcpy(new_pop[i], pop[j], sizeof(short)*nr_var);
				break;
			}
	}
	actual_pop_size = pop_size;
	for (i = 0; i < pop_size; i++)
		memcpy(pop[i], new_pop[i], sizeof(short)*nr_var);
}

double AG(double Pm, double Pc, int nr_generatii, int pop_size, short taieri, short nr_var, int nr_clauze, short propozitie[][lungime_clauza])
{
	short pop[max_pop][lungime_cromozom], actual_pop_size;
	int locci, i, new_n = 0, a, b, j, an, bn,fit;
	double r;
	long max;

	genereaza_populatie(pop, pop_size, nr_var);
	
	max = 999999999;

	actual_pop_size = pop_size;
	for (i = 0; i < nr_generatii; i++)
	{
		for (j = 0; j < pop_size; j++)
		{

			r = (double)(rand() % 99 + 1) / 100;
			if (r <= Pc)
			{
				a = rand() % actual_pop_size;
				b = rand() % actual_pop_size;

				incrucisare(pop[a], pop[b], pop[actual_pop_size], pop[actual_pop_size+1], nr_var, taieri);
				actual_pop_size += 2;
			}


			a = rand() % actual_pop_size;
			mutatie(pop[a], Pm, nr_var);
		}
		selectie(pop, pop_size, actual_pop_size, nr_var, nr_clauze, propozitie, Pm, Pc);
		max = -1;
		for (j = 0; j < actual_pop_size; j++)
		{
			fit = fitness(propozitie,pop[j],nr_var,nr_clauze);
			//cout << fit << " ";
			if (fit > max)
				max = fit;
		}
		//cout << "Generatia " << i << " cu min " << max << "\n";
	}
	//cout << min << "\n";
	return max;
}

int rmhc(short nr_var, int nr_clauze, short propozitie[][lungime_clauza])
{
	short max_hilltop[3000], hilltop[3000];
	int i, loccus, max_rep;
	double max_fitness, fitness_val;

	genereaza_cromozom(max_hilltop, nr_var);

	max_fitness = fitness(propozitie,max_hilltop, nr_var, nr_clauze);

	max_rep = nr_var * 3;

	for (i = 0; i < max_rep; i++)
	{
		memcpy(hilltop, max_hilltop, (sizeof(short))*nr_var);

		loccus = rand() % (nr_var);

		if (hilltop[loccus])
			hilltop[loccus] = 0;
		else
			hilltop[loccus] = 1;

		fitness_val = fitness(propozitie, hilltop, nr_var, nr_clauze);


		if (fitness_val >= max_fitness)
		{
			memcpy(max_hilltop, hilltop, (sizeof(short))*nr_var);
			max_fitness = fitness_val;
		}
	}
	return max_fitness;
}
