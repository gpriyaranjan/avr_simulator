cmake_minimum_required(VERSION 3.26)
project(ATMegaSim_sim)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES
        alu_ops.cpp
        environment.cpp
        log_ops.cpp
        sreg_ops.cpp
        branch_ops.cpp
        call_ops.cpp
        xfer_ops.cpp
        io_ops.cpp

        alu_ops_mc.cpp
        branch_ops_mc.cpp
        call_ops_mc.cpp
        io_ops_mc.cpp
)

set(HEADER_FILES
        alu_ops.h
        environment.h
        decoder.h
        types.h
        log_ops.h
        sreg_ops.h
        all_ops.h
        branch_ops.h
        status_reg.h
        regs_mems.h
        call_ops.h
        instructions.h
        exceptions.h
        xfer_ops.h
        io_ops.h

        alu_ops_mc.h
        branch_ops_mc.h
        call_ops_mc.h
        io_ops_mc.h
        log_ops_mc.cpp
        log_ops_mc.h
        sreg_ops_mc.cpp
        sreg_ops_mc.h
        xfer_ops_mc.cpp
        xfer_ops_mc.h
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