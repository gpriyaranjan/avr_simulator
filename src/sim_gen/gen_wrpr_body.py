import logging
from typing import Dict, List

from gen_common import (
    AnyFile,
    read_json_file,
    camel_case,
    FuncSpec,
    WrapperCommon
)
from pattern_utils import BitsInfo, Pattern, BitInfo, BitRangesExpr


class WrapperBodyFile(AnyFile):

    def gen_includes(self, module_name: str):
        self.fprint('#include "%s.h"' % module_name)
        self.fprint('#include "%s_impl.h"' % module_name)

    def gen_forward_classes(self):
        self.fprint('class Environ;')

    def prepare_impl_args(self, func_spec:FuncSpec):
        bitsInfo : BitsInfo = Pattern.get_bit_counts(func_spec.P)
        for ch, bitInfo in bitsInfo.__dict__.items():
            arg_type, arg_name = WrapperCommon.gen(ch, bitInfo.count)
            arg_init_expr = BitRangesExpr.gen(
                "instrn", func_spec.instrn_size(), bitInfo.pos)
            self.fprint("\t%s %s = %s;" % (arg_type, arg_name, arg_init_expr))

    def make_impl_call(self, wrapper_name: str, func_name: str, func_spec: FuncSpec):
        impl_class_name: str = "%sImpl" % wrapper_name
        bitsInfo : BitsInfo = Pattern.get_bit_counts(func_spec.P)
        arg_names: List[str] = []
        for ch, bitInfo in bitsInfo.__dict__.items():
            _, arg_name = WrapperCommon.gen(ch, bitInfo.count)
            arg_names.append(arg_name)
        args_str: str = ", ".join(["env"] + arg_names)
        self.fprint("\t%s::%s(%s);" % (impl_class_name, func_name, args_str))

    def gen_func(self, wrapper_name: str, func_name: str, func_spec: FuncSpec):
        instrn_defn: str = (
            "LongInstrn" if func_spec.is_long_instrn() else "ShortInstrn")
        self.fprint("void %s::%s(Environ& env, %s instrn) {" % (wrapper_name, func_name, instrn_defn))
        self.prepare_impl_args(func_spec)
        self.make_impl_call(wrapper_name, func_name, func_spec)
        self.fprint("}")

    def gen_funcs(self, module_name: str, spec_json: Dict[str,Dict]):
        wrapper_name = camel_case(module_name)
        for (func_name, func_spec) in spec_json.items():
            self.gen_func(wrapper_name, func_name, FuncSpec(func_spec))
            self.gen_newline()

    def gen_file_body(self, module_name: str, spec_json: Dict[str,Dict]):
        self.gen_includes(module_name)
        self.gen_newline()
        self.gen_forward_classes()
        self.gen_newline()
        self.gen_funcs(module_name, spec_json)

    def gen_file(self, module_name: str, module_file: str, hdr_file: str):
        logging.info("Generating WrapCpp logs for %s from %s and writing to %s"
                     % (module_name, module_file, hdr_file))
        self.out_fp = open(hdr_file, "w")
        spec_json: Dict[str,Dict[str,str]] = read_json_file(module_file)
        self.gen_file_body(module_name, spec_json)
        self.out_fp.close()
        logging.info("Generated WrapCpp file")

if __name__ == "__main__":
    WrapperBodyFile().gen_file("alu_ops", "specs/alu_ops.json", "out/alu_ops.cpp")
