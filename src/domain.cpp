#include "domain.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

using std::string;

namespace MonoWrapper {

bool Domain::s_monoDirectoryInitialized = false;

Domain::Domain(const string& name) {
    // static initialize
    if (!s_monoDirectoryInitialized) {
        ::mono_set_dirs(MONO_LIB_DIR, MONO_ETC_DIR);
        s_monoDirectoryInitialized = true;
    }

    m_domain = mono_jit_init(name.c_str());
}

}

