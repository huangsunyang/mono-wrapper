using System;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;

namespace Name {
namespace Script
{
    class Program
    {
        public static void HelloWorld(string str = "Hello World", string str2 = "h")
        {
            if (str == null)
            {
                Console.WriteLine("str is null");
            }
            NativeMethodUsingInternalCall();

            ManagedStruct s = new ManagedStruct();
            s.number = 123;
            s.float_number = 111.11;
            s.boolean = true;
            NativeMethodUsingPInvoke(s);
            Console.WriteLine(str2);
        }

        public static void Main()
        {
            HelloWorld(str2: "asdfasdf");
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void NativeMethodUsingInternalCall();


        [DllImport("main", EntryPoint = "NativeMethodUsingPInvoke")]
        static extern void NativeMethodUsingPInvoke(ManagedStruct s);

        public static string s = "";

        int property {
            get; set;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    class ManagedStruct {
        public IntPtr vtable;
        public int number;
        public double float_number;
        public bool boolean;
    };
}
}