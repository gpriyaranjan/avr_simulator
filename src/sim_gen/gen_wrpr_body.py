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

    @classmethod
    def gen_includes(cls, module_name: str):
        print('#include "%s.h"' % module_name)

    @classmethod
    def gen_forward_classes(cls):
        print('class Environ;')

    @classmethod
    def prepare_impl_args(cls, func_spec:FuncSpec):
        bitsInfo : BitsInfo = Pattern.get_bit_counts(func_spec.P)
        for ch, bitInfo in bitsInfo.__dict__.items():
            arg_type, arg_name = WrapperCommon.gen(ch, bitInfo.count)
            arg_init_expr = BitRangesExpr.gen(
                "instrn", func_spec.instrn_size(), bitInfo.pos)
            print("\t%s %s = %s;" % (arg_type, arg_name, arg_init_expr))

    @classmethod
    def make_impl_call(cls, wrapper_name: str, func_name: str, func_spec: FuncSpec):
        impl_class_name: str = "%sMc" % wrapper_name
        bitsInfo : BitsInfo = Pattern.get_bit_counts(func_spec.P)
        arg_names: List[str] = []
        for ch, bitInfo in bitsInfo.__dict__.items():
            _, arg_name = WrapperCommon.gen(ch, bitInfo.count)
            arg_names.append(arg_name)
        args_str: str = ", ".join(arg_names)
        print("\t%s::%s(env, %s);" % (impl_class_name, func_name, args_str))

    @classmethod
    def gen_func(cls, wrapper_name: str, func_name: str, func_spec: FuncSpec):
        instrn_defn: str = (
            "LongInstrn" if func_spec.is_long_instrn() else "ShortInstrn")
        print("void %s::%s(Environ& env, %s instrn) {" % (wrapper_name, func_name, instrn_defn))
        cls.prepare_impl_args(func_spec)
        cls.make_impl_call(wrapper_name, func_name, func_spec)
        print("}")

    @classmethod
    def gen_funcs(cls, module_name: str, spec_json: Dict[str,Dict]):
        wrapper_name = camel_case(module_name)
        for (func_name, func_spec) in spec_json.items():
            cls.gen_func(wrapper_name, func_name, FuncSpec(func_spec))
            cls.gen_newline()

    @classmethod
    def gen_file_body(cls, module_name: str, spec_json: Dict[str,Dict]):
        cls.gen_includes(module_name)
        cls.gen_newline()
        cls.gen_forward_classes()
        cls.gen_newline()
        cls.gen_funcs(module_name, spec_json)

    @classmethod
    def gen_file(cls, module_name: str, module_file: str):
        spec_json: Dict[str,Dict[str,str]] = read_json_file(module_file)
        cls.gen_file_body(module_name, spec_json)

if __name__ == "__main__":
    WrapperBodyFile.gen_file("alu_ops", "info_alu_ops.json")
