#ifndef ATMEGASIM_SRC_ALL_OPS_H
#define ATMEGASIM_SRC_ALL_OPS_H

#include "../gen2/alu_ops.h"
#include "../gen2/logic_ops.h"
#include "../gen2/sreg_ops.h"
#include "../gen2/branch_ops.h"
#include "../gen2/call_ops.h"
#include "../gen2/xfer_ops.h"

class AllOps : public
        AluOps,
        LogicOps,
        SregOps,
        BranchOps,
        CallOps,
        XferOps
        {
};

#endif //ATMEGASIM_SRC_ALL_OPS_H
