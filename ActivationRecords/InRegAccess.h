
#ifndef H_INREG
#define H_INREG

#include <iostream>
#include "Access.h"

namespace AR {

	class InRegAccess : public IAccess {

	public:
		
		InRegAccess(T_RecordsType _type, int _size, int _reg_number): 
			type(_type), size(_size), reg_number(_reg_number),
			temp("r" + std::to_string(reg_number + 2)) {}

		virtual const int get_size() const override { return size; }

		virtual const T_RecordsType get_type() override { return type; }

		virtual const int get_reg_number() const { return reg_number; }

		virtual void print(const Temp* fp) const override {
			std::cout << "Register: " << reg_number << std::endl; 
		}

		virtual const IExp* get_exp(IRTree& tree, const Temp framePtr) const override {
			return new TempExp(tree, temp);
		}


	private:
		T_RecordsType type;
		int size;
		int reg_number;
		Temp temp;
	};
}

#endif