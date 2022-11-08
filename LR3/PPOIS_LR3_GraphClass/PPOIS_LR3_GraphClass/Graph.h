#pragma once

#include <stdio.h>
#include <vector>
#include <string>


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
	};
	std::vector<Edge> edge_container;
public:
	Graph() {
		
	}
	Graph(const Graph& ref_graph) {
		this->edge_container = ref_graph.edge_container;
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
};