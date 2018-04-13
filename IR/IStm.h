#ifndef H_ISTMT
#define H_ISTMT

class IRTree;

class IStm {
public:
	std::string id = "";
	virtual ~IStm() {}
	virtual void print(IRTree& tree) const = 0;
	std::string label;
};


#endif // H_ISTMT