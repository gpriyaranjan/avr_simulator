cmake_minimum_required(VERSION 3.26)
project(ATMegaSim_sim)
set(CMAKE_CXX_STANDARD 23)

set(GEN_DIR "gen2")

set(GEN_CPP_FILES
    ${GEN_DIR}/alu_ops.cpp
    ${GEN_DIR}/logic_ops.cpp
    ${GEN_DIR}/sreg_ops.cpp
    ${GEN_DIR}/branch_ops.cpp
    ${GEN_DIR}/call_ops.cpp
    ${GEN_DIR}/xfer_ops.cpp
    ${GEN_DIR}/io_ops.cpp
    ${GEN_DIR}/instrns.cpp
    ${GEN_DIR}/all_ops.cpp
)

set(PRJ_CPP_FILES
    ops/alu_ops_impl.cpp
    ops/branch_ops_impl.cpp
    ops/call_ops_impl.cpp
    ops/io_ops_impl.cpp
    ops/logic_ops_impl.cpp
    ops/sreg_ops_impl.cpp
    ops/xfer_ops_impl.cpp
)

set(GEN_HDR_FILES
    ${GEN_DIR}/instrns.h
    ${GEN_DIR}/alu_ops.h
    ${GEN_DIR}/branch_ops.h
    ${GEN_DIR}/call_ops.h
    ${GEN_DIR}/io_ops.h
    ${GEN_DIR}/logic_ops.h
    ${GEN_DIR}/sreg_ops.h
    ${GEN_DIR}/xfer_ops.h
    ${GEN_DIR}/all_ops.cpp
)

set(GEN_HDR_IMPL_FILES
    ${GEN_DIR}/alu_ops_impl.h
    ${GEN_DIR}/branch_ops_impl.h
    ${GEN_DIR}/call_ops_impl.h
    ${GEN_DIR}/io_ops_impl.h
    ${GEN_DIR}/logic_ops_impl.h
    ${GEN_DIR}/sreg_ops_impl.h
    ${GEN_DIR}/xfer_ops_impl.h

)

set(PRJ_HDR_FILES
    infra/environment.h
    infra/types.h
    ops/all_ops.h
    infra/status_reg.h
    infra/regs_mems.h
    infra/exceptions.h
    infra/control_unit.h
)

set(SOURCE_FILES
    ${GEN_CPP_FILES}
    ${PRJ_CPP_FILES}
)

set(HEADER_FILES
    ${GEN_HDR_FILES}
    ${GEN_HDR_IMPL_FILES}
    ${PRJ_HDR_FILES}
)

add_library(
    ATMegaSim_lib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(ATMegaSim_lib)
add_executable(
        ATMegaSim ../main.cpp
)