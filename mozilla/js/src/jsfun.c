/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * Reserve three slots in all function objects. The first two are used by
 * XPConnect to remember information about what interface and member function a
 * particular cloned function represents.  The third slot is used by
 * js_CloneFunctionObject to remember a cloned function object's principal.
 * Cloned function objects are objects created when we need to dynamically bind
 * a function to a closure that is not its compile-time closure (e.g., a
 * function statement or brutal sharing).  See the uses of JS_GetReservedSlot in
 * xpcwrappednativeinfo.cpp and XPCDispObject.cpp
 *
 * Note that this does not bloat every instance, only those on which reserved
 * slots are set, and those on which ad-hoc properties are defined.