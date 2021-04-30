pub mod c_optr;
pub use c_optr::optr__PubCtor_t as optr_PubCtor_t;
pub use c_optr::optr__PrvCtor_t as optr_PrvCtor_t;
pub use c_optr::optr__AllPrv_t as optr_AllPrv_t;
pub use c_optr::optr__Opaque_t as optr_Opaque_t;

pub use c_optr::optr__PubCtor_ctor as optr_PubCtor_ctor;
pub use c_optr::optr__PubCtor_dtor as optr_PubCtor_dtor;
pub use c_optr::optr__PubCtor_doit as optr_PubCtor_doit;
pub use c_optr::optr__PrvCtor_doit as optr_PrvCtor_doit;


#[cfg(test)]
mod test;
