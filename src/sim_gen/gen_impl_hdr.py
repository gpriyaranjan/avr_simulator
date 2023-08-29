from typing import Dict, List, Tuple

from gen_common import (
    read_json_file,
    HeaderFile,
    camel_case,
    FuncSpec,
    WrapperCommon
)
from pattern_utils import Pattern, BitsInfo


class ImplHdrFile(HeaderFile, WrapperCommon):

    @classmethod
    def gen_func_args(cls, func_spec: FuncSpec)->List[Tuple[str,str]]:

        bit_counts: BitsInfo = Pattern.get_bit_counts(func_spec.P)
        res: List[Tuple[str,str]] = []
        for ch, bit_info in bit_counts.__dict__.items():
            bc: int = bit_info.count
            arg_type, arg_name = WrapperCommon.gen(ch, bc)
            res.append((arg_type, arg_name),)
        return res

    @classmethod
    def gen_func(cls, func_name: str, func_spec: FuncSpec):
        def juxtapose(x:Tuple[str, str])->str:
            return x[0] + " " + x[1]

        func_args: List[Tuple[str,str]] = cls.gen_func_args(func_spec)
        args: List[Tuple[str,str]] = [("Environ&", "env")] + func_args
        args_list: List[str] = list(map(lambda x: x[0] + " " + x[1], args))
        args_str: str = ", ".join(args_list)
        print("\tvoid %s(%s);" % (func_name, args_str))

    @classmethod
    def gen_struct(cls, module_name: str, spec_json: Dict[str,Dict]):
        class_name: str = "%sImpl" % camel_case(module_name)
        print("class %s {" % class_name)
        for (func_name, func_spec) in spec_json.items():
            cls.gen_func(func_name, FuncSpec(func_spec))
            cls.gen_newline()
        print("};")

    @classmethod
    def gen_file_body(cls, module_name: str, spec_json: Dict[str,Dict]):
        cls.gen_file_header(module_name)
        cls.gen_newline()
        cls.gen_struct(module_name, spec_json)
        cls.gen_newline()
        cls.gen_file_trailer(module_name)

    @classmethod
    def gen_file(cls, module_name: str, module_file: str):
        spec_json: Dict[str,Dict[str,str]] = read_json_file(module_file)
        cls.gen_file_body(module_name, spec_json)

if __name__ == "__main__":
    ImplHdrFile.gen_file("alu_ops", "info_alu_ops.json")
