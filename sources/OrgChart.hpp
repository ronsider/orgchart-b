#include <string>
#include <iostream>
#include <vector>
#include <queue>
using std::string;
using std::vector;
using std::queue;
namespace ariel
{
    struct Personal
    {
        string duty{};
        vector<Personal>underlings{};

    };
    class OrgChart
    {
        public:
        OrgChart& add_root(const string&);
        OrgChart& add_sub(const string&, const string&);
        friend std::ostream& operator <<(std::ostream& os,OrgChart&);

        OrgChart* begin_level_order();
        OrgChart* end_level_order();
        OrgChart* begin_reverse_order();
        OrgChart* reverse_order();
        OrgChart* begin_preorder();
        OrgChart* end_preorder();

        OrgChart* operator ->()const ;
        std::string operator *()const;

        friend bool operator == (const OrgChart& , const OrgChart&);
        

        int size()
        {
            return 42;
        }

        auto begin()
        {
            return m_begin_level_order;
        }

        auto end()
        {
            return m_begin_level_order;
        }

        private:
        OrgChart* m_begin_level_order{};

        //vectors, each storing some level of travesal:

        vector<string>v_bfs{};//breadth 
        vector<string>rv_bfs{};//breadth reversed
        vector<string>v_dfs{};//depth 


        //traversal algorithms:
        void bfs(Personal ptr)
        {
         queue<Personal>temp{};
         temp.push(ptr);
       
       do
       {
           for(const auto& i:temp.front().underlings)
           {
               temp.push(i);
           }
           //cout<<temp.front().duty<<" ";
           v_bfs.push_back(temp.front().duty);
           temp.pop();

       } 
       while(!temp.empty());

        }

        void reverse_bfs(Personal ptr)
        {
          queue<Personal>temp{};
          temp.push(ptr);
       
       do
       {
        //    for(const auto& i:temp.front().underlings)
        //    {
        //        temp.push(i);
        //    }
        for( auto it=temp.front().underlings.rbegin();it!=temp.front().underlings.rend();it++)
        {
            temp.push(*it);
        }
                                                    
           //cout<<temp.front().duty<<" ";
           rv_bfs.push_back(temp.front().duty);
           temp.pop();

       } 
       while(!temp.empty());

        }

    };
}