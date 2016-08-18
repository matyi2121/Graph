#include "Graph.h"
#include <algorithm>
#include <queue>
#include <stack>
Graph::~Graph()
{
    if(!m_V.empty())
    {
        for(auto& i : m_V)
            delete i.second;
    }
}

void Graph::addvertex(const std::string &name)
{
	auto it=m_V.find(name);
	if(it==m_V.end())
	{
		vertex *v;
		v= new vertex(name);
		m_V[name]=v;
		return;
	}
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
        delete it->second;
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
    std::string retTopo = "";
    auto it = m_V.find(name);
    if(it != m_V.end())
    {
        std::stack<vertex*> Stack;
        vertex* curr = it->second;
        Stack.push(curr);//push stackbe
        curr->visited = true;//megjeloles
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
                    retTopo += curr->name + " ";
                }
                if(!Stack.empty())
                {
                    curr = Stack.top();
                }
            }
        }
        if(topo)
        {
            std::reverse(retTopo.begin(),retTopo.end());
            retTopo.erase(retTopo.begin());
        }
        for(auto& i : m_V)
            i.second->visited = false;
    }
    if(topo)
        return retTopo;
    return ret;
}
