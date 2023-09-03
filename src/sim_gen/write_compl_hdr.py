import logging
from typing import Dict, Tuple, List
from gen_common import HeaderFile, camel_case, FuncSpec, WrapperCommon, SpecCommon
from pattern import Pattern, ArgBitInfo


class CompilerHdrFile(HeaderFile):

    def gen_includes(self):
        self.write_include_files(["../infra/types.h"])

    def write_impl_func(self, func_name: str, func_spec: FuncSpec):

        pattern: Pattern = func_spec.pattern
        args: List[Tuple[str,str]] = WrapperCommon.gen_func_args(pattern)

        ret_type: str = "LongInstrn" if func_spec.pattern.is_long_instrn() else "ShortInstrn"
        self.write_func_header(ret_type, func_name, args, indent=1)

    def gen_struct(self, module_name: str, spec_json: Dict[str,Dict[str,str]]):
        class_name: str = camel_case(module_name)
        self.write_class_prefix(class_name)

        for (func_name, func_spec) in spec_json.items():
            self.write_impl_func(func_name, FuncSpec(func_spec))
            self.blankline()

        self.write_class_suffix()

    def gen_file_body(self, module_name: str, spec_json: Dict[str,Dict]):
        self.write_file_header(module_name)
        self.blankline()
        self.gen_includes()
        self.blankline()
        # self.gen_forward_classes()
        self.blankline()
        self.gen_struct(module_name, spec_json)
        self.blankline()
        self.write_file_trailer(module_name)

    def gen_file(self, module_name: str, module_file: str, out_file: str):
        logging.info("Generating CmplHdr logs for %s from %s and writing to %s"
                         % (module_name, module_file, out_file))
        self.out_fp = open(out_file, "w+")
        spec_json: Dict[str,Dict[str,str]] = SpecCommon.read_json_file(module_file)
        class_mod_name = "%s_cmpl" % module_name
        self.gen_file_body(class_mod_name, spec_json)
        self.out_fp.close()
        logging.info("Generated CmplHdr file")
