import logging
from typing import Dict

from gen_common import (
    HeaderFile,
    read_json_file,
    camel_case, FuncSpec
)

class WrapperHdrFile(HeaderFile):

    def gen_includes(self):
        self.fprint('#include "../infra/types.h"')

    def gen_forward_classes(self):
        self.fprint("class Environ;")

    def gen_func_from_spec(self, func_name: str, func_spec: FuncSpec):
        instrn_defn: str = (
            "LongInstrn" if func_spec.is_long_instrn() else "ShortInstrn")
        self.fprint("\tstatic void %s(Environ& env, %s instrn);" %
                    (func_name, instrn_defn) )


    def gen_struct(self, module_name: str, spec_json: Dict[str,Dict]):
        class_name: str = camel_case(module_name)
        self.gen_class_prefix(class_name)

        for (func_name, func_spec) in spec_json.items():
            self.gen_func_from_spec(func_name, FuncSpec(func_spec))
            self.gen_newline()

        self.gen_class_suffix()


    def gen_file_body(self, module_name: str, spec_json: Dict[str,Dict]):
        self.gen_file_header(module_name)
        self.gen_newline()
        self.gen_includes()
        self.gen_newline()
        self.gen_forward_classes()
        self.gen_newline()
        self.gen_struct(module_name, spec_json)
        self.gen_newline()
        self.gen_file_trailer(module_name)


    def gen_file(self, module_name: str, module_file: str, out_file: str):
        logging.info("Generating WrapHdr logs for %s from %s and writing to %s"
                     % (module_name, module_file, out_file))
        self.out_fp = open(out_file, "w+")
        spec_json: Dict[str,Dict[str,str]] = read_json_file(module_file)
        self.gen_file_body(module_name, spec_json)
        self.out_fp.close()
        logging.info("Generated WrapHdr file")

if __name__ == "__main__":
    WrapperHdrFile().gen_file("alu_ops", "specs/alu_ops.json", "out/alu_ops.h")
