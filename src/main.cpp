#include <iostream>
#include <string>
#include <stdio.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

#include "utils.h"


char* PyNet_ExceptionToString(MonoObject *e) {
    MonoMethodDesc* mdesc = mono_method_desc_new(":ToString()", false);
    MonoMethod* mmethod = mono_method_desc_search_in_class(mdesc, mono_get_object_class());
    mono_method_desc_free(mdesc);

    mmethod = mono_object_get_virtual_method(e, mmethod);
    MonoString* monoString = (MonoString*) mono_runtime_invoke(mmethod, e, NULL, NULL);
    mono_runtime_invoke(mmethod, e, NULL, NULL);
    return mono_string_to_utf8(monoString);
}

struct NativeStruct {
    int number;
    double float_number;
    bool boolean;
    virtual void test() {}; // test vtable
};

extern "C" __declspec( dllexport ) void NativeMethodUsingPInvoke(NativeStruct *);

void NativeMethodUsingPInvoke(NativeStruct * s)
{
    Region region("Native method using PInvoke");
    std::cout << s->number << ' ' << s->float_number << ' ' << s->boolean << std::endl;
}

void NativeMethodUsingInternalCall()
{
    std::cout << "In Native Method using Internl Call" << std::endl;
}


int _main ()
{
    std::cout << getCurrentDir() << std::endl;

    // create domain
    MonoDomain * my_domain = mono_jit_init("my-domain");
    ASSERT_NOT_NULL(my_domain);

    // {
        // Region region("run csharp main");

        // try load assembly exe
        // MonoAssembly * script_exe = mono_domain_assembly_open(my_domain, "script.exe");
        // ASSERT_NOT_NULL(script_exe);

        {
            Region region("register internal call");
            mono_add_internal_call("Name.Script.Program::NativeMethodUsingInternalCall", NativeMethodUsingInternalCall);
        }

        // exec main func of assembly
        // don't think it's useful
        // char* argv[1] = {"script.exe"};
        // int retval = mono_jit_exec(my_domain, script_exe, 1, argv);
    // }

    {
        Region region("iterate methods");

        // try load assembly dll
        MonoAssembly * script_dll = mono_domain_assembly_open(my_domain, "script.dll");
        ASSERT_NOT_NULL(script_dll);

        // try get mono image
        MonoImage * script_image = mono_assembly_get_image(script_dll);
        ASSERT_NOT_NULL(script_image);

        // try get mono class
        MonoClass * program_class = mono_class_from_name(script_image, "Name.Script", "Program");
        ASSERT_NOT_NULL(program_class);

        // try get mono methods
        MonoMethod * method = nullptr;
        void * iter = nullptr;
        while (method = mono_class_get_methods(program_class, &iter)) {
            std::string name = mono_method_get_name(method);
            MonoObject * exc = nullptr;
            if (name == "HelloWorld") {
                Region region("Invoke HelloWorld");
                void *params[] = {nullptr, mono_string_new(my_domain, "hello")};
                mono_runtime_invoke(method, nullptr, params, &exc);
                CHECK_EXC(exc);
            } else if (name == "NativeMethod") {
                Region region("Invoke NativeMethod");
                mono_runtime_invoke(method, nullptr, nullptr, &exc);
                CHECK_EXC(exc);
            }
            std::cout << name << std::endl;
        }
    }

    return 0;
}