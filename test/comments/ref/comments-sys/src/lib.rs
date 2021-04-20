pub mod c_comments;
pub use c_comments::comments__Class_t as comments_Class_t;

pub use c_comments::comments__Class_method as comments_Class_method;
pub use c_comments::comments_function as comments_function;


#[cfg(test)]
mod test;
