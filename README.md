Andrea Caravano - Alberto Cantele - Biagio Cancelliere

## Formal Methods for Concurrent and Real-time Systems: Kratos 2 tool presentation (M.Sc. Computer Science and Engineering, A.Y. 2024/25) - Politecnico di Milano (PoliMi)

Evaluated positively: 30L/30L on 09/05/2025

### License and publishing notes

See [license file](LICENSE)

### Brief description

This repository contains the final outcomes and the working files used to produce the `Kratos 2: an all-in-one C development companion` slideshow, presented in the context of the _Formal Methods for Concurrent and Real-time Systems_ course at Politecnico di Milano, on May 9, 2025, describing the [Kratos 2](https://kratos.fbk.eu/) software verification tool as part of the _student presentations project_.

As a result, the following artifacts can be freely inspected:

* [The paper](paper/cav23a.pdf) `Kratos 2: an SMT-Based Model Checker for Imperative Programs` and its related artifacts and code snippets, which have been the main work resource.
* [Some of the](presentation/sv-comp) _SV-COMP_ (Competition on Software Verification) tasks that have been used to outline the main features and inner workings of the tool. They are also part of the _benchmarking_ suite presented in the paper artifact, which also includes a [specific wrapper](paper/kratos-svcomp.py) for the execution of such tasks in a more organized way.
* The [development container](.devcontainer) specifically tailored to the Kratos 2's development cycle by the authors of this presentation: to prepare it, some of the indications provided by the [vm-preparation](paper/vm-preparation.md) document have been followed, alongside the main C and Python standard development requirements and tools.
* The [final presentation](presentation/complete.pdf) held on May 9, 2025, alongside its [resources](presentation/res), [demo](presentation/sv-comp/demo) and _LaTeX_ [presentation code](presentation/src).