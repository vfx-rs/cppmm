
fn main() {
    let dst = cmake::Config::new("/home/anders/code/cppmm/build/test/function_pointers/output/function_pointers-sys/function_pointers-c").build();
    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=dylib=function_pointers-c-0_1");


    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-lib=dylib=stdc++");
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-lib=dylib=c++");
}
    