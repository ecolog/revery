#include <caml/callback.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <caml/threads.h>
#include <caml/alloc.h>

#include "caml_values.h"
#include "utilities.h"

/* Sourced from Brisk's `BriskCocoa`
    Thank you @wokalski!
*/
void revery_caml_call_n(camlValue f, int argCount, camlValue *args) {
    caml_c_thread_register();
    caml_acquire_runtime_system();
    caml_callbackN(f, argCount, args);
    caml_release_runtime_system();
}

void revery_caml_call(camlValue f) {
    value args[] = {Val_unit};
    revery_caml_call_n(f, 1, args);
}

/* Create an OCaml value encapsulating the pointer p */
value revery_wrapPointer(void *p) {
    value v = caml_alloc(1, Abstract_tag);
    *((void **) Data_abstract_val(v)) = p;
    return v;
}

/* Extract the pointer encapsulated in the given OCaml value */
void *revery_unwrapPointer(value v) {
    return *((void **) Data_abstract_val(v));
}

/* Create an OCaml value encapsulating the pointer p
    None when p == NULL, Some(p) when p != NULL
*/
value revery_wrapOptionalPointer(void *p) {
    if (p != NULL) {
        value v = revery_wrapPointer(p);
        return Val_some(v);
    } else {
        return Val_none;
    }
}
