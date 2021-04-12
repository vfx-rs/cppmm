
fn main() {
    let dst = cmake::Config::new("/home/anders/code/cppmm/test/usd/ref-c").build();
    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=dylib=/home/anders/code/cppmm/test/usd/ref-c");


    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-lib=dylib=stdc++");
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-lib=dylib=c++");
}
    