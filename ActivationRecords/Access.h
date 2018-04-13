#ifndef H_ACCESS
#define H_ACCESS

#include "../SymbolTable/Symbol.h"
#include "../IR/Temp.h"
#include "../IR/IExp.h"
#include <string>

//class IRTree;

namespace AR {

	enum T_RecordsType {
		RT_Formal,
		RT_Local,
		RT_FramePointer,
		RT_StackPointer,
		RT_AddressExit,
		RT_AddressReturnValue
	};

	enum T_VariableType {
		VT_Int,
		VT_IntArray,
		VT_Short,
		VT_ShortArray,
		VT_Boolean,
		VT_UserClass
	};

	class IAccess {

	public:
		virtual ~IAccess() {}
		virtual const T_RecordsType get_type() = 0;
		virtual const int get_size() const = 0;
		//virtual void print(const Temp* fp) const = 0;
		virtual const IExp* get_exp(IRTree& tree, const Temp framePtr) const = 0;
	};

}

#endif //H_ACCESS
