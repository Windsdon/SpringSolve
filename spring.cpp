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

void gaussSeidelSolve(vector<vector<double> > &a, vector<double> &b, vector<double> &solution) {
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

		cout << "Antes: " << endl;
		for (int j = 0; j < dim; j++) {
			for (int k = 0; k < dim; k++) {
				cout << setw(15) << a[j][k] << " ";
			}
			cout << " | " << b[j] << endl;
		}

		//eliminação
		for (int j = i + 1; j < dim; j++) {
			double alpha = a[j][i] / a[i][i];

			for (int k = i; k < dim; k++) {
				a[j][k] -= a[i][k] * alpha;
			}

			b[j] -= b[i] * alpha;
		}

		cout << "Depois: " << endl;
		for (int j = 0; j < dim; j++) {
			for (int k = 0; k < dim; k++) {
				cout << setw(15) << a[j][k] << " ";
			}
			cout << " | " << b[j] << endl;
		}
	}

	cout << "====\n";
	//cálculo da solução
	for (int i = dim - 1; i >= 0; i--) {
		solution[i] = b[i];

		cout << solution[i] << " ";

		for (int j = i + 1; j < dim; j++) {
			solution[i] -= a[j][i] * solution[j];
		}

		cout << solution[i] << " " << a[i][i] << endl;

		solution[i] /= a[i][i];
	}
}

int main(int argc, char **argv) {

	vector<vector<double> > a(5);
	vector<double> b;
	vector<double> sol;

	double a1[] = { 1, 2, 3, 4, 5 };
	double a2[] = { 5, 4, 3, 2, 1 };
	double a3[] = { 1, 1, 1, 1, 1 };
	double a4[] = { 2, 3, 4, 5, 6 };
	double a5[] = { 4, 4, 4, 5, 5 };

	a[0].assign(a1, a1 + 5);
	a[1].assign(a2, a2 + 5);
	a[2].assign(a3, a3 + 5);
	a[3].assign(a4, a4 + 5);
	a[4].assign(a5, a5 + 5);

	b.push_back(15);
	b.push_back(15);
	b.push_back(5);
	b.push_back(20);
	b.push_back(22);

	gaussSeidelSolve(a, b, sol);

	for (int i = 0; i < 5; i++) {
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

