#include <iostream>
#include <fstream>
#include <string>

int** Crt2DArr(int n) {
    int** Arr = new int* [n]();
    for (int i = 0; i < n; i++) {
        Arr[i] = new int[n]();
    }
    return Arr;
}

void Del2DArr(int** Arr, int n) {
    for (int i = 0; i < n; i++) {
        delete[] Arr[i];
    }
    delete[] Arr;
}

void DisplayGraph(int** arr, int n) {
    std::cout << "Матрица смежности графа: " << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) std::cout << arr[i][j] << " ";
        std::cout << std::endl;
    }
}

void DFS(int** graph, bool* visited, int graph_size, int vertex) {
    std::cout << vertex + 1 << " ";
    visited[vertex] = true;
    for (int i = 0; i < graph_size; i++) {
        if ((graph[vertex][i] != 0) && (!visited[i]))
            DFS(graph, visited, graph_size, i);
    }
}

void DFS(int** graph, int graph_size) {
	
	bool* visited = new bool[graph_size];
	for (int i = 0; i < graph_size; i++) {
		visited[i] = false;
	}

    std::cout << "Порядок обхода вершин: ";
	for (int i = 0; i < graph_size; i++) {
		if (!visited[i]) {
			DFS(graph, visited, graph_size, i);
		}
	}

	delete[] visited;
}

void WFS(int** graph, int graph_size, int start_vertex) {
	
    bool* visited = new bool[graph_size];
	for (int i = 0; i < graph_size; i++) {
		visited[i] = false;
	}

	int* queue = new int[graph_size];
	int head = 0, tail = -1;

    visited[start_vertex] = true;
    queue[++tail] = start_vertex;
		
	std::cout << "Порядок обхода вершин: ";
	while (head <= tail) {
		int vertex = queue[head++];
		std::cout << vertex + 1 << " ";

		for (int i = 0; i < graph_size; i++) {
			if (graph[vertex][i] && !visited[i]) {
				queue[++tail] = i;
                visited[i] = true;				
			}
		}
	}

	delete[] visited;
	delete[] queue;
}


bool Cycler(int** graph, int graph_size, bool* visited,  int vertex, int parent) {
	visited[vertex] = true;

	for (int i = 0; i < graph_size; i++) {
		if (graph[vertex][i]) {
			if (!visited[i]) {
				if (Cycler(graph, graph_size, visited, i, vertex)) {
					return true;
				}
			}
			else if (i != parent) {
				return true;
			}
		}
	}
	return false;
}

bool FindCycle(int** graph, int graph_size) {
	bool* visited = new bool[graph_size];
	for (int i = 0; i < graph_size; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < graph_size; i++) {
		if (!visited[i]) {
			if (Cycler(graph, graph_size, visited, i, -1)) {
				delete[] visited;
				return true;
			}
		}
	}

	delete[] visited;
	return false;
}

void DisplayGraphVertx(int** graph, int g_size) {
    std::cout << "Текстовый вид орграфа: " << std::endl;

    for (int i = 0; i < g_size; i++) {
        std::cout << i + 1 << ": ";
        int vertx_value = 0;
        for (int j = 0; j < g_size; j++) {
            vertx_value += graph[i][j];
            if (graph[i][j] != 0) {
                std::cout << " " << j + 1;
            }
        }
        if (vertx_value == 0) std::cout << " нет";
        std::cout << std::endl;
    }
}

void TopoVertxDisplay(int** graph, int g_size, int vertex, bool* visited, int& currentIndex, int* vertx_list) {
    visited[vertex] = true;
    for (int i = 0; i < g_size; i++) {
        if (graph[vertex][i] && !visited[i]) {
            TopoVertxDisplay(graph, g_size, i, visited, currentIndex, vertx_list);
        }
    }
    vertx_list[currentIndex--] = vertex;
}

void TopoVertxDisplay(int** graph, int g_size) {
    int* vertx_list = new int[g_size];
    bool* visited = new bool[g_size];
    for (int i = 0; i < g_size; i++) {
        visited[i] = false;
    }
    int currentIndex = g_size - 1;
    for (int i = 0; i < g_size; i++) {
        if (!visited[i]) {
            TopoVertxDisplay(graph, g_size, i, visited, currentIndex, vertx_list);
        }
    }

    std::cout << "Топологический порядок вершин: ";
    for (int i = 0; i < g_size; i++) {
        std::cout << vertx_list[i] + 1 << " ";
    }
    std::cout << std::endl;

    delete[] visited;
    delete[] vertx_list;
}

int main() {

    std::string filename;
    do  {
        int file_num;
        std::cout << "Введите номер текстового файла (1 или 2): ";
        std::cin >> file_num;
        if (file_num == 1) {
            filename = "input1.txt";
            break;
        } else if (file_num == 2) {
            filename = "input2.txt";
            break;           
        } else {std::cout << "Введено некоретное число." << std::endl;}

    } while (true); 

    int g_size;
    std::ifstream file(filename);

   if (file.is_open()) {
        
        file >> g_size;
        int** graph = Crt2DArr(g_size);
       
        while (!file.eof()) {
            for (int i = 0; i < g_size; i++) {
                for (int j = 0; j < g_size; j++) {
                    file >> graph[i][j];
                }
            }
        }

        file.close();

        TopoVertxDisplay(graph, g_size);
        Del2DArr(graph, g_size);
    }
    else {
        std::cout << "Файл не открывается!" << std::endl;
    }

    return 0;
}