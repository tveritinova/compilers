#ifndef H_FRAME
#define H_FRAME

#include "Access.h"
#include "../SymbolTable/VariableInfo.h"
#include "../SymbolTable/Symbol.h"

namespace AR {

	class IFrame {
		
	public:
		virtual ~IFrame() { }
		virtual void AddFormal(const VariableInfo& name) = 0;
		virtual void AddLocal(const VariableInfo& name) = 0;
		virtual void AddAddressExit() = 0;
		virtual void AddAddressReturnValue() = 0;
		virtual int FormalsCount() const = 0;
		virtual const IAccess* Formal(int index) const = 0;
		virtual std::pair<bool, const IAccess*> CheckLocalOrFormal(const SymbolTable::Symbol* _name) const = 0;
		virtual const IAccess* ExitAddress() const = 0;
		virtual const IAccess* ReturnAddress() const = 0;
		virtual const Temp FP() const = 0;
	};

}

#endif //H_FRAME