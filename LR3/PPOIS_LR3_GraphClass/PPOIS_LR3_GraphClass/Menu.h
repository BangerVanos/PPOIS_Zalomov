#pragma once

#include "Graph.h"


template <typename T>
class Menu {
private:
	Graph<T> graph;
	static void start(int choise) {
		switch (choise) {
		case 1:
			std::cout << graph;
			std::cout << '\n';
			break;
		case 2:
			std::cout << "Adding new vertex" << std::endl;
			T vertex_value;
			std::cout << "Enter vertex value: ";
			std::cin >> vertex_value;			
			graph.add_vertex(Vertex(vertex_value));
			std::cout << "\nDone\n";
			break;
		case 2:
			std::cout << "Adding new edge" << std::endl;
			T out_value, to_value;
			std::cout << "Enter vertexes values: ";
			std::cin >> out_value >> to_value;
			graph.add_edge(Vertex(out_value), Vertex(to_value));
			std::cout << "\nDone\n";
			break;
		case 3:
			std::cout << "Deleting vertex" << std::endl;
			T delete_value;
			std::cout << "Enter vertex to delete: ";
			std::cin >> delete_value;
			graph.delete_vertex(Vertex(delete_value));
			std::cout << "\nDone\n";
			break;
		case 4:
			std::cout << "Deleting edge" << std::endl;
			T delete_out_value, delete_to_value;
			std::cout << "Enter vertex to delete: ";
			std::cin >> delete_out_value >> delete_to_value;
			graph.delete_edge(Vertex(delete_out_value), Vertex(delete_to_value));
			std::cout << "\nDone\n";
			break;
		case 5:
			std::cout << "Vertex amount: " << graph.vertex_amount() << "\n";
			break;
		case 6:			
			T vertex_value;
			std::cout << "Enter vertex value: ";
			std::cin >> vertex_value;
			std::cout << vertex_value << " vertex degree: " << graph.vertex_degree(Vertex(vertex_value)) << "\n";
			std::cout << "\nDone\n";
			break;
		case 7:
			T vertex_value;
			std::cout << "Enter vertex value: ";
			std::cin >> vertex_value;
			std::cout << "Does vertex " << vertex_value << " exist? " << graph.is_represented_vertex(Vertex(vertex_value));
			break;
		case 8:
			T out_value, to_value;
			std::cout << "Enter edge value: ";
			std::cin >> out_value >> to_value;
			std::cout << "Does vertex " << out_value << "---" << to_value << " exist? " << graph.is_represented_vertex(Vertex(out_value), Vertex(to_value));
			break;
		}
	}
};