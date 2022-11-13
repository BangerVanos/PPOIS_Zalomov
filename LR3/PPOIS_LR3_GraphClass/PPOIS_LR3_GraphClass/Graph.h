#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>


using iterator_category = std::forward_iterator_tag;
using difference_type = std::ptrdiff_t;


template <typename T>
class Graph {
private:
	class Vertex {
	private:
		T value;
		std::vector<Vertex> adjacent_vertexes;
		std::vector<Edge> incident_edges;
	public:
		Vertex(T value) {
			this->value = value;
		}
		~Vertex(){}
		Vertex(const Vertex& ref_node) {
			this->value = ref_node.value;
			this->adjacent_vertexes = ref_node.adjacent_vertexes;
		}
		bool operator==(const Vertex& ref_vertex) {
			return this->value == ref_vertex.value;
		}
		bool operator !=(const Vertex& ref_vertex) {
			return this->value != ref_vertex.value;
		}
		void setValue(T value) {
			this->value = value;
		}
		T getValue() {
			return this->value;
		}
		std::vector<Vertex> getAdjacentVertexes() {
			return this->adjacent_vertexes;
		}
		std::vector<Edge> getIncidentEdges() {
			return this->incident_edges;
		}
		void setAdjacentVertexes(std::vector<Vertex> adjacent_vertexes) {
			this->adjacent_vertexes = adjacent_vertexes;
		}
		void addAdjacentVertex(Vertex vertex) {
			this->adjacent_vertexes.push_back(vertex);
		}
		void addAdjacentVertex(T vertex_value) {
			this->adjacent_vertexes.push_back(Node(vertex_value));
		}
		void clearAdjacentVertexes() {
			this->adjacent_vertexes.clear();
		}
		void addIncidentEdge(Edge incident_edge) {
			this->incident_edges.push_back(incident_edge);
		}
		void setIncidentEdges(std::vector<Edge> incident_edges) {
			this->incident_edges = incident_edges;
		}
		void clearIncidentEdges() {
			this->incident_edges.clear();
		}

		//Iterator for incident edges

		class IncidentEdgeIterator : public std::iterator<iterator_category, edge_value_type, edge_pointer, edge_reference> {
		private:
			edge_pointer e_ptr;
		public:
			IncidentEdgeIterator(edge_pointer e_ptr) : e_ptr(e_ptr) {

			}

			edge_reference operator*() const {
				return *e_ptr;
			}
			edge_pointer operator->() {
				return e_ptr;
			}

			IncidentEdgeIterator& operator++() {
				e_ptr++;
				return *this;
			}

			IncidentEdgeIterator operator++(int) {
				IncidentEdgeIterator tmp = *this;
				++(*this);
				return tmp;
			}
			IncidentEdgeIterator& operator--() {
				e_ptr--;
				return *this;
			}

			IncidentEdgeIterator operator--(int) {
				IncidentEdgeIterator tmp = *this;
				--(*this);
				return tmp;
			}

			bool operator==(const IncidentEdgeIterator& other)
			{
				return this->e_ptr == other.e_ptr;
			}

			bool operator!=(const IncidentEdgeIterator& other)
			{
				return this->e_ptr != other.e_ptr;
			}
		};

		IncidentEdgeIterator incident_begin() {
			return IncidentEdgeIterator(&incident_edges[0]);
		}

		IncidentEdgeIterator incident_end() {
			return IncidentEdgeIterator(&incident_edges[incident_edges.size() - 1] + 1);
		}

		class AdjacentVertexesIterator :public std::iterator<iterator_category, vertex_value_type, vertex_pointer, vertex_reference> {
		private:
			vertex_pointer v_ptr;
		public:
			AdjacentVertexesIterator(vertex_pointer v_ptr) : v_ptr(v_ptr) {

			}

			vertex_reference operator*() {
				return *v_ptr;
			}
			vertex_pointer operator->() {
				return v_ptr;
			}
			AdjacentVertexesIterator& operator++() {
				v_ptr++;
				return *this;
			}
			AdjacentVertexesIterator& operator++(int) {
				AdjacentVertexesIterator tmp = *this;
				v_ptr++;
				return tmp;
			}
			AdjacentVertexesIterator& operator--() {
				v_ptr--;
				return *this;
			}
			AdjacentVertexesIterator& operator--(int) {
				AdjacentVertexesIterator tmp = *this;
				v_ptr--;
				return tmp;
			}
			bool operator==(const AdjacentVertexesIterator& other) {
				return this->v_ptr == other.v_ptr;
			}
			bool operator!=(const AdjacentVertexesIterator& other) {
				return this->v_ptr != other.v_ptr;
			}

			AdjacentVertexesIterator adjacent_begin() {
				return AdjacentVertexesIterator(&adjacent_vertexes[0]);
			}

			AdjacentVertexesIterator adjacent_end() {
				return AdjacentVertexesIterator(&adjacent_vertexes[adjacent_vertexes.size() - 1] + 1);
			}
		};
	};

	class Edge {
	private:
		Vertex out_vertex;
		Vertex to_vertex;
	public:
		Edge(T out_vertex, T to_vertex) {
			this->out_vertex = Vertex(out_vertex);
			this->to_vertex = Vertex(to_vertex);
		}
		Edge(Vertex out_vertex, Vertex to_vertex) {
			this->out_vertex = out_vertex;
			this->to_vertex = to_vertex;
		}
		Edge(const Edge& ref_edge) {
			this->to_vertex = ref_edge.to_vertex;
			this->out_vertex = ref_edge.out_vertex;
		}
		Vertex getOutVertex() {
			return out_vertex;
		}
		Vertex getToVertex() {
			return to_vertex;
		}
		void setOutVertex(Vertex vertex) {
			this->out_vertex = vertex;
		}
		void setToVertex(Vertex vertex) {
			this->to_vertex = vertex;
		}
		bool operator ==(const Edge& cmp_edge) {
			if ((out_vertex == cmp_edge.out_vertex && to_vertex == cmp_edge.to_vertex) ||
				(to_vertex == cmp_edge.out_vertex && out_vertex == cmp_edge.to_vertex)) return true;
			return false;
		}
		bool is_vertex_represented_in_edge(Vertex vertex) {
			if (vertex == out_vertex || vertex == to_vertex) return true;
			return false;
		}		
	};
	std::vector<Edge> edge_container;
	void update_info_about_vertexes() {
		for (Edge edge : edge_container) {
			adjacent_vertexes_for_vertex(edge.getToVertex());
			adjacent_vertexes_for_vertex(edge.getOutVertex());
			incident_edges_for_vertex(edge.getToVertex());
			incident_edges_for_vertex(edge.getOutVertex());
		}
	}
	std::vector<Vertex> get_vertex_list() {
		std::vector<Vertex> vertex_list;
		for (Edge edge : edge_container) {
			if (std::find(edge_container.begin(), edge_container.end(), edge.getOutVertex()) != edge_container.end()) vertex_list.push_back(edge.getOutVertex());
			if (std::find(edge_container.begin(), edge_container.end(), edge.getToVertex()) != edge_container.end()) vertex_list.push_back(edge.getToVertex());
		}
	}
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
	bool is_represented_vertex(Vertex vertex) {
		for (Edge edge : edge_container) {
			if (vertex == edge.to_vertex || vertex == edge.out_vertex) return true;
		}
		return false;
	}
	bool is_represented_edge(Vertex out_vertex, Vertex to_vertex) {
		Edge intrested_edge(out_vertex, to_vertex);
		for (Edge edge : edge_container) {
			if (edge == intrested_edge) return true;
		}
		return false;
	}
	void add_vertex(Vertex vertex) {
		Edge new_edge(vertex, vertex);
		if (is_represented_edge(new_edge)) {
			std::cout << "Such vertex is already represented in graph!" << std::endl;
			return;
		}
		edge_container.push_back(new_edge);
		update_info_about_vertexes();
	}
	void add_edge(Vertex out_vertex, Vertex to_vertex) {
		Edge new_edge(out_vertex, to_vertex);
		if (is_represented_edge(new_edge)) {
			std::cout << "Such edge is already represented in graph!" << std::endl;
			return;
		}
		edge_container.push_back(new_edge);
		update_info_about_vertexes();
	}
	void delete_edge(Vertex out_vertex, Vertex to_vertex) {
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
		update_info_about_vertexes();
	}
	void delete_vertex(Vertex vertex) {
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
		update_info_about_vertexes();
	}
	int edge_amount() {
		return edge_container.size();
	}
	int vertex_amount() {
		std::vector<Vertex> mentioned_vertexes;
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
	int vertex_degree(Vertex vertex) {
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
	void adjacent_vertexes_for_vertex(Vertex& vertex) {
		vertex.clearAdjacentVertexes();		
		for (Edge edge : edge_container) {
			if (vertex == edge.getOutVertex()) vertex.addAdjacentVertex(edge.getToVertex());
			else if (vertex == edge.getToVertex()) vertex.addAdjacentVertex(edge.getOutVertex());
		}
	}
	void incident_edges_for_vertex(Vertex& vertex) {
		vertex.clearIncidentEdges();
		for (Edge edge : edge_container) {
			if (vertex == edge.getOutVertex() || vertex == edge.getToVertex()) vertex.addIncidentEdge(edge);
		}
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
		if (!graph.edge_container.empty()) {
			in << "-----VERTEXES-----" << std::endl;
			for (auto it = graph.vertex_begin(); it != vertex_end(); it++) {
				s << it->getValue() << std::endl;
			}
			in << "-----EDGES--------" << std::endl;
			for (auto it = graph.edge_begin(); it != graph.edge_end(); it++) {
				s << it->getOutVertex() << "---" << it->getToVertex() << std::endl();
			}
		}
	}

	//Iterator for edges

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

	//Iterator for vertex

	using vertex_value_type = Vertex;
	using vertex_pointer = Vertex*;
	using vertex_reference = Vertex&;

	class VertexIterator : public std::iterator<iterator_category, vertex_value_type, vertex_pointer, vertex_reference> {
	private:
		vertex_pointer v_ptr;
	public:
		VertexIterator(vertex_pointer v_ptr) : v_ptr(v_ptr) {

		}
		vertex_reference operator*() {
			return *v_ptr;
		}
		vertex_pointer operator->() {
			return v_ptr;
		}
		VertexIterator& operator++() {
			v_ptr++;
			return *this;
		}

		VertexIterator operator++(int) {
			VertexIterator tmp = *this;
			++(*this);
			return tmp;
		}
		VertexIterator& operator--() {
			v_ptr--;
			return *this;
		}

		VertexIterator operator--(int) {
			VertexIterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const VertexIterator& other)
		{
			return this->v_ptr == other.v_ptr;
		}

		bool operator!=(const VertexIterator& other)
		{
			return this->v_ptr != other.v_ptr;
		}
	};

	VertexIterator vertex_begin() {
		std::vector<Vertex> vertex_list = get_vertex_list();
		return VertexIterator(&vertex_list[0]);
	}

	VertexIterator vertex_end() {
		std::vector<Vertex> vertex_list = get_vertex_list();
		return VertexIterator(&vertex_list[vertex_list.size() - 1] + 1);
	}
};