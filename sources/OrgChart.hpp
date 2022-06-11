#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using std::string;
using std::vector;
using std::queue;
using std::stack;
namespace ariel
{
    struct Personal
    {
        string duty{};
        vector<Personal>underlings{};

        // Personal()=default;
        // Personal(const string& str):duty{str}{}
        // Personal(const string& str,vector<Personal>per):
        // duty{str},underlings{per}{}
        
        // ~Personal();

    };
    class OrgChart
    {
        public:
       // OrgChart()=default;
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
        
        //feature testing
        void prt_bfs(OrgChart& ptr);
        

        
        int size()
        {
            return 42;
        }

        auto begin()
        {
            return m_Personal;
        }

        auto end()
        {
            return m_Personal;
        }

        private:
        OrgChart* m_Personal{};

        //vectors, each storing some level of travesal:

        vector<string>v_bfs{};//breadth 
        vector<string>rv_bfs{};//breadth reversed
        vector<string>v_dfs{};//depth 


        //traversal algorithms:
        void bfs(Personal& ptr);
        

        void reverse_bfs(Personal& ptr);
        

     void dfs(Personal& ptr);
       

       //in addition of putting the obj. into stack, print it
    void place_in_stack(Personal& personal,stack<Personal>& st);
    

    };
}