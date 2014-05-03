/*
 * spring.cpp
 *
 * Trabalho de M�todos Num�ricos
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
		 * force: for�a que age no bloco
		 */
		void registerBlock(float force);

		/**
		 * a, b: blocos em que a mola est� conectada
		 * k: constante el�stica
		 */
		void registerSpring(int a, int b, unsigned float k);

		/**
		 * Resolve o sistema e coloca a solu��o no final de solutions
		 * a ordem � a mesma em que as molas foram registradas
		 *
		 * @return true se conseguir resolver
		 */
		bool solve(vector<float> &solutions);

	private:
		vector<Spring*> springs;
		vector<Block*> blocks;

};

int main(int argc, char **argv) {
	string line;
	ifstream file;

	file.open("in.txt", ifstream::in);

	if(!file.is_open()){
		return 1;
	}

	SpringSolver solver;

	int countSprings, countBlocks;
	file >> countSprings >> countBlocks;

	while(countBlocks--){
		float f;
		cin >> f;

		solver.registerBlock(f);
	}

	while(countSprings--){
		int a, b;
		unsigned float k;
		cin >> a >> b >> k;

		solver.registerSpring(a, b, k);
	}

	vector<float> sol;

	solver.solve(sol);

	return 0;
}
