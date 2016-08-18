#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <map>
#include <string>
struct vertex{
	using ve = std::pair<int,vertex*>;
	std::vector<ve> adj;
	std::string name;
	bool visited;//Might use set locally for visited nodes
	int degp;
	int degm;
	int value;
	vertex(const std::string& s)
	:name(s),visited(false),degp(0),degm(0),value(0)
	{}
};

class Graph
{
    public:
        Graph() = default;
        ~Graph();
        using vmap = std::map<std::string, vertex*>;
		void addvertex(const std::string&);
		void addedge(const std::string& from, const std::string& to, int cost);
		void removevertex(const std::string& name);
		void removeedge(const std::string& from, const std::string& to);
		bool adjacent(const std::string& from, const std::string& to);
		std::vector<std::string> neighbours(const std::string& name);
		std::string bfs(const std::string& name);
		std::string dfs(const std::string& name, bool topo=false);
    private:
        vmap m_V;
};

#endif // GRAPH_H
