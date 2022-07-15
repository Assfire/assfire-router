load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "com_google_protobuf",
    commit = "22d0e265de7d2b3d2e9a00d071313502e7d4cccf", 
    shallow_since = "1643340956 -0800",
    remote = "https://github.com/protocolbuffers/protobuf",
)

git_repository(
    name = "rules_proto_grpc",
    commit = "c618f7f7c06e130b3daa4c776ce4ba2401b260a2", 
    shallow_since = "1640903766 +0000",
    remote = "https://github.com/rules-proto-grpc/rules_proto_grpc",
)

http_archive(
    name = "bazel_gazelle",
    sha256 = "501deb3d5695ab658e82f6f6f549ba681ea3ca2a5fb7911154b5aa45596183fa",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-gazelle/releases/download/v0.26.0/bazel-gazelle-v0.26.0.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.26.0/bazel-gazelle-v0.26.0.tar.gz",
    ],
)

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"],
  strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5",
)

git_repository(
    name = "assfire_common_concepts",
    commit = "fe7b3f554042feca0323df4c624bf1ef93cddc65", 
    shallow_since = "1657181835 +0300",
    remote = "https://gitlab.com/assfire/assfire-concepts.git",
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies")
gazelle_dependencies()



load("@rules_proto_grpc//:repositories.bzl", "rules_proto_grpc_toolchains", "rules_proto_grpc_repos")
rules_proto_grpc_toolchains()
rules_proto_grpc_repos()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

load("@rules_proto_grpc//:repositories.bzl", "bazel_gazelle", "io_bazel_rules_go")  # buildifier: disable=same-origin-load
io_bazel_rules_go()
bazel_gazelle()

load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")
go_rules_dependencies()
go_register_toolchains(
    version = "1.17.1",
)

load("@rules_proto_grpc//cpp:repositories.bzl", "cpp_repos")
cpp_repos()

load("@rules_proto_grpc//go:repositories.bzl", "go_repos")
go_repos()

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
