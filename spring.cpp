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

class SparseMatrix {
	public:
		int dim;
		double get(int i, int j) {
			map<int, map<int, double> >::iterator it1 = mtrx.find(i);
			if(it1 != mtrx.end()){
				map<int, double>::iterator it2 = (it1->second).find(j);

				if(it2 != it1->second.end()){
					return it2->second;
				}else{
					return 0;
				}
			}else{
				return 0;
			}
		}

		void set(int i, int j, double val){
			mtrx[i][j] = val;
		}

	private:
		map<int, map<int, double> > mtrx;
};

void gaussSeidelSolve(SparseMatrix a, map<int, double> b, vector<double> &solution){
	solution.assign(1, 0);


}

int main(int argc, char **argv) {

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

	vector<double> sol;

	solver.solve(sol);

	return 0;
}

bool SpringSolver::solve(vector<double> &solutions) {
	SparseMatrix a;
	a.dim = springs.size();

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


