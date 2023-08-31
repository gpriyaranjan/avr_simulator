cmake_minimum_required(VERSION 3.26)
project(ATMegaSim_sim)

set(CMAKE_CXX_STANDARD 23)

set(GEN_CPP_FILES
    v1/alu_ops.cpp
    v1/logic_ops.cpp
    v1/sreg_ops.cpp
    v1/branch_ops.cpp
    v1/call_ops.cpp
    v1/xfer_ops.cpp
    v1/io_ops.cpp
)

set(PRJ_CPP_FILES
    alu_ops_impl.cpp
    branch_ops_impl.cpp
    call_ops_impl.cpp
    io_ops_impl.cpp
    log_ops_impl.cpp
    sreg_ops_impl.cpp
    xfer_ops_impl.cpp
)

set(GEN_HDR_FILES
    v1/alu_ops.h
    v1/branch_ops.h
    v1/call_ops.h
    v1/io_ops.h
    v1/logic_ops.h
    v1/sreg_ops.h
    v1/xfer_ops.h
)

set(GEN_HDR_IMPL_FILES
    v1/alu_ops_impl.h
    v1/branch_ops_impl.h
    v1/call_ops_impl.h
    v1/io_ops_impl.h
    v1/logic_ops_impl.h
    v1/sreg_ops_impl.h
    v1/xfer_ops_impl.h
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
    ${PRJ_CPP_FILES}
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