#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <array>
#include <algorithm>
#include <iterator>
#include <string>
using std::vector;
using std::unordered_map;
using std::cout;
using std::array;
using std::endl;
using std::string;
using std::queue;
using std::stack;

namespace ariel
{
    //personal serves as the node in the graph
struct Personal
{
    //aggregate initialization -> incase of no constructor compilers knows for simple field which initialization fits
    string duty{};
    vector<Personal>underlings{};//children
};


//orgchart serves as container and Graph_Iterator iterates over content
class OrgChart
{
public:

    //begin to implemt the iterator:
    struct Graph_Iterator
    {
        //https://internalpointers.com/post/writing-custom-iterators-modern-cpp
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = string;
        using pointer = string*;  // or also value_type*
        using reference = string&;  // or also value_type&

        Graph_Iterator(pointer ptr):m_ptr{ptr}{}

        reference operator * ()const
        {
            return *m_ptr;
        }
        pointer operator->()
        {
            return m_ptr;
        }
        //prefix incement
        Graph_Iterator& operator++() 
        {
            m_ptr++; 
            return *this; 
        }

        // Postfix increment
        Graph_Iterator operator++(int)
        {
            Graph_Iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }
        
        //used for loops to compare iterator positions
        friend bool operator== (const Graph_Iterator& a, const Graph_Iterator& b) 
        { 
            return a.m_ptr == b.m_ptr; 
        };
        friend bool operator!= (const Graph_Iterator& a, const Graph_Iterator& b)
        {
            return a.m_ptr != b.m_ptr; 
        };
        
        
    private:
        pointer m_ptr;//Graph iterator serves as wrapper for this ptr which points to node of type string
    };
    //

    
    //rule of zero Classes that have custom destructors, 
    //copy/move constructors or copy/move assignment operators
    // should deal exclusively with ownership (which follows from the Single Responsibility Principle). 
    //Other classes should not have custom destructors, copy/move constructors or copy/move assignment operators.

    //https://en.cppreference.com/w/cpp/language/rule_of_three
    void place_in_stack(Personal& personal, stack<Personal>& st)
    {
        //cout<<personal.underlings[0].duty<<" ";
        v_dfs.push_back(personal.underlings[0].duty);
        st.push(personal.underlings[0]);

        auto it = personal.underlings.begin();
        personal.underlings.erase(it);
    }
    //
    void insert_to_dfs(const Personal& ptr)//pre order algorithms
    {
        stack<Personal>temp{};
        //cout<<ptr.duty<<" ";
        v_dfs.push_back(ptr.duty);
        temp.push(ptr);
        do
        {
            //if (temp.top().underlings.size() != 0)
            if(!temp.top().underlings.empty())
            {
                place_in_stack(temp.top(), temp);
            }
            else
            {
                temp.pop();
            }

        } while (!temp.empty());

    }

    OrgChart& add_root(const string& str)
    {
        if (str == root.duty)
        {
            return *this;
        }
        if(str.empty())
        {
            throw "empty string is not valid as node root";
        }
        const array<char,9>special_chars{'\n','\t','\v','\b','\r','\f','\a','\\','\?'};
        for(const auto& i:str)
        {
            if(std::find(special_chars.begin(),special_chars.end(),i)!=special_chars.end())
            {
                throw "case of special char";
            }
        }
        um.erase(root.duty);
        root.duty = str;
        um.insert({ str,1 });
        return *this;

    }

    friend std::ostream& operator <<(std::ostream& os,const OrgChart& org)
        {
            os<<"tree";
            return os;
        };

    OrgChart& add_sub(const string& str1, const string& str2)
    {
        if(str1.empty())
        {
            throw "empty name is not valid";
        }
        if (um.empty())
        {
            throw "graph is empty";
        }
        const array<char,9>special_chars{'\n','\t','\v','\b','\r','\f','\a','\\','\?'};
        for(const auto& i:str2)
        {
            if(std::find(special_chars.begin(),special_chars.end(),i)!=special_chars.end())
            {
                throw "case of special char";
            }
        }
        for(const auto& j:str1)
        {
            if(std::find(special_chars.begin(),special_chars.end(),j)!=special_chars.end())
            {
                throw "case of special char";
            }
        }
        auto it = um.find(str1);
        if (it == um.end())
        {
            throw "node does not exist";
        }
        queue<Personal*>temp{};
        //Personal& ptr = root;
        Personal* ptr = &root;
        temp.push(ptr);
        do
        {

            if (temp.front()->duty == str1)
            {

                temp.front()->underlings.push_back(Personal{ str2 });

                um.insert({ str2,1 });

                break;
            }
  
            for (auto& i : temp.front()->underlings)     
            {
                Personal* temp_ptr = &i;
                temp.push(temp_ptr);
            }
            temp.pop();

        } while (!temp.empty());

        return *this;
    }

    void prt_this()//not included in running, used for debugging and see if container stores elemnts in right order
    {
        queue<Personal>temp{};

        temp.push(root);

        do
        {
            for (const auto& i : temp.front().underlings)
            {
                temp.push(i);
            }
            cout << temp.front().duty << " ";
            temp.pop();

        } while (!temp.empty());

    }



    //
    
    void iterate_over_dfs()
    {
        insert_to_dfs(root);
        for (const auto& i : v_dfs)
        {
            cout << i<<" ";
        }

    }

    void insert_to_bfs(const Personal& ptr)
    {
        queue<Personal>temp{};
        temp.push(ptr);
        do
        {
            for(const auto& i:temp.front().underlings)
            {
                temp.push(i);
            }
            v_bfs.push_back(temp.front().duty);
            temp.pop();

        } while (!temp.empty());
    }

    void iterate_over_bfs()
    {
        insert_to_bfs(root);
        for(const auto& i:v_bfs)
        {
            cout << i << " ";
        }
    }
    ///////////
    ///////////


    void insert_to_v_rbfs(const Personal& ptr)//a reverse represntation of bfs
    {
        queue<Personal>temp{};
        temp.push(ptr);
        do
        {
      
            for (auto it = temp.front().underlings.rbegin(); it != temp.front().underlings.rend(); it++)
            {
                temp.push(*it);
            }
            v_rbfs.push_back(temp.front().duty);
            temp.pop();

        } while (!temp.empty());
    }

    void iterate_over_v_rbfs()
    {
        v_rbfs.clear();
        insert_to_v_rbfs(root);
        std::reverse(v_rbfs.begin(), v_rbfs.end());
        for (const auto& i : v_rbfs)
        {
            cout << i << " ";
        }
    }

    //type of iteration Graph_Iterator supports:
    Graph_Iterator begin()
    {
        v_bfs.clear();
        insert_to_bfs(root);
        if(root.duty.empty())
        {
            throw "graph is empty";
        }
        if(v_bfs.empty())
        {
            throw "error at range based for loop";
        }
        
        
        return Graph_Iterator(&v_bfs[0]);
        
    }

    Graph_Iterator end()
    {
        if(root.duty.empty())
        {
            throw "graph is empty";
        }
        return Graph_Iterator(&v_bfs[0] + v_bfs.size());
    }

    ///////
    ///////

    //begin level order :
    Graph_Iterator begin_level_order()
    {
        v_bfs.clear();
        insert_to_bfs(root);
        if(root.duty.empty())
        {
            throw "graph is empty";
        }
       
        if(v_bfs.empty())
        {
            throw "error at v_bfs begin level order";
        }
        
    
        return Graph_Iterator(&v_bfs[0]);
        
    }

    Graph_Iterator end_level_order()
    {
        if(root.duty.empty())
        {
            throw "empty graph";
        }
        return Graph_Iterator(&v_bfs[0] + v_bfs.size());
    }
    //

    //begin_pre_order
    Graph_Iterator begin_preorder()
    {
        v_dfs.clear();
        insert_to_dfs(root);
        if(root.duty.empty())
        {
            throw "graph is empty";
        }
        if(v_dfs.empty())
        {
            throw "error at begin pre order";
        }
        
        
        return Graph_Iterator(&v_dfs[0]);
        
    }
    Graph_Iterator end_preorder()
    {
        if(root.duty.empty())
        {
            throw "empty graph";
        }
        return Graph_Iterator(&v_dfs[0]+v_dfs.size());
    }
    //

    //begin reverse order
    Graph_Iterator begin_reverse_order()
    {
        v_rbfs.clear();
        if(root.duty.empty())
        {
            throw "empty graph";
        }
        insert_to_v_rbfs(root);
        std::reverse(v_rbfs.begin(), v_rbfs.end());
        if(v_rbfs.empty())
        {
            throw "error at begin reverse order";
        }
        
            
        return Graph_Iterator(&v_rbfs[0]);
        
    }

    Graph_Iterator reverse_order()
    {
        if(root.duty.empty())
        {
            throw "graph is empty";
        }
        return Graph_Iterator(&v_rbfs[0]+v_rbfs.size());
    }
    
    //
   

private:
string str{"str"};
    //from this node the graph starts:
    Personal root{};

    //look up table
    unordered_map<string, int>um{};

    //node storage
    vector<string>v_dfs{};
    vector<string>v_bfs{};
    vector<string>v_rbfs{};

    Personal* ptr{};//pointer for iterating over containers==> strating at root

};
}



