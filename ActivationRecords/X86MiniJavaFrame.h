
#ifndef H_X86
#define H_X86


#include <assert.h>
#include <unordered_map> 
#include <vector>
#include <string>

#include "Frame.h"
#include "Access.h"
#include "../SymbolTable/Symbol.h"
#include "InRegAccess.h"
#include "InFrameAccess.h"

namespace AR {

	class X86MiniJavaFrame : public IFrame {
		/*
		 * LocalAddress = access address + FP
		 * FormalAddress = access address or regIndex
		 */
	public:
		static const int WORD_SIZE = 4;

		virtual void AddFormal(const VariableInfo& name) override;
		virtual void AddLocal(const VariableInfo& name) override;
		
		virtual void AddAddressExit() override;
		virtual void AddAddressReturnValue() override;
		
		virtual int FormalsCount() const override;
		
		virtual const IAccess* Formal(int index) const override;

		virtual std::pair<bool, const IAccess*> CheckLocalOrFormal(const SymbolTable::Symbol* _name) const override;
		
		virtual const IAccess* ExitAddress() const override;
		virtual const IAccess* ReturnAddress() const override;
		
		const int FormalSize(int index) const;
		const int FormalSize(const Symbol* name) const;
				
		virtual const Temp FP() const override;

	private:

		std::vector<IAccess*> formalList;
		std::unordered_map<const SymbolTable::Symbol*, IAccess*> formalAccess;
		std::unordered_map<const SymbolTable::Symbol*, IAccess*> localAccess;
		
		int addressExitIndex;
		int addressReturnValueIndex;
		
		int formalTopPointer = 0;
		int localTopPointer = 0;

		Temp fp = Temp("fp");

		IAccess* createFormal(T_RecordsType type, T_VariableType vartype, int size);
		IAccess* createLocal(int size, T_VariableType _varType);
	};
}

#endif