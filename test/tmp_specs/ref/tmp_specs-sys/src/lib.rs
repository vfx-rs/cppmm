pub mod c_specs;
pub use c_specs::specs__Attribute_int__t as specs_IntAttribute_t;
pub use c_specs::specs__Attribute_float__t as specs_FloatAttribute_t;
pub use c_specs::specs__Specs_t as specs_Specs_t;

pub use c_specs::specs__Attribute_int__value as specs_IntAttribute_value;
pub use c_specs::specs__Attribute_float__value as specs_FloatAttribute_value;
pub use c_specs::specs__Specs_findAttribute_int as specs_Specs_findAttribute_int;
pub use c_specs::specs__Specs_findAttribute_float as specs_Specs_findAttribute_float;


#[cfg(test)]
mod test;
