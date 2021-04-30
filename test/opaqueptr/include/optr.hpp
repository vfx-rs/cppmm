#pragma once

namespace optr {

struct PubCtor {
    PubCtor();
    ~PubCtor();

    void doit() {}
};

class PrvCtor {
    PrvCtor();
    ~PrvCtor();

public:
    void doit() {}
};

class AllPrv {
    AllPrv();
    ~AllPrv();

    void doit() {}
};

class Opaque;

} // namespace optr
