#ifndef ATMEGASIM_SRC_ALL_OPS_H
#define ATMEGASIM_SRC_ALL_OPS_H

#include "v1/alu_ops.h"
#include "v1/logic_ops.h"
#include "v1/sreg_ops.h"
#include "v1/branch_ops.h"
#include "v1/call_ops.h"
#include "v1/xfer_ops.h"

class AllOps : public
        AluOps,
        LogicOps,
        SRegOps,
        BranchOps,
        CallOps,
        XferOps
        {
};

#endif //ATMEGASIM_SRC_ALL_OPS_H
