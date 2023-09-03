import logging
from typing import Dict, List, Tuple

from gen_common import SpecCommon, camel_case, FuncSpec, WrapperCommon, CppFile
from pattern import Pattern, ArgBitsInfo, ArgBitRangesExpr


class CompilerCppFile(CppFile):

    def gen_includes(self, mod_class_name: str):
        self.write_include_files([
            "../infra/types.h",
            "instrns.h",
            "%s.h" % mod_class_name
        ])

    def prepare_impl_args(self, ret_var: str, pattern: Pattern):
        bitsInfo : ArgBitsInfo = pattern.get_arg_bits_info()
        for ch, bitInfo in bitsInfo.__dict__.items():
            arg_type, arg_name = WrapperCommon.gen_func_arg(ch, bitInfo.count)
            arg_init_expr = ArgBitRangesExpr.gen_insertion(
                arg_name, pattern.instrn_size(), bitInfo.pos)
            self.fprintln(f"\t{ret_var} = ${ret_var} | ${arg_init_expr};")


    def gen_func(self, wrapper_name: str, func_name: str, func_spec: FuncSpec):

        pattern: Pattern = func_spec.pattern
        args: List[Tuple[str,str]] = WrapperCommon.gen_func_args(pattern)

        ret_type: str = "LongInstrn" if func_spec.pattern.is_long_instrn() else "ShortInstrn"
        self.write_func_body_hdr(ret_type, wrapper_name, func_name, args)

        ret_var: str = "instrn"
        self.fprintln(f"\t{ret_type} {ret_var} = InstrnMask::{func_name};")

        self.prepare_impl_args(ret_var, pattern)
        self.fprintln(f"\treturn {ret_var};")
        self.fprintln("}")


    def gen_funcs(self, module_name: str, spec_json: Dict[str,Dict]):
        wrapper_name = camel_case(module_name)
        for (func_name, func_spec) in spec_json.items():
            self.gen_func(wrapper_name, func_name, FuncSpec(func_spec))
            self.fprintln()

    def gen_file_body(self, mod_class_name: str, spec_json: Dict[str,Dict]):
        self.gen_includes(mod_class_name)
        self.blankline()
        # self.gen_forward_classes()
        self.blankline()
        self.gen_funcs(mod_class_name, spec_json)

    def gen_file(self, module_name: str, module_file: str, out_file: str):
        logging.info("Generating CmplCpp logs for %s from %s and writing to %s"
                     % (module_name, module_file, out_file))
        self.out_fp = open(out_file, "w+")
        spec_json: Dict[str,Dict[str,str]] = SpecCommon.read_json_file(module_file)
        class_mod_name = f"{module_name}_cmpl"
        self.gen_file_body(class_mod_name, spec_json)
        self.out_fp.close()
        logging.info("Generated CmplCpp file")
