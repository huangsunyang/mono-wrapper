#include <string>

using std::string;

class MonoDomain;

#define MONO_LIB_DIR "C:\\Program Files\\Mono\\lib"
#define MONO_ETC_DIR "C:\\Program Files\\Mono\\etc"

namespace MonoWrapper {

class Domain {
public:
    Domain(const string& domain_name);

private:
    static bool s_monoDirectoryInitialized;

    MonoDomain * m_domain;
};

}