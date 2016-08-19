#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <map>
#include <string>
struct vertex
{
    using ve = std::pair<int,vertex*>;
    std::vector<ve> adj;
    std::string name;
    bool visited;//Might use set locally for visited nodes
    int value;
    vertex(const std::string& s)
    :name(s),visited(false),value(0)
    {}
};
class Graph
{
    private:
        using vmap = std::map<std::string, vertex*>;
        vmap m_V;
        void filladj(const std::vector<std::string>& names, const Graph& g);
    public:
        Graph() = default;
        Graph(const Graph& g);
        Graph& operator=(const Graph& g);
        Graph(const Graph&& g) = delete;
        Graph& operator=(const Graph&& g) = delete;
        ~Graph();
		vmap::iterator addvertex(const std::string&);
		void addedge(const std::string& from, const std::string& to, int cost);
		void removevertex(const std::string& name);
		void removeedge(const std::string& from, const std::string& to);
		bool adjacent(const std::string& from, const std::string& to);
		std::vector<std::string> neighbours(const std::string& name);
		std::string bfs(const std::string& name);
		std::string dfs(const std::string& name, bool topo=false);
		std::string cycle(bool& found);
		size_t size()const noexcept{return m_V.size();};
		std::vector<std::string> getkeys()const;
        vertex* at(const std::string& name)const;
};

#endif // GRAPH_H
