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
#include <sstream>
#include <stack>

using namespace std;

struct Block;
struct Spring {
	public:
		Block *connectsA;
		Block *connectsB;

		int id;

		double k;
};

struct Block {
	public:
		vector<Spring*> springs;

		int id;

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

		/**
		 * rel: Relação das molas
		 */
		void registerRelation(const string &rel);

	private:
		vector<Spring*> springs;
		vector<Block*> blocks;
		vector<string> relations;

		bool isOperator(char c);
		bool makeRelation(const string &e, vector<vector<double> > &rel);

};

class CompoundGroup {
	public:
		vector<int> springs;

		void operator=(CompoundGroup& other) {
			springs = other.springs;
		}
};

bool gauss(vector<vector<double> > a, vector<double> b, vector<double> &solution) {
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

	return true;
}
template<typename T>
void vectorPrint(const vector<T> &v) {
	for (int i = 0; i < v.size(); i++) {
		cout << "x[" << setw(2) << i << "] = " << v[i] << ";\n";
	}
}

bool gaussSeidel(vector<vector<double> > a, vector<double> b, vector<double> &solution) {
	int dim = b.size();
	double maxE = 0.001;

	solution.assign(dim, 1);

	for (int i = 0; i < dim; i++) {
		double d = a[i][i];
		b[i] /= d;
		for (int j = 0; j < dim; j++) {
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

	ifstream file;

	file.open("in.txt", ifstream::in);

	if (!file.is_open()) {
		cout << "Could not open file" << endl;
		return 1;
	}

	SpringSolver solver;

	int countSprings, countBlocks;
	file >> countSprings >> countBlocks;

	while (countBlocks--) {
		double f;
		file >> f;

		solver.registerBlock(f);
	}

	while (countSprings--) {
		int a, b;
		double k;
		file >> a >> b >> k;

		solver.registerSpring(a, b, k);
	}

	int c;

	file >> c;

	string temp;
	getline(file, temp); //para limpar o \n

	while (c--) {
		string str;
		getline(file, str);
		solver.registerRelation(str);
	}

	vector<double> sol;

	if (!solver.solve(sol)) {
		cout << "Não converge!" << endl;
	}

	vectorPrint(sol);

	return 0;
}

bool SpringSolver::solve(vector<double> &solutions) {

	vector<vector<double> > a;
	vector<double> b;

	unsigned int dim = springs.size();

	//Primeiro, as equações de equilíbrio dos blocos
	for (unsigned int i = 0; i < blocks.size(); i++) {
		Block *block = blocks[i];
		vector<Spring*> &bsprings = block->springs;

		vector<double> eq(dim, 0);

		for (unsigned int j = 0; j < bsprings.size(); j++) {
			Spring *s = bsprings[j];

			if (s->connectsA == block) { //conecta por baixo
				eq[s->id] = -s->k;
			} else { //conecta por cima
				eq[s->id] = s->k;
			}
		}

		//adiciona a equação ao sistema
		a.push_back(eq);
		b.push_back(-block->force);
	}

	//ler relações
	for (unsigned int i = 0; i < relations.size(); i++) {
		vector<vector<double> > rel;
		makeRelation(relations[i], rel);

		for (unsigned int j = 0; j < rel.size(); j++) {
			a.push_back(rel[j]); //colocar no sistema
			b.push_back(0);
		}
	}

	if (a.size() != dim) {
		cout << "Poucas equações!" << endl;
		return false;
	} else {
		cout << "Sistema: " << endl;
		for (unsigned int i = 0; i < dim; i++) {
			for (unsigned int j = 0; j < dim; j++) {
				cout << setw(5) << a[i][j] << " ";
			}
			cout << " | " << b[i] << endl;
		}
	}

	return gauss(a, b, solutions);
}

void SpringSolver::registerBlock(double force) {
	Block *b = new Block();
	b->force = force;
	b->id = blocks.size();

	blocks.push_back(b);
}

void SpringSolver::registerSpring(int a, int b, double k) {
	Spring *s = new Spring();

	s->k = k;
	if (a >= 0) {
		s->connectsA = blocks[a];
		blocks[a]->springs.push_back(s);
	} else {
		s->connectsA = 0;
	}
	if (b >= 0) {
		s->connectsB = blocks[b];
		blocks[b]->springs.push_back(s);
	} else {
		s->connectsB = 0;
	}
	s->id = springs.size();

	springs.push_back(s);
}

void SpringSolver::registerRelation(const string &rel) {
	relations.push_back(rel);
}

bool SpringSolver::isOperator(char c) {
	switch (c) {
		case '+':
		case '=':
			return true;
	}

	return false;
}

bool SpringSolver::makeRelation(const string &e, vector<vector<double> > &rel) {
	int dim = springs.size();

	stringstream str(e);
	string s;
	stack<CompoundGroup> g;
	stack<int> sp;
	int num;
	str >> num;
	while (str >> s) {
		if (isOperator(s[0])) {
			switch (s[0]) {
				case '+': {
					if (sp.empty()) {
						cout << "Operacao invalida no stack!" << endl;
						cout << "Durante operação + em " << s << endl;
						return false;
					}

					CompoundGroup cg;

					while (!sp.empty()) {
						cg.springs.push_back(sp.top());
						sp.pop();
					}

					g.push(cg);
					break;
				}

				case '=': {
					//cria uma equação

					if (!sp.empty()) {
						//grupo não criado
						CompoundGroup cg;

						while (!sp.empty()) {
							cg.springs.push_back(sp.top());
							sp.pop();
						}

						g.push(cg);
					}

					//usamos a - b = 0
					CompoundGroup a = g.top();
					g.pop();
					CompoundGroup b = g.top();

					g.push(a); //retornando a ao stack

					vector<double> v(dim, 0);

					for (unsigned int i = 0; i < a.springs.size(); i++) {
						Spring *s = springs[a.springs[i]];
						v[s->id] = 1;
					}

					for (unsigned int i = 0; i < b.springs.size(); i++) {
						Spring *s = springs[b.springs[i]];
						v[s->id] = -1;
					}

					rel.push_back(v);

					break;
				}

				default:
					return false;

			}
		} else {
			int n;
			stringstream(s) >> n;

			sp.push(n);
		}
	}

	return true;

}

