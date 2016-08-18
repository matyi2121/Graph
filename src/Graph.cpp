#include "Graph.h"
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
vertex* Graph::at(const std::string& name)const
{
    auto it = m_V.find(name);
    if(it != m_V.end())
    {
        return it->second;
    }
    else throw;
}
std::vector<std::string> Graph::getkeys()const
{
    std::vector<std::string> ret;
    ret.resize(size());
    int ind = 0;
    for(auto& i : m_V)
    {
        ret[ind++] = i.first;
    }
    return ret;
}
Graph::Graph(const Graph& g)
{
    std::vector<std::string> names = g.getkeys();
    for(size_t i = 0; i < g.size(); i++)
        addvertex(names[i]);

    for(size_t i = 0; i < m_V.size(); i++)
    {
        auto it = m_V.find(names[i]);
        vertex* tmp = g.at(names[i]);
        vertex* pIt = it->second;
        for(auto& j : tmp->adj)
        {
            //1.cost
            //2.vertex* in this graph
            pIt->adj.push_back(std::make_pair(j.first,
                                              m_V.find(j.second->name)->second));
        }
    }
}
/*
    As long as there are vertexes
    change name,clean adjacency list.   x
    After that create new vertexes.     x
    Then fill adjacency lists.
    Clean remaining not needed vertexes x
*/
Graph& Graph::operator=(const Graph& g)
{
    int n = m_V.size() - g.size();
    ///if there are more vertexes than needed: n > 0
    ///if it is just the right size: n = 0
    ///if there are not enough vertexes: n < 0
    std::vector<std::string> names = getkeys();
    std::vector<std::string> namesTO = g.getkeys();
    if(!(n<0))
    {
        for(size_t i = 0; i < g.size(); i++)
        {
            auto it = m_V.find(names[i]);
            it->second->name = namesTO[i];
            it->second->adj.clear();
        }
        //Clean remaining not needed vertexes
        for(int i = g.size(); i < n; i++)
            removevertex(names[i]);
    }
    else
    {
        for(size_t i = 0; i < g.size(); i++)
            addvertex(namesTO[i]);
    }
    //Filling adjacency list
    for(size_t i = 0; i < g.size(); i++)
    {
        auto it = m_V.find(namesTO[i]);
        vertex* pIt = it->second;
        vertex* tmp = g.at(namesTO[i]);
        for(auto& j : tmp->adj)
        {
            pIt->adj.push_back(std::make_pair(j.first,
                                              m_V.find(j.second->name)->second));
        }
    }
    return *this;
}

Graph::~Graph()
{
    if(!m_V.empty())
    {
        for(auto& i : m_V)
            delete i.second;
    }
}

Graph::vmap::iterator Graph::addvertex(const std::string& name)
{
	auto it=m_V.find(name);
	if(it==m_V.end())
	{
		vertex *v;
		v = new vertex(name);
		m_V[name]=v;
		return it;
	}
	return m_V.end();
}

void Graph::addedge(const std::string& from, const std::string& to, int cost)
{
    auto fromIt = m_V.find(from);
    auto toIt   = m_V.find(to);
    if(fromIt != m_V.end() && toIt != m_V.end())
    {
        vertex *f = (fromIt->second);
        vertex *t = (toIt->second);
        std::pair<int,vertex*> edge = std::make_pair(cost,t);
        f->degp++;
        t->degm++;
        f->adj.push_back(edge);
    }
}

void Graph::removevertex(const std::string& name)
{
    auto it = m_V.find(name);
    if(it != m_V.end())
    {
        for(auto& i : m_V)
        {
            if(i.second != it->second)
            {
                vertex* v = i.second;
                for(auto& j : v->adj)
                {
                    if(j.second->name == name)
                    {
                        removeedge(j.second->name,name);
                    }
                }
            }
        }
        delete it->second;
        m_V.erase(it);
    }
}

void Graph::removeedge(const std::string& from, const std::string& to)
{
    auto fromIt = m_V.find(from);
    auto toIt   = m_V.find(to);
    if(fromIt != m_V.end() && toIt != m_V.end())
    {
        vertex* v = fromIt->second;
        size_t i = 0;
        while(i < v->adj.size() && !(v->adj[i].second->name == to))
            i++;
        if(i < v->adj.size())
        {
            v->adj.erase(v->adj.begin()+i);
        }
    }
}

bool Graph::adjacent(const std::string& from, const std::string& to)
{
    auto fromIt = m_V.find(from);
    auto toIt   = m_V.find(to);
    if(fromIt != m_V.end() && toIt != m_V.end())
    {
        for(auto& i : fromIt->second->adj)
        {
            if(i.second->name == to)
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<std::string> Graph::neighbours(const std::string& name)
{
    auto it = m_V.find(name);
    std::vector<std::string> ret;
    if(it != m_V.end())
    {
        for(auto& i : it->second->adj)
            ret.push_back(i.second->name);
    }
    return ret;
}

std::string Graph::bfs(const std::string& name)
{
    std::string ret = "";
    auto it = m_V.find(name);
    if(it != m_V.end())
    {
        std::queue<vertex*> Queue;
        vertex* curr = it->second;
        Queue.push(curr);
        curr->visited = true;
        ret += curr->name + " ";

        while(!Queue.empty())
        {
            for(auto& i : curr->adj)
            {
                if(i.second->visited == false)
                {
                    Queue.push(i.second);
                    i.second->visited = true;
                    ret+= i.second->name + " ";
                }
            }
            Queue.pop();
            if(!Queue.empty())
            {
                curr = Queue.front();
            }
        }

        for(auto& i : m_V)
            i.second->visited = false;
    }
    return ret;
}

std::string Graph::dfs(const std::string& name, bool topo)
{
    std::string ret = "";
    auto it = m_V.find(name);
    if(it != m_V.end())
    {
        std::stack<vertex*> Stack;
        vertex* curr = it->second;
        Stack.push(curr);
        curr->visited = true;
        if(!topo)
            ret += curr->name + " ";

        while(!Stack.empty())
        {
            bool found = false;
            size_t i = 0;
            while(i < curr->adj.size() && !found)
            {
                if(curr->adj[i].second->visited == false)
                {
                    found = true;
                    curr = curr->adj[i].second;
                    curr->visited = true;
                    if(!topo)
                        ret += curr->name + " ";
                    Stack.push(curr);
                }
                i++;
            }
            if(!found)
            {
                Stack.pop();
                if(topo)
                {
                    ret += curr->name + " ";
                }
                if(!Stack.empty())
                {
                    curr = Stack.top();
                }
            }
        }
        if(topo)
        {
            std::reverse(ret.begin(),ret.end());
            ret.erase(ret.begin());//remove space at the beginning
        }
        else ret.erase(ret.end()-1);//remove space at the end
        for(auto& i : m_V)
            i.second->visited = false;
    }
    return ret;
}

std::string Graph::cycle(bool& found)
{
    std::string ret = "";
    std::set<vertex*> white;
    std::set<vertex*> grey;
    std::set<vertex*> black;
    std::map<vertex*,vertex*> parentMap;
    ///Init all vertexes into white
    for(auto& i : m_V)
        white.insert(i.second);
    vertex* curr = *white.begin();
    vertex* prev = nullptr;
    grey.insert(curr);
    white.erase(curr);
    parentMap[curr] = prev;
    while(black.size() != m_V.size())
    {
        found = false;
        size_t i = 0;
        while(i < curr->adj.size() && !found)
        {
            vertex* v = curr->adj[i].second;
            if(white.find(v) != white.end())
            {
                prev = curr;
                curr = v;
                grey.insert(curr);
                white.erase(curr);
                parentMap[curr] = prev;
                found = true;
                i = 0;
            }
            else if(grey.find(v) != grey.end())
            {
                found = true;
                ret += v->name + " " + curr->name + " ";
                while(curr != nullptr)
                {
                    curr = parentMap.find(curr)->second;
                    if(curr != nullptr)
                        ret += curr->name + " ";
                }
                std::reverse(ret.begin(),ret.end());
                ret.erase(ret.begin());
                return ret;
            }
            else
                i++;
        }
        if(!found)
        {
            black.insert(curr);
            grey.erase(curr);
            prev = nullptr;
            curr = parentMap.find(curr)->second;
            if(curr == nullptr && !white.empty())
            {
                curr = *white.begin();
                grey.insert(curr);
                white.erase(curr);
                parentMap[curr] = prev;
            }
        }
    }
    return ret;
}
