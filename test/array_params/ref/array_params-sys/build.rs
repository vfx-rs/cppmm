
fn main() {
    let dst = cmake::Config::new("/home/anders/code/cppmm/build/test/array_params/output/array_params-sys/array_params-c").build();
    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=dylib=array_params-c-0_1");

    let out_dir = std::env::var("OUT_DIR").unwrap();
    let output = std::process::Command::new("python")
        .args(&["array_params-c/abigen/insert_abi.py", 
            "cppmm_abi_in", 
            &format!("{}/cppmm_abi_out", out_dir), 
            &format!("{}/build/abigen.txt", out_dir)])
        .output().expect("couldn't do the thing");

    if !output.status.success() {
        for line in std::str::from_utf8(&output.stderr).unwrap().lines() {
            println!("cargo:warning={}", line);
        }
        panic!("failed");
    }




    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-lib=dylib=stdc++");
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-lib=dylib=c++");
}
    