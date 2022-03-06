#include <napi.h>
//#include "./language.h"
#include "./parser.h"
//#include "./query.h"
//#include "./tree.h"

namespace node_tree_sitter_napi {

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  Parser::Init(env, exports);
  //Query::Init(env, exports);
  //Tree::Init(exports);
  return exports;
}

NODE_API_MODULE(tree_sitter_runtime_binding_napi, Init)

}
