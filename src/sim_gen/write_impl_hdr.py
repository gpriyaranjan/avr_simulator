import logging
from typing import Dict, List, Tuple

from gen_common import (
    read_json_file,
    HeaderFile,
    camel_case,
    FuncSpec,
    WrapperCommon
)
from pattern import Pattern
from src.sim_gen.pattern import ArgBitsInfo


class ImplHdrFile(HeaderFile, WrapperCommon):

    def gen_includes(self):
        self.fprintln('#include "../infra/types.h"')

    def gen_forward_classes(self):
        self.fprintln("class Environ;")

    def gen_func_args(self, func_spec: FuncSpec)->List[Tuple[str,str]]:

        bit_counts: ArgBitsInfo = Pattern(func_spec.P).get_arg_bits_info()
        res: List[Tuple[str,str]] = []
        for ch, bit_info in bit_counts.get_items():
            bc: int = bit_info.count
            arg_type, arg_name = WrapperCommon.gen_func_arg(ch, bc)
            res.append((arg_type, arg_name),)
        return res


    def gen_func(self, func_name: str, func_spec: FuncSpec):
        def juxtapose(x:Tuple[str, str])->str:
            return x[0] + " " + x[1]

        func_args: List[Tuple[str,str]] = self.gen_func_args(func_spec)
        args: List[Tuple[str,str]] = [("Environ&", "env")] + func_args
        args_list: List[str] = list(map(lambda x: x[0] + " " + x[1], args))
        args_str: str = ", ".join(args_list)
        self.fprintln("\tstatic void %s(%s);" % (func_name, args_str))


    def gen_class(self, module_name: str, spec_json: Dict[str,Dict]):
        class_name: str = "%sImpl" % camel_case(module_name)
        self.write_class_prefix(class_name)

        for (func_name, func_spec) in spec_json.items():
            self.gen_func(func_name, FuncSpec(func_spec))
            self.blankline()

        self.write_class_suffix()


    def gen_file_body(self, module_name: str, spec_json: Dict[str,Dict]):
        self.write_file_header("%s_IMPL" % module_name)
        self.blankline()
        self.gen_includes()
        self.blankline()
        self.gen_forward_classes()
        self.blankline()
        self.gen_class(module_name, spec_json)
        self.blankline()
        self.write_file_trailer("%s_IMPL" % module_name)


    def gen_file(self, module_name: str, module_file: str, out_file: str):
        logging.info("Generating ImpHdr logs for %s from %s and writing to %s"
                     % (module_name, module_file, out_file))
        self.open_writer(out_file)
        spec_json: Dict[str,Dict[str,str]] = read_json_file(module_file)
        self.gen_file_body(module_name, spec_json)
        self.close_writer()
        logging.info("Generated ImplHdr file")

if __name__ == "__main__":
    ImplHdrFile().gen_file(
        "alu_ops", "specs/alu_ops.json", "out/alu_ops_impl.h")
