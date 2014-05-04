/*
 * spring.cpp
 *
 * Trabalho de Métodos Numéricos
 * Autores:
 *
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Block;
struct Spring {
	public:
		Block *connectsA;
		Block *connectsB;

		double k;
};

struct Block {
	public:
		vector<Spring*> springs;

		double force;
};

class SpringSolver {
	public:
		/**
		 * force: força que age no bloco
		 */
		void registerBlock(double force);

		/**
		 * a, b: blocos em que a mola está conectada
		 * k: constante elástica
		 */
		void registerSpring(int a, int b, double k);

		/**
		 * Resolve o sistema e coloca a solução no final de solutions
		 * a ordem é a mesma em que as molas foram registradas
		 *
		 * @return true se conseguir resolver
		 */
		bool solve(vector<double> &solutions);

	private:
		vector<Spring*> springs;
		vector<Block*> blocks;

};

void gauss(vector<vector<double> > a, vector<double> b, vector<double> &solution) {
	int dim = a.size();
	solution.assign(dim, 0);

	for (int i = 0; i < dim; i++) {
		double mv = a[i][i];
		int mj = i;

		//encontrando o maior pivot
		for (int j = i; j < dim; j++) {
			if (abs(a[j][i]) > mv) {
				mj = j;
				mv = abs(a[j][i]);
			}
		}

		//trocando as linhas
		if (mj != i) {
			vector<double> temp = a[i];
			a[i] = a[mj];
			a[mj] = temp;

			double temp2 = b[i];
			b[i] = b[mj];
			b[mj] = temp2;
		}

		//eliminação
		for (int j = i + 1; j < dim; j++) {
			double alpha = a[j][i] / a[i][i];

			for (int k = i + 1; k < dim; k++) {
				a[j][k] -= a[i][k] * alpha;
			}

			b[j] -= b[i] * alpha;
		}
	}

	//cálculo da solução
	for (int i = dim - 1; i >= 0; i--) {
		solution[i] = b[i];

		for (int j = i + 1; j < dim; j++) {
			solution[i] -= a[i][j] * solution[j];
		}

		solution[i] /= a[i][i];
	}
}
template<typename T>
void vectorPrint(const vector<T> &v) {
	for (int i = 0; i < v.size(); i++) {
		cout << "v[" << setw(2) << i << "] = " << v[i] << ";\n";
	}
}

bool gaussSeidel(vector<vector<double> > a, vector<double> b, vector<double> &solution) {
	int dim = b.size();
	double maxE = 0.001;

	solution.assign(dim, 0);

	for(int i = 0; i < dim; i++){
		double d = a[i][i];
		b[i] /= d;
		for(int j = 0; j < dim; j++){
			a[i][j] = a[i][j] / d;
		}
	}

	double e = -1;
	int maxIter = 100;
	do {
		for (int i = 0; i < dim; i++) {
			double prev = solution[i];
			solution[i] = b[i];
			for (int j = 0; j < dim; j++) {
				if (j == i) {
					continue;
				}
				solution[i] -= a[i][j] * solution[j];
			}

			double ek;
			if (solution[i] == 0) {
				ek = prev - solution[i];
			} else {
				ek = abs((prev - solution[i]) / solution[i]);
			}

			if (!i || ek > e) {
				e = ek;
			}
		}
	} while (e > maxE && maxIter--);

	if (maxIter >= 0) {
		return true;
	} else {
		return false;
	}

}

int main(int argc, char **argv) {

	vector<vector<double> > a(3);
	vector<double> b;
	vector<double> sol;

	double a1[] = { 5, 1, -10 };
	double a2[] = { 3, 4, 1 };
	double a3[] = { 3, 3, 6 };

	a[0].assign(a1, a1 + 5);
	a[1].assign(a2, a2 + 5);
	a[2].assign(a3, a3 + 5);

	b.push_back(5);
	b.push_back(6);
	b.push_back(0);

	gauss(a, b, sol);

	for (int i = 0; i < 3; i++) {
		cout << sol[i] << ", ";
	}

	cout << "\nGauss Seidel" << endl;

	gaussSeidel(a, b, sol);

	for (int i = 0; i < 3; i++) {
		cout << sol[i] << ", ";
	}

	return 0;

	ifstream file;

	file.open("in.txt", ifstream::in);

	if (!file.is_open()) {
		return 1;
	}

	SpringSolver solver;

	int countSprings, countBlocks;
	file >> countSprings >> countBlocks;

	while (countBlocks--) {
		double f;
		cin >> f;

		solver.registerBlock(f);
	}

	while (countSprings--) {
		int a, b;
		double k;
		cin >> a >> b >> k;

		solver.registerSpring(a, b, k);
	}

	return 0;
}

bool SpringSolver::solve(vector<double> &solutions) {
	//Primeiro, as equações de equilíbrio

	return true;
}

void SpringSolver::registerBlock(double force) {
	Block *b = new Block();
	b->force = force;

	blocks.push_back(b);
}

void SpringSolver::registerSpring(int a, int b, double k) {
	Spring *s = new Spring();

	s->k = k;
	s->connectsA = blocks[a];
	s->connectsB = blocks[b];

	blocks[a]->springs.push_back(s);
	blocks[b]->springs.push_back(s);
}

