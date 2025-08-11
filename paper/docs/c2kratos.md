The C to K2 Frontend
====================

The support for programs written in C is provided by the `c2kratos` frontend.
The tool is written in Python, and requires the [`pycparser`](https://pypi.org/project/pycparser/) module
and a C preprocessor compatible with [GNU CPP](https://gcc.gnu.org/onlinedocs/cpp/)
(or alternatively, the installation of the Python [`pcpp`](https://pypi.org/project/pcpp/) module).

`c2kratos` comes with many options that allow to fine-tune its behaviour. The easiest way to run it is to use its [SV-COMP](https://sv-comp.sosy-lab.org/) compatibility mode:

```
  $ python c2kratos.py --svcomp --svcomp-spec SPECFILE -o PROGRAM.k2 PROGRAM.c
```

For more options, see `c2kratos.py --help`.