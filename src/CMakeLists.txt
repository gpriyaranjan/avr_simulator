cmake_minimum_required(VERSION 3.26)
project(ATMegaSim_src)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES
        simulation/alu_ops.cpp
        simulation/environment.cpp
        simulation/log_ops.cpp
        simulation/sreg_ops.cpp
        simulation/branch_ops.cpp
        simulation/call_ops.cpp
)

set(HEADER_FILES
        simulation/alu_ops.h
        simulation/environment.h
        simulation/decoder.h
        simulation/types.h
        simulation/log_ops.h
        simulation/sreg_ops.h
        simulation/all_ops.h
        simulation/branch_ops.h
        simulation/status_reg.h
        simulation/regs_mems.h
        utils/bitset_wrappers.h
        simulation/call_ops.h
        utils/hash_map.h
        simulation/instructions.h
        sim_gen/instrn_info.h
        sim_gen/sim_gen.h
)

add_library(
        ATMegaSim_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

target_link_libraries(ATMegaSim_lib)
add_executable(
        ATMegaSim main.cpp
)