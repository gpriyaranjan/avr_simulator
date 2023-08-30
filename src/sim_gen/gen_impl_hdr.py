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

    def gen_func_args(self, func_spec: FuncSpec)->List[Tuple[str,str]]:

        bit_counts: BitsInfo = Pattern.get_bit_counts(func_spec.P)
        res: List[Tuple[str,str]] = []
        for ch, bit_info in bit_counts.__dict__.items():
            bc: int = bit_info.count
            arg_type, arg_name = WrapperCommon.gen(ch, bc)
            res.append((arg_type, arg_name),)
        return res


    def gen_func(self, func_name: str, func_spec: FuncSpec):
        def juxtapose(x:Tuple[str, str])->str:
            return x[0] + " " + x[1]

        func_args: List[Tuple[str,str]] = self.gen_func_args(func_spec)
        args: List[Tuple[str,str]] = [("Environ&", "env")] + func_args
        args_list: List[str] = list(map(lambda x: x[0] + " " + x[1], args))
        args_str: str = ", ".join(args_list)
        self.fprint("\tvoid %s(%s);" % (func_name, args_str))


    def gen_struct(self, module_name: str, spec_json: Dict[str,Dict]):
        class_name: str = "%sImpl" % camel_case(module_name)
        self.fprint("class %s {\n" % class_name)
        for (func_name, func_spec) in spec_json.items():
            self.gen_func(func_name, FuncSpec(func_spec))
            self.gen_newline()
        self.fprint("};")


    def gen_file_body(self, module_name: str, spec_json: Dict[str,Dict]):
        self.gen_file_header(module_name)
        self.gen_newline()
        self.gen_struct(module_name, spec_json)
        self.gen_newline()
        self.gen_file_trailer(module_name)


    def gen_file(self, module_name: str, module_file: str, hdr_file: str):
        self.out_fp = open(hdr_file, "w")
        spec_json: Dict[str,Dict[str,str]] = read_json_file(module_file)
        self.gen_file_body(module_name, spec_json)
        self.out_fp.close()

if __name__ == "__main__":
    ImplHdrFile().gen_file(
        "alu_ops", "specs/alu_ops.json", "out/alu_ops_impl.h")
