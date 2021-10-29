#pragma once

namespace foo {

class PublicBase {
public:
    // PublicBase(){}
    // PublicBase(const PublicBase&){};
    // PublicBase(PublicBase&&){};
};

class PrivateBase {
public:
    PrivateBase(){}

private:
    PrivateBase(const PrivateBase&){};
    PrivateBase(PrivateBase&&){};
};

class DeletedBase {
public:
    DeletedBase(){}

private:
    DeletedBase(const DeletedBase&)=delete;
    DeletedBase(DeletedBase&&)=delete;
};

class PublicDerived: public PublicBase {};
class PrivateDerived: public PrivateBase {};
class DeletedDerived: public DeletedBase {};

}
