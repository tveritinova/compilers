#include "X86MiniJavaFrame.h"

namespace AR {

	static const int MAX_IN_REG = 4;

	static const char* const EXIT_ADDRESS_NAME = "@EXIT_ADDRESS@";
	static const char* const RETURN_ADDRESS_NAME = "@RETURN_ADDRESS@";

	static const int intSize = 1 * X86MiniJavaFrame::WORD_SIZE;
	static const int booleanSize = 1 * X86MiniJavaFrame::WORD_SIZE;
	static const int referenceSize = 1 * X86MiniJavaFrame::WORD_SIZE;

	int typeSize(const SymbolTable::Symbol* type) {

		if (type == Symbol::GetIntern("int"))
			return intSize;

		if (type == Symbol::GetIntern("int[]"))
			return intSize;

		if (type == Symbol::GetIntern("boolean"))
			return intSize;

		return referenceSize;
	}


	void X86MiniJavaFrame::AddFormal(const VariableInfo& var) {
		T_VariableType type = VT_UserClass;

		if (var.get_type() == Symbol::GetIntern("int"))
			type = VT_Int;

		if (var.get_type() == Symbol::GetIntern("int[]"))
			type = VT_IntArray;

		if (var.get_type() == Symbol::GetIntern("boolean"))
			type = VT_Boolean;


		IAccess* p = createFormal(T_RecordsType::RT_Formal, type, typeSize(var.get_type()));
		formalAccess.insert(std::make_pair(var.get_id(), p));
		formalList.push_back(p);

		std::cout << "111  added formal " << var.get_id()->String() << std::endl;
	}

	void X86MiniJavaFrame::AddLocal(const VariableInfo& var) {

		T_VariableType type = VT_UserClass;

		if (var.get_type() == Symbol::GetIntern("int"))
			type = VT_Int;

		if (var.get_type() == Symbol::GetIntern("int[]"))
			type = VT_IntArray;

		if (var.get_type() == Symbol::GetIntern("boolean"))
			type = VT_Boolean;

		IAccess* acc = createLocal(typeSize(var.get_type()),type);
		localAccess.insert(std::make_pair(var.get_id(), acc));

		std::cout << "111  added local " << var.get_id()->String() << std::endl;
	}

	void X86MiniJavaFrame::AddAddressExit() {
		IAccess* p = createFormal(T_RecordsType::RT_AddressExit, T_VariableType::VT_UserClass, referenceSize);
		formalAccess.insert(std::make_pair(Symbol::GetIntern(EXIT_ADDRESS_NAME), p));
		this->addressExitIndex = formalList.size();
		formalList.push_back(p);
	}

	void X86MiniJavaFrame::AddAddressReturnValue() {
		IAccess* p = createFormal(T_RecordsType::RT_AddressReturnValue, T_VariableType::VT_UserClass, referenceSize);
		formalAccess.insert(std::make_pair(SymbolTable::Symbol::GetIntern(RETURN_ADDRESS_NAME), p));
		this->addressReturnValueIndex = formalList.size();
		formalList.push_back(p);
	}

	int X86MiniJavaFrame::FormalsCount() const {
		return formalList.size();
	}

	const IAccess* X86MiniJavaFrame::Formal(int index) const {
		return formalList[index];
	}

	std::pair<bool, const IAccess*> X86MiniJavaFrame::CheckLocalOrFormal(const SymbolTable::Symbol* name) const {

		/*std::cout << "~~~ locals ~~~" << std::endl;
		for (auto it: localAccess) {
			std::cout << it.first->String();
			printf(" %p ", it.first);
			std::cout << std::endl;
		}

		std::cout << "~~~ formals ~~~" << std::endl;
		for (auto it: formalAccess) {
			std::cout << it.first->String();
			printf(" %p ", it.first);
			std::cout << std::endl;
		}

		std::cout << "to check " << name->String() << " ";
		printf(" %p ", name);
		std::cout << std::endl << std::endl;*/

		for (auto it: localAccess) {
			if (it.first == name) {
				return std::make_pair(true, it.second);
			}
		}

		for (auto it: formalAccess) {
			if (it.first == name) {
				return std::make_pair(false, it.second);
			}
		}

		assert(true);
		return std::make_pair(false, nullptr);
	}


	const IAccess* X86MiniJavaFrame::ExitAddress() const {
		return formalList[addressExitIndex];
	}

	const IAccess* X86MiniJavaFrame::ReturnAddress() const {
		return formalList[addressReturnValueIndex];
	}

	const int X86MiniJavaFrame::FormalSize(int index) const {
		return formalList[index]->get_size();
	}

	const int X86MiniJavaFrame::FormalSize(const SymbolTable::Symbol* name) const {
		auto res = formalAccess.find(name);
		assert(res != formalAccess.end());
		return res->second->get_size();
	}

	const Temp X86MiniJavaFrame::FP() const {
		//return new IRTree::Temp(formalTopPointer);
		return fp;
	}

	IAccess* X86MiniJavaFrame::createFormal(T_RecordsType type, T_VariableType _varType, int size) {

		if (formalList.size() < MAX_IN_REG) {
			return new InRegAccess(type, size, formalList.size());
		}
		else {
			IAccess* access = new InFrameAccess(type, _varType, size, -formalTopPointer-size, 0);
			formalTopPointer += size;
			return access;
		}
	}

	IAccess* X86MiniJavaFrame::createLocal(int size, T_VariableType _varType) {
		IAccess* access = new InFrameAccess(RT_Local, _varType, size, localTopPointer, 0);
		localTopPointer += size;
		return access;
	}

}