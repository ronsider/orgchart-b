#include <string>
#include <iostream>
#include <vector>
using std::string;
using std::vector;
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

    };
}