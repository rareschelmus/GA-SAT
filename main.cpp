#include"functii.h"
#include<time.h>


int main()
{
	short propozitie[clauze_max][lungime_clauza];
	int nr_clauze, nr_var, nr, i, max=-1,j,k;
	long long int suma_ag, suma_rmhc;
	double medie_ag, medie_rmhc;

	parse_and_build_matrix(propozitie,nr_var, nr_clauze);
	srand(time(NULL));
	for (j = 10; j <= 1000; j *= 10)
	{
		suma_ag = 0;
		suma_rmhc = 0;
		for (k = 0; k < 100; k++)
		{
			nr = AG(0.04, 0.6, j, 50, 4, nr_var, nr_clauze, propozitie);
			//cout << nr << "\n";
			suma_ag += nr;
			for (i = 0; i < j; i++)
			{
				nr = rmhc(nr_var, nr_clauze, propozitie);
				//cout << nr << "\n";
				if (nr > max)
					max = nr;
			}
			//cout << max << "\n\n";
			suma_rmhc += max;
		}
		medie_ag = suma_ag / 100;
		medie_rmhc = suma_rmhc / 100;
		cout << "nr iteratii: " << j << " - medie_ag= " << medie_ag << " - medie_rmhc= " << medie_rmhc << "\n";
	}
	system("pause");
	return 0;
}