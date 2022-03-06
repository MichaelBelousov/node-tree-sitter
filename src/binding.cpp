#include <napi.h>
#include "./language.h"
#include "./parser.h"
#include "./query.h"
#include "./tree.h"

namespace node_tree_sitter_napi {

void Init(Napi::Env env, Napi::Object exports) {
  Language::Init(env, exports);
  Parser::Init(env, exports);
  Query::Init(env, exports);
  Tree::Init(exports);
}

NODE_API_MODULE(tree_sitter_runtime_binding_napi, Init)

}
