#pragma once
#include <string>
#include <vector>
using namespace std;
class Ticker
{
public:
	class Timestamp {
		struct exchange{
			string id;
			long timestamp;
			};
		public:
			long total;
			vector<exchange> exchanges;

		
	}
	//ticker(void);
	//~ticker(void);
};

