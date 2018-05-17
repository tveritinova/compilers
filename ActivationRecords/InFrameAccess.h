
#ifndef H_INFRAME
#define H_INFRAME

#include "Access.h"
#include "Frame.h"
#include "../IR/IRTree_OP.h"
#include <iostream>

namespace AR {
	class InFrameAccess : public IAccess {

	public:

		InFrameAccess(T_RecordsType _type, T_VariableType _varType, int _size, int _offset, int _address) : 
			size(_size), address(_address), offset(_offset), recordType(_type), varType(_varType) {};

		virtual const int get_size() const override { return size; }

		virtual const T_RecordsType get_type() override { return recordType; }

		const int get_offset() const { return offset; }

		virtual void print(const Temp* fp) const override {
			std::cout << "In frame position " << std::endl;
		}

		virtual IExp* get_exp(IRTree& tree, Temp framePtr) const override {
		return new MemExp(tree,
			new BinopExp(tree, IRTree_OP::OP_BIN::PLUS_, new TempExp(tree, framePtr), new ConstExp(tree, offset)), 
			size);
	}

	private:

		const int size;
		int address;
		const int offset;
		const T_RecordsType recordType;
		const T_VariableType varType;
	};
}

#endif