import logging
from typing import Dict, List, Tuple

from gen_common import (
    CppFile,
    SpecCommon,
    camel_case,
    FuncSpec,
    WrapperCommon
)
from pattern import Pattern
from src.sim_gen.pattern import ArgBitInfo, ArgBitsInfo, ArgBitRangesExpr


class WrapperBodyFile(CppFile):

    def gen_includes(self, module_name: str):
        self.fprintln('#include "%s.h"' % module_name)
        self.fprintln('#include "%s_impl.h"' % module_name)

    def gen_forward_classes(self):
        self.fprintln('class Environ;')

    def prepare_impl_args(self, func_spec:FuncSpec):

        bitsInfo : ArgBitsInfo = func_spec.pattern.get_arg_bits_info()

        for ch, bitInfo in bitsInfo.__dict__.items():
            arg_type, arg_name = WrapperCommon.gen_func_arg(ch, bitInfo.count)
            arg_init_expr = ArgBitRangesExpr.gen_extraction(
                "instrn", func_spec.pattern.instrn_size(), bitInfo.pos)
            self.fprintln("\t%s %s = %s;" % (arg_type, arg_name, arg_init_expr))

    def make_impl_call(self, wrapper_name: str, func_name: str, func_spec: FuncSpec):
        impl_class_name: str = "%sImpl" % wrapper_name
        bitsInfo : ArgBitsInfo = Pattern(func_spec.P).get_arg_bits_info()
        arg_names: List[str] = []
        for ch, bitInfo in bitsInfo.get_items():
            _, arg_name = WrapperCommon.gen_func_arg(ch, bitInfo.count)
            arg_names.append(arg_name)
        args_str: str = ", ".join(["env"] + arg_names)
        self.fprintln("\t%s::%s(%s);" % (impl_class_name, func_name, args_str))

    def gen_func(self, wrapper_name: str, func_name: str, func_spec: FuncSpec):
        instrn_type: str = (
            "LongInstrn" if func_spec.pattern.is_long_instrn() else "ShortInstrn")

        args: List[Tuple[str,str]] = [("Environ&", "env"), (instrn_type, "instrn")]
        self.write_func_body_hdr("void", wrapper_name, func_name, args)
        self.prepare_impl_args(func_spec)
        self.make_impl_call(wrapper_name, func_name, func_spec)
        self.fprintln("}")

    def gen_funcs(self, module_name: str, spec_json: Dict[str,Dict]):
        wrapper_name = camel_case(module_name)
        for (func_name, func_spec) in spec_json.items():
            self.gen_func(wrapper_name, func_name, FuncSpec(func_spec))
            self.blankline()

    def gen_file_body(self, module_name: str, spec_json: Dict[str,Dict]):
        self.gen_includes(module_name)
        self.blankline()
        self.gen_forward_classes()
        self.blankline()
        self.gen_funcs(module_name, spec_json)

    def gen_file(self, module_name: str, module_file: str, hdr_file: str):
        logging.info("Generating WrapCpp logs for %s from %s and writing to %s"
                     % (module_name, module_file, hdr_file))
        self.out_fp = open(hdr_file, "w")
        spec_json: Dict[str,Dict[str,str]] = SpecCommon.read_json_file(module_file)
        self.gen_file_body(module_name, spec_json)
        self.out_fp.close()
        logging.info("Generated WrapCpp file")

if __name__ == "__main__":
    WrapperBodyFile().gen_file("alu_ops", "specs/alu_ops.json", "out/alu_ops.cpp")
