#include <iostream>
#include <vector>
#include <random>

// Maze class representing the graph
class Maze {
public:
    Maze(int rows, int cols) : rows_(rows), cols_(cols), graph_(rows* cols) {}

    // Function to generate the maze graph
    void generateMaze() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                int node = i * cols_ + j;
                if (i > 0) {
                    int topNode = (i - 1) * cols_ + j;
                    if (dis(gen) == 0) {
                        graph_[node].push_back(topNode);
                        graph_[topNode].push_back(node);
                    }
                }
                if (j > 0) {
                    int leftNode = i * cols_ + (j - 1);
                    if (dis(gen) == 0) {
                        graph_[node].push_back(leftNode);
                        graph_[leftNode].push_back(node);
                    }
                }
            }
        }
    }

    // Function to print the maze graph
    void printMaze() {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                int node = i * cols_ + j;
                std::cout << "Node " << node << ": ";
                for (int neighbor : graph_[node]) {
                    std::cout << neighbor << " ";
                }
                std::cout << std::endl;
            }
        }
    }

private:
    int rows_;
    int cols_;
    std::vector<std::vector<int>> graph_;
};

int main() {
    int rows = 5;
    int cols = 5;

    Maze maze(rows, cols);
    maze.generateMaze();
    maze.printMaze();

    return 0;
}
