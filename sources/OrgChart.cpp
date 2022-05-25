#include "OrgChart.hpp"
namespace ariel
{

OrgChart& OrgChart::add_root(const string& str)
{
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
    return m_begin_level_order;
}

OrgChart* OrgChart::end_level_order()
{
    return m_begin_level_order;//implement in B
}

OrgChart* OrgChart::begin_reverse_order()
{
    return m_begin_level_order;//implement in B
}

OrgChart* OrgChart::reverse_order()
{
    return m_begin_level_order;//implement in B
}

OrgChart* OrgChart::begin_preorder()
{
    return m_begin_level_order;//implement in B
}

OrgChart* OrgChart::end_preorder()
{
    return m_begin_level_order;//implement in B
}

OrgChart* OrgChart::operator->()const 
{
    return m_begin_level_order;
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