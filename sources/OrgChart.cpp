#include "OrgChart.hpp"
namespace ariel
{
    void OrgChart::bfs(Personal& ptr)
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

        void OrgChart::reverse_bfs(Personal& ptr)
        {
          queue<Personal>temp{};
          temp.push(ptr);
       
       do
       {
        
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

    void OrgChart::dfs(Personal& ptr)
    {
        {
        stack<Personal>temp{};
        //cout<<ptr.duty;
        v_dfs.push_back(ptr.duty);
       temp.push(ptr);
       do
       {
           if(temp.top().underlings.size()!=0)
           {
             place_in_stack(temp.top(),temp);
           }
           else
           {
               temp.pop();
           }

       }while(!temp.empty());

       }  
    }

    void OrgChart::place_in_stack(Personal& personal, stack<Personal>&st)
    
    {
        //cout<<personal.underlings[0].duty;

        st.push(personal.underlings[0]); 

        auto it=personal.underlings.begin();
        personal.underlings.erase(it);     
    }
    
    void OrgChart::prt_bfs(OrgChart& ptr)
    {
       // std::cout<<"walla";
        
            for(const auto& i:ptr.rv_bfs)
            {
                std::cout<<i<<" ";
            }
        
    }

OrgChart& OrgChart::add_root(const string& str)
{
    Personal personal{str};
    m_Personal=&personal;
    
    return *this;
}

OrgChart& OrgChart::add_sub(const string& s1, const string& s2)
{
    return *this;
}

 std::ostream& operator<<(std::ostream& os,OrgChart& oc)
{
    return os;
}

OrgChart* OrgChart::begin_level_order()
{
    return m_Personal;
}

OrgChart* OrgChart::end_level_order()
{
    return m_Personal;//implement in B
}

OrgChart* OrgChart::begin_reverse_order()
{
    return m_Personal;//implement in B
}

OrgChart* OrgChart::reverse_order()
{
    return m_Personal;//implement in B
}

OrgChart* OrgChart::begin_preorder()
{
    return m_Personal;//implement in B
}

OrgChart* OrgChart::end_preorder()
{
    return m_Personal;//implement in B
}

OrgChart* OrgChart::operator->()const 
{
    return m_Personal;
}

std::string OrgChart::operator*()const
{
   return "42";
}

bool operator==(const OrgChart& oc1,const OrgChart& oc2)
{
    return true;
}

}