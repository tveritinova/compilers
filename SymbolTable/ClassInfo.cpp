#include "ClassInfo.h"    

void ClassInfo::add_method(const MethodInfo* method_info) {
    methods.push_back(std::make_pair(method_info->get_method_id(), method_info));
}

void ClassInfo::add_field(const VariableInfo* variable_info) {
    fields.push_back(std::make_pair(variable_info->get_id(), variable_info));
}

bool ClassInfo::has_method(const Symbol* method_id) const {
	int cnt = 0;

	for (auto p: methods) {
		if (p.first == method_id) {
			++cnt;
		}
	}

    return cnt == 1;
}

bool ClassInfo::has_field(const Symbol* var_id) const {
	int cnt = 0;

	for (auto p: fields) {
		if (p.first == var_id) {
			++cnt;
		}
	}

    return cnt == 1;
}