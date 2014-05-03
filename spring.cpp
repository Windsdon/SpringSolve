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

void gaussSeidelSolve(vector<vector<double> > a, vector<double> b, vector<double> &solution) {
	int dim = a.size();
	solution.assign(dim, 0);

	for (int i = 0; i < dim; i++) {
		double mv = a[i][i];
		int mj = i;

		//encontrando o maior pivo
		for (int j = i; j < dim; j++) {
			if (a[j][i] > mv) {
				mj = j;
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
			double alpha = a[i][i] / a[j][i];

			for (int k = i + 1; k < dim; k++) {
				a[j][k] -= a[i][k] * alpha;
			}

			b[j] -= b[i] * alpha;
		}
	}

	//cálculo da solução
	for (int i = dim - 1; i >= 0; i--) {
		solution[i] = b[i];

		for (int j = i; j < dim; j++) {
			solution[i] -= a[j][i] * solution[j];
		}

		solution[i] /= a[i][i];
	}
}

int main(int argc, char **argv) {

	vector<vector<double> > a(5);
	vector<double> b(5);
	vector<double> sol;

	double a1[] =  {3, 7, 9, -1, -100};
	double a2[] =  {-12, 8, 9, 130};
	double a3[] =  {41, 8, 9, -9, 0};
	double a4[] =  {0, 7, 2, 9, 0};
	double a5[] =  {7, 1, 3, 9, 1};

	a[0].assign(a1, a1 + 5);
	a[1].assign(a2, a2 + 5);
	a[2].assign(a3, a3 + 5);
	a[3].assign(a4, a4 + 5);
	a[4].assign(a5, a5 + 5);

	b.push_back(-82);
	b.push_back(135);
	b.push_back(49);
	b.push_back(18);
	b.push_back(21);

	gaussSeidelSolve(a, b, sol);

	for(int i = 0; i < 5; i++){
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

