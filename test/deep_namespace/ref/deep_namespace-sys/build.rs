
fn main() {
    let dst = cmake::Config::new("/home/anders/code/cppmm/build/test/deep_namespace/output/deep_namespace-sys/deep_namespace-c").build();
    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=dylib=deep_namespace-c-0_1");


    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-lib=dylib=stdc++");
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-lib=dylib=c++");
}
    