#ifndef H_IRTREE_OP
#define H_IRTREE_OP 

namespace IRTree_OP {
	enum OP_BIN { PLUS_, MINUS_, MULTIPLY_, AND_, LESS_, GREATER_, EQUAL_ };
	enum OP_COMPARE { EQ_, LT_, GT_ };

	inline std::string bin_to_string(OP_BIN operation) {

		switch (operation) {
		case OP_BIN::PLUS_: return "plus";
		case OP_BIN::MINUS_: return "minus";
		case OP_BIN::MULTIPLY_: return "mul";
		case OP_BIN::AND_: return "and";
		case OP_BIN::LESS_: return "less";
		case OP_BIN::GREATER_: return "greater";
		case OP_BIN::EQUAL_: return "eq";
		}
	}

	inline std::string compare_to_string(OP_COMPARE operation) {

		switch (operation) {
		case OP_COMPARE::EQ_: return "EQ";
		case OP_COMPARE::LT_: return "LT";
		case OP_COMPARE::GT_: return "GT";
		}
	}

	inline OP_COMPARE bin_to_compare(OP_BIN operation) {

		switch (operation) {
		case OP_BIN::LESS_: return OP_COMPARE::LT_;
		case OP_BIN::EQUAL_: return OP_COMPARE::EQ_;
		case OP_BIN::GREATER_: return OP_COMPARE::GT_;
		default: assert(true);
		}

		return OP_COMPARE::LT_;
	}
}

#endif