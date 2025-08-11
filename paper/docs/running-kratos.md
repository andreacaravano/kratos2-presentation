# Running Kratos

## Property verification

* Basic usage: `./kratos -stage=mc PROGRAM.k2`
  The above works only if `PROGRAM.k2` contains only a single property.
  If multiple properties are present,
  the target for verification should be selected by specifying
  `-error_id=TARGET` (for reachability)
  or `-live_id=TARGET` (for liveness).

* For counterexample generation, add `-cex_type=path`,
  and possibly `-cex_output_file=FILENAME`

* The verification engine can be selected with `-model_checking_engine=ENGINE`.
  Note that not all the engines support all the theories, and some engines might only support reachability properties.

## Benchmark generation

* Use: `./kratos -stage=trans -trans_output_format=FORMAT -output_file=FILENAME PROGRAM.k2`
  to convert imperative programs to symbolic transition systems or CHCs.
  Note that not all formats support all features of K2.

## Symbolic execution

* To run the symbolic execution engine, use: `./kratos -stage=symexec -error_id=TARGET PROGRAM.k2`.
  Only reachability properties are supported.

## Additional options

* See `./kratos -help` to get a list of all the available options.