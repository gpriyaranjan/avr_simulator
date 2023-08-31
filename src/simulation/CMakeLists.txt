cmake_minimum_required(VERSION 3.26)
project(ATMegaSim_sim)

set(CMAKE_CXX_STANDARD 23)

set(GEN_CPP_FILES
    gen1/alu_ops.cpp
    gen1/logic_ops.cpp
    gen1/sreg_ops.cpp
    gen1/branch_ops.cpp
    gen1/call_ops.cpp
    gen1/xfer_ops.cpp
    gen1/io_ops.cpp
)

set(PRJ_CPP_FILES
    ops/alu_ops_impl.cpp
    ops/branch_ops_impl.cpp
    ops/call_ops_impl.cpp
    ops/io_ops_impl.cpp
    ops/log_ops_impl.cpp
    ops/sreg_ops_impl.cpp
    ops/xfer_ops_impl.cpp
)

set(GEN_HDR_FILES
    gen1/alu_ops.h
    gen1/branch_ops.h
    gen1/call_ops.h
    gen1/io_ops.h
    gen1/logic_ops.h
    gen1/sreg_ops.h
    gen1/xfer_ops.h
)

set(GEN_HDR_IMPL_FILES
    gen1/alu_ops_impl.h
    gen1/branch_ops_impl.h
    gen1/call_ops_impl.h
    gen1/io_ops_impl.h
    gen1/logic_ops_impl.h
    gen1/sreg_ops_impl.h
    gen1/xfer_ops_impl.h
)

set(PRJ_HDR_FILES
    environment.h
    decoder.h
    types.h
    all_ops.h
    status_reg.h
    regs_mems.h
    instructions.h
    exceptions.h
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