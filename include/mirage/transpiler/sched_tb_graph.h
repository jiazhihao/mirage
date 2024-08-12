#pragma once

#include <vector>

#include "mirage/transpiler/common.h"

namespace mirage {
namespace transpiler {

enum class tb_sched_node_t {
	OPERATOR,
	SYNCTHREADS
};

// A "node" in the final schedule
// A "schedule" is the execution order of all operators in a threadblock
// graph. It's important since it affects the number of `__syncthreads()` and
// the peak usage of shared mem.
class TBSchedNode {
public:
	tb_sched_node_t type;

	// The following fields are only valid if type == OPERATOR
	// We use a vector here since we may perform operator fusion
	std::vector<tb::TBOperator const*> ops;
};

// A schedule of a threadblock graph
class TBSched {
public:
	std::vector<TBSchedNode> pre_loop_nodes;	// Nodes before the for loop, e.g. reading input with forloop_dim = -1
	std::vector<TBSchedNode> loop_nodes;			// Nodes inside the for loop
	std::vector<TBSchedNode> post_loop_nodes;	// Nodes after the for loop
};

}
}