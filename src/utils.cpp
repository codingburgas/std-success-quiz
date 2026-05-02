#include <string>

std::string numToString(int number)
{
	std::string ret = "";
	int div = 1;
	while (number/div) div *= 10;
	div /= 10;
	for (; div; div/=10)
		ret.push_back((number/div%10)+48);

	return ret;
}

std::string getProgressString(int current, int total)
{
	std::string ret;

	ret += numToString(current+1);
	ret.push_back('/');
	ret += numToString(total);

	return ret;
}
