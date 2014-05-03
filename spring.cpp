/*
 * spring.cpp
 *
 * Trabalho de Métodos Numéricos
 * Autores:
 *
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Block;
struct Spring {
	public:
		Block *connectsA;
		Block *connectsB;

		unsigned float k;
};

struct Block {
	public:
		vector<Spring*> springs;

		float force;
};

class SpringSolver {
	public:
		SpringSolver();

		/**
		 * force: força que age no bloco
		 */
		void registerBlock(float force);

		/**
		 * a, b: blocos em que a mola está conectada
		 * k: constante elástica
		 */
		void registerSpring(int a, int b, unsigned float k);

		/**
		 * Resolve o sistema e coloca a solução no final de solutions
		 * a ordem é a mesma em que as molas foram registradas
		 *
		 * @return true se conseguir resolver
		 */
		bool solve(vector<float> &solutions);

	private:
		vector<Spring*> springs;
		vector<Block*> blocks;

};

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
		float f;
		cin >> f;

		solver.registerBlock(f);
	}

	while (countSprings--) {
		int a, b;
		unsigned float k;
		cin >> a >> b >> k;

		solver.registerSpring(a, b, k);
	}

	vector<float> sol;

	solver.solve(sol);

	return 0;
}

void SpringSolver::registerBlock(float force) {
	Block *b = new Block();
	b->force = force;

	blocks.push_back(b);
}

void SpringSolver::registerSpring(int a, int b, unsigned float k){
	Spring *s = new Spring();

	s->k = k;
	s->connectsA = blocks[a];
	s->connectsB = blocks[b];

	blocks[a]->springs.push_back(s);
	blocks[b]->springs.push_back(s);
}
