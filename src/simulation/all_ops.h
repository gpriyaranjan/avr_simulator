#ifndef ATMEGASIM_SRC_ALL_OPS_H
#define ATMEGASIM_SRC_ALL_OPS_H

#include "alu_ops.h"
#include "log_ops.h"
#include "sreg_ops.h"
#include "branch_ops.h"
#include "call_ops.h"
#include "xfer_ops.h"

class AllOps : public
        AluOps,
        LogOps,
        SRegOps,
        BranchOps,
        CallOps,
        XferOps
        {
};

#endif //ATMEGASIM_SRC_ALL_OPS_H
