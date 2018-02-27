#include <queue>
#include <functional>



class barber_list {

	struct barber {
		int m_num;
		int m_eff;
		int m_accu;
		barber(int num, int eff, int accu);
	};


	struct barber_comparison {
		bool operator()(const barber& lhs, const barber& rhs);
	};


public:
	barber_list();
	~barber_list();

	void add_barber(int efficiency);
	
	int add_client();


private:
	std::priority_queue<barber, std::vector<barber>, barber_comparison> list;


};


