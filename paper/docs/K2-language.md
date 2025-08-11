The K2 Language
===============

Kratos2 works on an intermediate verifiation language called K2,
with a semantic based on first-order logic and Satisfiability Modulo Theories.

K2 uses S-expressions for its concrete syntax.

## Types

* Booleans: `bool`;
* Integers: `int`;
* Reals: `real`;
* Signed bit-vectors: `(sbv SIZE)`,
  where `SIZE` is an integer representing the bit-width;
* Unsigned bit-vectors: `(ubv SIZE)`;
* IEEE Floating-point numbers: `(fp EXPONENT MANTISSA)`,
  where `EXPONENT` is the bit-width of the
  exponent, and `MANTISSA` is the bit-width of the mantissa (without the
  extra implicit 1);
* Maps: `(map INDEX ELEM)`, where `INDEX` is the type of the index and `ELEM` is the type of the element. (Maps correspond to arrays in the standard SMT-LIB theory);
* Enumeratives: `(enum VALUE_1 VALUE_2 ... VALUE_N)`, where `VALUE_i`'s are the enum values. (There is no ordering relation among the values);
* Functions: `(fun (ARG_1 ... ARG_N) (RET_1 ... RET_N))`, where `ARG_i` and `RET_i` are the types of the input parameters and return values.

## Expressions

* Variables: `(var NAME TYPE)`, where `NAME` is a symbol;
* Constants: `(const VALUE TYPE)`, where `VALUE` is a symbol of `TYPE` is a basic type, or an association list of `TYPE` is a map type;
* Type conversions: `(cast NEWTYPE EXPR)` and `(bitcast NEWTYPE EXPR)`,
  where `NEWTYPE` is a type and `EXPR` an expression.
  The actual semantics depends on both the source and destination types
  (not all combinations are supported);
* Logical operations:
  `(and EXPR_1 EXPR_2)`,
  `(or EXPR_1, EXPR_2)`,
  `(not EXPR)`;
* Bit-level operations (with bit-vector arguments):
  `(lshift EXPR_1 EXPR_2)`,
  `(rshift EXPR_1 EXPR_2)`,
  `(bitand EXPR_1 EXPR_2)`,
  `(bitor EXPR_1, EXPR_2)`,
  `(bitxor EXPR_1, EXPR_2)`,
  `(bitnot EXPR)`;
* Arithmetic operations (overloaded according to the operand types):
  `(add EXPR_1 EXPR_2)`,
  `(sub EXPR_1 EXPR_2)`,
  `(mul EXPR_1 EXPR_2)`,
  `(neg EXPR)`,
  `(div EXPR_1 EXPR_2)`,
  `(rem EXPR_1 EXPR_2)`,
  `(floor EXPR)`;
* Comparison operators:
  `(eq EXPR_1 EXPR_2)`,
  `(le EXPR_1 EXPR_2)`,
  `(lt EXPR_1 EXPR_2)`,
  `(ge EXPR_1 EXPR_2)`,
  `(gt EXPR_1 EXPR_2)`;
* IEEE floating-point predicates:
  `(isfinite EXPR)`,
  `(isinf EXPR)`,
  `(isnan EXPR)`,
  `(isnormal EXPR)`,
  `(issubnormal EXPR)`,
  `(iszero EXPR)`;
* Map operations:
  `(mapget MAP INDEX)`,
  returning the value of `MAP` at the given `INDEX`
  (corresponding to an array read in SMT-LIB),
  and
  `(mapset MAP INDEX VALUE)`,
  returning a new updated map with the element at `INDEX` set to the given `VALUE`
  (corresponding to an array write in SMT-LIB).

## Statements

* Assignments: `(assign VAR RHS)`, where `VAR` is a variable and `RHS` an expression;
* Assumptions: `(assume COND)`, where `COND` is an expression;
* Havoc: `(havoc VAR)`, where `VAR` is a variable;
* Label: `(label NAME)`, where `NAME` is a symbol;
* Non-deterministic jumps: `(jump TARGET_1 ... TARGET_N)`, where `TARGET_i` are labels;
* Sequential composition: `(seq STMT_1 ... STMT_N)`, where `STMT_i` are statements;
* Function calls: `(call FUNC ARG_1 ... ARG_N RET_1 ... RET_N)`,
where `FUNC` is an expression of function type,
`ARG_i` are expressions, and
`RET_i` are variables;
* Conditional jumps: `(condjump COND TARGET)`, where `COND` is an expression and `TARGET` is a label. This is equivalent to the following:
```
      (seq
        (jump (label then) (label else))
        (label then)
        (assume COND)
        (jump TARGET)
        (label else)
        (assume (not COND)))
```
  where `(label then)` and `(label else)` are fresh.

## Functions

```
    (function NAME (PARAM_1 ... PARAM_N) (return RET_1 ... RET_N)
       (locals VAR_1 ... VAR_N)
     BODY)
```

where:

* `NAME` is the function name (a symbol);
* `PARAM_i` are the formal parameter variables.
  The list can be empty;
* `RET_i` are the return variables. The list can be empty;
* `VAR_i` are the local variables. The list can be empty;
* `BODY` is a statement.

## Programs

A program is a list of function definitions, plus an optional list of global
variables, an entry point defining the main function, an optional initial
constraint, and an optional list of type definitions.
The syntax is the following:

```
    (type TYPENAME_1 TYPE_1)
    ...
    (type TYPENAME_N TYPE_N)

    (entry NAME)
    (init CONSTR)
    (globals VAR_1 ... VAR_N)

    FUNCTION_1
    ...
    FUNCTION_N
```

where:

* `TYPENAME_i` are symbls, and `TYPE_i` are types. This is similar to typedefs in
  C, and is used to avoid having to repeat often long types;
* `NAME` is the name of the main function (entry point);
* `CONSTR` is an expression over global variables;
* `VAR_i` are variable expressions for global variables.

## Annotations and Properties

Expressions, statements and function definitions can be annotated with metadata.
The syntax is the following:

```
  (! SEXP :KEY VALUE)
```

where:

* `SEXP` is an expression, statement or function declaration;
* `KEY` and `VALUE` are symbols.

Properties can be defined by annotating label statements as follows:

* `(! LABEL :error NAME)` states that `LABEL` is unreachable;
* `(! LABEL :notlive NAME)` states that `LABEL` is eventually unreachable;
* `(! LABEL :live NAME)` states that `LABEL` can be reached infinitely often in all infinite executions.

## Example

Here is a simple C program and its equivalent formulation in K2:

### C version
```
     var glbl;

     int f(int x)
     {
         if (glbl > 0) {
             return x - 1;
         } else {
             glbl = 0;
             return x;
         }
     }

     void main(void)
     {
         int y;
         y = f(23);
     }
```

### K2 version

```
     (type cint (sbv 32))
     (entry main)
     (globals (var glbl cint))

     (function f ((var x cint)) (return (var ret cint))
       (locals)
       (seq
         (jump (label then) (label else))
         (label then)
         (assume (op gt glbl (const 0 cint)))
         (assign ret (op sub x (const 1 cint)))
         (jump (label end))
         (label else)
         (assume (op not (op gt glbl (const 0 cint))))
         (assign glbl (const 0 cint))
         (assign ret x)
         (label end)))

     (function main () (return)
        (locals (var y cint))
        (call f (const 23 cint) y))
```