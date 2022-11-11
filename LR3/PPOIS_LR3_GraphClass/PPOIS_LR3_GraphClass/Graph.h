#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


using iterator_category = std::forward_iterator_tag;
using difference_type = std::ptrdiff_t;


template <typename T>
class Graph {
private:
	class Edge {
	private:
		T out_vertex;
		T to_vertex;
	public:
		Edge(T out_vertex, T to_vertex) {
			this->out_vertex = out_vertex;
			this->to_vertex = to_vertex;
		}
		Edge(const Edge& ref_edge) {
			this->to_vertex = ref_edge.to_vertex;
			this->out_vertex = ref_edge.out_vertex;
		}
		T getOutVertex() {
			return out_vertex;
		}
		T getToVertex() {
			return to_vertex;
		}
		T setOutVertex(T value) {
			this->out_vertex = value;
		}
		T setToVertex(T value) {
			this->to_vertex = value;
		}
		bool operator ==(const Edge& cmp_edge) {
			if ((out_vertex == cmp_edge.out_vertex && to_vertex == cmp_edge.to_vertex) ||
				(to_vertex == cmp_edge.out_vertex && out_vertex == cmp_edge.to_vertex)) return true;
			return false;
		}
		bool is_vertex_represented_in_edge(T vertex) {
			if (vertex == out_vertex || vertex == to_vertex) return true;
			return false;
		}
	};
	std::vector<Edge> edge_container;
public:
	Graph() {
		
	}
	Graph(const Graph& ref_graph) {
		this->edge_container = ref_graph.edge_container;
	}
	~Graph() {

	}
	bool empty() {
		return this->edge_container.empty();
	}
	void clear() {
		edge_container.clear();
	}
	bool is_represented_vertex(T vertex) {
		for (Edge edge : edge_container) {
			if (vertex == edge.to_vertex || vertex == edge.out_vertex) return true;
		}
		return false;
	}
	bool is_represented_edge(T out_vertex, T to_vertex) {
		Edge intrested_edge(out_vertex, to_vertex);
		for (Edge edge : edge_container) {
			if (edge == intrested_edge) return true;
		}
		return false;
	}
	void add_vertex(T vertex) {
		Edge new_edge(vertex, vertex);
		if (is_represented_edge(new_edge)) {
			std::cout << "Such vertex is already represented in graph!" << std::endl;
			return;
		}
		edge_container.push_back(new_edge);
	}
	void add_edge(T out_vertex, T to_vertex) {
		Edge new_edge(out_vertex, to_vertex);
		if (is_represented_edge(new_edge)) {
			std::cout << "Such edge is already represented in graph!" << std::endl;
			return;
		}
		edge_container.push_back(new_edge);
	}
	void delete_edge(T out_vertex, T to_vertex) {
		Edge deleted_edge(out_vertex, to_vertex);
		if (!is_represented_edge(deleted_edge)) {
			std::cout << "Such edge isn't represented in graph!" << std::endl;
			return;
		}
		std::vector<Edge>::iterator graph_it = edge_container.begin();
		while (graph_it != edge_container.end()) {
			if (deleted_edge == (*graph_it)) {
				edge_container.erase(graph_it);
				return;
			}
			graph_it++;
		}
	}
	void delete_vertex(T vertex) {
		if (!is_represented_vertex(vertex)) {
			std::cout << "Such vertex isn't represented in graph!" << std::endl;
			return;
		}
		std::vector<Edge>::iterator graph_it = edge_container.begin();
		while (graph_it != edge_container.end()) {
			if (graph_it->is_vertex_represented_in_edge(vertex)) {
				edge_container.erase(graph_it);
			}
			graph_it++;
		}
	}
	int edge_amount() {
		return edge_container.size();
	}
	int vertex_amount() {
		std::vector<T> mentioned_vertexes;
		for (Edge edge : edge_container) {
			if (std::find(mentioned_vertexes.begin(), mentioned_vertexes.end(), edge.getOutVertex()) == mentioned_vertexes.end()) {
				mentioned_vertexes.push_back(edge.getOutVertex());
			}
			if (std::find(mentioned_vertexes.begin(), mentioned_vertexes.end(), edge.getToVertex()) == mentioned_vertexes.end()) {
				mentioned_vertexes.push_back(edge.getToVertex());
			}
		}
		return mentioned_vertexes.size();
	}
	int vertex_degree(T vertex) {
		if (!is_represented_vertex(vertex)) {
			std::cout << "Such vertex isn't represented in graph!" << std::endl;
			return;
		}
		int degree = 0;
		for (Edge edge : edge_container) {
			if (edge.is_vertex_represented_in_edge(vertex)) degree++;
		}
		return degree;
	}
	bool operator ==(const Graph& cmp_graph) {
		if (edge_container.size != cmp_graph.edge_container.size()) return false;
		for (Edge edge : this->edge_container) {
			bool edge_represented_in_cmp_graph = false;
			for (Edge cmp_edge : cmp_graph.edge_container) {
				if (edge = cmp_edge) {
					edge_represented_in_cmp_graph = true;
					break;
				}
			}
			if (!edge_represented_in_cmp_graph) return false;
		}
		return true;
	}
	bool operator !=(const Graph& cmp_graph) {
		return !( *this == cmp_graph );
	}
	bool operator <=(const Graph& cmp_graph) {
		return edge_container.size() <= cmp_graph.edge_container.size();
	}
	bool operator >=(const Graph& cmp_graph) {
		return edge_container.size() >= cmp_graph.edge_container.size();
	}
	bool operator <(const Graph& cmp_graph) {
		return edge_container.size() < cmp_graph.edge_container.size();
	}
	bool operator >(const Graph& cmp_graph) {
		return edge_container.size() > cmp_graph.edge_container.size();
	}
	friend std::ostream operator <<(std::ostream& in, const Graph& graph) {

	}

	//Iterators for edges

	using edge_value_type = Edge;
	using edge_pointer = edge_value_type*;
	using edge_reference = edge_value_type&;

	class EdgeIterator : public std::iterator<iterator_category, edge_value_type, edge_pointer, edge_reference> {
	private:
		edge_pointer e_ptr;
	public:
		EdgeIterator(edge_pointer e_ptr) : e_ptr(e_ptr) {

		}

		edge_reference operator*() const {
			return *e_ptr;
		}
		edge_pointer operator->() {
			return e_ptr;
		}

		EdgeIterator& operator++() {
			e_ptr++;
			return *this;
		}

		EdgeIterator operator++(int) {
			EdgeIterator tmp = *this;
			++(*this);
			return tmp;
		}
		EdgeIterator& operator--() {
			e_ptr--;
			return *this;
		}

		EdgeIterator operator--(int) {
			EdgeIterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const EdgeIterator& other)
		{
			return this->e_ptr == other.e_ptr;
		}

		bool operator!=(const EdgeIterator& other)
		{
			return this->e_ptr != other.e_ptr;
		}


	};

	EdgeIterator edge_begin() {
		return EdgeIterator(&edge_container[0]);
	}

	EdgeIterator edge_end() {
		return EdgeIterator(&edge_container[edge_container.size() - 1] + 1);
	}
};